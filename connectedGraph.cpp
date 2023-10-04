/*It is a programme in which functioning of connected graph using Matrix is shown*/
#include <iostream>
using namespace std;


class Flight{
    public :
        string city[5];
        int flight[5][5];
        Flight(){
            city[0] = "A";
            city[1] = "B";
            city[2] = "C";
            city[3] = "D";
            city[4] = "E";

            for(int i = 0; i < 5;i++){
                for(int j = 0; j < 5;j++){
                    flight[i][j] = 0;
                }
            }

            flight[0][1] = 5;
            flight[1][0] = 5;
            flight[0][2] = 5;
            flight[2][0] = 5;
            flight[1][3] = 5;
            flight[3][1] = 5;
            flight[2][4] = 5;
            flight[4][2] = 5;
            //flight[4][0] = 5;
            //flight[0][4] = 5;
        }

        string getCity(int index);
        int getIndex(string city);
        void setFlight();
        void searchFlight();
        void displayFlights();
        void deleteFlight();
};

//Displaying flights in matrix form
void Flight :: displayFlights(){
    cout<<"\t";
    for(int i =0;i<5;i++){
        cout<<city[i]<<"\t";
    }
    cout<<endl;
    for(int i = 0; i < 5; i++){
        cout<<city[i]<<"\t";
        for(int j = 0; j<5;j++){
            cout<<flight[i][j]<<"\t";
        }
        cout<<endl;
    }
}

//This function return the the city name by passing city index
string Flight :: getCity(int index){
    if(index < 5){
        return city[index];
    } else {
        return "-1";
    }
}

//This function return the the city index by passing city name
int Flight :: getIndex(string searchCity){
    for(int i = 0;i<5;i++){
        if(city[i] == searchCity){
            return i;
        }
    }
    return -1;
}

void Flight :: setFlight(){
    string startCity,endCity;
    int fuel;
    
    cout<<"Enter start city : ";
    cin>>startCity;
    cout<<"Enter destination city : ";
    cin>>endCity;
    cout<<"Enter fuel required : ";
    cin>>fuel;

    int sIndex,dIndex;
    sIndex = getIndex(startCity);
    dIndex = getIndex(endCity);

    if(sIndex != -1 && dIndex != -1){
        flight[sIndex][dIndex] = fuel;
        flight[dIndex][sIndex] = fuel;
        cout<<"Path successfully set!"<<endl;
    } else {
        cout<<"Failed to update path"<<endl;
    }
}

void Flight :: deleteFlight(){
    string startCity,endCity;
    int fuel;
    
    cout<<"Enter start city : ";
    cin>>startCity;
    cout<<"Enter destination city : ";
    cin>>endCity;
    
    fuel = 0;
    int sIndex,dIndex;
    sIndex = getIndex(startCity);
    dIndex = getIndex(endCity);

    if(sIndex != -1 && dIndex != -1){
        flight[sIndex][dIndex] = fuel;
        flight[dIndex][sIndex] = fuel;
        cout<<"Deleted successfully set!"<<endl;
    } else {
        cout<<"Failed to delete flight!"<<endl;
    }
}


class Node{
    public:
        string cityName;
        int currentIndex,totalFuel,myIndex;
        Node(string name,Flight f){
            cityName = name;
            myIndex = f.getIndex(name);
            currentIndex = 0;
            totalFuel = 0;
        }
};

class stack{
    public:
        int top;
        stack(){
            top = -1;
        }
        Node *array[100];
        void push(Node *putTop);
        Node *pop();
        bool empty();
        bool checkElement(string name);
        Node* getTop();
};

Node* stack :: getTop(){
    if(top != -1){
        return array[top];
    } else {
        return NULL;
    }
}

void stack :: push(Node *putTop){
    if(top == 99){
        cout<<"The stack is already full"<<endl;
    } else {
        top++;
        array[top] = putTop;
    }
}

Node* stack :: pop(){
    if(top == -1){
        cout<<"The stack is alredy empty"<<endl;
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
bool stack :: checkElement(string name){
    for(int i = 0;i<= top;i++){
        if(array[i]->cityName == name){
            return true;
        }
    }
    return false;
}

//This functio search the connected cities via flight
//It uses backtracking algorithm to search the connected cities if they are not connected directly
//It also shows stack operations performed during search
//test A to E to know the algo fully
void Flight :: searchFlight(){
    string startCity,endCity;
    
    cout<<"Enter start city : ";
    cin>>startCity;
    cout<<"Enter destination city : ";
    cin>>endCity;
    cout<<endl;

    stack s1;
    Node *current;

    if(flight[getIndex(startCity)][getIndex(endCity)] != 0){
        cout<<"The fuel required to reach from "<<startCity<<" to "<<endCity<<" is "<<flight[getIndex(startCity)][getIndex(endCity)]<<endl;
    } else {
        //cout<<"The flight between city "<<startCity<<" to "<<endCity<<" does not exist"<<endl;
        current = new Node(startCity,*this);
        s1.push(current);
        cout<<"pushed "<<startCity<<endl;
        while(!s1.empty()){

            bool pushedNewCity = false;
            //cout<<s1.getTop()->cityName<<" "<<s1.getTop()->currentIndex<<endl;
            for(int i = s1.getTop()->currentIndex; i< 5; i++){

                if(flight[s1.getTop()->myIndex][i] > 0){
                    //cout<<"true : "<<true<<endl;
                    //cout<<city[i]<<" "<<"check "<<s1.checkElement(city[i])<<endl;
                    if(!s1.checkElement(city[i])){

                        cout<<"pushed "<<city[i]<<endl;
                        s1.getTop()->currentIndex = i + 1;
                        int fuel = flight[s1.getTop()->myIndex][i];
                        //cout<<"city "<<s1.getTop()->cityName<<" to "<<city[i]<<" fuel "<<fuel<<endl;
                        current = new Node(city[i],*this);
                        current->totalFuel = s1.getTop()->totalFuel + fuel;
                        s1.push(current);
                        pushedNewCity = true;
                        break;
                    }
                }
            }

            if(s1.getTop()->cityName == endCity){
                break;
            }

            if(!pushedNewCity){
                cout<<"pop "<<s1.pop()->cityName<<endl;
            }
        }

        cout<<endl;
        if(!s1.empty()){
            stack s2;
            while(!s1.empty()){
                s2.push(s1.pop());
            }
            cout<<"The path is : ";
            while(!s2.empty()){
                current = s2.pop();
                cout<<current->cityName<<" ";
            }

            cout<<endl;
            cout<<"Total fuel required is "<<current->totalFuel<<endl<<endl;
        } else {
            cout<<"No path exist"<<endl<<endl;
        }
        
    }
}


int main(){
    Flight f;
    int choice = -1;
    while(choice != 0){
        cout<<"Enter 1 to arrange a flight "<<endl;
        cout<<"Enter 2 to search a flight"<<endl;
		cout<<"Enter 3 to delete a flight"<<endl;
        cout<<"Enter 4 to display flight matrix"<<endl;
        cout<<"Enter choice : ";
        cin>>choice;

        switch(choice){
            case 1:
                f.setFlight();
                break;
            
            case 2:
                f.searchFlight();
                break;

            case 3:
                f.deleteFlight();
                break;

            case 4:
                f.displayFlights();
                break;
        }
    }
            
    return 0;
}

/*
OUTPUT:

Display (4)
        A       B       C       D       E
A       0       5       5       0       0
B       5       0       0       5       0
C       5       0       0       0       5
D       0       5       0       0       0
E       0       0       5       0       0

Search (2) //used Back tracking algorithm
Enter start city : A
Enter destination city : E
pushed A
pushed B
pushed D
pop D
pop B
pushed C
pushed E
A C E
Total fuel required is 10

Set  (1)

Enter start city : C
Enter destination city : E 
Enter fuel required : 2
Path successfully set!


Delete (3)

Enter start city : C
Enter destination city : E
Deleted successfully set!
Enter 1 to arrange a flight
Enter 2 to search a flight
Enter 3 to delete a flight
Enter 4 to display flight matrix
Enter choice :
*/