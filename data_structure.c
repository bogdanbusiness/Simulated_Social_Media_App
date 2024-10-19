#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "users.h"
#include "data_structure.h"
#include "friends.h"
#include "posts.h"

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX_STRING_SIZE	256
#define MAX_USERS 550

/* ----QUEUE IMPLEMENTATION---- */

queue *q_create(unsigned int data_size, unsigned int max_size,
				void (*data_copy)(void *, void *),
				void (*data_delete)(void *))
{
	queue *q = calloc(1, sizeof(*q));
	DIE(!q, "calloc queue failed");

	q->__data_size = data_size;
	q->__max_size = max_size;
	q->__data_duplicator = data_copy;
	q->__data_destructor = data_delete;

	q->buff = malloc(max_size * sizeof(*q->buff));
	DIE(!q->buff, "malloc buffer failed");

	return q;
}

unsigned int q_get_size(queue *q)
{
	return !q ? 0 : q->__size;
}

unsigned int q_is_empty(queue *q)
{
	return (q->__size == 0) ? 1 : 0;
}

void *q_front(queue *q)
{
	if (!q || !q->__size)
		return NULL;

	return q->buff[q->__read_idx];
}

int q_dequeue(queue *q)
{
	if (!q || !q->__size)
		return 0;

	q->__data_destructor(q->buff[q->__read_idx]);
	free(q->buff[q->__read_idx]);

	q->__read_idx = (q->__read_idx + 1) % q->__max_size;
	--q->__size;
	return 1;
}

int q_enqueue(queue *q, void *new_data)
{
	void *data;
	if (!q || q->__size == q->__max_size)
		return 0;

	data = malloc(q->__data_size);
	DIE(!data, "malloc data failed");
	memcpy(data, new_data, q->__data_size);

	q->__data_duplicator(data, new_data);
	q->buff[q->__write_idx] = data;

	q->__write_idx = (q->__write_idx + 1) % q->__max_size;
	++q->__size;

	return 1;
}

void q_clear(queue *q)
{
	unsigned int i;
	if (!q || !q->__size)
		return;

	for (i = q->__read_idx; i != q->__write_idx; i = (i + 1) % q->__max_size) {
		q->__data_destructor(q->buff[i]);
		free(q->buff[i]);
	}

	q->__read_idx = 0;
	q->__write_idx = 0;
	q->__size = 0;
}

void q_free(queue *q)
{
	if (!q)
		return;

	q_clear(q);
	free(q->buff);
	free(q);
}

/* ----DOUBLY LINKED LIST IMPLEMENTATION---- */

dll_head *dll_create(unsigned int data_size)
{
	dll_head *dll = (dll_head *)calloc(1, sizeof(*dll));
	DIE(dll == NULL, "list head memory allocation fail");

	dll->head = NULL;
	dll->tail = NULL;
	dll->data_size = data_size;
	dll->size = 0;

	return dll;
}

dll_node *__dll_node_create(uint16_t user_ID)
{
	// Create a new node and copy data
	dll_node *node = (dll_node *)calloc(1, sizeof(*node));
	DIE(node == NULL, "list node memory allocation fail");

	node->data = (info *)calloc(1, sizeof(info));
	DIE(node->data == NULL, "list node memory allocation fail");

	node->next = NULL;
	node->prev = NULL;

	__info_create(node->data, user_ID);

	return node;
}

void __info_create(info *data, uint16_t user_ID)
{
	data->connected_node = user_ID;
}

void dll_add_first_node(dll_head *list, uint16_t user_ID)
{
	dll_node *node = __dll_node_create(user_ID);
	dll_insert_first_node(list, node);
}

void dll_add_last_node(dll_head *list, uint16_t user_ID)
{
	dll_node *node = __dll_node_create(user_ID);
	dll_insert_last_node(list, node);
}

void dll_insert_first_node(dll_head *list, dll_node *node)
{
	dll_node *cur = list->head;

	// Special case: List is empty
	if (list->size == 0) {
		list->tail = node;
	} else if (list->size > 0) {
		cur->prev = node;
		node->next = list->head;
	}

	list->head = node;
	list->size++;
}

void dll_insert_last_node(dll_head *list, dll_node *node)
{
	dll_node *cur = list->tail;

	// Special case: List is empty
	if (list->size == 0) {
		list->head = node;
	} else if (list->size > 0) {
		cur->next = node;
		node->prev = cur;
	}

	list->tail = node;
	list->size++;
	return;
}

void dll_remove_node(dll_head *list, dll_node *node)
{
	if (!list || list->size == 0 || !node)
		return;

	// Special case: Remove first node
	if (node == list->head) {
		if (node->next)
			node->next->prev = NULL;
		else
			list->tail = list->tail->prev;

		list->head = list->head->next;
	} else if (node == list->tail) {  // Special case: Remove last node
		if (node->prev)
			node->prev->next = NULL;
		else
			list->head = list->head->next;

		list->tail = list->tail->prev;
	} else {  // Normal case
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}

	node->next = NULL;
	node->prev = NULL;

	list->size--;
}

void __info_delete(void *data)
{
    // Legacy code
    ((info *)data)->connected_node = ((info *)data)->connected_node;
}


void dll_free(dll_head **pp_list, void (*info_delete)(void *))
{
	dll_node *cur = (*pp_list)->head;
	dll_node *aux;

	while (cur) {
        // printf("am sters %d\n", ((info *)cur->data)->connected_node);
		info_delete(cur->data);
		free(cur->data);
		aux = cur->next;
		free(cur);
		cur = aux;
	}

	free(*pp_list);
	*pp_list = NULL;
}

/* Graful este ORIENTAT */

list_graph* lg_create(int nodes)
{
	list_graph *graph = (list_graph *)calloc(1, sizeof(*graph));
    graph->nodes = nodes;

    graph->neighbors = (dll_head **)calloc(nodes, sizeof(dll_head *));

    for (int i = 0; i < graph->nodes; i++)
        graph->neighbors[i] = dll_create(sizeof(int));

    return graph;
}

/* Returneaza 1 daca exista muchie intre cele doua noduri, 0 in caz contrar */
int lg_has_edge(list_graph* graph, uint16_t src, uint16_t dest)
{
    dll_node *node = graph->neighbors[src]->head;
    
    for (unsigned int i = 0; i < graph->neighbors[src]->size; i++) {
        if (((info *)node->data)->connected_node == dest)
            return 1;
        
        node = node->next;
    }

    return 0;
}

/* Adauga o muchie intre nodurile primite ca parametri */
void lg_add_edge(list_graph* graph, uint16_t src, uint16_t dest)
{
    if (!lg_has_edge(graph, src, dest)) {
        dll_add_last_node(graph->neighbors[src], dest);
        dll_add_last_node(graph->neighbors[dest], src);
    }
}

/* Elimina muchia dintre nodurile primite ca parametri */
void lg_remove_edge(list_graph* graph, uint16_t src, uint16_t dest)
{
    dll_node *node = graph->neighbors[src]->head;
    for (unsigned int i = 0; i < graph->neighbors[src]->size; i++) {
        if (((info *)node->data)->connected_node == dest) {
            dll_remove_node(graph->neighbors[src], node);
            free(node->data);
            free(node);
            break;
        }
        
        node = node->next;
    }

    node = graph->neighbors[dest]->head;
    for (unsigned int i = 0; i < graph->neighbors[dest]->size; i++) {
        if (((info *)node->data)->connected_node == src) {
            dll_remove_node(graph->neighbors[dest], node);
            free(node->data);
            free(node);
            return;
        }
        
        node = node->next;
    }
}

/* Elibereaza memoria folosita de lista de adiacenta a grafului */
void lg_free(list_graph* graph)
{
    // printf("am %d\n", graph->nodes);
    for (int i = 0; i < graph->nodes; i++)
        dll_free(&graph->neighbors[i], __info_delete);
    
    free(graph->neighbors);
    free(graph);
}

int16_t __bfs(list_graph* graph, uint16_t start, uint16_t target, uint16_t size)
{
    uint16_t *dist = (uint16_t *)calloc(size, sizeof(uint16_t));
    uint16_t* color = (uint16_t *)calloc(size, sizeof(uint16_t));
	queue * next_nodes = q_create(sizeof(uint16_t *), size, __copy_int, __delete_int);

    // Initiate colors vector
	for (int i = 0; i < size; i++) {
		color[i] = 0;
        dist[i] = 0;
    }

    // Queue and visit the first vector
	color[start] = 1;
	q_enqueue(next_nodes, &start);

    // BFS
	while(!q_is_empty(next_nodes)) {
        // Get the next_node
		uint16_t front_node = *(uint16_t *)q_front(next_nodes);

        // Check if the next node is the target node
        if (front_node == target) {
            uint16_t result = dist[front_node];
            free(dist);
            free(color);
            q_free(next_nodes);
            return result;
        }

		q_dequeue(next_nodes);

		dll_node *node = graph->neighbors[front_node]->head;
        // Search the graph for unvisited neighbours
		for (unsigned int i = 0; i < graph->neighbors[front_node]->size; i++) {
            uint16_t neighbour = ((info *)node->data)->connected_node;

			if (color[neighbour] == 0) {
            	color[neighbour] = 1;
            	q_enqueue(next_nodes, &neighbour);
                dist[neighbour] = dist[front_node] + 1;
        	}

			node = node->next;
		}

        // Finish visiting the node
    	color[front_node] = 2;
	}

    free(dist);
    free(color);
	q_free(next_nodes);
    return -1;
}

void __copy_int(void *data, void *new_data) {
    *(uint16_t *)data = *(uint16_t *)new_data;
}

void __delete_int(void *data) {
    *(uint16_t *)data = 0;
}

int16_t lg_distance(list_graph *graph, uint16_t src, uint16_t dest) {
    return __bfs(graph, src, dest, MAX_USERS);
}

#define MAX_NODES 1000

int visited[MAX_NODES];
int common_nodes[MAX_NODES];
int common_nodes_count = 0;

int compare(const void * a, const void * b) {
    return ( *(int*)b < *(int*)a );
}


void dfs(list_graph *graph, int node, int target, int source) {
    dll_node *node_it, *node_it_source, *node_it_target;

    visited[node] = 1;

    // Iterate over the neighbors of the current node
    for (node_it = graph->neighbors[node]->head; node_it != NULL; node_it = node_it->next) {
        int neighbor = *(uint16_t *)node_it->data;

        // If the neighbor has not been visited, visit it
        if (!visited[neighbor]) {
            dfs(graph, neighbor, target, source);
        }

        // If the current node is not the source or target, check if it is a neighbor of both the source and target
        if (node != source && node != target) {
            int is_neighbor_of_source = 0, is_neighbor_of_target = 0;

            for (node_it_source = graph->neighbors[source]->head; node_it_source != NULL; node_it_source = node_it_source->next) {
                int neighbor_source = *(uint16_t *)node_it_source->data;
                if (node == neighbor_source) {
                    is_neighbor_of_source = 1;
                    break;
                }
            }

            for (node_it_target = graph->neighbors[target]->head; node_it_target != NULL; node_it_target = node_it_target->next) {
                int neighbor_target = *(uint16_t *)node_it_target->data;
                if (node == neighbor_target) {
                    is_neighbor_of_target = 1;
                    break;
                }
            }

            if (is_neighbor_of_source && is_neighbor_of_target) {
                // Check if the node has already been added to the common nodes list
                int is_already_added = 0;
                for (int i = 0; i < common_nodes_count; i++) {
                    if (common_nodes[i] == node) {
                        is_already_added = 1;
                        break;
                    }
                }

                // If the node hasn't been added to the common nodes list, add it
                if (!is_already_added) {
                  	//printf("%s %s %s\n", get_user_name(node), get_user_name(neighbor), get_user_name(target));
                    common_nodes[common_nodes_count++] = node;
                }
            }
        }
    }
}

void find_common_nodes(list_graph *graph, int node1, int node2) {
    // Initialize visited array
    for (int i = 0; i < graph->nodes; i++) {
        visited[i] = 0;
    }    
	for (int i = 0; i < MAX_NODES; i++) {
        common_nodes[i] = 0;
    }
 	common_nodes_count = 0;
    // Perform DFS from node1 to node2
    dfs(graph, node1, node2, node1);
	
	 qsort(common_nodes, common_nodes_count, sizeof(int), compare);

	

	int rsp=1;

	if(common_nodes_count==0)
		rsp=-1;
			if (rsp == -1) {
		printf(NO_COMMON_FRIENDS,
			   get_user_name(node1),
			   get_user_name(node2));
	} else {
	printf(COMMON_FRIENDS,
		   get_user_name(node1),
		   get_user_name(node2));
		for (int i = 0; i < common_nodes_count; i++) {
        printf("%s\n", get_user_name(common_nodes[i]));
    }
	}
	
}

////////////////////POSTS////////////////////////////

posts* posts_create(int size) {
    posts* new_posts = (posts*)malloc(size * sizeof(posts));
    if (new_posts == NULL) {
        return NULL; // return NULL if memory allocation failed
    }

    // Initialize each post
    for (int i = 0; i < size; i++) {
        new_posts[i].id = 0;
        memset(new_posts[i].titlu, 0, sizeof(new_posts[i].titlu));
        new_posts[i].user_id = 0;
        // Initialize events field as needed, depending on your list_graph implementation
    }

	new_posts->num_posts=0;
	printf("AM CREATE POSTS\n");
    return new_posts;
}

void posts_free(posts* postari)
{
	postari=NULL;
	free(postari);
   return;
}