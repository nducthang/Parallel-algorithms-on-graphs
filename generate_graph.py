import random
import sys


def get_possible_edges(n, d):
    possible_edges = []

    for i in range(n):
        neighbors = []

        while len(neighbors) < d:
            x = random.randint(0, n - 1)

            if x == i or (i, x) in neighbors:
                continue

            neighbors.append((i, x))

        possible_edges.extend(neighbors)

    return possible_edges


def generate_graph(n, d, p):
    possible_edges = get_possible_edges(n, d)

    m_max = n * (n - 1) / 2
    m = int(p * m_max)

    random.shuffle(possible_edges)
    edges = possible_edges[:m]

    return edges


if __name__ == "__main__":
    n_graphs = 1
    n_nodes = 500
    n_degree = 4
    p_edges = 0.3

    while n_nodes <= 40000:
        for i in range(n_graphs):
            print("GENERATING GRAPH", i, "...")
            edges = generate_graph(n_nodes, n_degree, p_edges)

            print("\tCREATING FILE...")
            file_name = "./src/Prim/data/graph_" + \
                str(n_nodes) + "_nodes" + ".txt"
            f = open(file_name, "w")

            x = random.randint(0, n_nodes)
            # f.write(str(n_nodes) + " " + str(x) + "\n")
            f.write(str(n_nodes) + "\n")
            for edge in edges:
                edge_description = str(
                    edge[0]) + " " + str(edge[1]) + " " + str(random.randint(0, n_nodes * 2)) + "\n"
                f.write(edge_description)

            f.close()

            print("\tCREATED FILE!")
            n_nodes += 500
