//Author : Rugved Kulkarni
//Programme to display doubly ended queue using linked list

#include<iostream>
#include<string.h>
using namespace std;


//Node to store data
class node
{
    
    public:
        node()
        {
            nex = prev = NULL;
        }
        node *nex,*prev;
        string data;
        void set_data();//Function to wrtie data in the node
        void get_data();//Function to display data in the node
};

void node :: set_data()
{
    cout<<"Enter data : ";
    cin.ignore();
    getline(cin,data);
}

void node :: get_data()
{
    cout<<"Data : "<<data<<endl;    
}


//Queue to handle the nodes
class dqueue
{
private:
    node *head,*tail;
public:
    dqueue()
    {
        head = tail = NULL;
    }
        void add_front();//Add's the node in the front 
        void dlt_front();//deletes the node in the front
        void add_rear();//Add's the node in the rear
        void dlt_rear();//deletes the node in the rear
        void display();//Display's the queue
}dq;

void dqueue :: add_front()
{   
    if(head == NULL)
    {
        node *temp;
        temp = new node();
        temp->set_data();
        temp->get_data();
        head = tail = temp;
    }
    else
    {
        node *temp;
        temp = new node();
        temp->set_data();
        temp->get_data();
        temp->nex = head;
        head->prev = temp;
        head = temp;
    }
}

void dqueue :: dlt_front()
{   
    if(head == NULL)
    {
        cout<<"The list is already empty! "<<endl;
    }
    else
    {
        node *temp;
        temp = head;
        temp->get_data();
        if(head == tail)
        {
            head = tail = NULL;
        }
        else
        {
            head = temp->nex;
        }
        if(head != NULL){
            head->prev = NULL;
        }
        delete temp;
    }
}

void dqueue :: add_rear()
{   
    if(tail == NULL)
    {
        node *temp;
        temp = new node();
        temp->set_data();
        temp->get_data();
        head = tail = temp;
    }
    else
    {
        node *temp;
        temp = new node();
        temp->set_data();
        temp->get_data();
        temp->prev = tail;
        tail->nex = temp;
        tail = temp;
    }
}

void dqueue :: dlt_rear()
{   
    if(tail == NULL)
    {
        cout<<"The list is already empty! "<<endl;
    }
    else
    {
        node *temp;
        temp = tail;
        temp->get_data();
        if(head == tail)
        {
            head = tail = NULL;
        }
        else
        {
            tail = temp->prev;
        }
        if(tail != NULL){
            head->nex = NULL;
        }
        delete temp;
    }
}

void dqueue :: display()
{   
    node* temp;
    temp = head;
    int i = 1;
    while(temp != NULL)
    {   
        cout<<i<<") ";
        temp->get_data();
        temp = temp->nex;
        i++;
    }
}

int main()
{   
    int ch = 1;
    while(ch != 0)
    {
        cout<<"Enter 1 to add data at front\nEnter 2 to delete data at front\nEnter 3 to add data at rear";
        cout<<"\nEnter 4 to delete data at rear\nEnter 5 to display data\nEnter choice : ";
        cin>>ch;
        switch (ch)
        {
        case 1:
            dq.add_front();
            break;
        case 2:
            dq.dlt_front();
            break;

        case 3:
            dq.add_rear();
            break;
        
        case 4:
            dq.dlt_rear();
            break;
        
        case 5:
            dq.display();
        
        default:
            break;
        }
    }
    return 0;
}