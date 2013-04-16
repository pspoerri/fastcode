import numpy as np
import matplotlib.pyplot as plt
import pickle
plt.rc('text', usetex=True)
plt.rc('font', family='serif')

#filename = 'run_13_04_16__10_10.pickle'
#filename = 'run_13_04_16__10_23.pickle'
filename = 'run_13_04_16__10_48.pickle'

fig = plt.figure()

f = open(filename, 'r')
runtime_data = pickle.load(f) 
plot_refs = []
legend_refs = []
for f,results in runtime_data.iteritems():
    
    d = map(lambda l: (int(l['block_size']), float(l['flops_cycle'])), results)
    d.sort()
    print f
    print d
    block_sizes, flops_cycle = zip(*d)
#print block_sizes
#    print flops_cycle

    p = plt.plot(block_sizes, flops_cycle, label=str(f))
plt.legend(loc='best')
plt.grid(True)
plt.xlabel('Block Size') 
plt.title('Flops/Cycle')
plt.show()


