#include "tree.h"
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_usage(void) {
    printf("Usage:  unique NUM NUM NUM ...       (normal output)\n");
    printf("        unique -d NUM NUM NUM ...    (debugging output)\n");
    exit(0);
}

/*
* Confirm that all characters of the string s are digits.
* If any character is NOT a digit, then call print_usage().
*/
void check_number(const char *s) {
    while (*s) {
	    if (!isdigit((unsigned char)*s)) {
			    print_usage();
			    return;
	     }
	     s++;
  }// replace this comment with your code
}

/*
* Usage:    unique 4 8 1 4 ...          call tree_print()
*           unique -d 4 8 1 4 ...       call tree_dump()
*/
int main(int argc, char **argv) {
 Tree *tree = tree_alloc();
   if (tree == NULL) {
        printf("Failed to allocate tree.\n");
        return 1;  // Exit early if tree allocation fails
    }
    int dump_flag = 0;
    if (argc == 1) {
            return 1; }
    for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-d") == 0) {
                    dump_flag = 1;
            } else {
                    check_number(argv[i]);
                    int num = atoi(argv[i]);
                    tree_add(tree, num);
            }
    }
    if(dump_flag) {
            tree_dump(tree);
    } else {
            tree_print(tree);
    }
    tree_free(&tree);// replace this comment with your code
    return 0;
}


