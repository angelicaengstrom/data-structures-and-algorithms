from matplotlib import pyplot as plt
from matplotlib import style
import numpy as np
import math


def show(filename, plot):
    N, seconds, std, sample = np.loadtxt(
        'C:\\Users\\angel\\OneDrive\\Dokument\\DT046G Datastrukturer och Algoritmer\\lab2\\data\\' + filename + '.csv',
        unpack=True,
        delimiter=",")

    k1 = seconds[9] / (N[9] ** 2)
    ON2 = []

    k2 = seconds[9] / (N[9])
    ON = []

    k3 = seconds[9] / (N[9] * math.log(N[9], 2))
    ONlogN = []

    for element in N:
        ON2.append(element**2 * k1)
        ON.append(element * k2)
        ONlogN.append(element * math.log(element, 2) * k3)

    plot.plot(N, ON2, label="O(N^2)", ls='-', color='orange')
    plot.plot(N, ON, label="O(N)", ls='-', color='lightblue')
    plot.plot(N, ONlogN, label="O(N log N)", ls='-', color='lightgreen')

    plot.plot(N, seconds, label=filename, color='magenta', ls='', marker='o')
    plot.errorbar(N, seconds, yerr=std, ls='', color='magenta')

    plot.ylabel("Time [s]")
    plot.xlabel("Elements [N]")
    plot.legend()


style.use('ggplot')

plt.figure(1)
plt.subplot(2, 2, 1)
plt.title("Selection sort")
show('selection_sort_random', plt)

plt.subplot(2, 2, 2)
show('selection_sort_constant', plt)

plt.subplot(2, 2, 3)
show('selection_sort_rising', plt)

plt.subplot(2, 2, 4)
show('selection_sort_falling', plt)
plt.show()

plt.figure(2)
plt.subplot(2, 2, 1)
plt.title("Insertion sort")
show('insertion_sort_random', plt)

plt.subplot(2, 2, 2)
show('insertion_sort_constant', plt)

plt.subplot(2, 2, 3)
show('insertion_sort_rising', plt)

plt.subplot(2, 2, 4)
show('insertion_sort_falling', plt)
plt.show()

plt.figure(3)
plt.subplot(2, 2, 1)
plt.title('std::sort')
show('std_sort_random', plt)

plt.subplot(2, 2, 2)
show('std_sort_constant', plt)

plt.subplot(2, 2, 3)
show('std_sort_rising', plt)

plt.subplot(2, 2, 4)
show('std_sort_falling', plt)
plt.show()

plt.figure(4)
plt.subplot(2, 2, 1)
plt.title("Quick Sort")
show('quick_sort_random', plt)

plt.subplot(2, 2, 2)
show('quick_sort_constant', plt)

plt.subplot(2, 2, 3)
show('quick_sort_rising', plt)

plt.subplot(2, 2, 4)
show('quick_sort_falling', plt)
plt.show()

plt.figure(5)
plt.subplot(2, 2, 1)
plt.title("Quick Sort Median Of Three")
show('quick_sort_mot_random', plt)

plt.subplot(2, 2, 2)
show('quick_sort_mot_constant', plt)

plt.subplot(2, 2, 3)
show('quick_sort_mot_rising', plt)

plt.subplot(2, 2, 4)
show('quick_sort_mot_falling', plt)
plt.show()
