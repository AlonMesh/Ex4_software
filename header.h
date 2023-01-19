#include <stdio.h>
#include <stdlib.h>
#ifndef GRAPH_
#define GRAPH_

typedef struct GRAPH_NODE_ node;

typedef struct edge_
{
    int weight;
    node *endpoint;
    struct edge_ *next;
} edge;

typedef struct GRAPH_NODE_
{
    int node_num;
    edge *edges;
    struct GRAPH_NODE_ *next;
    int delta;
} node;

char build_graph_cmd(node **);
void cmd_print_graph(node *);
void insert_node_cmd(node **);
void delete_node_cmd(node **);

void deleteGraph_cmd(node **);

void shortsPath_cmd(node *);
void TSP_cmd(node *);

void swap(int *, int *);
void permute(int *, int, int, int, node *, int *);
void dijkstra(node *, int , int );


#endif