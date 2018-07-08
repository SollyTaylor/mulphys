# 近似模型
# Kriging法,基于反距离加权插值法

# by twocui
# 20170510
# v 0.2

import numpy as np
import scipy.optimize as opt
import json
import argparse
from IDW import*


##############################################################################
# ################################克里金模型##################################
##############################################################################
# 普通克里金插值（基于反距离加权法）
def Kriging_IDW_build(filepath):

    # 读取json文件
    input = json.loads(open(filepath + '/surrogate_model_input.json').read())
    x_sample = np.array(input['x_samples'])
    y_sample = np.array(input['y_samples'])
    configure = input['configurations']

    # 由样本点中挑选n个子样本点,基于移除子样本之后的样本点进行插值并计算误差
    # 选取子样本点
    n_sub = len(x_sample[0]) // 10 + 1
    i_sub = np.random.choice([i for i in range(1, len(x_sample[0]) - 1)],
                             n_sub,
                             replace=False)
    x_sub = x_sample[:, i_sub]
    y_sub = y_sample[:, i_sub]
    # 在原始样本点中删除子样本点
    x_sample_pro = np.delete(x_sample, np.s_[i_sub], 1)
    y_sample_pro = np.delete(y_sample, np.s_[i_sub], 1)

    # 计算各个子样本点的输出以及误差
    residuali = np.zeros([len(y_sub)])
    for i in range(n_sub):
        # 提取子样本点
        x = x_sub[:, [i]]
        y = y_sub[:, i]  # 注意i没有括号
        y = np.where(np.abs(y) < 1e-10, 1e-10, y)  # 修正样本点中的零项

        # 输出删除子样本点的中间临时json文件
        tempdata = {}
        tempdata['x_samples'] = x_sample_pro.tolist()
        tempdata['y_samples'] = y_sample_pro.tolist()
        tempdata['x_inputs'] = x.reshape([len(x), ]).tolist()
        tempdata['configurations'] = configure

        # 计算
        y_idw = IDW_calc(filepath, tempdata)
        temp_residual = np.abs(y - y_idw) / np.abs(y)
        temp_residual = np.where(temp_residual > 0.5, 0, temp_residual)
        residuali += temp_residual
        # residuali += np.abs(y - y_idw) / y

    # 计算精度
    Accuracy = 1 - residuali / n_sub

    # 输出中间文件
    interput = {}
    interput['Accuracies'] = Accuracy.tolist()
    f = open(filepath + '/surrogate_model_intermediate.json', 'w')
    f.write(json.dumps(interput,
                       sort_keys=False,
                       indent=4,
                       separators=(',', ' : ')
                       )
            )
    f.close()

    return Accuracy


def Kriging_IDW_calc(filepath, input={}):

    # 读取json文件
    if input == {}:
        input = json.loads(
            open(filepath + '/surrogate_model_input.json').read())
    x = np.array(input['x_inputs'])
    x = x.reshape([len(x), 1])
    x_sample = np.array(input['x_samples'])
    y_sample = np.array(input['y_samples'])
    configure = input['configurations']

    n_s = np.shape(x_sample)[1]  # 样本点数量
    n_y = np.shape(y_sample)[0]  # 输出变量数量

    # 再次计算任意两点的距离
    d = []
    for i in range(n_s):
        di = []
        for j in range(n_s):
            di += [np.sqrt(
                sum(np.square(x_sample[:, i] - x_sample[:, j])))]
        d += [di]
    d = np.array(d)
    dr = d.reshape([1, n_s * n_s])

    # 计算不同的输出变量对应的半方差
    rr = np.zeros([n_y, n_s * n_s])
    for ii in range(n_y):

        # 计算样本数据半方差
        r = []
        yi = y_sample[ii]
        for i in range(n_s):
            ri = []
            for j in range(n_s):
                ri += [np.square(yi[i] - yi[j]) / 2]
            r += [ri]
        r = np.array(r)
        rr[ii, :] = r.reshape([1, n_s * n_s])

    # 计算插值点与样本点之间的距离
    di0 = []
    for i in range(n_s):
        di0 += [np.sqrt(sum(np.square(x[:, 0] - x_sample[:, i])))]
    # print(len(di0))

    # 分别计算插值点不同输出变量与样本点之间的半方差（基于IDW算法）
    ri0 = []
    for i in range(n_s):
        # 调用IDW算法
        tempdata = {}
        tempdata['x_inputs'] = [di0[i]]
        tempdata['x_samples'] = dr.tolist()
        tempdata['y_samples'] = rr.tolist()
        tempdata['configurations'] = configure
        ri0 += [np.array(IDW_calc(filepath, tempdata))]
    ri0 = np.array(ri0)
    # print(ri0)

    # 分别针对每个输出变量求解lambdar，并进一步求解
    y = []
    for i in range(n_y):
        ri = ri0[:, i]

        # 通过优化算法求解lambdar权重
        ri = ri.reshape([len(ri), 1])

        # 目标函数
        def optfunc(x):
            x = np.array(x).reshape([len(x), 1])
            y = np.linalg.norm((np.dot(r, x) - ri), 2)
            return y
        # 约束
        cons = {'type': 'eq',
                'fun': lambda x: sum(x) - 1
                }

        # 初值
        x_ini = []
        for j in range(n_s):
            x_ini += [1.0 / n_s]

        # 梯度优化
        Result_Opt = opt.minimize(optfunc,
                                  x_ini,
                                  method='SLSQP',
                                  constraints=cons)
        # 全局优化
        # mink = {"method": "SLSQP",
        #                   "constraints": cons}
        # Result_Opt = opt.basinhopping(func=optfunc,
        #                               x0=x_ini,
        #                               niter=100,
        #                               disp=True,
        #                               minimizer_kwargs=mink)
        lambdar = Result_Opt.x
        lambdar = np.transpose(lambdar)

        # 5555求解估计值
        y += [sum((y_sample[ii] * lambdar))]

    output = {}
    output['Results'] = []
    for i in range(len(y)):
        output['Results'] += [y[i]]

    f = open(filepath + '/surrogate_model_output.json', 'w')

    f.write(json.dumps(output,
                       sort_keys=False,
                       indent=4,
                       separators=(',', ' : ')
                       )
            )
    f.close()

    return y


# # 测试
# filepath = 'D:/GitHub/Approximate_Model'

# Accuracy = Kringing_IDW_build(filepath)
# print('Accuracy:----------------------------------------------')
# print(Accuracy)

# y = Kringing_IDW_calc(filepath)
# print('Result:------------------------------------------------')
# print(y)


# 读取批处理参数
def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("mode")
    parser.add_argument("working_directory")
    args = parser.parse_args()
    # print(args.mode)
    # print(args.working_directory)

    if (args.mode == 'build'):
        Kriging_IDW_build(args.working_directory)
    elif (args.mode == 'calc'):
        Kriging_IDW_calc(args.working_directory)
    else:
        print('the first args must be "build" or "calc"')


if __name__ == '__main__':
    main()
