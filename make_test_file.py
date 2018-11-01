import os

test_root = './test_file'
matrix = []

roll = "roll"
query = "query"
help = "help"
quit = "quit"
sell = "sell"
step = "step"
buy = "buyhouse"
restart = "restart"

player_num = ['2', '3', '4']
player_name = ['1', '2', '3', '4']
not_common_place = ['14', '28', '35', '49', '63']


'''
ADD_HOUSE_FLAG(0, START);
ADD_HOUSE_FLAG(14, HOSPITAL);
ADD_HOUSE_FLAG(28, TOOL);
ADD_HOUSE_FLAG(35, GIFT);
ADD_HOUSE_FLAG(49, PRISON);
ADD_HOUSE_FLAG(63, MAGIC);
'''


def make_iteration1(name='iteration1'):
    file_path = os.path.join(test_root, name)
    with open(file_path, 'w') as f:
        for x in range(len(not_common_place)):
            matrix.append(player_num[0])
            matrix.append(player_name[0])
            matrix.append(player_name[1])
            matrix.append(buy)
            matrix.append(step)
            matrix.append(not_common_place[x])
            matrix.append(restart)
        f.write('\n'.join(matrix))



if __name__ == '__main__':
    make_iteration1()
