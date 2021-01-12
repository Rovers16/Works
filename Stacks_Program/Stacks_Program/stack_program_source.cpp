#include<iostream>
#include<string>
#include<fstream>
#include"stack.h"

using namespace std;

ifstream fin;
ofstream fout;

void createstack(stacktype &stk1);
void printarestore(stacktype &stk1);
void removeelement(stacktype &stk1);
void printrecursively(stacktype &stk1);
void Istack(stacktype &stk1, stacktype &stk2, stacktype &IntersectionStack);
void Suc_stack(stacktype &stk1, stacktype &successor_stack);
void Unionstack(stacktype &stk1, stacktype &stk2, stacktype &Unstack);
int count(stacktype &stk1);
void copystack(stacktype &stk1, stacktype &stk2);
bool equal(stacktype &stk1, stacktype &stk2);
void find_max_min(stacktype &stk1);
void delete_entry(stacktype &stk1, el_t stringval);
void delete_top_bottom(stacktype &stk1);
void reverse_element(stacktype &stk1);
void print_bottomelement(stacktype &stk1);
bool Vowel(el_t element);
void recursivereplace(stacktype &stk1, el_t replace);


int main()
{
	fin.open("input.txt");
	fout.open("output.txt");

	stacktype stk1, stk2, stk3, stk4, stk5, Intersectionstack, Unstack, succesor_stack, copystk;
	el_t stringval = "strap", replace = "yyyyy";
	int num;

	createstack(stk1);
	createstack(stk2);
	createstack(stk3);
	createstack(stk4);
	createstack(stk5);
	printarestore(stk1);
	
	removeelement(stk3);
	printarestore(stk3);

	fout << "Below is a stack printed backwards recusively." << endl;
	printrecursively(stk3);
	fout << endl << endl;
	printarestore(stk3);

	Istack(stk1, stk2, Intersectionstack);
	printarestore(Intersectionstack);

	fout << "The succesor stack is." << endl;
	Suc_stack(stk2, succesor_stack);
	printarestore(succesor_stack);
	
	Unionstack(stk2, stk3, Unstack);
	printarestore(Unstack);

	num = count(stk3);
	fout << "The length of the stack is." << endl;
	fout << num << endl << endl;

	copystack(stk1, copystk);
	printarestore(copystk);

	if (equal(stk1, stk2))
		fout << "The stacks are equal." << endl << endl;
	else
		fout << "The stacks are not equal." << endl << endl;

	if (equal(stk1, copystk))
		fout << "The stacks are equal." << endl << endl;
	else
		fout << "The stacks are not equal." << endl << endl;

	find_max_min(stk2);

	delete_entry(stk4, stringval);
	printarestore(stk4);

	delete_top_bottom(stk3);
	printarestore(stk3);

	reverse_element(stk4);
	printarestore(stk4);

	print_bottomelement(stk4);

	recursivereplace(stk5, replace);
	printarestore(stk5);

	fin.close();
	fout.close();
	return 0;
}

void createstack(stacktype &stk1)
{//puts elements into a stack based on the class
	el_t element, sentinel;

	fin >> sentinel >> element;

	while (!stk1.isFullStack() && element != sentinel)
	{
		stk1.push(element);
		fin >> element;
	}
}//end createstack

void printarestore(stacktype &stk1)
{//prints the elements of a stack and restores the stack
	stacktype tempstk;
	el_t element;

	fout << "Below are the elements of a stack" << endl;

	while (!stk1.isEmptyStack())
	{
		stk1.pop(element);
		fout << element << " ";
		tempstk.push(element);
	}

	fout << endl << endl;

	while (!tempstk.isEmptyStack())
	{
		tempstk.pop(element);
		stk1.push(element);
	}
}//end printarestore

void removeelement(stacktype &stk1)
{//removes the second element of a stack
	stacktype tempstk;
	el_t element;

	if (!stk1.isEmptyStack())
	{//removing the first element using an if statement
		stk1.pop(element);
		tempstk.push(element);
	}
	
	if (!stk1.isEmptyStack())
	{//checking if there is a second element before removing it
		stk1.pop(element);
		fout << "The second element that's removed is" << endl
			 << element << endl << endl;
	}
	
	if (!tempstk.isEmptyStack())
	{//putting the first element back
		tempstk.pop(element);
		stk1.push(element);
	}

}

void printrecursively(stacktype &stk1)
{//prints a stack backwards using recursion
	el_t element;

	if (!stk1.isEmptyStack())
	{
		stk1.pop(element);
		printrecursively(stk1);
		fout << element << " ";//printing the elements here so they come out in reverse order
		stk1.push(element);
	}
}

void Istack(stacktype &stk1, stacktype &stk2, stacktype &IntersectionStack)
{//stack to create an intersection stack of two other stacks
	el_t element, element2, element3;
	bool found;
	stacktype temp, temp2, temp3;

	while (!stk1.isEmptyStack())
	{//outer loop using the first stack
		stk1.pop(element);
		temp.push(element);

		while (!stk2.isEmptyStack())
		{//inner loop using the second stack
			found = false;//setting found to false
			
			stk2.pop(element2);
			temp2.push(element2);
			
			if (element == element2)
			{//checking if the elements from both stacks match
				while (!IntersectionStack.isEmptyStack() && !found)
				{//going through the intersection stack to make sure there are no repeating elements
					IntersectionStack.pop(element3);
					temp3.push(element3);
					if (element == element3)
						found = true;//changing found to show the element is already in the stack
				}//end while

				while (!temp3.isEmptyStack())
				{
					temp3.pop(element3);
					IntersectionStack.push(element3);
				}//end while

				if (!IntersectionStack.isFullStack() && !found)//adding the element into the stack if stack is false and not full
					IntersectionStack.push(element);
			}//end if statement
		}//end while

		while (!temp2.isEmptyStack())
		{//resetting the second stack
			temp2.pop(element2);
			stk2.push(element2);
		}//end while
	}

	while (!temp.isEmptyStack())
	{
		temp.pop(element);
		stk1.push(element);
	}//end while
}

void Suc_stack(stacktype &stk1, stacktype &successor_stack)
{/*adds element to the new stack if the first character in the element 
 is the next alphabetic character of the last character in the previous element*/ 

	el_t element;
	char oldch, newch;
	stacktype temp;

	while (!stk1.isEmptyStack())
	{
		stk1.pop(element);
		//oldch = element.at(4);
		temp.push(element);
	}

	while (!temp.isEmptyStack())
	{
		temp.pop(element);
		stk1.push(element);
		element.at(0) = element.at(0) + 1;
		successor_stack.push(element);
	}
}

void Unionstack(stacktype &stk1, stacktype &stk2, stacktype &Unstack)
{//creating a union stack of two stacks
	el_t element;
	stacktype temp;

	while (!stk1.isEmptyStack())
	{
		stk1.pop(element);
		temp.push(element);
	}

	while (!temp.isEmptyStack())
	{//putting elements back into the first stack while also adding them into the Union stack
		temp.pop(element);
		stk1.push(element);
		Unstack.push(element);
	}

	while (!stk2.isEmptyStack())
	{
		stk2.pop(element);
		temp.push(element);
	}

	while (!temp.isEmptyStack())
	{//putting elements back into the second stack while also adding them into the Union stack
		temp.pop(element);
		stk2.push(element);
		if (!Unstack.isFullStack())//checking if the union stack is full before adding into it since it's now bigger than the other stacks 
			Unstack.push(element);
	}
}

int count(stacktype &stk1)
{//counting the elements in a stack
	stacktype tempstk;
	el_t element;
	int count = 0;

	while (!stk1.isEmptyStack())
	{
		stk1.pop(element);
		count++;//counting the elements as they are removed from the stack
		tempstk.push(element);
	}

	while (!tempstk.isEmptyStack())
	{
		tempstk.pop(element);
		stk1.push(element);
	}

	return count;
}

void copystack(stacktype &stk1, stacktype &stk2)
{//copies the elements of a stack into another one
	stacktype tempstk;
	el_t element;

	while (!stk1.isEmptyStack())
	{
		stk1.pop(element);
		tempstk.push(element);
	}

	while (!tempstk.isEmptyStack())
	{//putting the elements back into the original stack and into the new stack
		tempstk.pop(element);
		stk1.push(element);
		stk2.push(element);
	}
}

bool equal(stacktype &stk1, stacktype &stk2)
{//finding whether two stacks are equal
	stacktype tempstk, tempstk2;
	bool same = true;
	el_t element, element2;

	while (!stk1.isEmptyStack() && !stk2.isEmptyStack() && same)
	{//going through both stacks
		stk1.pop(element);
		stk2.pop(element2);
		if (element != element2)//checking whether the elements are the same
			same = false;//changing to false to show the elements are different
		tempstk.push(element);
		tempstk2.push(element2);
	}

	if (!stk1.isEmptyStack())
		same = false;//showing it's false if this stack is not empty when the earlier loop ended
	if (!stk2.isEmptyStack())//showing it's false if this stack is not empty when the earlier loop ended
		same = false;

	while (!tempstk.isEmptyStack())
	{
		tempstk.pop(element);
		stk1.push(element);
	}

	while (!tempstk2.isEmptyStack())
	{
		tempstk2.pop(element2);
		stk2.push(element2);
	}

	return same;
}

void find_max_min(stacktype &stk1)
{//finding the max and min elements in a stack
	stacktype tempstk;
	el_t element, max, min;
	
	if (!stk1.isEmptyStack())
	{//declaring the first element is the max and the min before the loop starts
		stk1.pop(element);
		tempstk.push(element);
		min = element;
		max = element;
	}

	while (!stk1.isEmptyStack())
	{
		stk1.pop(element);
		if (element > max)//checking if the element is higher than the current max
			max = element;
		if (element < min)//checking if the element is lower than the current min
			min = element;
		tempstk.push(element);
	}

	while (!tempstk.isEmptyStack())
	{
		tempstk.pop(element);
		stk1.push(element);
	}

	fout << "The max element in the stack is" << endl << max << endl
		<< "The min element in the stack is" << endl << min << endl << endl;
}

void delete_entry(stacktype &stk1, el_t stringval)
{//deletes all element "stringval" from a stack
	stacktype tempstk;
	el_t element;

	while (!stk1.isEmptyStack())
	{
		stk1.pop(element);
		if(element != stringval)
			tempstk.push(element);//putting all elements except the stringval ones into a the temp stack
	}

	while (!tempstk.isEmptyStack())
	{
		tempstk.pop(element);
		stk1.push(element);
	}
}

void delete_top_bottom(stacktype &stk1)
{//deletes the top and bottom elements of a stack
	stacktype tempstk;
	el_t element;

	if (!stk1.isEmptyStack())
		stk1.pop(element);//deletes the top element

	while (!stk1.isEmptyStack())
	{
		stk1.pop(element);
		tempstk.push(element);
	}

	if (!tempstk.isEmptyStack())
		tempstk.pop(element);//removes the bottom element

	while (!tempstk.isEmptyStack())
	{
		tempstk.pop(element);
		stk1.push(element);
	}
}

void reverse_element(stacktype &stk1)
{
	el_t element;
	stacktype temp, temp2;

	while (!stk1.isEmptyStack())
	{
		stk1.pop(element);
		temp.push(element);
	}

	while (!temp.isEmptyStack())
	{
		temp.pop(element);
		temp2.push(element);
	}

	while (!temp2.isEmptyStack())
	{
		temp2.pop(element);
		stk1.push(element);
	}
}

void print_bottomelement(stacktype &stk1)
{
	el_t element;

	while (!stk1.isEmptyStack())
		stk1.pop(element);
	
	fout << "The bottom element in this stack is" << endl
		<< element << endl << endl;
}

bool Vowel(el_t element)
{
	bool isvowel = true;
	char ch;

	while (!element.empty() && isvowel)
	{
		ch = element.at(0);

		switch (ch)
		{
		case'a':
		case'A':
		case'e':
		case'E':
		case'i':
		case'I':
		case'o':
		case'O':
		case'u':
		case'U':
			isvowel = true;
			break;
		default:
			isvowel = false;
			break;
		}
		element = element.substr(1, element.length());
	}
	return isvowel;
}

void recursivereplace(stacktype &stk1, el_t replace)
{
	stacktype temp;
	el_t element;

	if (!stk1.isEmptyStack())
	{
		stk1.pop(element);
		recursivereplace(stk1, replace);
		if (Vowel(element))
			stk1.push(replace);
		else
			stk1.push(element);
	}
}






