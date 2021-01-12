#include<iostream>
#include<string>
#include<fstream>

using namespace std;

struct nodetype
{
	char info;
	nodetype *link;
};

nodetype *builditforward(ifstream& fin);
void printlist(nodetype *head, ofstream& fout);
bool search(nodetype *head, char searchitem);
int count(nodetype *Sbag);
void destroylist(nodetype *&head);
bool subbag(nodetype *Mbag, nodetype *Nbag);
bool equal(nodetype *Ubag, nodetype *Abag);
nodetype *intersection(nodetype *Ubag, nodetype *Bbag);
nodetype *A_complement(nodetype *Ubag, nodetype *Abag);
nodetype *findmax(nodetype *Unbag);
void addnewvalue(nodetype *&Dbag, char item);
/*void remitem(nodetype *&Cbag, char item);*/
void removefirstoccurence(nodetype *&Mbag, char item, ofstream& fout);
nodetype *copylist(nodetype *Ubag);
void sort(nodetype *bag);
nodetype *unionbag(nodetype *Cbag, nodetype *Dbag);


int main()
{
	ifstream fin;
	ofstream fout;
	nodetype *Ubag, *Sbag, *Nbag, *Abag, *Mbag, *Bbag, *Ibag, *A_comple, *Unbag, *max, *CUbag, *R_dif;
	int num;

	fin.open("input.txt");//opening infile
	fout.open("output.txt");//opening outfile

	Ubag = builditforward(fin);//building the Universal list
	fout << "Ubag" << endl;
	printlist(Ubag, fout);
	
	
	Sbag = builditforward(fin);//building a list
	fout << "Sbag" << endl;
	printlist(Sbag, fout);
	
	
	Nbag = builditforward(fin);//building a list
	fout << "Nbag" << endl;
	printlist(Nbag, fout);
	
	
	Abag = builditforward(fin);//building a list
	fout << "Abag" << endl;
	printlist(Abag, fout);
	
	
	Mbag = Sbag;//assigning list that are the same 
	Bbag = Nbag;//assigning list that are the same 

	
	if (search(Sbag, 'M'))//calling the search function
		fout << "The Character was found." << endl;
	else
		fout << "The Charater was not found." << endl;
	
	
	num = count(Sbag);//calling the counting function
	fout << "Number of Elements in a bag" << endl;
	fout << num << endl;
	
	
	if (subbag(Mbag, Nbag))//calling the function that checks for subset relationship
		fout << "This is a subset." << endl;
	else
		fout << "This is not a subset." << endl;

	
	if (equal(Sbag, Nbag))//calling the equality check function
		fout << "The lists are equal." << endl;
	else
		fout << "The lists are not equal." << endl;

	
	Ibag = intersection(Ubag, Bbag);
	fout << "The intersection list of the 2 bags." << endl;
	printlist(Ibag, fout);
	
	A_comple = A_complement(Ubag, Abag);
	fout << "This is the complement of Abag." << endl;
	printlist(A_comple, fout);
	
	Unbag = unionbag(Mbag, Nbag);
	fout << "This is the union of the 2 lists" << endl;
	printlist(Unbag, fout);

	max = findmax(Unbag);
	fout << "This is the max value of the list" << endl;
	printlist(max, fout);

	addnewvalue(Abag, 'Q');
	fout << "This adds a new value to the Head of the list" << endl;
	printlist(Abag, fout);

	removefirstoccurence(Mbag, '3', fout);
	fout << "This is the list with an item removed." << endl;
	printlist(Mbag, fout);

	Mbag = builditforward(fin);//calling function to build a list
	removefirstoccurence(Mbag, '3', fout);
	fout << "This is the list with an item removed." << endl;
	printlist(Mbag, fout);
	
	CUbag = copylist(Ubag);
	fout << "The copy list is" << endl;
	printlist(CUbag, fout);
	
	R_dif = A_complement(Abag, Bbag);
	fout << "The relative difference is" << endl;
	printlist(R_dif, fout);
	
	destroylist(CUbag);
	printlist(CUbag, fout);
	
	fin.close();
	fout.close();
	return 0; 
}

nodetype *builditforward(ifstream& fin)
{//funtion to build the link list
	nodetype *head, *current, *newnode;
	char ch;
	fin >> ch;//getting the character from a file
	head = NULL;//setting head to NULL
	current = head;
	
	while (ch != '*')//setting the sentinel controlled loop
	{ 
		newnode = new nodetype;//making a new node
		newnode->info = ch;//putting the character into the node
		newnode->link = NULL;

		if (head == NULL)//creating the first node and saving the address
		{
			head = newnode;
			current = newnode;
		}
		else
		{//using current in all other nodes in the link
			current->link = newnode;
			current = newnode;
		}

		fin >> ch;//calling the next character from file 
		 
	}
	
	return head;//returning the pointer to the list
}

void printlist(nodetype *head, ofstream& fout)
{//function to print out the link list
	nodetype *current = head;

	if (head == NULL)
		fout << "This is no list" << endl;
	while (current != NULL)//while loop to traverse the list
	{
		fout << current->info << " ";//outputting the information in a node
		current = current->link;//moving to the next node 
	}
	fout << endl;//making sure to skip to next line at the end of the list
}

bool search(nodetype *head, char searchitem)
{//function to search for a particular character
	nodetype *current;
	bool found = false;// setting found to false since the char hasn't been found yet

	current = head;

	while (current != NULL && !found)//searching the list while making sure the char hasn't been found
		if (current->info == searchitem)
			found = true;//changing found to true to show the char has been found
		else
			current = current->link;//traversing the list since the char hasn't been found
	return found;//returning true or false 
}

int count(nodetype *Sbag)
{//function to count the number element in a list
	int count = 0;//setting the counter to zero
	nodetype *current = Sbag;

	while (current != NULL)//while loop to traverse the whole list
	{
		count++;//adding 1 to the count 
		current = current->link;
	}
	return count;//returning the total count
}

void destroylist(nodetype *&head)
{//function to destroy a list
	nodetype *temp;

	while (head != NULL)
	{
		temp = head;//making temp point to the head of the list
		head = head->link;//moving the head of the list up to the next node
		delete temp;//deleting the node that had the head of the list
	}
}

bool subbag(nodetype *Mbag, nodetype *Nbag)
{//function checks whether mbag is a subset of nbag
	nodetype *ptr, *ptr1;
	ptr = Mbag;
	bool subset;

	if(Mbag != NULL && Nbag != NULL) //making sure both list are not empty
		{
		while (ptr != NULL)
		{//the outer loop for mbag
			subset = false;
			ptr1 = Nbag;

			while ((ptr1 != NULL) && (!subset))
			{//the inner loop to traverse nbag while comparing it to mbag
				
				if (ptr->info == ptr1->info) 
				{// if ptr1 and ptr are the same.
					subset = true;
				}
				else 
				{ //traverse list by 1 they aren't equal
					ptr1 = ptr1->link;
				}

			}//end of inner loop
			if (subset == false)
				return false;//checking why the inner loop ended
			
			ptr = ptr->link;//traversing the outer loop by one
		}
		}

	return true;//returning true since the outer loop was able to end successfully
}

bool equal(nodetype *Ubag, nodetype *Abag)
{//function checks if two lists are equal or not
	nodetype *ptr, *ptr1;
	bool same = false;
	ptr = Ubag;
	ptr1 = Abag;
	
	if (Ubag != NULL && Abag != NULL)//checking that the lists are not empty
	{
		sort(ptr);//sorting the lists 
		sort(ptr1);

		while (ptr != NULL && ptr1 != NULL)//making sure both list are fully traversed before ending loop
		{
			if (ptr->info == ptr1->info)//checking if the characters are the same
			{
				ptr = ptr->link;//traversing the list
				ptr1 = ptr1->link;
			}
			else
				return same;//returing false if the characters don't match at any point
		}
		return same = true;//returning true since the list was fully traversed 
	}
}

nodetype *intersection(nodetype *Ubag, nodetype *Bbag)
{
	nodetype *ptr, *ptr1, *ptr2, *newnode, *Ibag;
	ptr = Ubag;
	ptr1 = Bbag;
	Ibag = NULL;
	bool found, find;

	if (ptr == NULL || ptr1 == NULL)//checking if either list is empty
		return NULL;
	while (ptr != NULL)//outer loop
	{
		found = false;
		ptr1 = Bbag;//resetting pointer for the inner loop

		while (ptr1 != NULL && !found)//inner loop
		{
			if (ptr->info == ptr1->info)//if an intersection is found
			{
				ptr2 = Ibag;//setting pointer2 to point at the Intersect list
				found = true;//saying an intersect point was found 
				find = false;//used to check for new intersect point in the intersect list
				if (Ibag == NULL)//checking if this is the first intersection point
				{
					newnode = new nodetype;
					newnode->info = ptr->info;
					Ibag = newnode;//setting the header for the new list
					Ibag->link = NULL;
					ptr2 = Ibag;//setting a pointer to the new list that i can use to traverse the list
				}
				else
				{
					while (ptr2 != NULL && !find)//traversing the intersect list to make sure info isn't repeated in the list
					{
						if (ptr->info == ptr2->info)//checking if the info is repeated
						{
							find = true;
						}
						else
							ptr2 = ptr2->link;
					}//end of Intersect loop
					if (!find)//if info is not in the Intersect list
					{
						newnode = new nodetype;
						newnode->info = ptr->info;
						newnode->link = Ibag;//linking the newnode to the head of the list
						Ibag = newnode;//making the newnode the head of the list
					}
				}
			}
			else
				ptr1 = ptr1->link;
		}//end of inner loop
		ptr = ptr->link;
	}//end of outer loop
	return Ibag;
}//end of function

nodetype *A_complement(nodetype *Ubag, nodetype *Abag)
{//finding the elements of Ubag that are not in Abag
	nodetype *ptr, *ptr1, *Newbag, *newnode;
	bool found;
	ptr = Ubag;
	Newbag = NULL;
	
	if (Abag == NULL)//checking if A has a list
		return Ubag;//returning Ubag since A is empty
	else if (Ubag == NULL)
		return NULL;//returning nothing since Ubag is empty
	else
	{
		while (ptr != NULL)//the outer loop representing Ubag
		{
			ptr1 = Abag;//setting it to point at Abag
			found = false;//saying that the element hasn't been found in Abag yet
			while (ptr1 != NULL && !found)//the inner loop
			{
				if (ptr->info == ptr1->info)//checking if there element is in both list
					found = true;//setting to true if the element is found in Abag
				else
					ptr1 = ptr1->link;
			}
			if (!found)//if the element is not found in Abag
			{
				newnode = new nodetype;//creating a newnode and putting the element in it
				newnode->info = ptr->info;
				if (Newbag == NULL)//checking if this is the first node in the new list
				{
					newnode->link = NULL;
					Newbag = newnode;
				}
				else
				{//adding the element to an existing list
					newnode->link = Newbag;
					Newbag = newnode;
				}
			}
			ptr = ptr->link;//traversing the outer loop
		}//end of outer loop
	}//end of the else statement
	return Newbag;
}

nodetype *findmax(nodetype *Unbag)
{
	char ch;
	nodetype *current, *max;

	current = Unbag;
	ch = current->info;
	max = current;//setting the max as the head of the list

	while (current != NULL)
	{
		if (current->info > ch)//checking if the info in the current node is more than the current max
		{
			max = current;//changing the current max
			ch = current->info;
		}
		current = current->link;//traversing the list
	}
	return max;//returning the pointer to the max
}

void addnewvalue(nodetype *&Dbag, char item)
{
	nodetype *newnode;

	if (Dbag == NULL)//checking if the is a list 
	{
		newnode = new nodetype;
		newnode->info = item;
		newnode->link = NULL;
		Dbag = newnode;
	}
	else
	{//adding the value at the head of the list
		newnode = new nodetype;
		newnode->info = item;
		newnode->link = Dbag;
		Dbag = newnode;
	}
}

/*void remitem(nodetype *&Cbag, char item)
{
	nodetype *current, *temp;

	current = Cbag;
	temp = Cbag;
	if (Cbag == NULL)//checking if the list is empty
		fout << "There is no list." << endl;
	else
	{
		while (current != NULL)
		{
			if (Cbag->info == item)//checking is the item is at the head of the list
			{
				temp = Cbag->link;//setting temp to cbag link
				delete Cbag;//deleting the head
				Cbag = temp;//moving the head to temp
				current = temp;//setting the current to temp
			}
			else if (current->info == item)//if the head of the list isn't the item
			{
				temp->link = current->link;
				delete current;
				current = temp->link;
			}
			else
			{
				temp = current;//moving the list along if the the item isn't in the current node
				current = current->link;
			}
		}
	}
}*/
				
void removefirstoccurence(nodetype *&Mbag, char item, ofstream& fout)
{
	nodetype *current, *temp;
	bool found = false;

	if (Mbag == NULL)//if there is no list
		fout << "There is no list." << endl;
	else
	{
		if (Mbag->info == item)//if the head of the list has the item you're searching for
		{
			temp = Mbag->link;
			delete Mbag;
			Mbag = temp;
		}
		else
		{
			current = Mbag;
			temp = Mbag;
			while (current != NULL && !found)//searching the rest of the list for the item
			{
				if (current->info == item)
				{
					found = true;//ends the loop if you find the item
					temp->link = current->link;
					delete current;
				}
				else
				{
					temp = current;//moving both pointers along 
					current = current->link;
				}
			}
		}
	}
}

nodetype *copylist(nodetype *Ubag)
{
	nodetype *current, *head, *last, *newnode;
	if (Ubag == NULL)//if the original list is empty 
	{
		head = NULL;
		last = NULL;
	}
	else
	{
		current = Ubag;
		//copying the first node
		head = new nodetype; //create new node
		head->info = current->info; //copying info
		head->link = NULL;
		last = head;
		current = current->link;
		//copying the remaining list
		while (current != NULL)
		{
			newnode = new nodetype;
			newnode->info = current->info;
			newnode->link = NULL;
			last->link = newnode;
			last = newnode;
			current = current->link;
		}
	}
	return head;
}

void sort(nodetype *bag)
{
	nodetype *ptr = bag->link, *ptr1;
	bool found;
	char ch;

	if (bag == NULL || bag->link == NULL) 
		return;
	
	while (ptr != NULL) {
		ch = ptr->info;
		found = false;
		ptr1 = bag;
		while (ptr1 != ptr) {
			if (ptr1->info > ptr->info && !found)
			{
				ch = ptr1->info;
				ptr1->info = ptr->info;
				found = 1;
				ptr1 = ptr1->link;
			}
			else {
				if (found == 1) {
					int temp = ch;
					ch = ptr1->info;
					ptr1->info = temp;
				}
				ptr1 = ptr1->link;
			}
		}
		ptr1->info = ch;
		ptr = ptr->link;
	}
}

nodetype *unionbag(nodetype *Cbag, nodetype *Dbag)
{
	nodetype *ptr, *ptr1, *Unbag;
	ptr = Cbag;

	if (Cbag == NULL && Dbag == NULL)
		return NULL;
	else if (Cbag != NULL && Dbag == NULL)
		return Dbag;
	else if (Cbag == NULL && Dbag != NULL)
		return Cbag;
	else
	{
		while (ptr->link != NULL)
		{
			ptr = ptr->link;
		}
		ptr->link = Dbag;
	}
	return Cbag;
}