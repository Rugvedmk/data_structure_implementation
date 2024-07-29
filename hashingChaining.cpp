#include<iostream>
#include<string>
using namespace std;

//Function to convert to String to integer for Hashing purpose
//This function returns the sum of ASCII values in the string
int stringConvert(string name){
	
	int size = 0;
	int sum = 0;
	while(name[size] != '\0'){
		sum += name[size];
		size++;
	}
	
	return sum;
}

class Node{
	public :
		string name;
		double number;
		Node *next,*previous;
		Node(){
			next = previous = NULL;
			name = "No Data";
			number = 0;
		}
		void displayNode();
		void setNodeData();
		int hash(Node keyName);
};

Node *temp;

int Node :: hash(Node keyName){
	int sum = stringConvert(keyName.name);
	int index = sum%23;
	
	return index;
}

void Node :: displayNode(){
	cout<<"Name : "<<name<<endl;
	cout<<"Number : "<<number<<endl<<endl;
}

void Node :: setNodeData(){
	cout<<"Enter Name : ";
	cin.ignore();
	getline(cin,name);
	cout<<"Enter Number : ";
	cin>>number;
}

class Dictonary{
	private:
		Node *array[23];
	public:
		Dictonary(){
			for(int i = 0;i<23;i++){
				array[i] = NULL;
			}
		}
		void insertData();
		void displayDictonary();
		void deleteData();		
};

void Dictonary :: insertData(){
	Node *temp = new Node();
	temp->setNodeData();
	
	int index = temp->hash(*temp);
	
	cout<<"Index : "<<index<<endl;
	
	Node *temp1;
	
	temp1 = array[index];
	
	
	if(temp1 != NULL){
		while(temp1->next != NULL){
			temp1 = temp1->next;	
		}
	}
	
	if(temp1 == NULL){
		array[index] = temp;
	} else if(temp1->next == NULL){
		temp1->next = temp;
		temp->previous = temp1;
	}
	
	
}

void Dictonary :: displayDictonary(){
	for(int i = 0; i < 23; i++){
		temp = array[i];
		cout<<i+1<<") "<<endl;
		
		if(temp == NULL){
			cout<<"No Data"<<endl<<endl;
		} else {
			while(temp != NULL){
				temp->displayNode();	
				temp = temp->next;	
			}
		}
		
	}

}

void Dictonary :: deleteData(){
	Node Searchkey;
	cout<<"Enter the name : ";
	cin.ignore();
	getline(cin,Searchkey.name);
	int index = Searchkey.hash(Searchkey);
	bool dataFoundFlag = false;
	Node *SearchPtr = array[index];

	if(SearchPtr == NULL){
		cout<<"No Data of this name found!"<<endl<<endl;
	} else {
		while(SearchPtr->name != Searchkey.name){
			if (SearchPtr->next == NULL)
			{	
				cout<<"No Data of this name found!"<<endl<<endl;
				break;
			}	
			SearchPtr = SearchPtr->next;	
		}
		if (SearchPtr->name == Searchkey.name)
		{
			SearchPtr->displayNode();
			Node *temp1;
			temp1 = SearchPtr;
			if (temp1->previous == NULL)
			{
				array[index] = temp1->next;
			} else if(temp1->next == NULL){
				//cout<<"Else if condition executed!"<<endl;
				temp1->previous->next = NULL;
			}else {
				temp1 = temp1->previous;
				temp1->next = SearchPtr->next;
			}		
			delete SearchPtr;
			dataFoundFlag = true;
		}
		if (dataFoundFlag == true)
		{
			cout<<"Data deleted successfully!"<<endl<<endl;
		}
				
	}
}

int main(){
	Dictonary obj;
	int choice = 1;
	while(choice != 0){
		cout<<"Press 1 to enter data"<<endl;
		cout<<"Press 2 to display data"<<endl;
		cout<<"Press 3 to delete data"<<endl;
		cout<<"Press 0 to exit data"<<endl;
		cout<<"Enter choice : ";
		cin>>choice;
		switch(choice){
			case 1:
				obj.insertData();
				break;
				
			case 2:
				obj.displayDictonary();
				break;

			case 3:
				obj.deleteData();
				break;
		}
	}

	return 0;
}

/*OUTPUT

Press 1 to enter data
Press 2 to display data
Press 3 to delete data
Press 0 to exit data

Enter choice : 1
Enter Name : ddd
Enter Number : 456
Index : 1

Enter choice : 1
Enter Name : cde
Enter Number : 456
Index : 1

Enter choice : 2
1)
No Data

2)
Name : ddd
Number : 456

Name : cde
Number : 456

3)
No Data
.
.
.

Enter choice : 3
Enter the name : cde
Name : cde
Number : 456

Data deleted successfully!

Enter choice : 2
1)
No Data

2)
Name : ddd
Number : 456

3)
No Data
.
.
.

Enter choice : 3
Enter the name : ddd
Name : ddd
Number : 456

Data deleted successfully!

Enter choice : 2
1)
No Data

2)
No Data

3)
No Data
.
.
.

Enter choice : 1
Enter Name : ddd
Enter Number : 456
Index : 1

Enter choice : 1
Enter Name : cde
Enter Number : 456
Index : 1

Enter choice : 1
Enter Name : bdf
Enter Number : 456
Index : 1

Enter choice : 2
1)
No Data

2)
Name : ddd
Number : 456

Name : cde
Number : 456

Name : bdf
Number : 456

3)
No Data
.
.
.

Enter choice : 3
Enter the name : cde
Name : cde
Number : 456

Data deleted successfully!

Enter choice : 2
1)
No Data

2)
Name : ddd
Number : 456

Name : bdf
Number : 456

3)
No Data
.
.
.
*/








