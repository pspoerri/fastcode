#!/usr/bin/env python
# -*- coding: utf-8 -*-

#Fill in data here and put it into the main file :)

DATAFILE = open('not_vectorized', 'r')
DATA = DATAFILE.read()
DATAFILE.close()

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

    unfiltered = get_array(DATA)
    mintime = map(lambda l: min(l[0], l[1]), zip(unfiltered[1][0::2], unfiltered[1][1::2]))
    mincycles = map(lambda l: min(l[0], l[1]), zip(unfiltered[2][0::2], unfiltered[2][1::2]))
    data = [unfiltered[0][0::2], mintime]
# print zip(data[0], data[1])
    gflops = map(lambda l: float(l[0])*2.0/l[1]/float(1e9), zip(data[0], data[1]))
    peak_performance = map(lambda l: l/(5.6/100), gflops)
#    print gflops
    plot_data(data[0], mincycles, "Runtime (cycles)")
    plot_data(data[0], gflops, "GFLop/s")
    plot_data(data[0], peak_performance, "Peak Performance (Percentage)")


if __name__ == "__main__":
    main()
