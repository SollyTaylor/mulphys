# 近似模型
# 反距离加权插值算法

# by twocui
# 20170510
# v 0.3

import numpy as np
import json
import argparse


# 建立近似模型
def IDW_build(filepath):

    # 读取json文件
    input = json.loads(open(filepath + '/surrogate_model_input.json').read())
    x_sample = np.array(input['x_samples'])
    y_sample = np.array(input['y_samples'])
    configure = input['configurations']

    # 由样本点中挑选n个子样本点,基于移除子样本之后的样本点进行插值并计算误差
    # 选取子样本点
    n_sub = len(x_sample[0]) // 10 + 1
    i_sub = []
    i_temp = 1
    for i in range(n_sub):
        i_sub += [i_temp]
        i_temp += len(x_sample[0]) // n_sub

    # i_sub = np.random.choice([i for i in range(1, len(x_sample[0]) - 1)],
    #                          n_sub,
    #                          replace=False)
    x_sub = x_sample[:, i_sub]
    y_sub = y_sample[:, i_sub]
    # 在原始样本点中删除子样本点
    x_sample_pro = np.delete(x_sample, np.s_[i_sub], 1)
    y_sample_pro = np.delete(y_sample, np.s_[i_sub], 1)

    # 基于IDW计算各个子样本点的输出以及误差
    residuali = np.zeros([len(y_sub)])
    for i in range(n_sub):
        # 提取子样本点
        x = x_sub[:, [i]]
        y = y_sub[:, i]  # 注意i没有括号
        y = np.where(np.abs(y) < 1e-10, 1e-10, y)  # 修正样本点中的零项

        # 删除子样本点的临时数据
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


# 应用近似模型
def IDW_calc(filepath, input={}):

    # 读取json文件
    if input == {}:
        input = json.loads(
            open(filepath + '/surrogate_model_input.json').read())
    x = np.array(input['x_inputs'])
    x = x.reshape([len(x), 1])
    x_sample = np.array(input['x_samples'])
    y_sample = np.array(input['y_samples'])
    configure = input['configurations']

    xd = np.square(x_sample - x)
    di = []
    for i in range(np.shape(xd)[1]):
        di += [np.sqrt(sum(xd[:, i]))]
    di = np.power(np.array(di), configure['Weight_Distance_Coefficient'])
    # 修正将距离过近导致的除零现象
    di = np.where(di < 1e-10, 1e-10, di)
    # print(di)

    fd = sum(1 / di)
    fu = [sum(y_sample[i] / di) for i in range(len(y_sample))]

    y = fu / fd

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


# # ---------------------------------------------------------------------
# # 测试
# # IDW计算测试
# filepath = 'D:/GitHub/Approximate_Model'
# Accuracy = IDW_build(filepath)
# print('Accuracy:----------------------------------------------')
# print(Accuracy)
# y = IDW_calc(filepath)
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
        IDW_build(args.working_directory)
    elif (args.mode == 'calc'):
        IDW_calc(args.working_directory)
    else:
        print('the first args must be "build" or "calc"')


if __name__ == '__main__':
    main()
