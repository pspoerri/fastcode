import subprocess
import ast
import sys
import pickle

RUN_CONFIGURATION = {
    "finalcode.c": range(56, 2000, 56),
#    "finalcode_176.c": range(176, 2000, 176),
    "code0.c": range(2, 64, 2)+range(64,128,4)+range(64,512,16)+range(512,1600,128)}
COMPILE_FLAGS = "-m64 -march=corei7 -fno-tree-vectorize -O3".split(" ")
COMPILE_FILES = ["main.c", "ftimer.c"]
COMPILER = "gcc-4.7"

def total_flops(NB):
    n = float(NB)
    return 2.0*n*n*n

def verify(SRC, NB, N):
    command_name = SRC[:-2]
    compile_args_shell = [COMPILER, "-DN="+str(N),"-DNB="+str(NB), "-DVERIFY=1" ]+COMPILE_FLAGS+["-o", command_name, SRC]+COMPILE_FILES
    try:
        o = subprocess.check_call(compile_args_shell)
    except:
        print "Error\n"
        sys.exit(-1);

    o = subprocess.check_call(["./"+command_name], shell=True)

    if (o != 0):
        print "Couldn't verify "+command_name+" with "+SRC+" and Blocksize: "+str(NB)+"\n"+str(o)
        sys.exit(-1)


        
def benchmark(SRC, NB, N):
    command_name = SRC[:-2]
    compile_args_shell = [COMPILER, "-DN="+str(N),"-DNB="+str(NB) ]+COMPILE_FLAGS+["-o", command_name, SRC]+COMPILE_FILES
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
        return result
#        num_runs = result['num_runs']
    except Exception as e:
        print "Error in execution of "+command_name+"\n"+str(e)+o 
        sys.exit(-1)

def measure():
    data = {}

    for f,matrix_sizes in RUN_CONFIGURATION.iteritems():
        results = []
        print f
        # benchmark(f, 2)
        block_size = matrix_sizes[0]
        for matrix_size in matrix_sizes:
            # verify(f, block_size)
            result_run = benchmark(f, block_size, matrix_size)
            results += [result_run]
            print result_run
            # print str(block_size)
            # print str(result_run['timebench']['flops_cycle'])
            # print str(result_run['microbench']['flops_cycle'])

        data[str(f)] = results
        
    
    from datetime import datetime
    f = open("matrix_run_"+datetime.now().strftime('%y_%m_%d__%H_%M')+'.pickle', 'wb')
    pickle.dump(data, f)

measure() 


        

