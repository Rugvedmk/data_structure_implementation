/*This programme shows BFS and DFS traversal on a Graph using matrix*/
#include <iostream>
#include <string.h>
using namespace std;

class ClgCampus{
    public:
        string area[5];
        int graph[5][5];

        ClgCampus(){
            area[0] = "Center";
            area[1] = "A wing";
            area[2] = "B wing";
            area[3] = "C wing";
            area[4] = "D wing";

            for(int i = 0;i < 5;i++){
                for(int j = 0;j<5;j++){
                    graph[i][j] = 0;
                }
            }

            graph[0][1] = 1;
            graph[1][0] = 1;
            graph[0][2] = 1;
            graph[2][0] = 1;
            graph[0][3] = 1;
            graph[3][0] = 1;
            graph[0][4] = 1;
            graph[4][0] = 1;
            graph[1][2] = 1;
            graph[2][1] = 1;
            graph[1][4] = 1;
            graph[4][1] = 1;
            graph[2][3] = 1;
            graph[3][2] = 1;
            graph[4][3] = 1;
            graph[3][4] = 1;     
        }

        int myIndex(string name);
        string myName(int index);
        void setPath();
        //void searchPath();
        void displayPaths();
        void deletePath();
        void DFS();
        void BFS();
};

//Displaying paths in matrix form
void ClgCampus :: displayPaths(){
    cout<<"\t";
    for(int i =0;i<5;i++){
        cout<<area[i]<<"\t";
    }
    cout<<endl;
    for(int i = 0; i < 5; i++){
        cout<<area[i]<<"\t";
        for(int j = 0; j<5;j++){
            cout<<graph[i][j]<<"\t";
        }
        cout<<endl;
    }
}

void ClgCampus :: setPath(){
    string startArea,endArea;
    int time;
    
    cin.ignore();
    cout<<"Enter start Area : ";
    //cin>>startArea;
    getline(cin,startArea);
    cout<<"Enter destination Area : ";
    getline(cin,endArea);
    //cin>>endArea;
    cout<<"Enter Time required : ";
    cin>>time;

    int sIndex,dIndex;
    sIndex = myIndex(startArea);
    dIndex = myIndex(endArea);

    if(sIndex != -1 && dIndex != -1){
        graph[sIndex][dIndex] = time;
        graph[dIndex][sIndex] = time;
        cout<<"Path successfully set!"<<endl;
    } else {
        cout<<"Failed to update path"<<endl;
    }
}

void ClgCampus :: deletePath(){
    string startArea,endArea;
    int time;
    
    cin.ignore();
    cout<<"Enter start Area : ";
    getline(cin,startArea);
    //cin>>startArea;
    cout<<"Enter destination Area : ";
    getline(cin,endArea);
    //cin>>endArea;
    
    time = 0;
    int sIndex,dIndex;
    sIndex = myIndex(startArea);
    dIndex = myIndex(endArea);

    if(sIndex != -1 && dIndex != -1){
        graph[sIndex][dIndex] = time;
        graph[dIndex][sIndex] = time;
        cout<<"Deleted successfully set!"<<endl;
    } else {
        cout<<"Failed to delete flight!"<<endl;
    }
}

//This function return the the area index by passing area name
int ClgCampus :: myIndex(string name){
    for(int i = 0;i<5;i++){
        if(area[i] == name){
            return i;
        }
    }
    return -1;
}

//This function return the the area name by passing area index
string ClgCampus :: myName(int index){
    if(index < 5 && index >= 0){
        return area[index];
    } 
    return "";
}

class stack{
    public:
        string *array[100];
        int top;
        stack(){
            top = -1;
        }
        void push(string *area);
        string* pop();
        bool empty();
        bool check(string element);
};

void stack :: push(string *area){
    if(top == 99){
        cout<<"The stack is full "<<endl;
    } else {
        top++;
        array[top] = area;
    }
}

string* stack :: pop(){
    if(top == -1){
        cout<<"The stack is empty!"<<endl;
        return NULL;
    } else {
        int temp = top;
        top--;
        return array[temp];
    }
}

bool stack :: empty(){
    if(top == -1){
        return true;
    } else {
        return false;
    }
}

//This function returns true if the the element is already present in the stack
bool stack :: check(string element){
    for(int i = 0;i<=top;i++){
        if(*array[i] == element){
            return true;
        }
    }
    return false;
}

void ClgCampus :: DFS(){
    stack s1,s2;
    string startArea;
    int index;
    string answer = "";

    cout<<endl;
    cin.ignore();
    cout<<"Enter start Area : ";
    getline(cin,startArea);
    index = myIndex(startArea);

    if(index == -1){
        cout<<"Wrong input!"<<endl<<endl;
        return;
    }

    s1.push(&area[index]);
    s2.push(&area[index]);

    while(!s1.empty()){
        string *temp = s1.pop();
        //cout<<*temp<<"\t";
        cout<<"Poped "<<*temp<<endl;
        answer += *temp;
        answer += "\t";

        
        for(int i = 0; i < 5;i++){
            //cout<<"graph["<<myIndex(*temp)<<"]"<<"["<<i<<"] = "<<graph[myIndex(*temp)][i]<<endl;
            if(graph[myIndex(*temp)][i] > 0){
                if(!s2.check(area[i])){
                    cout<<"Pushed "<<area[i]<<endl;
                    s1.push(&area[i]);
                    s2.push(&area[i]);
                }
            }
        }
    }
    cout<<"DFS : "<<answer<<endl;
    cout<<endl;

}

class queue{
    public:
        string *array[100];
        int front,rear;
        void push(string *name);
        string* pop();
        bool empty();
        queue(){
            front = rear = -1;
        }
        bool check(string  name);
};

void queue :: push(string *name){
    if(rear == 99){
        cout<<"The queue is full !"<<endl;
    } else {
        if(front == -1 && rear == -1){
            front++;
            rear++;
            //cout<<"pushed "<<*name<<endl;
            array[rear] = name;
        } else {
            rear++;
            //cout<<"pushed "<<*name<<endl;
            array[rear] = name;
        }
    }
}

string* queue :: pop(){
    if(front == -1){
        cout<<"The queue is already empty!"<<endl;
        return NULL;
    } else {
        if(front == rear){
            int temp = front;
            front = rear = -1;
            //cout<<"poped "<<*array[temp]<<endl;
            return array[temp];
        } else {
            int temp = front;
            front++;
            //cout<<"poped "<<*array[temp]<<endl;
            return array[temp];
        }
    }
}

bool queue :: empty(){
    if(front == -1){
        return true;
    } else {
        return false;
    }
}

//This function returns true if the the element is already present in the queue
bool queue :: check(string name){
    for(int i = front; i<= rear; i++){
        if(*array[i] == name){
            return true;
        }
    }
    return false;
}

void ClgCampus :: BFS(){
    queue q1,q2;

    string startArea;
    int index;
    string answer = "";

    cout<<endl;
    cin.ignore();
    cout<<"Enter start Area : ";
    getline(cin,startArea);
    index = myIndex(startArea);

    if(index == -1){
        cout<<"Wrong input!"<<endl<<endl;
        return;
    }


    q1.push(&area[index]);
    q2.push(&area[index]);

    while(!q1.empty()){
        //cout<<"Inside while loop!"<<endl;
        string *temp = q1.pop();
        cout<<"Poped "<<*temp<<endl;
        //cout<<*temp<<" "<<endl;;
        //cout<<*temp<<"\t";
        answer += *temp + "\t";

        for(int i = 0;i<5;i++){
            if(graph[myIndex(*temp)][i] > 0){
                if(!q2.check(area[i])){
                    cout<<"Pushed "<<area[i]<<endl;
                    q1.push(&area[i]);
                    q2.push(&area[i]);
                }
            }
        }
    }
    cout<<"BFS : "<<answer<<endl;
    cout<<endl;
}

int main(){
    ClgCampus c;
    int choice = -1;
	while(choice != 0){
		cout<<"Enter 1 to set path "<<endl;
		cout<<"Enter 2 to display paths "<<endl;
		cout<<"Enter 3 for DFS "<<endl;
		cout<<"Enter 4 for BFS "<<endl;
        cout<<"Enter 5 to delete Path"<<endl;
		cout<<"Enter 0 to exit "<<endl;
		cout<<"Enter choice : ";
		cin>>choice;
		switch(choice){
			case 1:
				c.setPath();
				break;
			
			case 2:
				c.displayPaths();
				break;
			
			case 3:
				c.DFS();
				break;

			case 4:
				c.BFS();
				break;
				
            case 5:
                c.deletePath();
                break;
		}
	}	
	
	return 0;
    //c.DFS();
    //c.BFS();
    return 1;
}

/*OUTPUT

        Center  A wing  B wing  C wing  D wing
Center  0       1       1       1       1
A wing  1       0       1       0       1
B wing  1       1       0       1       0
C wing  1       0       1       0       1
D wing  1       1       0       1       0

Enter choice : 3

DFS

Enter start Area : B wing
Poped B wing
Pushed Center
Pushed A wing
Pushed C wing
Poped C wing
Pushed D wing
Poped D wing
Poped A wing
Poped Center
DFS : B wing    C wing  D wing  A wing  Center

Enter choice : 4 

BFS

Enter start Area : B wing
Poped B wing
Pushed Center
Pushed A wing
Pushed C wing
Poped Center
Pushed D wing
Poped A wing
Poped C wing
Poped D wing
BFS : B wing    Center  A wing  C wing  D wing

*/