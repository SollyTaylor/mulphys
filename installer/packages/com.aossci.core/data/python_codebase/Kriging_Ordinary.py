# 近似模型
# 克里金法，基于响应面方法

# by twocui
# 20170510
# v 0.2

import numpy as np
import scipy.optimize as opt
import json
import argparse


##############################################################################
# ################################克里金模型##################################
##############################################################################
# 普通克里金插值
def Kriging_Ordinary_build(filepath):  # 建立距离与半方差之间的拟合关系

    # 读取json文件
    input = json.loads(open(filepath + '/surrogate_model_input.json').read())
    x_sample = np.array(input['x_samples'])
    y_sample = np.array(input['y_samples'])
    configure = input['configurations']

    n_s = np.shape(x_sample)[1]  # 样本点数量
    n_y = np.shape(y_sample)[0]  # 输出变量数量

    # 计算任意两点的距离
    d = []
    for i in range(n_s):
        for j in range(n_s):
            d += [np.sqrt(
                sum(np.square(x_sample[:, i] - x_sample[:, j])))]
    d = np.array(d)
    # 计算不同的输出变量对应的半方差
    r = []
    for ii in range(n_y):
        # 计算样本数据半方差
        ri = []
        yi = y_sample[ii]
        for i in range(n_s):
            for j in range(n_s):
                ri += [np.square(yi[i] - yi[j]) / 2]
        r += [ri]

    # 相关函数模型
    if configure['Correlation_Function'] == 'Spherical':
        # 球型模型
        def correfunc(x):
            c0 = x[0]
            c = x[1]
            a = x[2]

            gamma = c0 + c * (1.5 * d / a - d**3 / 2 / a**3)
            gamma = np.where(d == 0, 0, gamma)
            gamma = np.where(d > a, c0 + c, gamma)

            f = gamma - ri
            return f
        # 初值和约束
        x0 = np.array([0, 0, 1])
        bnds = ([-np.inf, -np.inf, 0], [np.inf, np.inf, np.max(d)])

    # 22222曲线拟合
    corrcoef = []
    Accuracy = []
    for i in range(len(y_sample)):
        ri = np.array(r[i])
        # 最小二乘法
        Result_Opt = opt.least_squares(fun=correfunc,
                                       x0=x0,
                                       bounds=bnds)
        corrcoef += [Result_Opt.x.tolist()]
        Accuracy += [1 - Result_Opt.cost / sum(np.square(ri))]

    # 33333输出中间文件
    interput = {}
    intermediate_data = {}
    intermediate_data['corrcoef'] = corrcoef
    interput['Accuracies'] = Accuracy
    interput['intermediate_data'] = intermediate_data

    f = open(filepath + '/surrogate_model_intermediate.json', 'w')
    f.write(json.dumps(interput,
                       sort_keys=False,
                       indent=4,
                       separators=(',', ' : ')
                       )
            )
    f.close()
    return corrcoef, Accuracy


def Kriging_Ordinary_calc(filepath):

    # 读取json文件
    input = json.loads(open(filepath + '/surrogate_model_input.json').read())
    x = np.array(input['x_inputs'])
    x = x.reshape([len(x), 1])
    x_sample = np.array(input['x_samples'])
    y_sample = np.array(input['y_samples'])
    configure = input['configurations']
    interput = json.loads(
        open(filepath + '/surrogate_model_intermediate.json').read())
    corrcoef = np.array(interput['intermediate_data']['corrcoef'])

    n_s = np.shape(x_sample)[1]  # 样本点数量
    n_y = np.shape(corrcoef)[0]  # 输出变量数量

    # 再次计算不同的输出变量对应的半方差
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
    di0 = np.array(di0)
    # print(len(di0))

    # 分别计算插值点不同输出变量与样本点之间的半方差（基于拟合函数）
    ri0 = []
    if configure['Correlation_Function'] == 'Spherical':
        # 球型模型
        for i in range(n_y):
            c0 = corrcoef[i][0]
            c = corrcoef[i][1]
            a = corrcoef[i][2]

            gamma = c0 + c * (1.5 * di0 / a - di0**3 / 2 / a**3)
            gamma = np.where(di0 == 0, 0, gamma)
            gamma = np.where(di0 > a, c0 + c, gamma)

            ri0 += [gamma]

    # 分别针对每个输出变量求解lambdar，并进一步求解
    y = []
    for i in range(n_y):
        ri = ri0[i]

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
        x0 = []
        for j in range(n_s):
            x0 += [1.0 / n_s]

        # 梯度优化
        Result_Opt = opt.minimize(optfunc,
                                  x0=x0,
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

        # print(lambdar)
        # print(sum(lambdar))

        # 44444求解估计值
        y += [sum(y_sample[i] * lambdar)]

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
# corrcoef, Accuracy = Kringing_Ordinary_build(filepath)
# print('Accuracy:----------------------------------------------')
# print(Accuracy)
# print('corrcoef:-----------------------------------------------------')
# print(corrcoef)
# y = Kringing_Ordinary_calc(filepath)
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
        Kriging_Ordinary_build(args.working_directory)
    elif (args.mode == 'calc'):
        Kriging_Ordinary_calc(args.working_directory)
    else:
        print('the first args must be "build" or "calc"')


if __name__ == '__main__':
    main()
