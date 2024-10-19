#ifndef DATA_STRUCTURE_H
#define DATA_STRUCUTRE_H

#include <stdint.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX_STRING_SIZE	256


#define DIE(assertion, call_description)                       \
	do {                                                       \
		if (assertion) {                                       \
			fprintf(stderr, "(%s, %d): ", __FILE__, __LINE__); \
			perror(call_description);                          \
			exit(errno);                                       \
		}                                                      \
	} while (0)

/* ----QUEUE IMPLEMENTATION---- */

typedef struct
{
	// Buffer that stored the elements
	void **buff;

	// Size of data held by the queue
	unsigned int __data_size;

	// Max size of queue
	unsigned int __max_size;
	// Size of queue
	unsigned int __size;

	// Index used to read from queue
	unsigned int __read_idx;
	// Index used to write to queue
	unsigned int __write_idx;

	// Pointer function for data duplication
	void (*__data_duplicator)(void *, void *);
	// Pointer function for data deletion
	void (*__data_destructor)(void *);
} queue;

/**
 * @brief Creates a queue
 * @param data_size Size of data stored by the queue
 * @param max_size Maximum size of the queue
 * @param data_copy Pointer function for copying data
 * @param data_delete Pointer function for deleting data
 * @return Returns a pointer to the newly created queue
 */
queue *q_create(unsigned int data_size, unsigned int max_size,
				void (*data_copy)(void *, void *),
				void (*data_delete)(void *));

/**
 * @brief Returns the size of the queue
 */
unsigned int q_get_size(queue *q);

/**
 * @brief Returns in positive logic if the queue is empty
 */
unsigned int q_is_empty(queue *q);

/**
 * @brief Returns the data stored at the front of the queue
 */
void *q_front(queue *q);

/**
 * @brief Removes the element at the front of the queue
 * @return Returns if the operation was succesful or not (positive logic)
 */
int q_dequeue(queue *q);

/**
 * @brief Adds an element to the back of the queue
 * @param new_data The new data element added to the queue
 * @returns Returns if the operation was succesful or not (positive logic)
 */
int q_enqueue(queue *q, void *new_data);

/**
 * @brief Clears the queue without deleting it
 */
void q_clear(queue *q);

/**
 * @brief Frees all the memory allocated
 */
void q_free(queue *q);

/* ----DOUBLY LINKED LIST IMPLEMENTATION---- */

/// @brief Node of the doubly linked list
typedef struct dll_node
{
	void *data;
	struct dll_node *prev, *next;
} dll_node;

/// @brief Structure for what data will contain
typedef struct info
{
	uint16_t connected_node;
} info;

/// @brief Head of the doubly linked list
typedef struct dll_head
{
	dll_node *head;
	dll_node *tail;
	unsigned int size;
	unsigned int data_size;
} dll_head;

/**
 * @brief Creates a doubly linked list (DLL)
 * @param data_size Size of data stored by the DLL
 * @return Returns a pointer to the newly created DLL
 */
dll_head *dll_create(unsigned int data_size);

/**
 * @brief Helper function that creates a node
 */
dll_node *__dll_node_create(uint16_t user_ID);

/**
 * @brief Helper function that creates the info structure inside the nodes
 */
void __info_create(info *data, uint16_t user_ID);

/**
 * @brief Adds a new node at the start of the list
 */
void dll_add_first_node(dll_head *list, uint16_t user_ID);

/**
 * @brief Adds a new node at the end of the list
 */
void dll_add_last_node(dll_head *list, uint16_t user_ID);

/**
 * @brief Inserts a node at the nth position of the list
 * @param node The node that will be inserted into the list
 */
void dll_insert_first_node(dll_head *list, dll_node *node);

/**
 * @brief Inserts a node at the nth position of the list
 * @param node The node that will be inserted into the list
 */
void dll_insert_last_node(dll_head *list, dll_node *node);

/**
 * @brief Removes a node from the list
 * @param node The node that will be deleted from the list
 */
void dll_remove_node(dll_head *list, dll_node *node);

/**
 * @brief Helper function that deletes the info structure inside the nodes
 */
void __info_delete(void *data);

/**
 * @brief Deletes the entire linked list
 */
void dll_free(dll_head **pp_list, void (*info_delete)(void *));

void dll_print_int(dll_head *dll);

/* ----GRAPH IMPLEMENTATION---- */

typedef struct {
	dll_head** neighbors;
	uint16_t nodes;
} list_graph;

/**
 * 
*/
list_graph* lg_create(int nodes);

/**
 * 
*/
int lg_has_edge(list_graph* graph, uint16_t src, uint16_t dest);

/**
 * 
*/
void lg_add_edge(list_graph* graph, uint16_t src, uint16_t dest);

/**
 * 
*/
void lg_remove_edge(list_graph* graph, uint16_t src, uint16_t dest);

/**
 * 
*/
void lg_free(list_graph* graph);

int16_t lg_distance(list_graph *graph, uint16_t src, uint16_t dest);

int16_t __bfs(list_graph* graph, uint16_t start, uint16_t target, uint16_t size);

void find_common_nodes(list_graph *graph, int node1, int node2);

/* ----GRAPH IMPLEMENTATION---- */

void __copy_int(void *data, void *new_data);

void __delete_int(void *data);
////////////posts////////////////

typedef struct {
     int id;
     char titlu[300];
     int user_id; 
	 int num_posts;
     list_graph* events;
} posts;

posts* posts_create(int size);
void posts_free(posts* postari);
#endif /* DATA_STRUCTURE_H */