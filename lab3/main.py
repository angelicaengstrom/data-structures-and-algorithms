from matplotlib import pyplot as plt
from matplotlib import style
import numpy as np
import math

def show(filename, plot):
    N, seconds, std, sample = np.loadtxt(
        'C:\\Users\\angel\\OneDrive\\Dokument\\DT046G Datastrukturer och Algoritmer\\lab3\\data\\' + filename + '.csv',
        unpack=True,
        delimiter=",")

    O1 = []

    k2 = seconds[9] / (N[9])
    ON = []
    # k * N = sekunder => k = sekunder / N

    k3 = seconds[9] / (math.log(math.log(N[9], 2), 2))
    OloglogN = []

    k4 = seconds[9] / math.log(N[9], 2)
    OlogN = []

    for element in N:
        O1.append(seconds[9])
        ON.append(element * k2)
        OloglogN.append(math.log(math.log(element, 2), 2) * k3)
        OlogN.append(math.log(element, 2) * k4)

    plot.plot(N, O1, label="O(1)", ls='-', color='orange')
    plot.plot(N, OloglogN, label="O(loglogN)", ls='-', color='lightgreen')
    plot.plot(N, OlogN, label="O(logN)", ls='-', color='lightpink')
    plot.plot(N, ON, label="O(N)", ls='-', color='lightblue')

    plot.plot(N, seconds, label=filename, color='magenta', ls='', marker='o')
    plot.errorbar(N, seconds, yerr=std, ls='', color='magenta')

    plot.ylabel("Time [s]")
    plot.xlabel("Elements [N]")
    plot.legend()

style.use('ggplot')

plt.figure(1)
plt.title("Linear search")
show('linear_search', plt)
plt.show()

plt.figure(2)
plt.title("Binary search")
show('binary_search', plt)
plt.show()

plt.figure(3)
plt.title("Interpolation search")
show('interpolation_search', plt)
plt.show()

plt.figure(4)
plt.title("Binary tree search")
show('binary_tree_search', plt)
plt.show()

plt.figure(5)
plt.title("Hash table search")
show('hash_table_search', plt)
plt.show()