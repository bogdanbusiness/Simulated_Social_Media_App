#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"
#include "data_structure.h"
#include "friends.h"
#include "users.h"

void handle_input_friends(char *input, list_graph *friends)
{
	char *commands = strdup(input);
	char *cmd = strtok(commands, "\n ");

	if (!cmd)
		return;

	if (!strcmp(cmd, "add"))
		friend_add(input, friends);
	else if (!strcmp(cmd, "remove"))
		friend_remove(input, friends);
	else if (!strcmp(cmd, "suggestions"))
		suggestions(input, friends);
	else if (!strcmp(cmd, "distance"))
		friend_distance(input, friends);
	else if (!strcmp(cmd, "common"))
		common_friends(input, friends);
	else if (!strcmp(cmd, "friends"))
		(void)cmd;
		// TODO: Add function
	else if (!strcmp(cmd, "popular"))
		(void)cmd;
		// TODO: Add function

	free(commands);
}

void friend_add(char *input, list_graph *friends)
{
	uint16_t current_user, friend_user;
	__users_extract(input, &current_user, &friend_user);

	printf(ADD_CONNECTION,
		   get_user_name(current_user),
		   get_user_name(friend_user));

	lg_add_edge(friends, current_user, friend_user);
}

void friend_remove(char *input, list_graph *friends)
{
	uint16_t current_user, friend_user;
	__users_extract(input, &current_user, &friend_user);

	printf(REMOVED_CONNECTION,
		   get_user_name(current_user),
		   get_user_name(friend_user));

	lg_remove_edge(friends, current_user, friend_user);
}

void friend_distance(char *input, list_graph *friends)
{
	uint16_t current_user, friend_user;
	__users_extract(input, &current_user, &friend_user);

	// Get the distance
	int16_t dist = lg_distance(friends, current_user, friend_user);

	// Check if there is a way to the user
	if (dist == -1) {
		printf(NO_PATH_EXISTS,
			   get_user_name(current_user),
			   get_user_name(friend_user));
	} else {
		printf(PATH_EXISTS,
			   get_user_name(current_user),
			   get_user_name(friend_user),
			   dist);
	}
}

void suggestions(char *input, list_graph *friends) {
	uint16_t current_user;
	__user_extract(input, &current_user);

	printf(SUGGESTIONS, get_user_name(current_user));

	// Create a vector to sort the user ids and initialise it wtih -1
	int16_t *order = (int16_t *)calloc(MAX_PEOPLE, sizeof(*order));
	for (int16_t i = 0; i < MAX_PEOPLE; i++) {
		order[i] = -1;
	}

	uint16_t order_size;

	dll_node *friend_node = friends->neighbors[current_user]->head;
	for (uint16_t i = 0; i < friends->neighbors[current_user]->size; i++) {
		uint16_t friend_id = ((info *)friend_node->data)->connected_node;

		dll_node *suggest_node = friends->neighbors[friend_id]->head;
		for (uint16_t i = 0; i < friends->neighbors[friend_id]->size; i++) {
			uint16_t suggest_id = ((info *)suggest_node->data)->connected_node;
			
			// Dont store the current_user for suggestions
			if (suggest_id != current_user) {
				order[order_size] = suggest_id;
				order_size++;
			}

			suggest_node = suggest_node->next;
		}

		friend_node = friend_node->next;
	}

	bubble_sort(order, order_size, sizeof(*order), compare_uint16);

	for (uint16_t i = 0; i < order_size; i++)
		printf("%s\n", get_user_name(order[i]));


	free(order);
}

void common_friends(char *input, list_graph *friends) {
	uint16_t current_user, friend_user;
	__users_extract(input, &current_user, &friend_user);

	find_common_nodes(friends, current_user, friend_user);

	// Check if there is a way to the user

}

