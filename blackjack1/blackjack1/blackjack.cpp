#include<cstdlib>
#include<iomanip>
#include<iostream>
#include<fstream>
#include<ctime>
#include "stack.h"
#include<string>

using namespace std;

ofstream fout;
ifstream fin;

void getcardindex(stacktype &stk1);
void printarestore(stacktype &stk1);
void getcardname(string arr[]);
void getcardnum(int arr[]);
void printcards(string arr[], int intarr[]);
void readshuffle(stacktype &stk1, string arr[], int intarr[]);
int cardtotal(int intarr[], bool &bust, int card1, int card2, int card3, int card4, int card5, int card6, int count, bool &bj, string arr[]);
void draw2card(stacktype &stk1, int &card1, int &card2, bool &deck);
void drawcard(stacktype &sk1, int &card, bool &deck);
bool hit();
bool continueMenu();


int main()
{
	fout.open("deckofcards.txt");

	stacktype stk1;
	int cardnum[200], chips = 1000, card1, card2, card3, card4, card5, card6, bet, total, dealer, total1, count;
	string cardname[200];
	bool bust, deckEmpty = false, blackjack, blackjack1, bust1, betting, hit_stay, won, tie;

	getcardindex(stk1);
	//printarestore(stk1);

	getcardname(cardname);
	getcardnum(cardnum);
	//printcards(cardname, cardnum);

	fout << endl << "The shuffled deck." << endl;
	readshuffle(stk1, cardname, cardnum);

	bool exit = false;

	while (chips > 0 && !exit && !deckEmpty)
	{//begins the round of blackjack
		count = 0;
		card1 = 0;
		card2 = 0;
		card3 = 0;
		card4 = 0;
		card5 = 0;
		card6 = 0;
		bust = false;
		bust1 = false;
		blackjack = false;
		blackjack1 = false;
		betting = false;
		won = false;
		tie = false;
		exit = false;


		cout << "You have " << chips << " chips. How many in sets of 25 do you wish to bet." << endl;
		while (!betting)//getting the players bet
		{
			cin >> bet;
			if (bet % 25 == 0 && bet <= chips)
				betting = true;
			else
				cout << "Invalid bet. Try again." << endl;
		}

		draw2card(stk1, card1, card2, deckEmpty);//dealing the first 2 cards to the player
												 //display the players cards here
		if (!deckEmpty);//checks that the deck is not empty after the cards were dealt
		{
			total = cardtotal(cardnum, bust, card1, card2, card3, card4, card5, card6, count, blackjack, cardname);//card total after the first two cards
			if (!blackjack)
				hit_stay = hit();//player decides if they want to hit or stay
			while (hit_stay && !bust && !deckEmpty && count < 4 && !blackjack)//doesn't allow player to have more than 6 cards
			{//the players actions during the round
				count++;
				if (count == 1)//checks if player is getting the 3rd card or upwards
					drawcard(stk1, card3, deckEmpty);
				else if (count == 2)
					drawcard(stk1, card4, deckEmpty);
				else if (count == 3)
					drawcard(stk1, card5, deckEmpty);
				else
					drawcard(stk1, card6, deckEmpty);

				if (!deckEmpty)
				{//checks if the deck was empty when you picked up the last card
					total = cardtotal(cardnum, bust, card1, card2, card3, card4, card5, card6, count, blackjack, cardname);
					//need to display the players cards here
					if (count < 5 && !bust && !blackjack)
						hit_stay = hit();
					else if (bust)//bust becomes true when the total is over 21 
					{
						cout << "Bust. you lose." << endl;
						chips = chips - bet;
					}
					else if (blackjack)//this becomes true when your total is equal to 21
					{
						cout << "YOU GOT BLACKJACK... now let's see if the dealer can match it." << endl;
					}
				}

			}
		}


		count = 0;
		card1 = 0;
		card2 = 0;
		card3 = 0;
		card4 = 0;
		card5 = 0;
		card6 = 0;
		total1 = 0;


		cout << endl << endl;
		if (!bust)//no reason for the dealer to play if the player has already gone over 21
		{
			cout << "Now let's see if you've beaten the house." << endl << endl;
			draw2card(stk1, card1, card2, deckEmpty);
			if (!deckEmpty)
			{
				total1 = cardtotal(cardnum, bust1, card1, card2, card3, card4, card5, card6, count, blackjack1, cardname);
				system("pause");
				if (!blackjack1)
				{
					while (!bust1 && !deckEmpty && !blackjack1 && count < 4 && !won && !tie)
					{
						count++;
						if (count == 1)//checks if player is getting the 3rd card or upwards
							drawcard(stk1, card3, deckEmpty);
						else if (count == 2)
							drawcard(stk1, card4, deckEmpty);
						else if (count == 3)
							drawcard(stk1, card5, deckEmpty);
						else
							drawcard(stk1, card6, deckEmpty);

						if (!deckEmpty)
						{//checks if the deck was empty when you picked up the last card
							total1 = cardtotal(cardnum, bust1, card1, card2, card3, card4, card5, card6, count, blackjack1, cardname);

							if (bust1)
								cout << "BUST. you win" << endl;
							else if (total1 > total)
								won = true;
							else if (total1 == total && total1 >= 18)
								tie = true;
						}
						system("pause");
					}
				}
			}
			cout << endl << endl;

			cout << "Your cards total was " << total << endl;
			cout << "The houses cards total was " << total1 << endl;
			if (bust)//removing or adding chips based whether the player wins or loses
				chips -= bet;
			else if (bust1)
				chips += bet;
			else if (total > total1)
			{
				cout << "You win." << endl;
				chips += bet;
			}
			else if (total1 > total)
			{
				cout << "You lose." << endl;
				chips -= bet;
			}
			else
				cout << "Tie game" << endl;

			cout << endl << endl;
		}
		exit = continueMenu();//decides whether the game will continue or not
	}
	
	if (deckEmpty)
		cout << "The game has ended because the deck is Empty." << endl;
	if (chips == 0)
		cout << "Return when you have more chips." << endl;
	else
		cout << "You have " << chips << " remaining. We're ready to take them back anytime." << endl;

	fout.close();
	system("pause");
	return 0;
}

void getcardindex(stacktype &stk1)
{//gets the index number for the parralel arrays that represent the cards
	stacktype temp;
	el_t elem, num;
	int random_int = 1, count = 0;
	bool first = true, found;

	srand(time(0));

	while (random_int <= 52)
	{//sets the indexs into a stack, this way they simulate a shuffled deck
		found = false;
		num = rand() % 52;
		if (!stk1.isEmptyStack())
		{
			while (!stk1.isEmptyStack())
			{
				stk1.pop(elem);
				temp.push(elem);
				if (elem == num)
					found = true;

			}
			if (!found)
			{//after checking to make sure the new number isn't already in the stack it adds it in
				temp.push(num);
				random_int++;
			}
			while (!temp.isEmptyStack())
			{
				temp.pop(elem);
				stk1.push(elem);
			}
		}
		else
		{
			stk1.push(num);
			random_int++;
		}
	}

}

void printarestore(stacktype &stk1)
{//prints the elements of a stack and restores the stack
	stacktype tempstk;
	el_t element;
	int num = 1;

	fout << "Below are the elements of a stack" << endl;

	while (!stk1.isEmptyStack())
	{
		stk1.pop(element);
		fout << element << " ";
		if (num % 10 == 0)
			fout << endl;
		tempstk.push(element);
		num++;
	}

	fout << endl << endl;

	while (!tempstk.isEmptyStack())
	{
		tempstk.pop(element);
		stk1.push(element);
	}
}//end printarestore

void getcardname(string arr[])
{//gets the name of each card from a file and sets it in a particular index
	fin.open("cardStrings.txt");

	for (int i = 0; i < 52; i++)
	{
		getline(fin, arr[i]);
	}

	fin.close();
}

void getcardnum(int arr[])
{//gets the number value of each card 
	fin.open("cardInts.txt");

	int num;

	for (int i = 0; i < 52; i++)
	{
		fin >> num;
		arr[i] = num;
	}

	fin.close();
}

void printcards(string arr[], int intarr[])
{//prints the card names and number value so we can check to make sure they match
	int num;
	string str;

	for (int i = 0; i < 52; i++)
	{
		str = arr[i];
		num = intarr[i];
		fout << str << " " << num << endl;
	}
}

void readshuffle(stacktype &stk1, string arr[], int intarr[])
{//shows the card names and values in a shuffled state
	string str;
	stacktype temp;
	el_t elem;

	while (!stk1.isEmptyStack())
	{
		stk1.pop(elem);
		temp.push(elem);
		fout << arr[elem] << " " << intarr[elem] << endl;
	}

	while (!temp.isEmptyStack())
	{
		temp.pop(elem);
		stk1.push(elem);
	}
}

int cardtotal(int intarr[], bool &bust, int card1, int card2, int card3, int card4, int card5, int card6, int count, bool &bj, string arr[])
{//calculates the total value of the cards that the player has
	int total = 0;

	if (count == 0)
	{
		total = intarr[card1] + intarr[card2];
		cout << "The cards are." << endl;
		cout << arr[card1] << "  and  " << arr[card2] << endl;
	}
	else if (count == 1)
	{
		total = intarr[card1] + intarr[card2] + intarr[card3];
		cout << "The cards are." << endl;
		cout << arr[card1] << "  and  " << arr[card2] << "  and  " << arr[card3] << endl;
	}
	else if (count == 2)
	{
		total = intarr[card1] + intarr[card2] + intarr[card3] + intarr[card4];
		cout << "The cards are." << endl;
		cout << arr[card1] << "  and  " << arr[card2] << "  and  " << arr[card3] << "  and  " << arr[card4] << endl;
	}
	else if (count == 3)
	{
		total = intarr[card1] + intarr[card2] + intarr[card3] + intarr[card4] + intarr[card5];
		cout << "The cards are." << endl;
		cout << arr[card1] << "  and  " << arr[card2] << "  and  " << arr[card3] << "  and  " << arr[card4] << "  and  " << arr[card5] << endl;
	}
	else if (count == 4)
	{
		total = intarr[card1] + intarr[card2] + intarr[card3] + intarr[card4] + intarr[card5] + intarr[card6];
		cout << "The cards are." << endl;
		cout << arr[card1] << "  and  " << arr[card2] << "  and  " << arr[card3] << "  and  " << arr[card4] << "  and  " << arr[card5] << "  and  " << arr[card6] << endl;
	}

	if (total == 21)
	{
		bj = true;
		cout << total << endl;
		return total;
	}

	if (total > 21 && intarr[card1] == 11)
		intarr[card1] = 1;
	if (total > 21 && intarr[card2] == 11)
		intarr[card2] = 1;
	if (total > 21 && intarr[card3] == 11)
		intarr[card3] = 1;
	if (total > 21 && intarr[card4] == 11)
		intarr[card4] = 1;
	if (total > 21 && intarr[card5] == 11)
		intarr[card5] = 1;
	if (total > 21 && intarr[card6] == 11)
		intarr[card6] = 1;

	if (total > 21)
		bust = true;
	cout << total << endl; 
	return total;
}

void draw2card(stacktype &stk1, int &card1, int &card2, bool &deck)
{//draws the first 2 cards for the player
	el_t elem;

	if (!stk1.isEmptyStack())
	{
		stk1.pop(elem);
		card1 = elem;
		if (!stk1.isEmptyStack())
		{
			stk1.pop(elem);
			card2 = elem;
		}
		else
		{
			deck = true;
		}
	}
	else
		deck = true;
}

void drawcard(stacktype &stk1, int &card, bool &deck)
{//draws a card from the deck
	el_t elem;

	if (!stk1.isEmptyStack())
	{
		stk1.pop(elem);
		card = elem;
	}
	else
		deck = true;
}

bool hit()
{//menu for hit or stay
	char answer;
	bool f = false;

	cout << "Do you want to hit or stay? (Enter 'h' for hit and 's' for stay.)" << endl;
	cin >> answer;

	while (f == false)
	{
		if ((answer == 'h') || (answer == 'H'))//returns true for hit
			return true;
		else if ((answer == 's') || (answer == 'S'))//returns false for stay
			return false;
		else
		{//lets the player know the answer was invalid
			cout << answer << " is an invalid choice. Please enter 'h' for hit and 's' for stay." << endl;
			cin >> answer;
		}
	}

}

bool continueMenu()
{//menu to continue or exit
	char answer;
	bool f = false;

	cout << "Would you like to continue to another round or exit the game? (Enter 'c' for continue and 'e' for exit.)" << endl;
	cin >> answer;

	while (f == false)
	{
		if ((answer == 'c') || (answer == 'C'))//returns false if the player wants to continue
			return false;
		else if ((answer == 'e') || (answer == 'E'))//returns true if the player wants to exit
			return true;
		else
		{
			cout << answer << " is an invalid choice. Please enter 'c' for continue and 'e' for exit." << endl;
			cin >> answer;
		}
	}

}
