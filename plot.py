import matplotlib.pyplot as plt
import pandas as pd

if __name__ == '__main__':
    data1 = pd.read_csv('./src/ConnectedComponents/resultSequential.txt', header=None)
    data2 = pd.read_csv('./src/ConnectedComponents/resultParallel.txt', header=None)
    x = list(data1[0])
    y_line_1 = list(data1[1])
    y_line_2 = list(data2[1])
    plt.plot(x, y_line_1, label = 'Sequential')
    plt.plot(x, y_line_2, label = 'Parallel')
    plt.xlabel('Node')
    plt.ylabel('Time (s)')
    plt.title("ConnectedComponents (DFS) algorithm")
    plt.legend()
    plt.show()