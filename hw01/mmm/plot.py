#!/usr/bin/env python
# -*- coding: utf-8 -*-

#Fill in data here and put it into the main file :)

RUNTIME_DATA = """
100 0.000920
200 0.008479
300 0.029202
400 0.083903
500 0.160004
600 1.023856
700 2.401716
800 3.318314
900 5.158415
1000 7.155869
1100 10.019060
1200 12.687760
1300 16.615452
1400 21.608725
1500 26.936481
"""

CYCLES_DATA = """
100 2393049.671875 
200 22046439.000000
300 75926044.000000
400 218149074.000000
500 416009992.000000
600 2662026499.000000
700 6626138023.000000
800 8627616554.000000
900 13411879878.000000
1000 18605259735.000000
1100 26049555430.000000
1200 32988175141.000000
1300 43200175843.000000
1400 56182685840.000000
1500 70034851135.000000
"""

import numpy as np
import matplotlib.pyplot as plt
plt.rc('text', usetex=True)
plt.rc('font', family='serif')

# Warning: Table names defines the structure of the table and is hardcoded in this program
table_names = ["seconds"]

# Fuck it
def get_array(data):
    tmp = data.split('\n')
    tmp = filter(lambda t: t!= [''], map(lambda t: t.split(' '), tmp))
    tmp = map(lambda t: filter(None, t), tmp)
    tmp = map(lambda t: map(lambda v: float(v), t), tmp)
    return np.asarray((tmp)).transpose()


def plot_data(timesteps, data, title):
    fig = plt.figure()
    
#plt.loglog(timesteps, data)
    plt.plot(timesteps, data)
    plt.grid(True)
#    plt.ylabel('Seconds')
    plt.xlabel('n')
#plt.legend(shadow=True, fancybox=True, loc=0)
    
    plt.title(title)
## I'm lazy
    fig.savefig(title.replace(".","").replace(" ","").replace("(","").replace(")","").replace("/","")+".pdf")
#plt.show()
def pick_data(arr, names):
    timesteps = arr[0]
    data = arr[1:len(names)-1]
    reference = arr[-1]
    n = names[1:len(names)-1]
    return (timesteps, data, n, reference)

def main():

    runtime_data = get_array(RUNTIME_DATA)
    cycles_data = get_array(CYCLES_DATA)
    gflops = map(lambda l: (float(l[0])**3.0)*2.0/l[1]/float(1e9), zip(runtime_data[0], runtime_data[1], cycles_data[1]))
    flops_cycle = map(lambda l: (float(l[0])**3.0)*2.0/l[2], zip(runtime_data[0], runtime_data[1], cycles_data[1]))
    peak_performance = map(lambda l: l/(5.6/100), gflops)
#    print gflops
    plot_data(runtime_data[0], cycles_data[1], "Runtime (cycles)")
    plot_data(runtime_data[0], gflops, "GFLop/s")
    plot_data(runtime_data[0], flops_cycle, "Flops/Cycle")    
    plot_data(runtime_data[0], peak_performance, "Peak Performance (Percentage)")


if __name__ == "__main__":
    main()
