from pymouse import PyMouse
from pykeyboard import PyKeyboard
import time
import os
import sys

input_file_list = os.listdir("./test_file/input")
test_root = './test_file'
matrix = []
index = 0

roll = "roll"
query = "query"
help = "help"
quit = "quit"
sell = "sell"
step = "step"
buy = "buyhouse"
restart = "restart"

player_num = ['2', '3', '4']
player_name = \
    {
        'Q钱夫人': '1',
        'A阿土伯': '2',
        'J金贝贝': '3',
        'S孙小美': '4'
    }
not_common_place = \
    {
        'START': '0',
        'HOSPITAL': '14',
        'TOOL': '28',
        'GIFT': '35',
        'PRISON': '49',
        'MAGIC': '63'
    }


'''
ADD_HOUSE_FLAG(0, START);
ADD_HOUSE_FLAG(14, HOSPITAL);
ADD_HOUSE_FLAG(28, TOOL);
ADD_HOUSE_FLAG(35, GIFT);
ADD_HOUSE_FLAG(49, PRISON);
ADD_HOUSE_FLAG(63, MAGIC);
'''

m = PyMouse()
k = PyKeyboard()


def pause():
    time.sleep(0.05)


def input_string(string):
    k.type_string(string)
    k.tap_key('return')
    pause()


def press_n():
    k.tap_key('n')
    k.tap_key('return')
    pause()


def press_1():
    k.tap_key('1')
    k.tap_key('return')
    pause()


def press_2():
    k.tap_key('2')
    k.tap_key('return')
    pause()


def make_iteration(name='input_30'):
    file_path = os.path.join(test_root, name)
    with open(file_path, 'w') as f:
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
            print("请选择玩家{}的金钱，输入回车为1000".format(x))
            temp = sys.stdin.readline().strip()
            if temp == '':
                matrix.append('preset fund {} 1000'.format(x))
                print('添加指令preset fund {} 1000'.format(x))
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
            print("请选择玩家{}的炸弹数量，输入回车为0".format(x))
            temp = sys.stdin.readline().strip()
            if temp == '':
                pass
            else:
                if int(temp) != 0:
                    matrix.append('preset gift {} bomb {}'.format(x, temp))
                    print('添加指令preset gift {} bomb {}'.format(x, temp))

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
            print("请输入放置炸弹的位置，输入回车结束")
            temp = sys.stdin.readline().strip()
            if temp == '':
                break
            else:
                matrix.append('preset bomb {}'.format(temp))
                print('添加指令preset bomb {}'.format(temp))

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

        while True:
            print("请输入接下来的操作,输入回车结束")
            temp = sys.stdin.readline().strip()
            matrix.append(temp)
            print("添加指令{}".format(temp))
            if temp == '':
                break

        f.write('\n'.join(matrix))


def test():
    incorrect = 0
    correct = 0
    incorrect_list = []
    for file in input_file_list:
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


# def test_print():
#     # get size of screen
#     x_dim, y_dim = m.screen_size()
#     print(x_dim, y_dim)
#     m.click(x_dim / 6, y_dim / 6, 1)
#
#     # enter programme
#     input_string('./zillionaire')
#
#     # chose if read_data
#     press_n()
#
#     # chose num of players
#     press_2()
#
#     # chose index of players1
#     press_1()
#
#     # chose index of players2
#     press_2()
#
#     # a -> step 20
#     input_string('quit')


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
