#include<iostream>
#include<string.h>
using namespace std;

class AVLnode{
	public :
		string keyword,meaning;
		AVLnode *L,*R;
		int ht;
		void display();
		AVLnode(){
			L = R = NULL;
			ht = 0;
		}
};

void AVLnode :: display(){
	cout<<keyword<<" : "<<meaning<<endl;
}

class AVLtree{
	public:
		AVLnode *root;
		AVLtree(){ root = NULL; }
		AVLnode *rotate_right(AVLnode *x);
		AVLnode *rotate_left(AVLnode *x);
		AVLnode *LL(AVLnode *x);
		AVLnode *LR(AVLnode *x);
		AVLnode *RR(AVLnode *x);
		AVLnode *RL(AVLnode *x);
		int height(AVLnode *T);
		int BF(AVLnode *T);
		AVLnode *insert(AVLnode *root,string newKey,string mean);
		AVLnode *inorder(AVLnode *root);
		AVLnode *search(AVLnode *root, string key);
};

AVLnode *AVLtree :: rotate_right(AVLnode *x){
	AVLnode *y;
	y = x->L;
	x->L = y->R;
	y->R = x;
	x->ht = height(x);
	y->ht = height(y);
	return y;
}

AVLnode *AVLtree :: rotate_left(AVLnode *x){
	AVLnode *y;
	y = x->R;
	x->R = y->L;
	y->L = x;
	x->ht = height(x);
	y->ht = height(y);
	return y;
}

int AVLtree :: height(AVLnode *T){
	int hl,hr;
	if(T == NULL){
		return 0;
	}
	
	if(T->L == NULL && T->R == NULL){
		return 0;
	}
	
	hl = height(T->L);
	hr = height(T->R);
	if(hl < hr){
		return hr + 1;
	} else {
		return hl + 1;
	}
}

int AVLtree :: BF(AVLnode *T){
	int lh, rh;
	if(T == NULL){
		return 0;
	} else {
		if(T->L == NULL){
			lh = 0;
		} else {
			lh = 1+T->L->ht;
		}
		
		if(T->R == NULL){
			rh = 0;
		} else {
			rh = 1+T->R->ht;
		}
	}
	
	return (lh - rh);
	
}

AVLnode *AVLtree :: LL(AVLnode *T){
	cout<<"\n in LL rotation \n"<<endl;
	T = rotate_right(T);
	return T;
}

AVLnode *AVLtree :: RR(AVLnode *T){
	cout<<"\n in RR rotation \n"<<endl;
	T = rotate_left(T);
	return T;
}

AVLnode *AVLtree :: RL(AVLnode *T){
	cout<<"\n in RL rotation \n"<<endl;
	T->R = rotate_right(T->R);
	T = rotate_left(T);
	return T;
}

AVLnode *AVLtree :: LR(AVLnode *T){
	cout<<"\n in LR rotation \n"<<endl;
	T->L = rotate_left(T->L);
	T = rotate_right(T);
	return T;
}

AVLnode *temp;

AVLnode* AVLtree :: insert(AVLnode *root,string newKey,string mean){
	if(root == NULL){
		//cout<<"Executed"<<endl;
		//AVLnode* temp = new AVLnode();
		temp = new AVLnode();
		temp->keyword = newKey;
		temp->meaning = mean;
		temp->ht = 0;
		root = temp;
		cout<<root->keyword<<" : "<<root->meaning<<endl;
	} else {
		if(root->keyword > newKey){
			root->L = insert(root->L,newKey,mean);
			cout<<"BF L of "<<root->keyword<<" : "<<BF(root)<<endl;
			if(BF(root) == 2){
				if(BF(root->L) == 1 ){
					root = LL(root);
				} else {
					root = LR(root);// for BF(root->L) == -1
				}
			} 
		} else if(root->keyword < newKey){
			root->R = insert(root->R,newKey,mean);
			cout<<"BF R of "<<root->keyword<<" : "<<BF(root)<<endl;
			
			if(BF(root) == -2){
				if(BF(root->R) == -1){
					root = RR(root);
				} else {
					root = RL(root);
				}
			}
		} else {
			cout<< "Duplicate"<<endl;
		}

	}

	root->ht = height(root);
	return root;

}

AVLnode* AVLtree :: inorder(AVLnode* root){
	if(root == NULL){
		//cout<<"executed"<<endl;
		return NULL;
	}

	inorder(root->L);
	cout<<root->keyword<<" : "<<root->meaning<<endl;
	inorder(root->R);
}

AVLnode* AVLtree :: search(AVLnode* root,string key){
	if(root == NULL){
		cout<<"Key not found!"<<endl;
		return NULL;
	} else {
		if(root->keyword == key){
			root->display();
			return NULL;
		} else if(root->keyword > key){
			search(root->L,key);
		} else {
			search(root->R,key);
		}
	}
}

int main(){
	int choice = 1;
	AVLtree t;
	string keyword,meaning;
	while(choice != 0){
		cout<<"Enter 1 to enter data"<<endl;
		cout<<"Enter 2 to display data"<<endl;
		cout<<"Enter 3 to search node"<<endl;
		cout<<"Enter 0 to exit"<<endl;
		cout<<"Enter choice : ";
		cin>>choice;
		switch (choice)
		{
		case 1:
			cout<<"Enter keyword : ";
			cin>>keyword;
			cout<<"Enter meaning : ";
			cin>>meaning;
			t.root = t.insert(t.root,keyword,meaning);
			break;
		case 2:
			t.inorder(t.root);
			break;
			
		case 3:
			cout<<"Enter the search key : ";
			cin>>keyword;
			t.search(t.root,keyword);
		default:
			break;
		}

		}

	return 0;
}












