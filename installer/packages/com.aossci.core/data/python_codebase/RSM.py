# 近似模型
# 响应面法

# by twocui
# 20170510
# v 0.5

import numpy as np
import scipy.optimize as opt
import json
import argparse


##############################################################################
# ################################响应面模型##################################
##############################################################################

def RSM_build(filepath, input={}):

    # 读取json文件
    if input == {}:
        input = json.loads(
            open(filepath + '/surrogate_model_input.json').read())
    x_sample = np.array(input['x_samples'])
    y_sample = np.array(input['y_samples'])
    configure = input['configurations']

    # 11111定义多项式模型
    if configure['Polynomial_Order'] == 'Linear':
        # 一阶响应面模型
        def rsmfunc(x):
            y = x[0]
            for i in range(len(x_sample)):
                y += x[i + 1] * x_sample[i]
            f = y - yi
            return f
        # 系数初值
        x0 = []
        len_a = 1 + len(x_sample)
        for i in range(len_a):
            x0 += [0]

    elif configure['Polynomial_Order'] == 'Quadratic':
        # 二阶响应面模型
        def rsmfunc(x):
            y = x[0]
            for i in range(len(x_sample)):
                y += x[i + 1] * x_sample[i]
            for i in range(len(x_sample)):
                for j in range(len(x_sample)):
                    if j >= i:
                        y += x[i + len(x_sample)] * \
                            x_sample[i] * x_sample[j]
            f = y - yi
            return f
        # 系数初值
        x0 = []
        len_a = 1 + len(x_sample) * (len(x_sample) + 3) // 2
        for i in range(len_a):
            x0 += [0]

    # 22222曲线拟合
    fit_coefficient = []
    Accuracy = []
    for i in range(len(y_sample)):
        yi = y_sample[i]
        # 最小二乘法
        Result_Opt = opt.least_squares(fun=rsmfunc,
                                       x0=x0)
        fit_coefficient += [Result_Opt.x.tolist()]
        Accuracy += [1 - 2 * Result_Opt.cost / sum(np.square(yi))]

    # 33333输出中间文件
    interput = {}
    intermediate_data = {}
    intermediate_data['fit_coefficient'] = fit_coefficient
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

    return fit_coefficient, Accuracy


def RSM_calc(filepath, input={}):

    # 读取json文件
    if input == {}:
        input = json.loads(
            open(filepath + '/surrogate_model_input.json').read())
    x = np.array(input['x_inputs'])
    x = x.reshape([len(x), 1])
    configure = input['configurations']
    interput = json.loads(
        open(filepath + '/surrogate_model_intermediate.json').read())
    fit_coefficient = np.array(
        interput['intermediate_data']['fit_coefficient'])

    y = []
    if configure['Polynomial_Order'] == 'Linear':
        # 一阶响应面模型
        for ii in range(len(fit_coefficient)):
            yi = fit_coefficient[ii][0]
            for i in range(len(x)):
                yi += fit_coefficient[ii][i + 1] * x[i]
            y += yi.tolist()

    elif configure['Polynomial_Order'] == 'Quadratic':
        # 二阶响应面模型
        for ii in range(len(fit_coefficient)):
            yi = fit_coefficient[ii][0]
            for i in range(len(x)):
                yi += fit_coefficient[ii][i + 1] * x[i]
            for i in range(len(x)):
                for j in range(len(x)):
                    if j >= i:
                        yi += fit_coefficient[ii][i + len(x)] * x[i] * x[j]
            y += yi.tolist()

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


# # ----------------------------------------------------------------------
# # 测试
# # RSR计算测试
# filepath = 'D:/GitHub/Approximate_Model'
# fit_coefficient, Accuracy = RSM_build(filepath)
# print(fit_coefficient)
# print('Accuracy:----------------------------------------------')
# print(Accuracy)
# y = RSM_calc(filepath)
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
        RSM_build(args.working_directory)
    elif (args.mode == 'calc'):
        RSM_calc(args.working_directory)
    else:
        print('the first args must be "build" or "calc"')


if __name__ == '__main__':
    main()
