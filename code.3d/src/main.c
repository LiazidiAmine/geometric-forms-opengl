#include <stdio.h>
#include <stdlib.h>

typedef struct{

}Object;

typedef struct node{
	char op;
	Object *obj;
	Matrices Md;
	Matrices Mi;
	Matrices Mn;
	node *fd, *fg;
}