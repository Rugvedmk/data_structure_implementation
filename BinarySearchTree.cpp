/*This is the programme showing the functioning of binary search Tree*/
/*It also works with storing multiple info(numbers) for a single key*/
#include<iostream>
#include<string.h>
using namespace std;

class Node{
	public:
		Node *L,*R,*previous;
		string name;
		string number[5];
		int numberOfValues;
		Node(){
			L= R = previous = NULL;
			name = "";
			numberOfValues = 0;
			for(int i = 0;i<5;i++){
				number[i] = "";
			}
		}
		
		void setData(){
			cout<<"Enter name : ";
			//cin.ignore();
			//getline(cin,data);
			cin>>name;
			cout<<"Enter number : ";
			cin>>number[0];
			//numberOfValues++;
		}
		
		void displayData(){
			cout<<name<<" : "<<endl;
			for(int i = 0;i<=numberOfValues;i++){
				cout<<i+1<<")"<<number[i]<<endl;
			}
			cout<<endl;		
		}

};


class Tree{

	public:
		Node *root;
		bool mirror;

		Tree(){
			root = NULL;
			mirror = false;	
		}
		
		void insertData();
		Node* searchNode(Node *searchPtr);
		Node* minvalue(Node *root,Tree *T);
		Node* maxvalue(Node *root,Tree *T);
		Node* updateValue(Node *root,Tree *T);
};

void Tree :: insertData(){

	Node *temp = new Node();
	Node *PlaceHolder;
	
	temp->setData();
	PlaceHolder = root;
	cout<<endl;
	if(!mirror){
		while(true){
			if(root == NULL){
				root = temp;
				break;
			} else {
				if(PlaceHolder->name >= temp->name){
					if(PlaceHolder->L == NULL){
						cout<<"Initialaizing to left of : "<<PlaceHolder->name<<endl;
						PlaceHolder->L = temp;
						temp->previous = PlaceHolder;
						break;
					} else {
						cout<<"Travelling to left of : "<<PlaceHolder->name<<endl;
						PlaceHolder = PlaceHolder->L;
					}
				} else {
					if(PlaceHolder->name < temp->name){
						if(PlaceHolder->R == NULL){
							cout<<"Initialaizing to the right of : "<<PlaceHolder->name<<endl;
							PlaceHolder->R = temp;
							temp->previous = PlaceHolder;
							break;
						} else {
							cout<<"Travelling to the right of : "<<PlaceHolder->name<<endl;
							PlaceHolder = PlaceHolder->R;
						} 
					}
				}
				
			}
		}
	} else {
		while(true){
			if(root == NULL){
				root = temp;
				break;
			} else {
				if(PlaceHolder->name >= temp->name){
					if(PlaceHolder->R == NULL){
						cout<<"Initialaizing to the right of : "<<PlaceHolder->name<<endl;
						PlaceHolder->R = temp;
						temp->previous = PlaceHolder;
						break;
					} else {
						cout<<"Travelling to the right of : "<<PlaceHolder->name<<endl;
						PlaceHolder = PlaceHolder->R;
					}
				} else {
					if(PlaceHolder->name < temp->name){
						if(PlaceHolder->L == NULL){
							cout<<"Initialaizing to left of : "<<PlaceHolder->name<<endl;
							PlaceHolder->L = temp;
							temp->previous = PlaceHolder;
							//cout<<"Data set"<<endl;
							break;
						} else {
							cout<<"Travelling to left of : "<<PlaceHolder->name<<endl;
							PlaceHolder = PlaceHolder->L;
						} 
					}
				}
				
			}
		}
	}
}

Node* Tree :: searchNode(Node *searchPtr){
	
	Node *current = root;
	bool dataFound = false;
	
	if(current == NULL){
		//cout<<"The BStree is empty!"<<endl;
	} else { 
		while(true){
			if(current->name == searchPtr->name){
				//cout<<"Data found!"<<endl;
				dataFound = true;
				break;
			} else if(current->name >= searchPtr->name){
				if(current->L == NULL){
					//cout<<"The data is not present in the tree!"<<endl;
					break;
				} else {
					current = current->L;
				}
			} else if(current->name < searchPtr->name){
				if(current->R == NULL){
					//cout<<"The data is not present in the tree!"<<endl;
					break;
				} else {
					current = current->R;
				}
			}
		}
	
	}

	if(dataFound == true){
		return current;
	} else {
		return NULL;
	}
}

void displayTreeAscending(Node *temp){
	if(temp == NULL){
		
	} else {
		if(temp->L != NULL){
			Node *recursive = temp->L;
			displayTreeAscending(recursive);
			temp->displayData();
		} else {
			temp->displayData();
		}
				
		if(temp->R != NULL){
			Node *recursive = temp->R;
			displayTreeAscending(recursive);
		} 
	
	}
}

void displayTreeDescending(Node *temp){
	if(temp == NULL){
		
	} else {
		if(temp->R != NULL){
			Node *recursive = temp->R;
			displayTreeDescending(recursive);
			temp->displayData();
		} else {
			temp->displayData();
		}
				
		if(temp->L != NULL){
			Node *recursive = temp->L;
			displayTreeDescending(recursive);
		} 
	
	}
}


// void mirrorTree(Node *root){
// 	if(root != NULL){
// 		Node *temp = root->L;
// 		root->L = root->R;
// 		root->R = temp;
// 		mirrorTree(root->L);
// 		mirrorTree(root->R);
// 	}
// }




//This function will give minimum even after mirroring the tree
Node* Tree :: minvalue(Node *root,Tree *T){
	if(root == NULL){
		//cout<<"The BST is empty!"<<endl;
		return NULL;
	} else {
		if(root->L != NULL && root->L->name <= root->name){
			//cout<<"Minimum value : "<<root->data<<endl;
			return T->minvalue(root->L,T);
		} else if(root->R != NULL && root->R->name <= root->name){
			return T->minvalue(root->R,T);
		} else {
			return root;
		}
	}
}

//This function will give maximum even after mirroring the tree
Node* Tree :: maxvalue(Node *root,Tree *T){
	if(root == NULL){
		//cout<<"The BST is empty!"<<endl;
		return NULL;
	} else {
		if(root->L != NULL && root->L->name > root->name){
			//cout<<"Minimum value : "<<root->data<<endl;
			return T->maxvalue(root->L,T);
		} else if(root->R != NULL && root->R->name > root->name){
			return T->maxvalue(root->R,T);
		} else {
			return root;
		}
	}
}

void deleteData(Node *root,Tree *T){
	Node *deleteNode = T->searchNode(root);
  	Node *temp;
	// if(!(T->mirror)){}
	// else{
	// 	mirrorTree(T->root);
	// }
	if (deleteNode->L == NULL && deleteNode->R == NULL){
		if (deleteNode->previous != NULL)
		{
			if(deleteNode->previous->R == deleteNode){
				deleteNode->previous->R = NULL;
			} else {
				deleteNode->previous->L = NULL;
			}
		} else {
			T->root =  NULL;
		}
		
		delete deleteNode;
	} else if(deleteNode->L == NULL){
		if (deleteNode->previous != NULL){
			if(deleteNode->previous->R == deleteNode){
				deleteNode->previous->R = deleteNode->R;
				deleteNode->R->previous = deleteNode->previous;
			} else {
				deleteNode->previous->L = deleteNode->R;
				deleteNode->R->previous = deleteNode->previous;
			}
		} else {
			T->root = deleteNode->R;
		}
		delete deleteNode;
	} else if(deleteNode->R == NULL){
		if (deleteNode->previous != NULL){	
			if(deleteNode->previous->R == deleteNode){
				deleteNode->previous->R = deleteNode->L;
				deleteNode->R->previous = deleteNode->previous;
			} else {
				deleteNode->previous->L = deleteNode->L;
				deleteNode->R->previous = deleteNode->previous;
			}
		} else {
			T->root = deleteNode->L;
		}
		
		delete deleteNode;
	} else {
			temp = T->minvalue(deleteNode->R,T);
			temp->L = deleteNode->L;
			temp->previous->L = temp->L;
			if(temp != deleteNode->R){
				temp->R = deleteNode->R;
			}
			
			temp->previous = deleteNode->previous;
			if (deleteNode->previous != NULL){
				if(deleteNode->previous->R == deleteNode){
					deleteNode->previous->R = temp;
				} else {
					deleteNode->previous->L = temp;
				}	
			} else {
				T->root = temp;
			}
			delete deleteNode;

	} 
	

}

int maxheight(Node *root){
	int h1,h2;

	if(root == NULL){
		return 0;
	} else {
	}
	h1 = maxheight(root->L);
	h2 = maxheight(root->R);

	if(h1 > h2){
		return h1 + 1;
	} else {
		return h2 + 1;
	}
}

int minheight(Node *root){
	int h1,h2;

	if(root == NULL){
		return 0;
	} else {
	}
	h1 = minheight(root->L);
	h2 = minheight(root->R);

	if(h1 > h2){
		return h2 + 1;
	} else {
		return h1 + 1;
	}
}

Node* Tree :: updateValue(Node *root,Tree *T){
	Node *updateNode = T->searchNode(root);
	
	if(updateNode == NULL){
		cout<<"No such node exist!"<<endl;
	} else {
		updateNode->displayData();
		int ch;
		cout<<"Press 1 to add new number"<<endl;
		cout<<"Press 2 to update any of the above number"<<endl;
		cout<<"Enter choice : ";
		cin>>ch;
		cout<<endl;
		if(ch == 1){
			if(updateNode->numberOfValues < 5){
				updateNode->numberOfValues++;
				cout<<"Enter number : ";
				cin>>updateNode->number[updateNode->numberOfValues];
				cout<<endl;
			} else {
				cout<<"The node already has max number of values!"<<endl;
				cout<<endl;
			} 
		} else {
			int num = 0;
			cout<<"Enter the rank of number which you want to update : ";
			cin>>num;
			cout<<endl;
			if(num <= updateNode->numberOfValues){
				cout<<"Enter number : ";
				cin>>updateNode->number[num-1];
				cout<<endl;
			} else {
				cout<<"The number can not be updated"<<endl;
			}		
		}
			
	}
	return updateNode;
}

int main(){

	Tree T1;
	Node *tempPtr = new Node();
	//cin>>tempPtr->data;
	int choice = 1;
	while(choice != 0){	
		cout<<"Press 1 to insert new number "<<endl;
		cout<<"Press 2 to search number "<<endl;
		cout<<"Press 3 to display dictonary in ascending order "<<endl;
		cout<<"Press 4 to display dictonary in descending order "<<endl;
		cout<<"Press 5 to get max and min searches to find a node "<<endl;
		cout<<"Press 6 to delete data "<<endl;
		cout<<"Press 7 to update value "<<endl;
		cout<<"Enter choice : ";
		cin>>choice;
		cout<<endl;

		switch(choice){
			case 1:
				T1.insertData();
				break;
			
			case 2:
				cout<<"Enter the key : ";
				cin>>tempPtr->name;
				cout<<endl;
				if(T1.searchNode(tempPtr) == NULL){
						//cout<<"Data not found!"<<endl;
				} else {
					cout<<"Data :";
					T1.searchNode(tempPtr)->displayData();
					cout<<endl;
				}
				break;
				
			case 3:
				displayTreeAscending(T1.root);
				cout<<endl;
				break;

			case 4:
				displayTreeDescending(T1.root);
				cout<<endl;
				break;
			case 5:
				//cout<<"Enter the key : ";
				//cin>>tempPtr->data;
				cout<<"Maximum searches : "<<maxheight(T1.root)-1<<endl;
				cout<<"Minimum searches : "<<minheight(T1.root)-1<<endl;
				break;

			case 6:
				cout<<"Enter the key : ";
				cin>>tempPtr->name;
				cout<<endl;
				deleteData(tempPtr,&T1);
				break;
				
			case 7:
				cout<<"Enter the key : ";
				cin>>tempPtr->name;
				cout<<endl;
				T1.updateValue(tempPtr,&T1);
		
		}
	}


	return 0;
}


/*OUTPUT


Press 1 to insert new number 
Press 2 to search number 
Press 3 to display dictonary in ascending order 
Press 4 to display dictonary in descending order 
Press 5 to get max and min searches to find a node 
Press 6 to delete data 
Press 7 to update value 
Enter choice : 1

Enter name : h
Enter number : 123

Enter choice : 7

Enter the key : h

h :
1)123

Press 1 to add new number
Press 2 to update any of the above number
Enter choice : 1

Enter number : 456

Enter choice : 3

h :
1)123
2)456

Enter choice : 7

Enter the key : h

h :
1)123
2)456

Press 1 to add new number
Press 2 to update any of the above number
Enter choice : 2

Enter the rank of number which you want to update : 1

Enter number : 789 

Enter choice : 3

h :
1)789
2)456

Enter choice : 1

Enter name : d
Enter number : 123

Initialaizing to left of : h

Enter choice : 1

Enter name : b
Enter number : 456

Travelling to left of : h
Initialaizing to left of : d

Enter choice : 1

Enter name : e 
Enter number : 789

Travelling to left of : h
Initialaizing to the right of : d

Enter choice : 1

Enter name : l
Enter number : 123

Initialaizing to the right of : h

Enter choice : 3

b :
1)456

d :
1)123

e :
1)789

h :
1)789
2)456

l :
1)123

Enter choice : 4

l :
1)123

h :
1)789
2)456

e :
1)789

d :
1)123

b :
1)456

Enter choice : 5

Maximum searches : 2
Minimum searches : 1

Enter choice : 6

Enter the key : d

Enter choice : 3

b :
1)456

e :
1)789

h :
1)789
2)456

l :
1)123

Enter choice : 4

l :
1)123

h :
1)789
2)456

e :
1)789

b :
1)456
*/




