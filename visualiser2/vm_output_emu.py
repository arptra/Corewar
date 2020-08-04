#!/usr/bin/env python3

import random

# this script emulates output of corewar vm to stdout
# used to test corewar_visual in abscence of corewar vm

sep = '"'  # separator sign


def add_player(cycle, player_id, player_name, address, bytes):
    print(
        f'p{sep}{cycle}{sep}{player_id}{sep}{player_name}{sep}{address}{sep}{bytes}'
    )


def add_cursor(cycle, player_id, cursor_id, address):
    print(
        f'c{sep}{cycle}{sep}{player_id}{sep}{cursor_id}{sep}{address}'
    )


def kill_cursor(cycle, player_id, cursor_id):
    print(
        f'k{sep}{cycle}{sep}{player_id}{sep}{cursor_id}'
    )


def move_cursor(cycle, player_id, cursor_id, offset):
    print(
        f'm{sep}{cycle}{sep}{player_id}{sep}{cursor_id}{sep}{offset}'
    )


def write_memory(cycle, player_id, address, bytes):
    """ st & sti instruction"""
    print(
        f'w{sep}{cycle}{sep}{player_id}{sep}{address}{sep}{bytes}'
    )


def declare_winner(cycle, player_id):
    print(
        f'e{sep}{cycle}{sep}{player_id}'
    )


# start emulating output of corewar vm to stdout
add_player(1, 1, 'Some really long name',
           0, "00002901DA04446963742901DA"
           )
add_player(1, 2, 'Robin', 64*10, "df01bb09")
add_player(1, 3, 'Yoshi', 64*20, "47823958")
add_player(1, 4, 'Mario', 64*50, "44ff55eeaabbcacd9933")

# in corewar vm cursors technically do not belong to players, so each cursor id is unique
# but for visualization sake cursors do belong to players who created them and are colorized respectively
add_cursor(2, 1, 1, 0)  # player 1 adds cursor 1
add_cursor(2, 2, 2, 64*10)  # player 2 adds cursor 2
add_cursor(2, 3, 3, 64*20)  # player 3 adds cursor 3
add_cursor(2, 4, 4, 64*50)  # player 4 adds cursor 4

add_cursor(10, 1, 5, 64*13)  # player 1 adds cursor 5

move_cursor(20, 1, 5, 4)  # move cursor 5 of player 1
move_cursor(40, 1, 5, 4)  # move cursor 5 of player 1

cycle = 50
kill_cursor(cycle, 1, 5)  # kill cursor 5 of player 1
cycle += 1

for i in range(5000):
    move_cursor(cycle, 1, 1, 4)  # move cursor 1 of player 1
    write_memory(cycle, 1, i * 6 + random.randint(0, 10), "AAFF01Baedf0")

    move_cursor(cycle, 2, 2, 2)  # move cursor 2 of player 2
    write_memory(cycle, 2, 64*10 + i * 6 +
                 random.randint(0, 10), "BB162fab08"
                 )

    move_cursor(cycle, 3, 3, 3)  # move cursor 3 of player 3
    write_memory(cycle, 3, 64*20 - i * 7 +
                 random.randint(0, 10), "17aa3891fe"
                 )

    move_cursor(cycle, 4, 4, 8)  # move cursor 4 of player 4
    write_memory(cycle, 4, 64*50 + i * 10 +
                 random.randint(0, 10), "6D6F64652E0D0D0A2401"
                 )

    cycle += 1

kill_cursor(cycle, 1, 1)  # kill cursor 1 of player 1
kill_cursor(cycle, 2, 2)  # kill cursor 2 of player 2
kill_cursor(cycle, 3, 3)  # kill cursor 3 of player 3
kill_cursor(cycle, 4, 4)  # kill cursor 4 of player 4

declare_winner(cycle, 1)
