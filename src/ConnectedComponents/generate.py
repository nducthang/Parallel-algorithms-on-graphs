import sys
from random import randint

if __name__ == "__main__":
	num = 500
	step = 500
	while num <= 30000:
		file_name = "./src/ConnectedComponents/data/graph_%d_nodes.txt" % (num)
		file = open(file_name, "w")
		file.write("%d\n" % (num))
		m = num * 5
		while m != 0:
			x, y = -1, -1
			m -= 1
			while(x == y):
				x = randint(0, num - 1)
				y = randint(0, num - 1)
			file.write("%d %d\n" % (x, y))
		num += step
		file.close()
