import subprocess


def get_data(name1, name2, iter, file):
    arg1 = name1 + " -i " + str(iter) + " " + file
    arg2 = name2 + " -i " + str(iter) + " " + file
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

def new_line(sym):
    if sym.split(":")[0] == "o":
        return "\n"
    else:
        return ""

def print_diff(out1, out2, diff_line):
    for i in range(len(out1)):
        sym = out1[i].decode("utf-8")
        if sym.split(":")[0] == "a":
            print("[",i,"]","\t","arena_1", '\t', "arena_2", check(i, diff_line))
        else:
            print("[",i,"]","\t",out1[i], '\t', out2[i], check(i, diff_line), new_line(sym))

def make_diff(out1, out2):
    for i in range(len(out1) - 1):
        if out1[i] != out2[i] and out1[i].decode("utf-8").split(":")[0] != "o" and out1[i].decode("utf-8").split(":")[0] != "cycles_to_exec":
            print_diff(out1, out2, i)
            return i
    return -1

def full_test(name1, name2, file):
    iter = 1
    check_arena = False
    while(True):
        print ("iter " + str(iter) + " start")
        out1, out2 = get_data(name1, name2, iter, file)
        diff_line = make_diff(out1, out2)
        if diff_line > 0:
            sym = out1[diff_line].decode("utf-8")
            if sym.split(":")[0] == "a":
                check_arena = True
            break
        print ("iter " + str(iter) + " stop")
        iter += 1

    return diff_line, iter, check_arena


def make_str_to_list(arena):
    arr = []
    i = 0
    while i  < len(arena):
        if arena[i] != ' ':
            if i != (len(arena) - 1) and arena[i + 1] != ' ':
                byte = str(arena[i]) + str(arena[i + 1])
                arr.append(byte)
                i += 1
            else:
                byte = arena[i]
                arr.append(byte)
        i += 1
    return (arr)

def diff_arena(config, iter, diff_line):
    out1, out2 = get_data(config[0], config[1], iter, config[2])
    arena1 = out1[diff_line].decode("utf-8")[2:-1]
    arena2 = out2[diff_line].decode("utf-8")[2:-1]
    test1 = make_str_to_list(arena1)
    test2 = make_str_to_list(arena2)
    print ("\t\t\tvalue\n","\t\t", config[0], '\t', config[1])
    for i in range(len(test1)):
        if test1[i] != test2[i]:
            print ("ADDR = ", i, '\t', test1[i], '\t\t', test2[i])

if __name__ == "__main__":
    name1 = "./vm_vb"
    name2 =  "./vm_our"
    file = "not_pass/run_Kitty_RUN.cor"
    subprocess.run(["cp", "../cmake-build-debug/vm",  "./"])
    subprocess.run(["mv", "vm",  "vm_our"])
    diff_line, iter, check_arena = full_test(name1, name2, file)
    config = [ name1,
               name2,
               file,]
    if check_arena:
        print ("ARENA_DIFF")
        diff_arena(config, iter, diff_line)
    print ("DIFF_LINE = ", diff_line)