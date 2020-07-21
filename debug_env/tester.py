import subprocess
import os

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
    for file in dir:
        print ("TEST " + file, end = ' ')
        out1, out2 = get_data(name1, name2, file)
        if make_diff(out1, out2) >= 0:
            print ("NOT_PASS")
            subprocess.run(["mv", file,  not_pass_dir])
        else:
            print("OK")
    return 1

if __name__ == "__main__":
    name1 = "./vm_ref"
    name2 =  "./vm_ver_1"
    dir = "file_cor/"
    not_pass_dir = "not_pass/"
    list_files = os.listdir(dir)
    list_files = [dir + x for x in list_files]
    full_test(name1, name2, list_files, not_pass_dir)