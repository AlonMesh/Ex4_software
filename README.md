# Overview

This program is a command line tool that allows the user to create and manipulate a graph. The graph is implemented as a linked list of nodes, where each node has a unique integer identifier and a list of edges to other nodes. Each edge has a weight representing the distance or cost between the two nodes it connects. The program supports the following commands:

* A: Build a new graph by specifying the number of nodes and the edges between them.
* B: Insert a new node into the existing graph.
* D: Delete a node from the existing graph.
* P: Print the current state of the graph.
* S: Calculate the shortest path between two nodes using Dijkstra's algorithm.
* T: Calculate the shortest path of "travelling salesman problem" (TSP) in the graph.

## Usage

To use the program, compile it with the command 'make all' and then run it with './graph'. The program will then prompt the user for commands and input as needed to perform the desired actions on the graph. The input for each command is specified in the next section.

For example (if given an input in input.txt file):

    make all
    ./graph < input.txt


## Input

The input for each command is as follows:

* A: The first input is the number of nodes in the graph, followed by one or more lines where each line starts with the letter 'n' and an integer, followed by one or more pairs of integers representing the end node and weight of an edge.
* B: A single integer representing the identifier of the node to insert.
* D: A single integer representing the identifier of the node to delete.
* S: Two integers representing the start and end nodes of the path to calculate.
* T: An integer k and then k diffrent integers, representing the required nodes.
* P: no input needed.

## Output

The output for each command is as follows:

* A: No output.
* B: No output.
* D: No output.
* S: The shortest path distance from the start node to the end node as an integer. If no path exists, -1 is printed.
* T: The length of the shortest Hamiltonian cycle, if it exists. If no such cycle exists, -1 is printed.
* P: A list of the nodes and their edges in the format "Node #X: w(X,Y) = Z, w(X,Y) = Z,..." where X is the identifier of the node, Y is the identifier of an endpoint of an edge, and Z is the weight of the edge.

## Example

The next input:
    
    A 4 n 0 2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2 n 3 T 3 2 1 3 B 5 0 4 2 1 S 2 3 T 4 2 1 3 5 B 6 2 3 1 4 T 4 6 1 3 5 S 3 5

The program's output is:

    TSP shortest path: 6 
    Dijkstra shortest path: 6 
    TSP shortest path: 7 
    TSP shortest path: -1 
    Dijkstra shortest path: -1 
