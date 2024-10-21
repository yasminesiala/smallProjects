#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define EPSILON 1e-14

void usage(void) {
    printf("Usage:  ./nummy -e N\n");
    printf("        ./nummy -l N\n");
    printf("        ./nummy -p N\n");
    printf("        ./nummy -s N\n");
    printf("        for integer N\n");
    exit(1);
}

double absolute_value(double x) {
    if (x < 0) {
	    return -x;
    } else {
	    return x;
    }
    // replace this comment with the rest of your function's body
    return 0;
}

double my_sqrt(double x) {
    double next_y = 1.0;
    double y = 0.0;
    
    while (absolute_value(next_y - y) > EPSILON) {
	    y = next_y;
	    next_y = 0.5 * (y + x/y);
    }
    return next_y;// replace this comment with the rest of your function's body
    return 0;
}

double my_e(int n) {
    double e = 1.0;
    double factorial = 1.0;
    
    for (int k = 1; k <= n - 1; ++k) {
	 factorial *= k;
	 e += 1.0/factorial;
    } 
    return e; // replace this comment with the rest of your function's body
    return 0;
}

double my_pi(int n) {
   double pi = 0.0;
   double sqrt12 = my_sqrt(12.0);
   double sign = 1.0;
   double term = 0.0;

   for (int i = 0; i < n; ++i) {
	term = sign / (2 * i + 1); //calculates each term
	pi += term;
	sign /= -3;
   }
   return sqrt12 * pi; 
}

double my_ln2(int n) {
   double power = 2.0;
   double sum = 0.0;

   for (int i = 1; i <= n; ++i){
	sum += 1 / (power * i);
	power *= 2;
   }	// replace this comment with the rest of your function's body
    return sum;
}

/*
* Example usage:  nummy -p 10
*                 ^     ^  ^---argv[2]
*   argc == 3     ^     ^----argv[1]
*                 ^--------argv[0]
*/
int main(int argc, char **argv) {
    if (argc != 3) {
        usage();
    }

    int n = atoi(argv[2]);

    if        (strcmp(argv[1], "-e") == 0) {
        printf("e is %.13f\n", my_e(n));
    } else if (strcmp(argv[1], "-l") == 0) {
        printf("ln 2 is %.13f\n", my_ln2(n));
    } else if (strcmp(argv[1], "-p") == 0) {
	printf("pi is %.13f\n", my_pi(n));
    } else if (strcmp(argv[1], "-s") ==0)  {
	printf("sqrt(%d) is %.13f\n", n, my_sqrt(n));// replace this comment with the rest of your function's body
    } else {
        usage();
    }

    return 0;
}
