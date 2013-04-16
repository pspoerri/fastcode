import subprocess
import ast
import sys
import pickle

RUN_CONFIGURATION = {
    "code1.c": range(2, 800,2), 
    "code2.c": range(2, 800, 2), 
    "code3.c": range(8, 800, 8)}
COMPILE_FLAGS = "-m64 -march=corei7 -fno-tree-vectorize -O3".split(" ")
COMPILE_FILES = ["main.c", "ftimer.c"]
COMPILER = "gcc-4.7"

def total_flops(NB):
    n = float(NB)
    return 2.0*n*n*n

def verify(SRC, NB):
    command_name = SRC[:-2]
    compile_args_shell = [COMPILER, "-DNB="+str(NB), "-DVERIFY=1" ]+COMPILE_FLAGS+["-o", command_name, SRC]+COMPILE_FILES
    try:
        o = subprocess.check_call(compile_args_shell)
    except:
        print "Error\n"
        sys.exit(-1);

    o = subprocess.check_call(["./"+command_name], shell=True)

    if (o != 0):
        print "Couldn't verify "+command_name+" with "+SRC+" and Blocksize: "+str(NB)+"\n"+str(o)
        sys.exit(-1)


        
def benchmark(SRC, NB):
    command_name = SRC[:-2]
    compile_args_shell = [COMPILER, "-DNB="+str(NB) ]+COMPILE_FLAGS+["-o", command_name, SRC]+COMPILE_FILES
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
        cycles = float(result['cycles'])
        flops = cycles/total_flops(NB)
        print str(NB)+": "+str(flops)+","
        result['flops_cycle'] = flops
        return result
#        num_runs = result['num_runs']
    except Exception as e:
        print "Error in execution of "+command_name+"\n"+str(e)+o 
        sys.exit(-1)

def measure():
    data = {}

    print "{"
    for f,block_sizes in RUN_CONFIGURATION.iteritems():
        results = []
        # benchmark(f, 2)
        print '"'+f+'"'+": {"
        for block_size in block_sizes:
            # verify(f, block_size)
            result_run = benchmark(f, block_size)
            results += [result_run]
            print result_run
        data[str(f)] = results
        
        print "}, "
    print "}"
    
    from datetime import datetime
    f = open("run_"+datetime.now().strftime('%y_%m_%d__%H_%M')+'.pickle', 'wb')
    pickle.dump(data, f)

measure() 


        

