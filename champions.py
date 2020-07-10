instructions_ready = set([
    'sti',
    'ld',
    'zjmp',
    'add',
    'aff',
    'and',
    'ldi',
    "sub",
    "or",
    "xor",
    "lld",
    "lldi",
	'live',
])

# 0. Libraries import
import warnings
warnings.filterwarnings(action='ignore')
import logging
import subprocess
import os
import sys

# 1. Local variables and function definition
logging.getLogger().setLevel(logging.INFO)


def run_cmd(cmd):
    logging.info("%s" % cmd)
    cmd = cmd.split()
    p = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if p.stderr: logging.warn("stderr\n%s" % bytes.decode(p.stderr))
    return bytes.decode(p.stdout)


exe_asm_sys = './mac-os-vm-champ/asm' if str(
    sys.platform).lower() == 'darwin' else './vm-champ-linux/asm'
logging.info("path to given asm executable:%s" % (exe_asm_sys))

folder_for_cor_files = './cor-mac' if str(
    sys.platform).lower() == 'darwin' else './cor-linux'
logging.info("path to folder with .cor files:%s" % (folder_for_cor_files))


def compile_if_ready(path_to_file, instructions_ready=instructions_ready):
    instructions_all = set([
        "live",
        "ld",
        "st",
        "add",
        "sub",
        "and",
        "or",
        "xor",
        "zjmp",
        "ldi",
        "sti",
        "fork",
        "lld",
        "lldi",
        "lfork",
        "aff",
    ])
    instructions_not_ready = instructions_all - instructions_ready

    with open(path_to_file, 'r') as f:
        content = f.read()
        if instructions_not_ready & set(content.split()):
            f.close()
            return
    logging.info(path_to_file)
    path_to_file_new = os.path.join(
        folder_for_cor_files,
        path_to_file.split('/')[-1],
    )
    os.system(" ".join([
        'cp',
        path_to_file,
        path_to_file_new,
    ]))
    os.system(" ".join([
        exe_asm_sys,
        path_to_file_new,
    ]))
    os.system(" ".join([
        'rm',
        path_to_file_new,
    ]))

[
    compile_if_ready(os.path.join(os.path.abspath('s-linux-mac'), f))
    for f in os.listdir('s-linux-mac')
]
