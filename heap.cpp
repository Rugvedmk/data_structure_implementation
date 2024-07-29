/*This program shows how heap sort works*/

#include<iostream>
#include<string.h>
using namespace std;

class Students{
    public:
        int totalStudents;
        int *arr;
        bool testing;
        Students(int totalStudents){
            //this->totalStudents = totalStudents;
            //arr = new int[totalStudents];
            testing = false;
            /*
            //For testing purpose
            //During testing simply un comment this code and run option 1 then 3

            testing = true;
            this->totalStudents = 11;
            arr = new int[11];
            int values[] = {1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17};

            for (int i = 0; i < this->totalStudents; i++) {
                arr[i] = values[i];
                //cout<<values[i]<<" ";
            }
            //cout<<endl;
            */
        }

        void display();
        void setData();
        void heapify(int N,int i);
        void swap(int i,int j);
        void heapSort();
};

void Students :: display(){
    int level = -1;
    int count = 0;
    int incrementBy = 1;
    while(count < totalStudents){
        //cout<<"count : "<<count<<endl;
        count = count + incrementBy;
        incrementBy = incrementBy*2;
        level++;
    }
    //cout<<"Level = "<<level<<endl;
    count = 0;
    incrementBy = 1;
    int current = 0;
    for(int i = 0;i<totalStudents;i++){
        cout<<(arr[i])<<" ";
    }
    cout<<endl;
}

void Students :: setData(){
    cout<<"Enter the marks of students : "<<endl;
    for(int i = 0;i<totalStudents;i++){
        cout<<i+1<<")";
        cin>>arr[i];
    }
}

void Students :: swap(int i,int j){
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void Students :: heapify(int N,int i){
    int largest = i;
    int l = 2*i + 1; //Left child
    int r = 2*i + 2; //Right child

    if(l < N && arr[largest] < arr[l]){
        largest = l;
    }

    if(r < N && arr[largest] < arr[r]){
        largest = r;
    }

    if(largest != i){
        swap(largest,i);
        heapify(N,largest);
    }
}

void Students :: heapSort(){

    //Building heap
    for(int i = totalStudents/2 -1;i>=0;i--){
        heapify(totalStudents,i);
    }

    cout<<"Heapify : ";
    display();
    //Extracting largest element and putting it at i th position
    for (int i = totalStudents - 1; i > 0; i--) {
 
        // Move current root to end
        swap(0, i);
 
        // call max heapify on the reduced heap
        heapify(i, 0);
    }

    cout<<"Sorted Marks : ";
    display();
}

int main(){
    Students *s;

    int choice = 1;
    int totalstudents;
    while(choice != 0){
        cout<<"Enter 1 to setData"<<endl;
        cout<<"Enter 2 to sortData"<<endl;
        cout<<"Enter 3 to display data"<<endl;
        cout<<"Enter choice : ";
        cin>>choice;

        switch (choice)
        {
        case 1:
            cout<<"Enter total students : ";
            cin>>totalstudents;
            s = new Students(totalstudents);
            if(!s->testing){
                s->setData();
            }
            break;

        case 2:
            s->heapSort();
            break;

        case 3:
            s->display();
            break;

        default:
            break;
        }
    }

    return 0;
}

/*OUTPUT

Enter 1 to setData
Enter 2 to sortData
Enter 3 to display data
Enter choice : 1
Enter total students : 11

Enter choice : 3
1 3 5 4 6 13 10 9 8 15 17 

Enter choice : 2
Heapify : 17 15 13 9 6 5 10 4 8 3 1
Sorted Marks : 1 3 4 5 6 8 9 10 13 15 17

Enter choice : 3 
1 3 4 5 6 8 9 10 13 15 17

*/