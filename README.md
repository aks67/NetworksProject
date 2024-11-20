# NetworksProject

## Overview
This project focuses on building large-scale networks, simulating epidemics, rumors, and analyzing large-scale statistical properties. It includes functionalities for generating random networks, handling graph representation using adjacency matrices, supporting graph compression techniques, and capturing performance metrics.

## Current State

### Supported Random Networks:
- **ErdosRenyi Graph**: Random graph where each edge has a fixed probability of being present.
- **Newman Configuration Model Graph**: Graph generation using a predefined degree distribution.
- **Watts-Strogatz Graph**: Small-world graph generation model.
- **Barabasi-Albert Graph**: Scale-free network generation based on preferential attachment.

### Graph Representation:
- **Adjacency Matrix**: The graph is represented as a matrix with edges indicated by boolean values (1 or 0).
  - Additional support for sparse matrix representations like **Adjacency Array** (porting from a previous project).
  - Output formats include naive text format and portable bitmaps.

### Graph Compression:
- **RLE (Run-Length Encoding)**: Basic compression method applied to graph adjacency matrices.

### Web Viewer:
- Basic front-end for visualizing the graphs in the browser. Does not "really work"

### Performance Capturing:
- Capturing and logging performance data for different graph operations (generation, manipulation, etc.).

## Things to Improve and Refactor

- **Class and Code Design**: Enhancing the overall structure, making it more modular and reusable.
- **Templating and Object-Oriented Programming**: Refactoring code to use templates and leverage OOP for flexibility and maintainability.
- **Front-End Code**: Considering a graph web viewer.
- **Performance Optimization**: Enhancing the computational efficiency, particularly for large graphs.

## Goals Moving Forward

- **Sparse Matrix Compression**: Exploring Singular Value Decomposition (SVD) or other techniques to compress adjacency matrices.
- **Statistical Properties of Large Networks**: Implementing approximate algorithms for network analysis and random sampling techniques for large networks.
- **Epidemics/Information Diffusion Models**: Adding support for simulating the spread of epidemics or rumors across networks.
- **Better Sparse Matrix Support**: Improving the support for sparse matrix representations for large graphs.
- **Multi-Threading and Concurrent Processing**: Introducing multi-threading to handle large-scale networks more efficiently, especially for graph generation and statistical analysis.
