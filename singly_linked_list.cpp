// Author : Rugved Kulkarni
// This is the programme illustrating an example of singly linked list
/*
This is a programme to store the data of members of 'Pinnacle Club'
Functions to perform following operations are present in this programme using the concept of singly linked list

1)Set data
2)Display data
3)Create alinked list
4)Adding members
5)Deleting members
6)Display list

*/

#include <iostream>
#include <string.h>
using namespace std;

// Node
class Pinnacle
{
public:
    int PRN;
    string name;
    string year;
    string post;
    Pinnacle *next;
    void set_data();
    void display();
};

// Function to set the data of node
void Pinnacle ::set_data()
{
    cout << "Enter data : " << endl;
    cout << "PRN :";
    cin >> PRN;
    cout << "Name : ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter year : ";
    cin >> year;
}

// Function to display the data of node
void Pinnacle ::display()
{
    cout << "Name : " << name << endl;
    cout << "Year : " << year << endl;
    cout << "post : " << post << endl;
    cout << "PRN : " << PRN << endl;
}

// Linked list to handle multiple nodes
class Club_list
{
private:
    Pinnacle *president, *current;
    // Head node = presedint
public:
    Pinnacle *secretary;
    // Tail node = seceratory
    int count_members;
    Club_list()
    {
        president = secretary = NULL;
    }
    void create_list();
    void append();
    void del();
    void display();
    friend Club_list operator+(Club_list start_list, Club_list end_list);
};

// Creating a new list
void Club_list ::create_list()
{
    Pinnacle *temp1 = new Pinnacle();
    cout << "The data will be taken for PRESIDENT : " << endl;
    temp1->set_data();
    temp1->post = "PRESIDENT";
    president = temp1;
    Pinnacle *temp2 = new Pinnacle();
    cout << "The data will be taken for SECRETARY : " << endl;
    temp2->set_data();
    temp2->post = "SECRETARY";
    president->next = secretary;
    secretary->next = NULL;
    current = president;
    count_members = 2;
}

// Adding a node to the list
void Club_list ::append()
{
    Pinnacle *temp = new Pinnacle();
    temp->set_data();
    temp->post = "Member";
    temp->next = current->next;
    current->next = temp;
    count_members++;
}

// Function to delete the members of list
void Club_list ::del()
{
    cout << "Enter 1 to remove a member : " << endl;
    cout << "Enter 2 to remove a president : " << endl;
    cout << "Enter 3 to remove a secretary : " << endl;
    int ch;
    cout << "Enter choice : ";
    cin >> ch;
    if (ch == 1)
    {
        Pinnacle *temp, *temp1;
        temp = president->next;
        temp1 = president;
        string name;
        cout << "Enter name : ";
        cin.ignore();
        getline(cin, name);
        //Loop to find the node to be deleted
        while (temp->name != name || temp->next->post != "SECRETARY")
        {   
            //Seperating the node from the list
            temp1 = temp;
            temp = temp1->next;
        }
        if (temp->name == name)
        {
            temp1->next = temp->next;
            delete temp;
            cout << "Member removed " << endl;
        }
        else
        {
            cout << "No member of name " << name << " exist in the club " << endl;
        }
    }
    //Similar algorithm is applied in deleting president(head) and seceratory(tail)
    if (ch == 2)
    {
        Pinnacle *temp, *temp1;
        temp = president->next;
        temp1 = president;
        string name;
        cout << "Enter name of new president (the president should be a member of club): ";
        cin.ignore();
        getline(cin, name);
        while (temp->name != name || temp->next->post != "SECRETARY")
        {
            temp1 = temp;
            temp = temp1->next;
        }
        if (temp->name == name)
        {
            temp1->next = temp->next;
            president->PRN = temp->PRN;
            president->name = temp->name;
            president->year = temp->year;
            delete temp;
            cout << "The data of the new president is : " << endl;
            president->display();
        }
    }
    if (ch == 3)
    {
        Pinnacle *temp, *temp1, *temps, *temps1;
        temp = president->next;
        temps = president->next;
        temp1 = president;
        string name;
        cout << "Enter name of new secratary (the president should be a member of club): ";
        cin.ignore();
        getline(cin, name);
        while (temp->name != name || temp->next->post != "SECRETARY")
        {
            temp1 = temp;
            temp = temp1->next;
        }
        while (temps->post != "SECRETARY")
        {
            temps1 = temps;
            temps = temps1->next;
        }
        if (temp->name == name)
        {
            temp1->next = temp->next;
            secretary->PRN = temp->PRN;
            secretary->name = temp->name;
            secretary->year = temp->year;
            delete temp;
            cout << "The data of the new seratary is : " << endl;
            secretary->display();
        }
    }
}

// Function to display the members of list
void Club_list ::display()
{
    Pinnacle *temp;
    temp = president;
    while (temp != NULL)
    {
        temp->display();
        temp = temp->next;
    }
}

// Overloading '+' operator to add 2 lists
Club_list operator+(Club_list start_list, Club_list end_list)
{
    Club_list l3;
    l3 = start_list;
    l3.secretary->next = end_list.president;
    l3.count_members = start_list.count_members + end_list.count_members;
}

// Error handler for joining 2 lists
void er_lis_num(int count_list, int *lis_num)
{
    try
    {
        if (*lis_num == 0)
        {
            /* code */
        }
        if (*lis_num >= count_list)
        {
            throw *lis_num;
        }
    }
    catch (int *lis_num)
    {
        cout << "Invalid list number please enter the correct list number or 0 to exit : ";
        cin >> *lis_num;
        er_lis_num(count_list, lis_num);
    }
}

int main()
{
    Club_list *l[5];
    int count_list = 0;
    int ch;
    do
    {
        cout << "Press 1 if you want to create a list " << endl;
        cout << "Press 2 if you want to work on a list " << endl;
        cout << "Press 3 if you want to concatanate two lists " << endl;
        cout << "Press 4 if you want to exit " << endl;
        cout << "Enter choice : ";
        cin >> ch;
        if (ch == 1)
        {
            l[count_list] = new Club_list();
            l[count_list]->create_list();
            count_list++;
        }
        else if (ch == 2)
        {
            int lis_num;
            cout << "Enter list number on which you want to work : ";
            cin >> lis_num;
            er_lis_num(count_list, &lis_num);

            int operation;
            do
            {
                if (lis_num != 0)
                {

                    cout << "Press 1 if you want to append a data member " << endl;
                    cout << "Press 2 if you want to delete a data member in the list " << endl;
                    cout << "Press 3 if you want to display a list " << endl;
                    cout << "Press 4 if you want to exit " << endl;
                    cout << "Please enter your choice : ";
                    cin >> operation;
                    if (operation == 1)
                    {
                        l[lis_num - 1]->append();
                    }
                    else if (operation == 2)
                    {
                        l[lis_num - 1]->del();
                    }
                    else if (operation == 3)
                    {
                        l[lis_num - 1]->display();
                    }
                }
            } while (operation != 4);
        }
        else if (ch == 3)
        {
            int lis_num1, lis_num2;
            cout << "Enter list number : " << endl;
            cout << "list 1 : ";
            cin >> lis_num1;
            cout << "list 2 : ";
            cin >> lis_num2;
            l[count_list] = new Club_list();
            *l[count_list] = *l[lis_num1] + *l[lis_num2];
            count_list++;
            cout << "The concatenated list is stored at number " << count_list << endl;
        }

    } while (ch != 4);
}