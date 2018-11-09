import time
import os
import sys

input_file_list = os.listdir("./test_file/input")
output_file_list = os.listdir("./test_file/output")
dump_file_list = os.listdir("./test_file/output")

test_root = './test_file'
matrix = []


'''
ADD_HOUSE_FLAG(0, START);
ADD_HOUSE_FLAG(14, HOSPITAL);
ADD_HOUSE_FLAG(28, TOOL);
ADD_HOUSE_FLAG(35, GIFT);
ADD_HOUSE_FLAG(49, PRISON);
ADD_HOUSE_FLAG(63, MAGIC);
'''


def make_iteration():
    file_name = ""
    for x in range(0, 1000):
        if 'input_' + str(x) not in input_file_list:
            file_name = 'input_' + str(x)
            break
    file_path = os.path.join(test_root, 'input', file_name)
    with open(file_path, 'w') as f:
        matrix.append("t")

        print("请选择玩家id(AQSJ)")
        aid = sys.stdin.readline().strip()
        matrix.append('preset user {}'.format(aid))
        print('添加指令preset user {}'.format(aid))

        while True:
            print("设置地图块归属，房屋级别(3 A 2),输入回车结束")
            temp = sys.stdin.readline().strip()
            if temp == '':
                break
            else:
                temp2 = temp.split(' ')
                matrix.append('preset map {} {} {}'.format(temp2[0], temp2[1], temp2[2]))
                print('添加指令preset map {} {} {}'.format(temp2[0], temp2[1], temp2[2]))

        for x in aid:
            print("请选择玩家{}的金钱，输入回车为10000".format(x))
            temp = sys.stdin.readline().strip()
            if temp == '':
                matrix.append('preset fund {} 10000'.format(x))
                print('添加指令preset fund {} 10000'.format(x))
            else:
                if int(temp) != 0:
                    matrix.append('preset fund {} {}'.format(x, temp))
                    print('添加指令preset fund {} {}'.format(x, temp))

        for x in aid:
            print("请选择玩家{}的点数，输入回车为0".format(x))
            temp = sys.stdin.readline().strip()
            if temp == '':
                continue
            else:
                if int(temp) != 0:
                    matrix.append('preset credit {} {}'.format(x, temp))
                    print('添加指令preset credit {} {}'.format(x, temp))

        for x in aid:
            print("请选择玩家{}的障碍数量，输入回车为0".format(x))
            temp = sys.stdin.readline().strip()
            if temp == '':
                pass
            else:
                if int(temp) != 0:
                    matrix.append('preset gift {} barrier {}'.format(x, temp))
                    print('添加指令preset gift {} barrier {}'.format(x, temp))

            print("请选择玩家{}的机器娃娃数量，输入回车为0".format(x))
            temp = sys.stdin.readline().strip()
            if temp == '':
                pass
            else:
                if int(temp) != 0:
                    matrix.append('preset gift {} robot {}'.format(x, temp))
                    print('添加指令preset gift {} robot {}'.format(x, temp))

            print("请选择玩家{}的剩余财神轮数，输入回车为0".format(x))
            temp = sys.stdin.readline().strip()
            if temp == '':
                pass
            else:
                if int(temp) != 0:
                    matrix.append('preset gift {} god {}'.format(x, temp))
                    print('添加指令preset gift {} god {}'.format(x, temp))

        while True:
            print("请输入放置障碍的位置，输入回车结束")
            temp = sys.stdin.readline().strip()
            if temp == '':
                break
            else:
                matrix.append('preset barrier {}'.format(temp))
                print('添加指令preset barrier {}'.format(temp))

        for x in aid:
            print("请选择玩家{}停留的位置，轮次(20, 0)".format(x))
            temp = sys.stdin.readline().strip()
            matrix.append('preset userloc {} {}'.format(x, temp))
            print('添加指令preset userloc {} {}'.format(x, temp))

        print("请选择下一个行动的玩家")
        temp = sys.stdin.readline().strip()
        matrix.append('preset nextuser {}'.format(temp))
        print('添加指令preset nextuser {}'.format(temp))

        matrix.append("e")

        while True:
            print("请输入接下来的操作,输入回车结束")
            temp = sys.stdin.readline().strip()
            matrix.append(temp)
            print("添加指令{}".format(temp))
            if temp == '':
                break

        matrix.append("quit")
        matrix.append("\n")

        print("注意添加output_" + file_name[-1] + "!")

        f.write('\n'.join(matrix))


def test():
    incorrect = 0
    correct = 0
    incorrect_list = []
    for file in input_file_list:
        if file[0] != '.':
            print(file)
            input_file_index = file.split('_')[1]
            os.system('cd ./zillionaire;./zillion < ../test_file/input/{}'.format(file))
            os.system('mv -f ./test_file/temp/output ./test_file/dump/dump_{}'.format(input_file_index))
            dump_file = './test_file/dump/dump_{}'.format(input_file_index)
            output_file = './test_file/output/output_{}'.format(input_file_index)
            with open(dump_file, 'r') as d:
                rd = d.read().split('\n')
                if '\n' in rd:
                    rd.remove('\n')
                sd = set(rd)
            with open(output_file, 'r') as o:
                ro = o.read().split('\n')
                if '\n' in ro:
                    ro.remove('\n')
                so = set(ro)
            if sd == so:
                correct += 1
            else:
                incorrect += 1
                incorrect_list.append('dump_' + input_file_index)
    print("\n正确:{} | 错误:{}".format(str(correct), str(incorrect)))
    if incorrect > 0:
        print("\n错误用例名称：")
        for x in incorrect_list:
            print("\n" + x)



if __name__ == '__main__':
    print("请输入操作类型，1为测试，2为生成测试数据")
    while True:
        temp = sys.stdin.readline().strip()
        if temp == '1':
            test()
            break
        elif temp == '2':
            make_iteration()
            break
        else:
            break
