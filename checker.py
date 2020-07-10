#!/usr/bin/env python3
# coding: utf-8

# 0. Libraries import
import warnings
warnings.filterwarnings(action='ignore')
import logging
import subprocess
import os
import sys

# 1. Local variables and function definition
CEND    = '\33[0m'
CRED    = '\33[31m'
CGREEN  = '\33[32m'

logging.getLogger().setLevel(logging.INFO)

def run_cmd(cmd):
    logging.info("%s"%cmd)
    cmd = cmd.split()
    p = subprocess.run(cmd,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE)
    if p.stderr: logging.warn("stderr\n%s"%bytes.decode(p.stderr))
    return bytes.decode(p.stdout)

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

def parse_args(args):
	res = dict()
	res['players'] = []
	i = 1
	l = len(args)
	while i < l:
		if args[i] =='--start':
			i+=1
			try:res['start']=int(args[i])
			except Exception as e: 
				logging.warn("an error occuring with \'start\' argument: %s"%e)
				sys.exit(-1)
		elif args[i] =='--end':
			i+=1
			try:res['end']=int(args[i])
			except Exception as e: 
				logging.warn("an error occuring with \'end\' argument: %s"%e)
				sys.exit(-1)
		else:
			res['players'].append(args[i])
		i+=1
	if 'end' not in res.keys() and 'start' in res.keys():
		res['end'] = max(res['start'],10)
	elif 'end' in res.keys() and 'start' not in res.keys():
		res['start'] = res['end']
	elif 'end' not in res.keys() and 'start' not in res.keys():
		res['start'] = 10
		res['end'] = 10
	return res

# 2. Programs definition

logging.info("%s"%(sys.platform))

if 'Makefile' in set(os.listdir('.')):
    logging.info("will call a \'make re\' command")
    run_cmd("make re")
else:
    logging.warn("Makefile abcent, please, add it in dir:%s"%(os.path.abspath('.')))

exe_corewar_sys = './mac-os-vm-champ/corewar' if str(sys.platform).lower() == 'darwin' else './vm-champ-linux/corewar'
logging.info("path to given corewar executable:%s"%(exe_corewar_sys))

exe_asm_sys = './mac-os-vm-champ/asm' if str(sys.platform).lower() == 'darwin' else './vm-champ-linux/asm'
logging.info("path to given asm executable:%s"%(exe_asm_sys))

exe_corewar_our='./corewar'
logging.info("path to our corewar executable:%s"%(exe_corewar_our))

exe_asm_our='./asm'
logging.info("path to our asm executable:%s"%(exe_asm_our))

# 3. Programs execution

args = parse_args(sys.argv)

logging.info("start at: %i"%(args['start']))
logging.info("end at: %i"%(args['end']))
logging.info("players: %s"%(" ".join(args['players'])))

i1 = args['start']
players = " ".join(args['players'])
cnt = 0
while i1 <= args['end']:
	logging.info('--------Cicle #%i--------'%(i1))
	cmd1 = " ".join([
				exe_corewar_our,
				'-dump',
				str(i1),
				players,
					])

	stdout_our = run_cmd(cmd1).split("\n")

	cmd2 = " ".join([
				exe_corewar_sys,
				'-d',
				str(i1),
				players,
	])
	stdout_sys = run_cmd(cmd2).replace("\n",":").replace(" ","").split(":")
	for i2,line in enumerate(stdout_sys):
		if line[:6] != '0x0000':continue
		break
	stdout_sys = stdout_sys[i2+1::2]

	# 4. Compare and print out results 

	[prinf_diff(string_number,our,sys) for string_number,(our, sys) in enumerate(zip(stdout_our,stdout_sys))]
	i1+=1
	cnt+=1
	if cnt == 101:
		logging.warn("cicle artificially breaked")
		break

# 5. Final cleanup and finish
 
run_cmd("make fclean")
sys.exit(0)
