
import argparse
from IDW import IDW_build, IDW_calc
from Kriging_IDW import Kriging_IDW_build, Kriging_IDW_calc
from RSM import RSM_build, RSM_calc
from Kriging_RSM import Kriging_RSM_build, Kriging_RSM_calc
from Kriging_Ordinary import Kriging_Ordinary_build, Kriging_Ordinary_calc

def error_build_method(x):
	print('Build method provided " ' + x + ' " was not recognized')

def error_calc_method(x):
	print('Calculation method provided " ' + x + ' " was not recognized')

def build_method(x):
    return {
        'IDW': IDW_build,
        'Kriging_IDW': Kriging_IDW_build,
        'RSM' : RSM_build,
        'Kriging_RSM' : Kriging_RSM_build,
        'Kriging_Ordinary' : Kriging_Ordinary_build
    }.get(x, error_build_method)


def calc_method(x):
	return {
        'IDW': IDW_calc,
        'Kriging_IDW': Kriging_IDW_calc,
        'RSM' : RSM_calc,
        'Kriging_RSM' : Kriging_RSM_calc,
        'Kriging_Ordinary' : Kriging_Ordinary_calc
    }.get(x, error_calc_method)

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("method")
    parser.add_argument("mode")
    parser.add_argument("working_directory")
    args = parser.parse_args()
    # print(args.mode)
    # print(args.working_directory)

    if (args.mode == 'build'):
    	build_method(args.method)(args.working_directory)
    elif (args.mode == 'calc'):
        calc_method(args.method)(args.working_directory)
    else:
        print('the first args must be "build" or "calc"')


if __name__ == '__main__':
    main()