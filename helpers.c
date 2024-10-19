#include "helpers.h"

void __users_extract(char *input, uint16_t *cur_user, uint16_t *friend_user)
{
	// extract userid for each friend
	char *commands = strdup(input);
	char *name = strtok(commands, "\n "); // get rid of "add"

	name = strtok(NULL, "\n "); // first name
	*cur_user = get_user_id(name);
	
	name = strtok(NULL, "\n "); // second name
	*friend_user = get_user_id(name);

	free(commands);
}

void __user_extract(char *input, uint16_t *cur_user)
{
	// extract userid for each friend
	char *commands = strdup(input);
	char *name = strtok(commands, "\n "); // get rid of "add"

	name = strtok(NULL, "\n "); // first name
	*cur_user = get_user_id(name);

	free(commands);
}

void bubble_sort(void *base, size_t num, size_t size, compare_fn compare)
{
    char *arr = base;
    char *temp = malloc(size);

    for (size_t i = 0; i < num - 1; ++i) {
        for (size_t j = 0; j < num - 1 - i; ++j) {
            char *elem1 = arr + j * size;
            char *elem2 = arr + (j + 1) * size;

            if (compare(elem1, elem2) > 0) {
                memcpy(temp, elem1, size);
                memcpy(elem1, elem2, size);
                memcpy(elem2, temp, size);
            }
        }
    }

    free(temp);
}

// Returns positive if arg1 > arg2, negative if arg1 < arg2, 0 if equal
int16_t compare_uint16(const void *a, const void *b)
{
    uint16_t arg1 = *(const uint16_t *)a;
    uint16_t arg2 = *(const uint16_t *)b;
    return (arg1 > arg2) - (arg1 < arg2);
}
