#include "header.h"
#define INF 99999

// Building a graph
char build_graph_cmd(node **head) // A
{
	int n_n;

	char space;
	scanf(" %d", &n_n); 

	int graph_size = n_n;

	if (graph_size == 0) // if the amount of nodes is 0, it is not a graph
	{
		return 'k';
	}

	if ((*head) == NULL)
	{
		(*head) = (node *)malloc(sizeof(node));

		if ((*head) == NULL)
		{
			printf("Memory allocation failed!\n");
			exit(-1);
		}
	}

	// Setting the first node (node 0) manually
	(*head)->node_num = 0;
	(*head)->edges = NULL;
	(*head)->next = NULL;

	node *temp;
	temp = *head;

	// Creating all the other nodes, such that a LinkedList of nodes is recived.
	for (int i = 1; i < graph_size; i++) {
		node *Neighbor_node = (node *)malloc(sizeof(node));

		Neighbor_node->node_num = i;
		Neighbor_node->edges = NULL;
		Neighbor_node->next = NULL;
		Neighbor_node->delta = 0;
		temp->next = Neighbor_node;
		temp = temp->next;
	}

	// The next section is adding edges for each node
	int num;
	while (scanf(" %c", &space) == 1 && space == 'n')
	{
		scanf(" %d", &num);
		node *n = *head;

		for (int i = 0; i < num; i++)
		{
			n = n->next;
		}

		int x, w;
		edge **next = &(n->edges);

		while (scanf(" %d %d", &x, &w) == 2)
		{
			// Find the current node
			node *endpoint = *head;
			for (size_t i = 0; i < x; i++)
			{
				endpoint = endpoint->next;
			}

			// Creating an edge
			edge *Neighbor_ed = (edge *)malloc(sizeof(edge));

			Neighbor_ed->endpoint = endpoint;
			Neighbor_ed->weight = w;
			Neighbor_ed->next = NULL;

			// Adding the created edge to the current node
			*next = Neighbor_ed;
			next = &(Neighbor_ed->next);
		}
		*next = NULL;
	}

	return space;
}

// Inserting a new node to the graph, or editing existing one
void insert_node_cmd(node **head) // B
{
	int new_node_data; // the new data
	scanf(" %d", &new_node_data);
	node *temp = *head;
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

	node *new_node = (node *) malloc(sizeof(node));
	
	// flag_exist = 0: not exist
	if (flag_exist == 0)
	{
		new_node->node_num = new_node_data;
		new_node->edges = NULL;
		new_node->next = NULL;
		new_node->delta = 0;

		temp = *head;

		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = new_node;
	}

	else
	{
		free(new_node);
		new_node = NULL;
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
		edge *new_edge = (edge *) malloc(sizeof(edge));

		new_edge->endpoint = endpoint;
		new_edge->weight = w;
		new_edge->next = NULL;

		// add edge
		new_edge->next = new_node->edges;
		new_node->edges = new_edge;
	}
}

// Delete a given node, including all the edges that are coming from it and get into it
void delete_node_cmd(node **head) // D
{
	node *temp_no;
	temp_no = *head;

	int data_delete;
	scanf(" %d", &data_delete);


	// Delete the edges that theirs enpoints is the deleted Node.
	while (temp_no != NULL)
	{
		// Checks an edge case when a Node (or several) has no edges. 
		if (temp_no->edges == NULL) {
			while (temp_no->edges == NULL) {
				temp_no = temp_no->next;

				if (temp_no == NULL) {
					printf("broke\n");
					break;
				}
			}
		}
		if (temp_no == NULL) {
			break;
		}

		edge *temp_ed;
		temp_ed = temp_no->edges;

		// Head case - when the first element in the LinkedList shall be removed
		if (temp_ed->endpoint != NULL && data_delete == temp_ed->endpoint->node_num)
		{
			edge *del_ed;
			temp_no->edges = temp_no->edges->next;
			del_ed = temp_ed;
			temp_ed = temp_ed->next;
			free(del_ed);
			del_ed = NULL;
		}

		// "Normal" case - when an element (not first or last) in the LinkedList shall be removed
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

		// Tail case - when the last elemnt in the LinkedList shall be removed
		if (temp_ed->next != NULL && data_delete == temp_ed->next->endpoint->node_num)
		{
			edge *tail;
			tail = temp_no->edges;

			while (tail->next != NULL && tail->next->endpoint->node_num != data_delete) {
				tail = tail->next;
			}

			if (tail->next != NULL) {
				edge *last = tail->next;
				tail->next = NULL;
				free(last);
				last = NULL;
			}
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

		edge *deledge = del_point_node->edges;

		while (deledge != NULL)
		{
			edge *tmpedgedel = deledge;
			deledge = deledge->next;
			free(tmpedgedel);
		}

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
				edge *deledge = del_point_node->edges;

				while (deledge != NULL)
				{
					edge *tmpedgedel = deledge;
					deledge = deledge->next;
					free(tmpedgedel);
				}
				free(del_point_node);
				del_point_node = NULL;
				break;
			}
			temp_no = temp_no->next;
		}
	}
}

// Deleting and "free" any node and edge of the graph.
void deleteGraph_cmd(node **head) {
    node *temp_no, *del_point_node;
    edge *temp_ed, *del_ed;

    // Iterate through all the nodes in the graph
    temp_no = *head;
    while (temp_no != NULL) {
        temp_ed = temp_no->edges;

        // Iterate through all the edges connected to the current node
        while (temp_ed != NULL) {
            del_ed = temp_ed;
            temp_ed = temp_ed->next;
            free(del_ed);
			del_ed = NULL;
        }

        del_point_node = temp_no;
        temp_no = temp_no->next;

        free(del_point_node);
		del_point_node = NULL;

    }

    // Reset the head pointer
    *head = NULL;
}

// A function that scans inputs and send to dijkstra
void shortsPath_cmd(node *head)
{
	int s = 0, t = 0;
	scanf(" %d %d", &s, &t);

	dijkstra(head, s,t);
}

// Calculating the least heavy path from node S to node D by dijkstra's algorithm
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
	node** heap = (node**)malloc(heapSize * sizeof(node*));    
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
				heap = (node**)realloc(heap, (heapSize + 1) * sizeof(node*));
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
	free(heap);
	heap = NULL;
    if (temp == NULL) {
        printf("-1\n");
    } else {
			if (temp->delta == INF) {
				temp->delta = -1;
			}
            printf("Dijsktra shortest path: %d \n", temp->delta);
	}
}

int dijkstraInteger(node *head, int start, int end) {
    node *temp = head;
    int numNodes = 0;
    while(temp != NULL) {
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
	node** heap = (node**)malloc(heapSize * sizeof(node*));
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
				heap = (node**)realloc(heap, (heapSize + 1) * sizeof(node*));
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

	free(heap);
	heap = NULL;
    if (temp == NULL) {
        return -1;
    } else {
            return temp->delta;
	}
}

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
	printf("TSP shortest path: %d \n", x);
	free(arr);
	arr = NULL;
	min_path = NULL;
}

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

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
