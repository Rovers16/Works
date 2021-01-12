#ifndef QUEUETYPE_H
#define QUEUETYPE_H

#include<string>

using namespace std;

const unsigned int QUEUE_SIZE = 256;



typedef string el_t;
typedef int index_t;
typedef unsigned int count_t;

class queuetype
{
	public:
		queuetype(void);
		~queuetype(void);
		bool isemptyqueue(void);
		bool isfullqueue(void);
		void addqueue(el_t&);
		void deletequeue(el_t&); 

	protected:
		void queueError(char*);
		index_t front;
		index_t rear;
		count_t count;
		el_t el[QUEUE_SIZE];
};

#endif // !QUEUETYPE_H
