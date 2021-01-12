#ifndef  STACKTYPE_H
#define STACKTYPE_H
#include<string>

using namespace std;

const unsigned int MAX_NUM_ELS = 256;
typedef int el_t;


class stacktype
{
public:
	stacktype();
	~stacktype();
	bool isFullStack();
	bool isEmptyStack();
	void push(el_t);
	void pop(el_t&);
	int stacksize();


private:
	void stackError(char*);
	int top;
	int size;
	el_t el[MAX_NUM_ELS];
};

#endif // ! STACKTYPE_h



