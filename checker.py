# To add a new cell, type '# %%'
# To add a new markdown cell, type '# %% [markdown]'
# %%
#!/usr/bin/env python
# coding: utf-8

# 0. Libraries import
import warnings
warnings.filterwarnings(action='ignore')

import logging
import subprocess
logging.getLogger().setLevel(logging.INFO)

def run_cmd(cmd):
    logging.getLogger().setLevel(logging.INFO)
    logging.info("%s"%cmd)
    cmd = cmd.split()
    p = subprocess.run(cmd,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE)
    # if p.stdout: logging.info("stdout\n%s"%bytes.decode(p.stdout))
    if p.stderr: logging.warn("stderr\n%s"%bytes.decode(p.stderr))
    return bytes.decode(p.stdout)

import os

try:import numpy
except:os.system("pip3 install -q numpy --user")
import io
import sys

logging.info("%s"%(sys.platform))


# %%
from colors import *


# %%
if 'Makefile' in set(os.listdir('.')):
    logging.info("will call a \'make\' command")
    run_cmd("make re")


# %%
exe_corewar_sys = './mac-os-vm-champ/corewar' if str(sys.platform).lower() == 'darwin' else './vm-champ-linux/corewar'
logging.info("path to given corewar executable:%s"%(exe_corewar_sys))


# %%
exe_asm_sys = './mac-os-vm-champ/asm' if str(sys.platform).lower() == 'darwin' else './vm-champ-linux/asm'
logging.info("path to given asm executable:%s"%(exe_asm_sys))


# %%
exe_corewar_our='./corewar'
logging.info("path to our corewar executable:%s"%(exe_corewar_our))


# %%
exe_asm_our='./asm'
logging.info("path to our asm executable:%s"%(exe_asm_our))


# %%
cmd2 = " ".join( [    exe_corewar_sys,					"-d",
					"0",
					"mac-os-vm-champ/batman.cor",
					"mac-os-vm-champ/robin.cor",

])
stdout_sys = run_cmd(cmd2).replace("\n",":").replace(" ","").split(":")[4::2]


# %%
((stdout_sys))


# %%
cmd1 = " ".join( [    exe_corewar_our,					"-n",
					"1",
					"mac-os-vm-champ/batman.cor",
					"-n",
					"2",
					"mac-os-vm-champ/robin.cor",

])
stdout_our = run_cmd(cmd1).split("\n")


# %%
error = list(stdout_our[10])
error[7] = '-'
stdout_our[10] = "".join(error)


# %%
def prinf_diff(string_number,our,sys):
    if our==sys:
        logging.info("Strings number %i equals"%(string_number))
    else:
        logging.warn("Strings number %i NOT equals"%(string_number))
        diff_our= "".join([(our1) if our1==sys1 else (CRED+our1+CEND) for i,(our1,sys1) in enumerate(zip(our,sys))])
        diff_sys= "".join([" " if our1==sys1 else (CGREEN+sys1+CEND) for i,(our1,sys1) in enumerate(zip(our,sys))])
        logging.warn("our:%s"%diff_our)
        logging.warn("sys:%s"%diff_sys)
    return None    


# %%
[prinf_diff(string_number,our,sys) for string_number,(our, sys) in enumerate(zip(stdout_our,stdout_sys))];


# %%
run_cmd("make fclean")

