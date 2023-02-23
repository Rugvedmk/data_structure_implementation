//Author : Rugved Kulkarni
//This programme illustrates the functioning of stack

/*
This programme converts infix to post fix conversion of expression and post fix expression evaluation
*/


#include<iostream>
#include<string.h>
using namespace std;

string exp,c_exp = "";
string temp = "";
char stack[10];//Stack for converting in-fix to post-fix expressiom
float e_stack[10];//Stack for evaluating post-fix expression
int e_top = -1;//Top for e_stack
int top = -1;//Top for stack
int s_len = 0;//Stores the length of in-fix expression(c_exp) 
int c_len = -1;//Stores the length of post-fix expression

void get_exp()
{   
    exp = "";
    s_len = 0;
    cout<<"Enter the expression : ";
    cin.ignore();
    getline(cin,exp);
    while(exp[s_len] != '\0')
    {
        s_len++;
    }
}


//this function gives the priority of different operators
int prio(char c)
{
    if (c == '+' || c == '-')
    {
        return 1;
    }
    else if (c == '*' || c == '/')
    {
        return 2;
    }
}

void evaluate()
{   
    conversion();
    for(int i = 0;i<=c_len;i++)
    {
        if(c_exp[i] == '+' || c_exp[i] == '-' || c_exp[i] == '*' || c_exp[i] == '/')
        {
            if(c_exp[i] == '+')
            {   
                float temp1;
                temp1 =(float)e_stack[e_top] + e_stack[e_top - 1];
                e_top--;
                e_stack[e_top] = temp1;
                cout<<" e_top : "<<e_top<<" estack : "<<e_stack[e_top]<<endl;
            }
            else if(c_exp[i] == '-')
            {   
                float temp1;
                temp1 = (float)e_stack[e_top - 1] - e_stack[e_top];
                e_top--;
                e_stack[e_top] = temp1;
                cout<<" e_top : "<<e_top<<" estack : "<<e_stack[e_top]<<endl;
            }
            else if(c_exp[i] == '*')
            {   
                float temp1;
                temp1 = (float)e_stack[e_top - 1] * e_stack[e_top];
                e_top--;
                e_stack[e_top] = temp1;
                cout<<" e_top : "<<e_top<<" estack : "<<e_stack[e_top]<<endl;
            }
            else if(c_exp[i] == '/')
            {   
                float temp1;
                temp1 = (float)e_stack[e_top - 1] / e_stack[e_top];
                e_top--;
                e_stack[e_top] = temp1;
                cout<<" e_top : "<<e_top<<" estack : "<<e_stack[e_top]<<endl;
            }
        }
        else if(c_exp[i] == ' ')
        {
            if(temp == "")
            {}
            else
            {   
                e_top++;
                e_stack[e_top] = stoi(temp);
                //stoi() is the function converting string to integer
                cout<<" e_top : "<<e_top<<" estack : "<<e_stack[e_top]<<endl;
                temp = "";
            }
        }
        else
        {   
            temp += c_exp[i]; 
        }
    }
    
    cout<<"The evaluated value is : "<<e_stack[0]<<endl;
    e_top = -1;
}

void conversion()
{   
    c_exp = "";
    c_len = -1;
    for(int i = 0;i<s_len;i++)
    {
        if(exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/')
        {   
            if(top == -1)
            {
                top++;
                stack[top] = exp[i]; 
            }
            else if(prio(stack[top]) < prio(exp[i]))
            {
                top++;
                stack[top] = exp[i];
            }
            else
            {
                while(stack[top] > exp[i] || top != -1)
                {   
                    c_exp += ' ';
                    c_len++;
                    c_exp += stack[top];
                    c_len++;
                    top--;
                }
                top++;
                stack[top] = exp[i];
            }
        }
        else if(exp[i] == ' ')
        {}
        else
        {   
            c_exp += " ";
            c_exp += exp[i];
            c_len++;
            c_len++;
        }
    }
    while (top != -1)
    {   
        c_exp += " ";
        c_len++;
        c_exp += stack[top];
        c_len++;
        top--;
    }
    
    cout<<"The converted expression is : "<<c_exp<<" len "<<c_len<<endl;
}

int main()
{
    int ch = 1;
    while(ch != 0)
    {
        cout<<"Enter 1 to enter the expression\nEnter 2 to convert the expression\nEnter 3 to get the converted expression\n";
        cout<<"Enter 4 to evaluate the expression\nEnter 0 to exit\nEnter choice : ";
        cin>>ch;
        if(ch == 1)
        {
            get_exp();
        }
        else if (ch == 2)
        {
            conversion();
        }
        else if(ch == 3)
        {
            cout<<"The converted expression is : "<<c_exp<<endl;
        }
        else if(ch == 4)
        {
            evaluate();
        }

    }
    return 0;
}