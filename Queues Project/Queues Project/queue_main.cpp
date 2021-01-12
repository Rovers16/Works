#include "queuetype.h"
#include<string>
#include<fstream> 

using namespace std;

ifstream fin;
ofstream fout;

void createqueue(queuetype &que);
void printque(queuetype &que);
void print_1st_element(queuetype &que);
void squarequeue(queuetype &que);
void replaceelement(queuetype &que, el_t eval, el_t newval);
void concatenatequeue(queuetype &Aque, queuetype &Bque, queuetype &Cque);
void unionqueue(queuetype &Aque, queuetype &Bque, queuetype &Uque);
bool equal(queuetype &que, queuetype &que2);
void copyqueue(queuetype &que, queuetype &copyque);
int length(queuetype &que);
void combine(queuetype &Mque, queuetype &Nque, queuetype &MNque);
void recursivequeue(queuetype que);

 
int main()
{
	queuetype que1, que2, que3, que4, cque, uque, copyque, combineque;
	el_t eval = "strap", newval = "yyyyy";
	fin.open("input.txt");
	fout.open("output.txt");

	createqueue(que1);
	printque(que1);

	createqueue(que2);
	printque(que2);

	createqueue(que3);
	printque(que3);

	createqueue(que4);
	printque(que4);

	print_1st_element(que1);
	printque(que1);

	printque(que2);
	fout << "The square queue" << endl;
	squarequeue(que2);
	printque(que2);

	printque(que4);
	fout << "The replacement queue." << endl;
	replaceelement(que4, eval, newval);
	printque(que4);

	concatenatequeue(que2, que4, cque);
	fout << "The concatenated que" << endl;
	printque(cque);

	printque(que1);
	printque(que3);
	unionqueue(que1, que3, uque);
	fout << "The union queue." << endl;
	printque(uque);

	if (equal(que1, que2))
		fout << "The queues are equal." << endl;
	else
		fout << "They are not equal." << endl;
	if (equal(que1, que1))
		fout << "The queues in this second function are equal." << endl;
	else
		fout << "They are not equal." << endl;
		

	copyqueue(que1, copyque);
	fout << "The copy queue." << endl;
	printque(copyque);

	fout << "The queue has a length of." << endl << length(copyque) << endl << endl;

	printque(copyque);
	fout << "The recursive reverse print." << endl;
	recursivequeue(copyque);
	fout << endl << endl;
	printque(copyque);

	printque(que1);
	combine(que1, que2, combineque);
	printque(combineque);

	fin.close();
	fout.close();
	return 0;
}

void createqueue(queuetype &que)
{//creates a queue
	el_t elem, sentinel;

	fin >> sentinel >> elem;

	while(elem != sentinel && !que.isfullqueue())
	{//adding elements to the queue
		que.addqueue(elem);
		fin >> elem;
	}
}

void printque(queuetype &que)
{//prints the que
	queuetype temp;
	el_t elem;
	int num = 0;

	fout << "The elements in the queue are." << endl;

	if (!que.isemptyqueue())
	{//checking if the queue is empty
		while (!que.isemptyqueue())
		{
			que.deletequeue(elem);
			temp.addqueue(elem);
			fout << elem << " ";//printing the elements 
			num++;
			if (num % 15 == 0)//manipulating list so the user doesn't have to scroll 
				fout << endl;
		}

		fout << endl << endl;

		while (!temp.isemptyqueue())
		{//resetting the queue
			temp.deletequeue(elem);
			que.addqueue(elem);
		}
	}
	else//message if the queue is empty
		fout << "This queue is empty." << endl << endl;
}

void print_1st_element(queuetype &que)
{//prints the first element in a queue and resets the queue unchanged
	queuetype temp;
	el_t elem;

	if (!que.isemptyqueue())
	{//checking if the queue is empty
		que.deletequeue(elem);
		temp.addqueue(elem);
		
		fout << "The first element in the queue is." << endl
			<< elem << endl << endl;//printing the first element of the queue

		while (!que.isemptyqueue())
		{//moving the rest of the queue into the temp if there is more than 1 element in it
			que.deletequeue(elem);
			temp.addqueue(elem);
		}

		while (!temp.isemptyqueue())
		{//resetting the queue
			temp.deletequeue(elem);
			que.addqueue(elem);
		}
	}
	else//message if the queue is empty
		fout << "There are no elements in this queue." << endl << endl;
}

void squarequeue(queuetype &que)
{//function to square the elements in a queue. this means having it show twice with no space with strings
	queuetype temp;
	el_t elem;

	if (!que.isemptyqueue())
	{//checking if the queue is empty
		while (!que.isemptyqueue())
		{
			que.deletequeue(elem);
			elem = elem + elem;//changing the element before putting it into the temp queue
			temp.addqueue(elem);
		}

		while (!temp.isemptyqueue())
		{//resetting the queue
			temp.deletequeue(elem);
			que.addqueue(elem);
		}
	}
	else//message if the queue is empty
		fout << "The queue is empty." << endl << endl;
}

void replaceelement(queuetype &que, el_t eval, el_t newval)
{//replacing the element eval with the newval in the queues
	queuetype temp;
	el_t elem;

	if (!que.isemptyqueue())
	{//checking if the queue is empty
		while (!que.isemptyqueue())
		{
			que.deletequeue(elem);
			if (elem == eval)//checking if the element is the one we are looking for
				temp.addqueue(newval);//replacing the element if it is what we're looking for
			else
				temp.addqueue(elem);
		}

		while (!temp.isemptyqueue())
		{//resetting the queue
			temp.deletequeue(elem);
			que.addqueue(elem);
		}
	}
	else//message if the queue is empty
		fout << "The queue is empty." << endl << endl;
}

void concatenatequeue(queuetype &Aque, queuetype &Bque, queuetype &Cque)
{//function to concatenate 2 queues with Bque in front
	if (!Aque.isemptyqueue() || !Bque.isemptyqueue())
	{
		el_t elem;
		queuetype temp, temp2;

		while (!Bque.isemptyqueue())
		{//removing from Bque and putting in the Cque
			Bque.deletequeue(elem);
			Cque.addqueue(elem);
			temp.addqueue(elem);
		}

		while (!Aque.isemptyqueue())
		{//removing from Aque and setting in Cque
			Aque.deletequeue(elem);
			Cque.addqueue(elem);
			temp2.addqueue(elem);
		}

		while (!temp.isemptyqueue())
		{//resetting the queues
			temp.deletequeue(elem);
			Bque.addqueue(elem);
		}

		while (!temp2.isemptyqueue())
		{//resetting the queues
			temp2.deletequeue(elem);
			Aque.addqueue(elem);
		}
	}
	else//message if the queues are empty
		fout << "Both queues are empty." << endl << endl;
}

void unionqueue(queuetype &Aque, queuetype &Bque, queuetype &Uque)
{//making a union queue without any elements repeating
	if (!Aque.isemptyqueue() || !Bque.isemptyqueue())
	{//making sure there are elements in at least one of the queues
		queuetype temp, temp3;
		el_t elem, elem2;
		bool found;

		while (!Aque.isemptyqueue())
		{//taking from the Aque
			found = false;

			Aque.deletequeue(elem);
			temp.addqueue(elem);

			if (!Uque.isemptyqueue())
			{//checking if the Union que is empty
				while (!Uque.isemptyqueue())
				{
					Uque.deletequeue(elem2);
					temp3.addqueue(elem2);
					if (elem2 == elem)//checking if the element is already in the union que
						found = true;
				}

				while (!temp3.isemptyqueue())
				{//resetting the union que
					temp3.deletequeue(elem2);
					Uque.addqueue(elem2);
				}

				if (!found)//adding the element from Aque if the Union que is empty
					Uque.addqueue(elem);
			}
			else
				Uque.addqueue(elem);
		}

		while (!temp.isemptyqueue())
		{
			temp.deletequeue(elem);
			Aque.addqueue(elem);
		}

		while (!Bque.isemptyqueue())
		{//taking from the Bque
			found = false;

			Bque.deletequeue(elem);
			temp.addqueue(elem);

			if (!Uque.isemptyqueue())
			{//checking if the Union que is empty
				while (!Uque.isemptyqueue())
				{
					Uque.deletequeue(elem2);
					temp3.addqueue(elem2);
					if (elem2 == elem)//checking if the element is already in the union que
						found = true;
				}

				while (!temp3.isemptyqueue())
				{//resetting the union que
					temp3.deletequeue(elem2);
					Uque.addqueue(elem2);
				}

				if (!found)//adding the element from Aque if the Union que is empty
					Uque.addqueue(elem);
			}
			else
				Uque.addqueue(elem);
		}

		while (!temp.isemptyqueue())
		{
			temp.deletequeue(elem);
			Bque.addqueue(elem);
		}
	}

	else
		fout << "The queues are empty." << endl << endl;
}

bool equal(queuetype &que, queuetype &que2)
{//checking whether 2 queues are equal
	queuetype temp, temp2;
	bool isequal = true;
	el_t elem, elem2;

	if (!que.isemptyqueue() || !que2.isemptyqueue())
	{//checking whether there is something in either queue
		if (!que.isemptyqueue() && que2.isemptyqueue())
		{//checking whether both queues have elements
			while (!que.isemptyqueue() && !que2.isemptyqueue() && isequal)
			{//going through both queues to check if elements are equal
				que.deletequeue(elem);
				temp.addqueue(elem);
				que2.deletequeue(elem2);
				temp2.addqueue(elem2);

				if (elem != elem2)//checking the elements from both queues
					isequal = false;
			}

			while (!que.isemptyqueue())
			{//making sure the que is empty
				que.deletequeue(elem);
				temp.addqueue(elem);
			}
			
			while (!que2.isemptyqueue())
			{//making sure the que is empty
				que2.deletequeue(elem);
				temp2.addqueue(elem);
			}

			while (!temp.isemptyqueue())
			{//resetting the queue
				temp.deletequeue(elem);
				que.addqueue(elem);
			}

			while (!temp2.isemptyqueue())
			{//resetting the queue
				temp2.deletequeue(elem);
				que2.addqueue(elem);
			}
		}

		else//returning false since only one of the queues is empty
			return false;
	}
	
	return isequal;
}

void copyqueue(queuetype &que, queuetype &copyque)
{//creates a copy of the queue
	if (!que.isemptyqueue())
	{//checking if the que is empty
		queuetype temp;
		el_t elem;

		while (!que.isemptyqueue())
		{
			que.deletequeue(elem);
			copyque.addqueue(elem);//putting the elements in the copyqueue
			temp.addqueue(elem);
		}

		while (!temp.isemptyqueue())
		{//resetting the que
			temp.deletequeue(elem);
			que.addqueue(elem);
		}
	}

	else//message if the queue is empty
		fout << "The queue is empty." << endl << endl;
}

int length(queuetype &que)
{//finds the length of the queue
	int count = 0;//initialize the count

	if (!que.isemptyqueue())
	{//checking if the queue is empty
		queuetype temp;
		el_t elem;
		
		while (!que.isemptyqueue())
		{
			que.deletequeue(elem);
			temp.addqueue(elem);
			count++;//adding 1 to the count for every element found
		}

		while (!temp.isemptyqueue())
		{//resetting the queue
			temp.deletequeue(elem);
			que.addqueue(elem);
		}
	}

	return count;//returning the count
}

void combine(queuetype &Mque, queuetype &Nque, queuetype &MNque)
{//combines two ordered queues
	if (!Mque.isemptyqueue() || !Nque.isemptyqueue())
	{//checks whether the queues are empty
		queuetype temp, temp2;
		el_t elem, elem2;
		bool found, empty = true;

		while (!Mque.isemptyqueue())
		{//puts this queue into the MNque
			Mque.deletequeue(elem);
			temp.addqueue(elem);
			MNque.addqueue(elem);
			//empty = false;//shows that Mque is not empty
		}

		while (!temp.isemptyqueue())
		{//resets the queue
			temp.deletequeue(elem);
			Mque.addqueue(elem);
		}

		while (Nque.isemptyqueue())
		{//puts this que into MNque
			Nque.deletequeue(elem);
			temp.addqueue(elem);

			found = false;//resets 

			while (!MNque.isemptyqueue())
			{
				MNque.deletequeue(elem2);

				if (elem < elem2 && !found)
				{//putting the element into the queue in the right order
					temp2.addqueue(elem);
					temp2.addqueue(elem2);
					found = true;
				}
				else
					temp2.addqueue(elem2);
			}

			while (!temp2.isemptyqueue())
			{//resets queue
				temp2.deletequeue(elem2);
				MNque.addqueue(elem2);
			}
		}

		while (!temp.isemptyqueue())
		{//resets queue
			temp.deletequeue(elem);
			Nque.addqueue(elem);
		}
	}

	else
		fout << "The queues are empty." << endl << endl;
}

void recursivequeue(queuetype que)
{
	queuetype temp;
	el_t elem;
	
	if (!que.isemptyqueue())
	{
		que.deletequeue(elem);
		recursivequeue(que);
		que.addqueue(elem);
		fout << elem << " ";
	}
}




