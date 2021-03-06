import numpy as np
import matplotlib.pyplot as plt
import pickle
plt.rc('text', usetex=True)
plt.rc('font', family='serif')

#filename = 'run_13_04_16__10_10.pickle'
#filename = 'run_13_04_16__10_23.pickle'
#filename = 'run_13_05_09__15_04.pickle'
filename = 'run_13_05_09__19_13.pickle'
fig = plt.figure()

f = open(filename, 'r')
runtime_data = pickle.load(f) 
plot_refs = []
legend_refs = []
for f,results in runtime_data.iteritems():
    
    d = map(lambda l: (int(l['size']), float(l['flops_cycle'])), results)
    d.sort()
    print f
    print d
    matrix_sizes, flops_cycle = zip(*d)
#print block_sizes
#    print flops_cycle
    block_size = results[0]['size']

    p = plt.plot(matrix_sizes, flops_cycle, label=f)
plt.legend(loc='best')
plt.grid(True)
plt.xlabel('Size') 
plt.title('Flops/Cycle')
plt.show()


