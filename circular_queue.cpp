//Author : Rugved Kulkarni
//Programme to display circular queue using array

/*
In this programme we take the orders of a pizza parlor and store them in a circular queue using array of size 5
*/
#include<iostream>
#include<string.h>
using namespace std;


class pizza
{   

    private:
    int front,rear;
    public:
    pizza()
    {
        front = rear = -1;
    }
    string order[5];//Array to store data orders

    bool check_full();//function to check wether the queue is full
    bool check_empty();//function to check wether the queue is empty
    void get_ord();//function to get order
    void dlt_ord();//function to delete order
    void display();//function to display order
}O;

bool pizza :: check_full()
{
    int temp = (rear + 6)%5;
    if(temp == front)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool pizza :: check_empty()
{
    if(rear == -1 && front == -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void pizza :: get_ord()
{   
    if(!check_full())
    {
        string ord;
        cout<<"Enter your order : ";
        cin.ignore();
        getline(cin,ord);
        rear = (rear + 1)%5;
        order[rear] = ord;
        if(front == -1)
        {
            front = 0;
        }
    }
    else
    {
        cout<<"The order list is full!"<<endl;
    }
    cout<<" front : "<<front<<" rear : "<<rear<<endl;
}

void pizza :: dlt_ord()
{
    if(check_empty())
    {
        cout<<"The list is alredy empty"<<endl;
    }
    else if (rear == front)
    {
        front = rear = -1;
    }
    else
    {
        front = (front + 1)%5;
    }
}

void pizza :: display()
{   
    if(check_empty())
    {
        cout<<"The list is empty!"<<endl;
    }
    else if(front == rear)
    {
        int temp = front;
        int i = 1;
        cout<<"Order "<<i<<" : "<<order[temp]<<endl;
    }
    else
    {
    int temp = front;
    int i = 1;
    while (temp != rear)
    {
        cout<<"Order "<<i<<" : "<<order[temp]<<endl;
        temp = (temp + 1)%5;
        i++;
    }
    cout<<"Order "<<i<<" : "<<order[temp]<<endl; 
    }    
}

int main()
{   
    int ch = 1;
    while(ch != 0)
    {
        cout<<"Enter 1 to get order\nEnter 2 display order\nEnter 3 to delete order\nEnter 0 to exit\nEnter choice : ";
        cin>>ch;
        switch (ch)
        {
        case 1:
            O.get_ord();
            break;
        
        case 2:
            O.display();
            break;
        
        case 3:
            O.dlt_ord();
            break;
        
        default:
            break;
        }
    }
    return 0;
}