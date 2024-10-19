#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "users.h"
#include "posts.h"

void handle_input_posts(char *input, posts *postari)
{
	char *commands = strdup(input);
	char *cmd = strtok(commands, "\n ");

	if (!cmd)
		return;

	if (!strcmp(cmd, "create")){
		create_post(input, postari);
	}
	else if (!strcmp(cmd, "repost"))
		(void)cmd;
		// create_repost(input, postari);
	else if (!strcmp(cmd, "common-repost"))
		(void)cmd;
		// TODO: Add function
	else if (!strcmp(cmd, "like"))
		(void)cmd;
		// TODO: Add function
	else if (!strcmp(cmd, "ratio"))
		(void)cmd;
		// TODO: Add function
	else if (!strcmp(cmd, "delete"))
		(void)cmd;
		// TODO: Add function
	else if (!strcmp(cmd, "get-likes"))
		(void)cmd;
		// TODO: Add function
	else if (!strcmp(cmd, "get-reposts"))
	(void)cmd;
		// get_reposts(input, postari);
	else if (!strcmp(cmd, "get-likes"))
		(void)cmd;
		// TODO: Add function

	free(commands);
}

void create_post(char *input, posts *postari) {
	char *commands = strdup(input);
    commands = strtok(commands, " "); // get rid of "create"
    char *name = strtok(NULL, " "); // name
    char *content = strtok(NULL, ""); // content
	content[strlen(content) - 1] = '\0'; // remove '\n' from content


 // Initialize the new post
    postari[postari->num_posts].id = postari->num_posts + 1;
    strncpy(postari[postari->num_posts].titlu, content, sizeof(postari[postari->num_posts].titlu) - 1);
    postari[postari->num_posts].titlu[sizeof(postari[postari->num_posts].titlu) - 1] = '\0'; // Ensure null-termination
    postari[postari->num_posts].user_id = get_user_id(name); // Assuming the name is the user_id
    postari[postari->num_posts].events = lg_create(10); // Assuming 10 is the number of nodes

    postari->num_posts++;
    printf("Created %s for %s\n", content, name);

    free(commands);

}

void print_posts(posts *postari) {
    for (int i = 0; i < postari->num_posts; i++) {
        printf("Post ID: %d\n", postari[i].id);
        printf("Title: %s\n", postari[i].titlu);
        printf("User ID: %d\n", postari[i].user_id);
        // Print the events if necessary
        // printf("Events: %s\n", postari[i].events);
        printf("\n");
    }
}