#ifndef FRIENDS_H
#define FRIENDS_H

#define MAX_COMMAND_LEN 500
#define MAX_PEOPLE 550

#define ADD_CONNECTION     "Added connection %s - %s\n"
#define REMOVED_CONNECTION "Removed connection %s - %s\n"
#define NO_PATH_EXISTS     "There is no way to get from %s to %s\n"
#define PATH_EXISTS        "The distance between %s - %s is %d\n"
#define SUGGESTIONS        "Suggestions for %s:\n"
#define COMMON_FRIENDS     "The common friends between %s and %s are:\n"
#define NO_COMMON_FRIENDS  "No common friends for %s and %s\n"

/**
 * Function that handles the calling of every command from task 1
 *
 * Please add any necessary parameters to the functions
*/
void handle_input_friends(char *input, list_graph *friends);
void friend_add(char *input, list_graph *friends);
void friend_remove(char *input, list_graph *friends);
void friend_distance(char *input, list_graph *friends);
void suggestions(char *input, list_graph *friends);
void common_friends(char *input, list_graph *friends);

#endif // FRIENDS_H
