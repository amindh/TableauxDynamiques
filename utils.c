#include "utils.h"


/* ********************************************************************** */
int rand_ab(int a, int b)
{
    unsigned int c ;

    if ( a > b ) {
	c = a ;
	a = b ;
	b = c ;
    }

    return a+(b-a)*(rand()/(1.0+RAND_MAX)) ;
}

int min(int a, int b)
{
    return (a<b)?a:b ;
}

int max(int a, int b)
{
    return (a>b)?a:b ;
}

/* ********************************************************************** */
double rand_ab_f(double a, double b)
{
    double c ;

    if ( a > b ) {
	c = a ;
	a = b ;
	b = c ;
    }

    return a+(b-a)*(rand()/(1.0+RAND_MAX)) ;
}

float min_f(float a, float b)
{
    return (a<b)?a:b ;
}

float max_f(float a, float b)
{
    return (a>b)?a:b ;
}
