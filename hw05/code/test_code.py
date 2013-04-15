import subprocess
import ast
import sys

RUN_CONFIGURATION = {"code1.c": range(2, 1502,2), "code2.c": range(2, 1502, 2), "code3.c": range(8, 1508, 8)}
COMPILE_FLAGS = "-m64 -march=corei7-avx -fno-tree-vectorize -O3".split(" ")
COMPILER = "gcc-4.7"
def total_flops(NB):
    return 2.0*NB*NB*NB

def verify(SRC, NB):
    command_name = SRC[:-2]
    compile_args_shell = [COMPILER, "-DNB="+str(NB), "-DVERIFY=1" ]+COMPILE_FLAGS+["-o", command_name, SRC, "main.c"]
    try:
        o = subprocess.check_output(compile_args_shell)
    except:
        print "Error\n"+o
        sys.exit(-1);

    try:
        o = subprocess.check_output(["./"+command_name])

    except:
        print "Couldn't verify "+command_name+" with "+SRC+" and Blocksize: "+str(NB)+"\n"+o
        sys.exit(-1)


        
def benchmark(SRC, NB):
    command_name = SRC[:-2]
    compile_args_shell = [COMPILER, "-DNB="+str(NB) ]+COMPILE_FLAGS+["-o", command_name, SRC, "main.c"]
#    print compile_args_shell
    
    try:
        o = subprocess.check_output(compile_args_shell)
    except:
        print "Error\n"+o
        sys.exit(-1);

    try:
        o = subprocess.check_output(["./"+command_name])
#        print o
        result = ast.literal_eval(o)
#        print result
        cycles = result['cycles']
        return cycles/total_flops(NB)
#        num_runs = result['num_runs']
    except Exception as e:
        print "Error in execution of "+command_name+"\n"+str(e)+o 
        sys.exit(-1)

for f,block_sizes in RUN_CONFIGURATION.iteritems():
    # benchmark(f, 2)
    print "File: "+f
    for block_size in block_sizes:
        verify(f, block_size)
        cycles = benchmark(f, block_size)
        print str(block_size)+": "+str(cycles)

