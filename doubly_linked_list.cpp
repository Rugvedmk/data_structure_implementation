//Author : Rugved Kulkarni
//Programme to display doubly linked list

/*
This is the programme taking binary digit from the user and performing operations such as :

1)1's complement
2)2's complement

using the concept of doubly linked list
*/


#include <iostream>
using namespace std;

//Node
class binary
{
public:
	int bit;
	binary *nex, *prev;
	
	//Function to set data
	void setdata();

	//Function to display
	void display();
	binary()
	{
		nex = prev = NULL;
	}
};

void binary ::setdata()
{
	cout << "Enter bit : ";
	cin >> bit;
	nex = NULL;
	prev = NULL;
}

void binary ::display()
{
	cout << bit;
}

//Doubly linked list
class lis
{
private:
	binary *head;

public:
	binary *tail, *current;

	//Function to create list
	void create();

	//Function to add data member to the list
	void append();

	//Function to display list
	void display();

	//1's complement
	void com1();

	//2's complement
	void com2();
} l;


void lis ::create()
{
	binary *temp1, *temp2;
	temp1 = new binary();
	cout << "Enter MSB : " << endl;
	temp1->setdata();
	head = temp1;
	temp2 = new binary();
	cout << "Enter LSB : " << endl;
	temp2->setdata();
	tail = temp2;
	head->prev = NULL;
	head->nex = tail;
	tail->prev = head;
	tail->nex = NULL;
	current = head;
}

void lis ::append()
{
	binary *temp;
	temp = new binary();
	temp->setdata();
	current->nex->prev = temp;
	temp->nex = current->nex;
	current->nex = temp;
	temp->prev = current;
	current = temp;
}

void lis ::display()
{
	binary *temp;
	temp = head;
	while (temp != NULL)
	{
		temp->display();
		temp = temp->nex;
	}
	cout << "\n";
}

void lis ::com1()
{
	binary *temp;
	temp = head;
	while (temp != NULL)
	{

		if (temp->bit == 0)
		{
			temp->bit = 1;
		}
		else if (temp->bit == 1)
		{
			temp->bit = 0;
		}
		temp = temp->nex;
	}
}

void lis ::com2()
{	
	com1();
	int check;
	binary *temp;
	temp = tail;
	temp->bit += 1;
	while (temp != NULL)
	{
		check = 1;
		if (temp->bit == 2)
		{
			check = temp->bit;
			temp->bit = 0;
			if (temp->prev != NULL)
			{
				temp->prev->bit += 1;
			}
		}

		temp = temp->prev;
	}
	if (check == 2)
	{
		binary *temp2;
		temp2 = new binary();
		head->bit = 0;
		temp2->bit = 1;
		temp2->nex = head;
		head = temp2;
	}
}

int main()
{
	int ch;
	ch = 1;
	do
	{
		cout << "Press 1 if you want to create a list " << endl;
		cout << "Press 2 if you want to append a data member " << endl;
		cout << "Press 3 if you want to display a list " << endl;
		cout << "Press 4 if you want 1's complement the list " << endl;
		cout << "Press 5 if you want 2's complement of the list " << endl;
		cout << "Press 6 if you want to exit " << endl;
		cout << "Enter choice : ";
		cin >> ch;
		if (ch == 1)
		{
			l.create();
		}
		if (ch == 2)
		{
			l.append();
		}
		if (ch == 3)
		{
			l.display();
		}
		if (ch == 4)
		{
			l.com1();
		}
		if (ch == 5)
		{
			l.com2();
		}
	} while (ch != 6);
	return 0;
}
