#include <iostream>
#include <string>
#include <cstring>
#include "stack.h"

stacktype::stacktype()
{
	top = -1;
	size = 0;
}

stacktype::~stacktype()
{
	top = -1;
	size = 0;
}

bool stacktype::isEmptyStack(void)
{
	return(top == -1 ? true : false);
}

bool stacktype::isFullStack(void)
{
	return(top == (MAX_NUM_ELS - 1) ? true : false);
}

void stacktype::stackError(char* errorMessage)
{
	cerr << errorMessage;
	exit(1);
}

void stacktype::push(el_t element)
{
	if (isFullStack())
		stackError("The stack is full. \n");
	else
	{
		++top;
		++size;
		el[top] = element;
	}
}

void stacktype::pop(el_t& element)
{
	if (isEmptyStack())
		stackError("The stack is empty. \n");
	else
	{
		element = el[top];
		--top;
		--size;
	}
}

int stacktype::stacksize()
{
	return size;
}