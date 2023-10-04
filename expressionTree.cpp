#include <iostream>
using namespace std;

class Node
{
public:
    bool optr;
    string element;
    Node *l, *r;
    bool checkOptr(string element);
    Node(string element)
    {
        l = r = NULL;
        this->element = element;
        optr = checkOptr(element);
    }
};

bool Node ::checkOptr(string element)
{
    if (element == "+" || element == "-" || element == "*" || element == "/")
    {
        return true;
    }
    else
    {
        return false;
    }
}

class Tree
{
public:
    string prefixExpr;
    // int result;
    Node *root;
    Tree()
    {
        root = NULL;
        prefixExpr = "+--a*bc/def"; //for testing purpose
    }
    void getExpr();
    void constructTree();
    void display();
    void postOrder();
    // int getResult();
};

void Tree ::getExpr()
{
    cout << "Enter the prefix expression : ";
    cin >> prefixExpr;
}

class stack
{
public:
    int top;
    Node *array[100];
    Node *pop();
    void push(Node *temp);
    bool empty();
    stack()
    {
        top = -1;
    }
};

void stack ::push(Node *temp)
{
    if (top == 99)
    {
        cout << "The stack is alredy full!" << endl;
    }
    else
    {
        top++;
        array[top] = temp;
    }
}

Node *stack ::pop()
{
    if (top == -1)
    {
        cout << "The stack is already empty!" << endl;
        return NULL;
    }
    else
    {
        int temp = top;
        top--;
        return array[temp];
    }
}

bool stack ::empty()
{
    if (top == -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Tree ::constructTree()
{
    Node *current, *temp;
    stack s1;
    int length = prefixExpr.length();
    for (int i = 0; i < length; i++)
    {
        string convert = "";
        convert += prefixExpr[i];
        current = new Node(convert);

        if (root == NULL)
        {
            if (current->optr)
            {
                root = temp = current;
                cout<<"root is : "<<root->element<<endl;
                s1.push(current);
                continue;
            }
            else
            {
                cout << "Invalid expression!" << endl;
                return;
            }
        }

        if (!current->optr)
        {
            if (temp->l == NULL)
            {   
                cout<<"pushed "<<current->element<<" to the left of "<<temp->element<<endl;
                temp->l = current;
                s1.pop();
            }
            else
            {   
                cout<<"pushed "<<current->element<<" to the right of "<<temp->element<<endl;
                temp->r = current;
                temp = s1.pop();
            }
        }
        else
        {
            if (temp->l == NULL)
            {   
                cout<<"pushed "<<current->element<<" to the left of "<<temp->element<<endl;
                temp->l = current;
                s1.push(current);
                temp = temp->l;
            }
            else
            {   
                cout<<"pushed "<<current->element<<" to the right of "<<temp->element<<endl;
                temp->r = current;
                temp = temp->r;
                s1.push(current);
            }
        }
    }
}

void Tree :: display(){
    stack s1;
    Node *temp = root;
    if(root != NULL){
        //s1.push(root);
    } else {
        cout<<"returned"<<endl;
        return;
    }

    while(1){
        while(temp != NULL){
            s1.push(temp);
            temp = temp->l;
        }

        if(s1.empty()){
            break;
        }

        temp = s1.pop();
        cout<<temp->element<<" ";
        temp = temp->r;
    }
    cout<<endl;
}

void Tree :: postOrder(){
    stack s1,s2;

    if(root != NULL){
        s1.push(root);
        //s2.push(root);
    } else {
        cout<<"The tree is empty!"<<endl;
        return;
    }
    Node* temp;
    while(!s1.empty()){
        temp = s1.pop();
        s2.push(temp);

        if(temp->l){
            s1.push(temp->l);
        }

        if(temp->r){
            s1.push(temp->r);
        }
    }

    while(!s2.empty()){
        cout<<s2.pop()->element<<" ";
    }
    cout<<endl;
}

int main(){
    
    Tree t1;
    t1.constructTree();
    cout<<"tree constructed"<<endl;
    t1.display();
    t1.postOrder();
    int choice = 1;
    do{
        cout<<"Enter 1 to insert data"<<endl;
        cout<<"Enter 2 to display postorder data"<<endl;
        cout<<"Enter 3 to display inorder data"<<endl;
        cout<<"Enter 0 to exit"<<endl;
        cout<<"Enter choice : ";
        cin>>choice;
        switch(choice){
            case 1:
                t1.getExpr();
                t1.constructTree();
                break;
            
            case 2:
                t1.postOrder();
                break;
                
            case 3:
                t1.display();
                break;
        }
    }while(choice != 0);
}

/*

constructed a tree of the expression "+--a*bc/def"
root is : +
pushed - to the left of +
pushed - to the left of -
pushed a to the left of -
pushed * to the right of -
pushed b to the left of *
pushed c to the right of *
pushed / to the right of -
pushed d to the left of /
pushed e to the right of /
pushed f to the right of +
The stack is already empty!
tree constructed

inorder
a - b * c - d / e + f

post order
a b c * - d e / - f +
*/