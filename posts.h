#ifndef POSTS_H
#define POSTS_H
#include "data_structure.h"
/**
 * Function that handles the calling of every command from task 2
 *
 * Please add any necessary parameters to the functions
*/
void handle_input_posts(char *input, posts *postari);
void create_post(char *input, posts *postari);
void print_posts(posts *postari);

#endif // POSTS_H
