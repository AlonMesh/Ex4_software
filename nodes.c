#include "header.h"
#define INF 99999
// A, 4 ,n ,0 ,2 5 3 3 n 2 0 4 1 1 n 1 3 7 0 2
char build_graph_cmd(node **head) // A
{
	int n_n;

	char space;
	scanf(" %d", &n_n); // 4

	int graph_size;
	graph_size = n_n;

	if (graph_size == 0)
	{
		return 'k';
	}

	//   start to build the graph

	(*head)->node_num = 0;
	(*head)->edges = NULL;
	(*head)->next = NULL;

	// neybears
	node *temp;
	temp = *head;

	// the graph
	for (int i = 1; i < graph_size; i++) {
		node *Neighbor_node = NULL;
		if ((Neighbor_node = (node *)malloc(sizeof(node))) == NULL) {
			printf("Not enough memory, exit program\n");
			exit(-1);
		}

		Neighbor_node->node_num = i;
		Neighbor_node->edges = NULL;
		Neighbor_node->next = NULL;
		temp->next = Neighbor_node;
		temp = temp->next;
	}

	int num;
	while (scanf(" %c", &space) == 1 && space == 'n')
	{
		scanf(" %d", &num);
		node *n = *head;

		for (size_t i = 0; i < num; i++)
		{
			n = n->next;
		}

		int x, w;
		edge **next = &(n->edges);

		while (scanf(" %d %d", &x, &w) == 2)
		{
			// find x
			node *endpoint = *head;
			for (size_t i = 0; i < x; i++)
			{
				endpoint = endpoint->next;
			}

			// create edge
			edge *Neighbor_ed = NULL;
			if ((Neighbor_ed = (edge *)malloc(sizeof(edge))) == NULL)
			{
				printf("Not enough memory, exit program\n");
				exit(-1);
			}

			Neighbor_ed->endpoint = endpoint;
			Neighbor_ed->weight = w;

			// add edge
			*next = Neighbor_ed;
			next = &(Neighbor_ed->next);
		}
		*next = NULL;
	}

	return space;
}

/********************************************************************************************************/
void insert_node_cmd(node **head) // B
{
	int new_node_data; // the new data
	scanf(" %d", &new_node_data);
	node *temp;
	temp = *head;
	int flag_exist = 0;
	// chack if its exist
	while (temp != NULL && flag_exist == 0)
	{

		if (temp->node_num == new_node_data)
		{
			flag_exist = 1;
			break;
		}
		temp = temp->next;
	}

	node *new_node = calloc(1, sizeof(node));
	
	// flag_exist = 0: not exist
	if (flag_exist == 0)
	{
		new_node->node_num = new_node_data;
		new_node->edges = NULL;

		temp = *head;

		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = new_node;
	}

	else
	{
		new_node = temp;
		new_node->node_num = new_node_data;

		edge *temp_edge = new_node->edges;
		while (temp_edge != NULL)
		{
			edge *del_edge = temp_edge;
			temp_edge = temp_edge->next;
			free(del_edge);
			del_edge = NULL;
		}

		new_node->edges = NULL;
	}

	int x, w;
	while (scanf(" %d %d", &x, &w) == 2)
	{
		// find x
		node *endpoint = *head;
		while (endpoint->node_num != x) {
			endpoint = endpoint->next;
		}

		// create edge
		edge *new_edge = calloc(1, sizeof(edge));

		new_edge->endpoint = endpoint;
		new_edge->weight = w;

		// add edge
		new_edge->next = new_node->edges;
		new_node->edges = new_edge;
	}
}

/****************************************************************************************************************************************/

void delete_node_cmd(node **head) // D
{
	node *temp_no;
	temp_no = *head;

	int data_delete;
	scanf(" %d", &data_delete);


	// first we delete the edges that theirs enpoints is the deleted Node.
	while (temp_no != NULL)
	{

		// First we checks an edge case when a Node (or several) has no edges. 
		if (temp_no->edges == NULL) {
			while (temp_no->edges == NULL) {
				temp_no = temp_no->next;

				if (temp_no == NULL) {
					break;
				}
			}
		}


		edge *temp_ed;
		temp_ed = temp_no->edges;

		if (temp_ed == NULL) {
			printf("Node %d is nulll\n", temp_no->node_num);
		}

		// head case
		if (temp_ed->endpoint != NULL && data_delete == temp_ed->endpoint->node_num)
		{
			edge *del_ed;
			temp_no->edges = temp_no->edges->next;
			del_ed = temp_ed;
			temp_ed = temp_ed->next;
			free(del_ed);
			del_ed = NULL;
		}

		while (temp_ed->next != NULL && temp_ed->next->next != NULL)
		{
			if (data_delete == temp_ed->next->endpoint->node_num)
			{
				edge *del_ed;
				del_ed = temp_ed->next;

				temp_ed->next = temp_ed->next->next;
				free(del_ed);
				del_ed = NULL;
			}

			temp_ed = temp_ed->next;
		}
		// tail case

		if (temp_ed->next != NULL && data_delete == temp_ed->next->endpoint->node_num)
		{
			edge *tail;
			tail = temp_no->edges;

			while (tail->next->next != NULL)
			{
				tail = tail->next;
			}
			edge *last = tail->next;
			tail->next = NULL;
			free(last);
			last = NULL;
		}

		temp_no = temp_no->next;
	}

	temp_no = *head;

	if (temp_no->node_num == data_delete)
	{
		node *del_point_node;
		del_point_node = temp_no;
		(*head) = (*head)->next;
		temp_no = temp_no->next;

		free(del_point_node);
		del_point_node = NULL;
	}
	else
	{
		while (temp_no->next != NULL)
		{
			if (data_delete == temp_no->next->node_num)
			{
				node *del_point_node;
				del_point_node = temp_no->next;
				temp_no->next = temp_no->next->next;
				free(del_point_node);
				del_point_node = NULL;
				break;
			}
			temp_no = temp_no->next;
		}
	}
}

/*******************************************************************************************************************************************/
void deleteGraph_cmd(node **head) {
    node *temp_no;
    temp_no = *head;

    // Iterate through all the nodes in the graph
    while (temp_no != NULL) {
        edge *temp_ed;
        temp_ed = temp_no->edges;

        // Iterate through all the edges connected to the current node
        while (temp_ed != NULL) {
            edge *del_ed;
            temp_no->edges = temp_no->edges->next;
            del_ed = temp_ed;
            temp_ed = temp_ed->next;
            free(del_ed);
			del_ed = NULL;
        }

        node *del_point_node;
        del_point_node = temp_no;

        (*head) = (*head)->next;
        temp_no = temp_no->next;

        // Remove the node from the graph
        if (del_point_node != *head) {
            free(del_point_node);
			del_point_node = NULL;
        }
    }

    // Reset the head pointer
    *head = NULL;
}
/******************************************************************************************************************************************/

void shortsPath_cmd(node *head)
{
	int s = 0, t = 0;
	scanf(" %d %d", &s, &t);

	dijkstra(head, s,t);
}

/******************************************************************************************************************************************/

void dijkstra(node *head, int start, int end) {
    node *temp = head;
    int numNodes = 0;
    while(temp != NULL){
        numNodes++;
        temp = temp->next;
    }
    temp = head;

    // Initialize the distance of all nodes to infinity
    while (temp != NULL) {
        temp->delta = INF;
        temp = temp->next;
    }
    // Set the distance of the start node to 0
    temp = head;
    while (temp != NULL && temp->node_num != start) {
        temp = temp->next;
    }
    if (temp != NULL) {
        temp->delta = 0;
    }

    // Create a min heap to store the unvisited nodes
    int heapSize = numNodes;
    node** heap = (node**)calloc(heapSize, sizeof(node*));
    temp = head;
    for(int i = 0; i < heapSize; i++){
        heap[i] = temp;
        temp = temp->next;
    }

    while (heapSize > 0) {
        // Extract the node with the smallest distance from the min heap
        node *curr = heap[0];
        int currIndex = 0;
        for (int i = 1; i < heapSize; i++) {
            if (heap[i]->delta < curr->delta) {
                curr = heap[i];
                currIndex = i;
            }
        }
        node *temp = heap[currIndex];
        heap[currIndex] = heap[heapSize - 1];
        heap[heapSize - 1] = temp;
        heapSize--;

        // Update the distances of the neighboring nodes
        edge *currEdge = curr->edges;
        while (currEdge != NULL) {
            int newDist = curr->delta + currEdge->weight;
            if (newDist < currEdge->endpoint->delta && newDist != INF) {
                currEdge->endpoint->delta = newDist;
				heap = (node**)realloc(heap, sizeof(node*) * (heapSize + 1));
                heap[heapSize] = currEdge->endpoint;
                heapSize++;
            }
            currEdge = currEdge->next;
        }
    }
    temp = head;
    while (temp != NULL && temp->node_num != end) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("-1\n");
    } else {
            printf("Dijkstra shortest path: %d\n ", temp->delta); // space or not spcae??
	}
}

/******************************************************************************************************************************************/

int dijkstraInteger(node *head, int start, int end) {
    node *temp = head;
    int numNodes = 0;
    while(temp != NULL){
        numNodes++;
        temp = temp->next;
    }
    temp = head;

    // Initialize the distance of all nodes to infinity
    while (temp != NULL) {
        temp->delta = INF;
        temp = temp->next;
    }
    // Set the distance of the start node to 0
    temp = head;
    while (temp != NULL && temp->node_num != start) {
        temp = temp->next;
    }
    if (temp != NULL) {
        temp->delta = 0;
    }

    // Create a min heap to store the unvisited nodes
    int heapSize = numNodes;
	node** heap = (node**)calloc(heapSize, sizeof(node*));
	temp = head;
    for(int i = 0; i < heapSize; i++){
        heap[i] = temp;
        temp = temp->next;
    }

    while (heapSize > 0) {
        // Extract the node with the smallest distance from the min heap
        node *curr = heap[0];
        int currIndex = 0;
        for (int i = 1; i < heapSize; i++) {
            if (heap[i]->delta < curr->delta) {
                curr = heap[i];
                currIndex = i;
            }
        }
        node *temp = heap[currIndex];
        heap[currIndex] = heap[heapSize - 1];
        heap[heapSize - 1] = temp;
        heapSize--;

        // Update the distances of the neighboring nodes
        edge *currEdge = curr->edges;
        while (currEdge != NULL) {
            int newDist = curr->delta + currEdge->weight;
            if (newDist < currEdge->endpoint->delta && newDist != INF) {
                currEdge->endpoint->delta = newDist;
				heap = (node**)realloc(heap, sizeof(node*) * (heapSize + 1));
                heap[heapSize] = currEdge->endpoint;
                heapSize++;
            }
            currEdge = currEdge->next;
        }
    }
    temp = head;
    while (temp != NULL && temp->node_num != end) {
        temp = temp->next;
    }
    if (temp == NULL) {
        return -1;
    } else {
            return temp->delta; // space or not spcae??
	}
}

/*************************************************************************************************************************************/

void TSP_cmd(node *head)
{
	int x = INF;
	int *min_path = &x;
	int k_num = 0;
	scanf(" %d", &k_num);
	int *arr;
	arr = (int *)malloc(sizeof(int) * k_num);

	for (int i = 0; i < k_num; i++)
	{
		scanf(" %d", &arr[i]);
	}

	permute(arr, 0, k_num - 1, k_num, head, min_path);
	
	if (x == INF) {
		x = -1;
	}
	printf("TSP shortest path: %d \n", x); //space?
	free(arr);
	arr = NULL;
	min_path = NULL;
}

/**************************************************************************************************************************************/
int Dir(node *head, int t, int s)
{
	node *temp_no;
	temp_no = head;
	node *s_start;
	node *wanted;

	// the start - inf all the ways exept the first one
	while (temp_no != NULL)
	{
		temp_no->delta = INF;

		if (temp_no->node_num == s)
		{
			temp_no->delta = 0;
			s_start = temp_no;
		}

		temp_no = temp_no->next;
	}

	edge *neb_ed;
	while (s_start->edges != NULL)
	{
		neb_ed = s_start->edges;

		while (neb_ed != NULL)
		{
			if (neb_ed->weight <= neb_ed->endpoint->delta)
			{
				neb_ed->endpoint->delta = ((s_start->delta) + (neb_ed->weight));
			}

			neb_ed = neb_ed->next;
		}
		s_start = s_start->edges->next->endpoint;
	}
	wanted = head;
	while (wanted->next != NULL && wanted->node_num != t)
	{
		wanted = wanted->next;
	}

	if (wanted->delta == INF)
	{
		return -1;
	}

	return (wanted->delta);
}
/**************************************************************************************************************************************/
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
/**************************************************************************************************************************************/

void permute(int *a, int l, int r, int size, node *head, int *min_path)
{
	if (l == r)
	{
		int sumWay = 0;

		for (int i = 0; i < size - 1; i++)
		{
			if (i + 1 < size)
				sumWay += dijkstraInteger(head, a[i], a[i + 1]);
		}
		if (sumWay < *min_path && sumWay != -1)
		{
			*min_path = sumWay;
		}
	}
	else
	{
		for (int i = l; i <= r; i++)
		{
			swap((a + l), (a + i));
			permute(a, l + 1, r, size, head, min_path);
			swap((a + l), (a + i));
		}
	}
}
