/*This is a programme showing hashing and collision handling*/
#include<iostream>
#include<string>
using namespace std;

struct phonebook{
	string name;
	double number;
};

phonebook *phonebook1[23];

int stringConvert(string name){
	int size = 0;
	int sum = 0;
	while(name[size] != '\0'){
		sum += name[size];
		size++;
	}
	
	//int index = sum%23;
	return sum;
}

int hash1(phonebook keyName){
	int sum = stringConvert(keyName.name);
	int index = sum%23;
	//cout<<"Index : " <<index<<endl<<endl;
	
	
	
	return index;
}

int hash2(phonebook keyName){
	int sum = hash1(keyName);
	
	int index = (sum*13)/23;
		
	//cout<<"Index2 : "<<index<<endl;
	
	return index;               
}

phonebook *obj1;

void setData(){
	obj1 = new phonebook();

	cout<<"Enter Name : ";
	cin>>(*obj1).name;
	cout<<"Enter number : ";
	cin>>(*obj1).number;
	cout<<endl;
	
	if (phonebook1[hash1(*obj1)] == NULL ){
		int index = hash1(*obj1);
		phonebook1[index] = obj1;
		cout<<"Data saved to phonebook successfully! by hash 1"<<endl;
		cout<<"Data saved at index : "<<index<<endl<<endl;
	} else if( phonebook1[hash2(*obj1)] == NULL) {
		int index = hash2(*obj1);
		phonebook1[index] = obj1;
		cout<<"Data saved to phonebook successfully! by hash 2"<<endl;
		cout<<"Data saved at index : "<<index<<endl<<endl;
	} else {
		//In this part we use linear probing starting from index next to hash2
		int probe = 0;
		int index = (hash2(*obj1) + 1)%23;
		for(probe = 0;probe<23;probe++){
			if (phonebook1[index] == NULL)
			{
				phonebook1[index] = obj1;
				cout<<"Probe : "<<probe+3<<endl;
				cout<<"Data saved at index : "<<index<<endl<<endl;
				break;
			} else if (probe  == 22) {
				cout<<"Hash Table is full!"<<endl<<endl;
				break;
			} else {
				index = (index + 1)%23;
			}
		}		
	}	
}

void display(){
	for (int i = 0; i <23 ; i++){
		if(phonebook1[i] == NULL){
			cout<<i<<"-> NULL"<<endl;
		} else {
		cout<<i<<"->"<<phonebook1[i]->name<<endl;
		}
	}
	cout<<endl;
}

int search(){
	obj1 = new phonebook();

	cout<<"Enter Name : ";
	cin>>(*obj1).name;
	int index = hash1(*obj1);
	int check = 0;
	if (phonebook1[index] != NULL)
	{
		if ( phonebook1[index]->name == (*obj1).name ){
			cout<<phonebook1[index]->name << " : " << phonebook1[index]->number << endl;
			check = 1;
		}
	}
	if (check == 0)
	{
		index = hash2(*obj1);
		if (phonebook1[index] != NULL)
		{
			if ( phonebook1[index]->name == (*obj1).name ){
				cout<<phonebook1[index]->name << " : " << phonebook1[index]->number << endl;
				check = 1;
			}
		}
	}
	
	if(check == 0){
		int probe = 0;
		int index = (hash2(*obj1) + 1)%23;
		for(probe = 0;probe<23;probe++){
			if (phonebook1[index] != NULL)
			{	
				if ( phonebook1[index]->name == (*obj1).name ){
				cout<<phonebook1[index]->name << " : " << phonebook1[index]->number << endl;
				check = 1;
				break;
				}
				cout<<"Probe : "<<probe<<endl;
			} 
			if (probe  == 22) {
				cout<<"Data not found!"<<endl;
				break;
			} else {
				cout<<"Probe : "<<probe<<endl;
				index = (index + 1)%23;
			}
		}
	}
	delete obj1;

	if(check == 0){
		return -1;
	} else {
		return index;
	}
}

void deleteData(){
	int index = search();

	if(index == -1){
		
	} else {
		delete phonebook1[index];
		phonebook1[index] = NULL;
		cout<<"\nData deleted successfully!\n"<<endl;
	}
}

int main(){

	for (int i = 0;i < 23; i++){
		phonebook1[i] = NULL;
	}
	
	int choice = 1;
	while(choice != 0){
		cout<<"Enter 1 to set data "<<endl;
		cout<<"Enter 2 to display data "<<endl;
		cout<<"Enter 3 to search data "<<endl;
		cout<<"Enter 4 to delete data "<<endl;
		cout<<"Enter 0 to exit"<<endl;
		cout<<"Enter choice : ";
		cin>>choice;
		if(choice == 1){
			setData();
		} else if(choice == 2) {
			display();
		} else if( choice == 3){
			search();
		} else if( choice == 4){
			deleteData();
		}
	}

	return 0;
}

/*OUTPUT


Enter 1 to set data 
Enter 2 to display data 
Enter 3 to search data 
Enter 4 to delete data 
Enter 0 to exit

Enter choice : 1
Enter Name : ddd
Enter number : 456

Data saved to phonebook successfully! by hash 1
Data saved at index : 1

Enter choice : 1
Enter Name : cde
Enter number : 456

Data saved to phonebook successfully! by hash 2
Data saved at index : 0

Enter choice : 1
Enter Name : cdf
Enter number : 456

Data saved to phonebook successfully! by hash 1
Data saved at index : 2

Enter choice : 2
0->cde
1->ddd
2->cdf
3-> NULL
.
.
.

Enter choice : 3
Enter Name : cde
cde : 456

Enter choice : 3
Enter Name : cdf
cdf : 456

Enter choice : 3
Enter Name : ddd
ddd : 456

Enter choice : 4
Enter Name : ddd
ddd : 456

Data deleted successfully!

Enter choice : 2
0->cde
1-> NULL
2->cdf
3-> NULL
.
.
.

*/








