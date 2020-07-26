import subprocess
import os
import random

def diff_file(file1, file2):
    f1 = open(file1)
    f2 = open(file2)
    count = 0
    Flag = 1
    fork1 = []
    fork2 = []
    while Flag:
        line1 = f1.__next__()
        line2 = f2.__next__()
        params1 = line1.split()
        params2 = line2.split()
        if "fork" in line1:
            fork1.append(line1)
        if "fork" in line2:
            fork2.append(line2)
        #print (params1, params2)
        #exit()
        count += 1
        for i in range(len(params1)):
            if params1[i] != params2[i]:
                print ("line = ", count)
                print (file1, " = ", line1)
                print (file2, " = ", line2)
                Flag = 0
                break
    [print(el) for el in fork1]
    [print(el) for el in fork2]
    print("len fork1 " + file1 + " = ", len(fork1))
    print("len fork2 " + file2 + " = ", len(fork2))


if __name__ == "__main__":
    name1 = "./vm_ref"
    name2 =  "./vm_ver_1"
    name3 = "./corewar"
    file = "not_pass/_.cor"
    dir = "file_cor/"
    not_pass_dir = "not_pass/"
    #subprocess.run(["cp", "../cmake-build-debug/vm",  "./"])
    #subprocess.run(["mv", "vm",  "vm_ver_1"])


    diff_file("pc_our", "pc")