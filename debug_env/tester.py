import subprocess
import os
import random

def get_data(name1, name2, file):
    arg1 = name1 + " " + file
    arg2 = name2 + " " + file
    p1 = subprocess.Popen(arg1, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    p2 = subprocess.Popen(arg2, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    param1 = []
    param2 = []
    for line in p1.stdout.readlines():
        param1.append(line)
    for line in p2.stdout.readlines():
        param2.append(line)
    return param1, param2

def check(i, diff_line):
    if i == diff_line:
        return "\t\033[4m\033[37m\033[44m{}\033[0m".format("DIFF_HERE")
    else:
        return ("\t")

def print_diff(out1, out2, diff_line):
    for i in range(len(out1)):
        print("[",i,"]","\t",out1[i], '\t', out2[i], check(i, diff_line))

def make_diff(out1, out2):
    if (len(out1) != len(out2)):
        return 0
    else:
        for i in range(len(out1)):
            if out1[i] != out2[i]:
                print_diff(out1, out2, i)
                return i
        return -1

def print_out(out1, out2):
    for i in range(len(out1)):
        print("[",i,"]","\t",out1[i], '\t', out2[i])

def full_test(name1, name2, dir, not_pass_dir):
    i = 1
    for file in dir:
        print ("TEST_" + str(i) + " " + file, end = ' ')
        out1, out2 = get_data(name1, name2, file)
        if make_diff(out1, out2) >= 0:
            print ("\033[31m {}" .format("NOT_PASS"))
            subprocess.run(["mv", file,  not_pass_dir])
        else:
            print("\033[32m {}" .format("OK"))
        i += 1
    return 1

def file_test(name1, name2, file):
    print ("TEST " + file, end = ' ')
    out1, out2 = get_data(name1, name2, file)
    if make_diff(out1, out2) >= 0:
        print ("NOT_PASS")
    else:
        print("OK")
        subprocess.run(["mv", file,  "file_cor/"])
    return 1

def multiplayer_data(name1, name2, dir, num_of_player):
    champions = [dir[random.randint(1, len(dir) - 1)] for x in range(num_of_player)]
    arg1 = name1 + " -n " + str(num_of_player) + " " + " ".join(champions)
    arg2 = name2 +  " " + " ".join(champions)
    p1 = subprocess.Popen(arg1, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    p2 = subprocess.Popen(arg2, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    param1 = []
    param2 = []
    for line in p1.stdout.readlines():
        param1.append(line)
    for line in p2.stdout.readlines():
        param2.append(line)
    return param1, param2, arg1, arg2

def multiplayer_test(name1, name2, dir, num_of_player, num_of_tests):
    for i in range(num_of_tests):
        out1, out2, arg1, arg2 = multiplayer_data(name1, name2, dir, num_of_player)
        print ("TEST" + str(i + 1))
        print ("ARG_1 = ", arg1, "\n", "ARG_2 = ", arg2)
        print (out1[-1], out2[-1])
        if out1[-1] != out2[-1]:
            print ("NOT_PASS")
        else:
            print("OK")

if __name__ == "__main__":
    name1 = "./vm_ref"
    name2 =  "./vm_ver_1"
    name3 = "./corewar"
    file = "not_pass/_.cor"
    dir = "file_cor/"
    not_pass_dir = "not_pass/"
    subprocess.run(["cp", "../cmake-build-debug/vm",  "./"])
    subprocess.run(["mv", "vm",  "vm_ver_1"])
    list_files = os.listdir(dir)
    list_files = [dir + x for x in list_files]

    #Multiplayers_tests
    num_of_players = random.randint(1, 4)
    num_of_tests = random.randint(1, 10)
    for num_of_players in range(5):
        if 2 <= num_of_players < 5:
                    multiplayer_test(name2,
                                     name3,
                                     list_files,
                                     num_of_players,
                                     3)

    #Test all files in dir
    #full_test(name1, name2, list_files, not_pass_dir)

    #Test not passed file, one more
    #subprocess.run(["cp", "../cmake-build-debug/vm",  "./"])
    #subprocess.run(["mv", "vm",  "vm_ver_1"])
    #files = os.listdir("not_pass/")
    #files = ["not_pass/" + x for x in files]
    #for file in files:
    #    file_test(name1, name2, file)
