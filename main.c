#include "header.h"

void cmd_print_graph(node *head)
{
	edge *currEdge = NULL;

	if (head == NULL)
	{
		printf("The graph is empty!\n");
		return;
	}

	while (head != NULL)
	{
		currEdge = head->edges;

		printf("Node #%d:\n", head->node_num);

		if (currEdge == NULL)
			printf("No edges are coming out from the node.");

		else
		{
			while (currEdge != NULL)
			{
				printf("w(%d,%d) = %d", head->node_num, currEdge->endpoint->node_num, currEdge->weight);
				currEdge = currEdge->next;

				if (currEdge != NULL)
					printf(", ");
			}
		}

		printf("\n");

		head = head->next;
	}
}

int main()
{
	node *head = (node *)malloc(sizeof(node));
	if (head == NULL)
	{
		printf("Memory allocation failed!\n");
		exit(-1);
	}

	char n_n = 'p';

	int is_first = 1;

	// Several chars can recived, each send to an unique function
	// Scanning input till it is over
	while ((scanf(" %c", &n_n) != -1 && n_n != 'n'))
	{
		if (n_n == 'A')
		{
			if (is_first == 1)
			{
				n_n = build_graph_cmd(&head);
				is_first = 0;
			}
			else
			{
				// If the graph is already built, deleting the exists one
				deleteGraph_cmd(&head);
				//free(head);
				
				node *tempHead = (node *)malloc(sizeof(node));
				if (tempHead == NULL)
				{
					printf("Memory allocation failed!\n");
					exit(-1);
				}
				
				head = tempHead;
				// free(tempHead);
				// tempHead = NULL;

				n_n = build_graph_cmd(&head);
				// Assumed that input is correct
			}
		}

		if (n_n == 'B')
		{
			insert_node_cmd(&head);
		}

		if (n_n == 'D')
		{
			delete_node_cmd(&head);
		}
		if (n_n == 'S')
		{
			shortsPath_cmd(head);
		}

		if (n_n == 'T')
		{
			TSP_cmd(head);
		}
	}

	//cmd_print_graph(head); // for self bebugging

	// Free the leaked memory
	deleteGraph_cmd(&head);

	//cmd_print_graph(head); // for self bebugging

	free(head);
	head = NULL;
	return 0;
}