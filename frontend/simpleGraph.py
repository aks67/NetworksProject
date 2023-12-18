import random

size = 100
density = 0.2  # Adjust the density as needed

# Generate a random adjacency matrix
adjacency_matrix = [[1 if random.random() < density else 0 for _ in range(size)] for _ in range(size)]

# Print the adjacency matrix as lists
for row in adjacency_matrix:
    print(row)