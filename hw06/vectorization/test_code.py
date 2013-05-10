import subprocess
import ast
import sys
import pickle

RUN_CONFIGURATION = {
    "base.c": { 
        "range": range(4, 804, 4),
        "flags": "-m64 -march=corei7-avx -fno-tree-vectorize -O3".split(" ")
    },
    "auto.c": {
        "range": range(4, 804, 4),
        "flags": "-m64 -march=corei7-avx -O3".split(" ")
    },
    "manual.c": {
        "range": range(4, 804, 4),
        "flags": "-m64 -march=corei7-avx -O3".split(" ")
    },
    "manual3.c": {
        "range": range(4, 804, 4),
        "flags": "-m64 -march=corei7-avx -O3".split(" ")
    },
    "manual4.c": {
        "range": range(4, 804, 4),
        "flags": "-m64 -march=corei7-avx -O3".split(" ")
    },
#    "manual3.c": {
#        "range": range(4, 804, 4),
#        "flags": "-m64 -march=corei7-avx -O3".split(" ")
#    },
}
COMPILE_FILES = ["main.c", "ftimer.c"]
COMPILER = "gcc-4.7"

def total_flops(NB):
    n = float(NB)
    return 3.0*n

#def verify(SRC, NB):
#    command_name = SRC[:-2]
#    compile_args_shell = [COMPILER, "-DNB="+str(NB), "-DVERIFY=1" ]+COMPILE_FLAGS+["-o", command_name, SRC]+COMPILE_FILES
#    try:
#        o = subprocess.check_call(compile_args_shell)
#    except:
#        print "Error\n"
#        sys.exit(-1);
#
#    o = subprocess.check_call(["./"+command_name], shell=True)
#
#    if (o != 0):
#        print "Couldn't verify "+command_name+" with "+SRC+" and Blocksize: "+str(NB)+"\n"+str(o)
#        sys.exit(-1)
#

        
def benchmark(SRC, NB, COMPILE_FLAGS):
    command_name = SRC[:-2]
    compile_args_shell = [COMPILER, "-DN="+str(NB) ]+COMPILE_FLAGS+["-o", command_name, SRC]+COMPILE_FILES
#    print compile_args_shell
    
    try:
        o = subprocess.check_output(compile_args_shell)
    except:
        print " ".join(compile_args_shell)
        #print "Error\n"+o
        sys.exit(-1);

    try:
        o = subprocess.check_output(["./"+command_name])
#        print o
        result = ast.literal_eval(o)
        return result
#        num_runs = result['num_runs']
    except Exception as e:
        print "Error in execution of "+command_name+"\n"+str(e)+o 
        sys.exit(-1)

def measure():
    data = {}

    for f,conf in RUN_CONFIGURATION.iteritems():
        block_sizes = conf["range"]
        COMPILE_FLAGS = conf["flags"]
        results = []
        print f
        # benchmark(f, 2)
        for block_size in block_sizes:
            # verify(f, block_size)
            result_run = benchmark(f, block_size, COMPILE_FLAGS)
            results += [result_run]
            print result_run
            # print str(block_size)
            # print str(result_run['timebench']['flops_cycle'])
            # print str(result_run['microbench']['flops_cycle'])
        label = str(f).replace(".c", "")
        data[label] = results
        
    
    from datetime import datetime
    f = open("run_"+datetime.now().strftime('%y_%m_%d__%H_%M')+'.pickle', 'wb')
    pickle.dump(data, f)

measure() 


        

