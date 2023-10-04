#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
//Using indxed sequential search

class Student{
    public:
        static int totalStudents;
        int rollNum;
        char name[20],adr[50],div[2];
        void setData();
        void getData();
        void writeSingleData();
        static void display();
        static void searchData();
        static void updateData();
        static void deleteData();
};

int Student :: totalStudents;

void Student :: deleteData(){
    fstream findex,frecord,findextemp,frecordtemp;
    findex.open("index.bin",ios::binary | ios :: in);
    frecord.open("studentRecord.bin",ios::binary | ios :: in);
    findextemp.open("indextemp.bin",ios::binary | ios :: out);
    frecordtemp.open("studentRecordtemp.bin",ios::binary | ios :: out);

    if(findextemp && frecordtemp){
        cout<<"File successfully open"<<endl;
    } else {
        cout<<"File did not open"<<endl;
    }

    cout<<endl;
    Student obj;
    string temp;
    bool deleted = false;
    int totalCount;//to store the total number of records
    char readName[20];//to read the name from index file
    int ch;//to get the choice
    int count = 0;//used to calculate the location of the data in the record file

    findex.read((char *) &totalCount, sizeof(count));
    findextemp.write((char *) &totalCount, sizeof(totalCount));

    cout<<"Enter Name : ";
    cin.ignore();
    getline(cin,temp);
    
    while(findex.read((char *) &readName, sizeof(readName)) && frecord.read((char *) &obj, sizeof(obj))){


        if(readName == temp){
            
            deleted = true;

        } else {

            count++;
            obj.rollNum = count;
            findextemp.write((char *) &readName, sizeof(readName));
            frecordtemp.write((char *) &obj, sizeof(obj));

        }
    }

    findextemp.close();
    if(deleted){
        findextemp.open("indextemp.bin",ios::binary | ios :: out | ios :: in);
        if(findextemp){
            findextemp.seekp(0, ios :: beg);
            findextemp.write((char *) &count, sizeof(count));
            cout<<"File opened successfully"<<endl;
        } else {
            cout<<"File did not open"<<endl;
        }
    }

    findextemp.close();
    frecordtemp.close();
    findex.close();
    frecord.close();

    remove("index.bin");
    remove("studentRecord.bin");
    rename("indextemp.bin","index.bin");
    rename("studentRecordtemp.bin","studentRecord.bin");
}

void Student :: setData(){
    cout<<endl;
    cout<<"Enter Name : ";
    cin.ignore();
    string temp;
    getline(cin,temp);
    strcpy(name,temp.c_str());
    cout<<"Enter address : ";
    getline(cin,temp);
    strcpy(adr,temp.c_str());
    cout<<"Enter division : ";
    cin>>div;
    //cout<<"Enter roll number : ";
    //cin>>rollNum;
    cout<<endl;
    totalStudents++;
    cout<<"Total students : "<<totalStudents<<endl;
    rollNum = totalStudents;
    writeSingleData();
}

void Student :: getData(){
    cout<<endl;
    cout<<"Name : "<<name<<" "<<"DIV : "<<div<<" Roll number : "<<rollNum<<endl;
    cout<<"Address : "<<adr<<endl;
    cout<<endl;
}

void Student :: writeSingleData(){
    ofstream fout,findex;
    findex.open("index.bin",ios::binary | ios :: in | ios :: out);//opening index file
    fout.open("studentRecord.bin",ios::binary | ios::app);//opening student record file
    

    //If the file is not already created then it does not directly open in ios in and out mode thus first we create it in normal binary mode
    if(findex){
       // cout<<"File open successfully "<<endl;
    } else {
        //cout<<"File did not open"<<endl;
        findex.open("index.bin", ios :: binary);
        findex.close();
        findex.open("index.bin", ios :: binary | ios :: in | ios :: out);
        if(findex){
           // cout<<"File open successfully "<<endl;
        } else {
           // cout<<"File did not open"<<endl;    
        }
    }

    fout.write((char *) this, sizeof(*this));//Writing the new data to the last of the record file
    
    findex.seekp(0 ,ios :: beg);
    findex.write((char *) &totalStudents, sizeof(totalStudents));//writing the total number of records stored at the start of the file
    findex.seekp(0, ios :: end);//taking the file pointer the last
    findex.write((char *) &this->name, sizeof(this->name));//appending the new name
    fout.close();
    findex.close();
}

void Student :: display(){
    ifstream fin;
    fin.open("studentRecord.bin",ios::binary);
    Student obj;
    while(fin.read((char *) &obj, sizeof(obj))){
        obj.getData();
    }
    fin.close();
}

void Student :: searchData(){
    cout<<endl;
    Student obj;
    ifstream fin;
    ifstream findex;
    string temp;
    int totalCount;//to store the total number of records
    char readName[20];//to read the name from index file
    int ch;//to get the choice
    int count = 0;//used to calculate the location of the data in the record file

    cout<<"Enter 1 to search via name"<<endl;
    cout<<"Enter 2 to search  via roll number"<<endl;
    cout<<"Enter choice : ";
    cin>>ch;
    
    findex.open("index.bin",ios :: binary);
    findex.read((char *) &totalCount, sizeof(count));
    
    fin.open("studentRecord.bin",ios :: binary);

    if(ch == 1){
        cout<<"Enter Name : ";
        cin.ignore();
        getline(cin,temp);
        
        while(findex.read((char *) &readName, sizeof(readName))){
            if(readName == temp){
                fin.seekg(ios :: beg + count*sizeof(obj));//taking the pointer just before the start of the required record
                fin.read((char *) &obj, sizeof(obj));//reading the record
                obj.getData();
                fin.close();
                return;
            }
            count++;
        }
    } else {
        cout<<"Enter roll number : ";
        cin>>count;
        count = count - 1;
        cout<<"total count : "<<totalCount<<endl;
        if(count <= totalCount){
            //cout<<"Inside if"<<endl;
            fin.seekg((count)*sizeof(obj),ios :: beg);//taking the pointer just before the start of the required record
            fin.read((char *) &obj, sizeof(obj));
            obj.getData();
            fin.close();
            return;
        }
    }

    cout<<"Data not found!"<<endl;
    cout<<endl;
    fin.close();
}

void Student :: updateData(){
    cout<<endl;
    Student obj;
    fstream f;
    f.open("studentRecord.bin",ios :: binary | ios::in | ios :: out);
    string name;
    string adr;
    cout<<"Enter Name : ";
    cin.ignore();
    getline(cin,name);
    cout<<"Enter new address : ";
    getline(cin,adr);
    while(f.read((char *) &obj,sizeof(obj))){
        if(obj.name == name){
            f.seekp(f.tellg() - sizeof(obj));//Taking the write pointer just before the start of the updating object
            strcpy(obj.adr,adr.c_str());//converting adr array to string with the help of c_str function
            f.write((char *) &obj, sizeof(obj));//re-writing the object
            cout<<"Address Updated!"<<endl;
            return;
        }
    }
    cout<<"No record Found!"<<endl;
    cout<<endl;
    f.close();
}

int main(){
    ifstream f;
    Student obj;
    try{
        f.open("index.bin",ios::binary);
        f.read((char *) &Student :: totalStudents,sizeof(Student :: totalStudents));
        f.close();
    } catch (...){
        cout<<"Error"<<endl;
    }
    //cout<<"Total students : "<<Student :: totalStudents<<endl;
    int choice = 1;
    while(choice != 0){
        cout<<"Enter 1 to add new record"<<endl;
        cout<<"Enter 2 to display all records"<<endl;
        cout<<"Enter 3 to search record"<<endl;
        cout<<"Enter 4 to update address"<<endl;
        cout<<"Enter 5 to delete record"<<endl;
        cout<<"Enter 0 to exit"<<endl;
        cout<<"Enter choice : ";
        cin>>choice;
        cout<<endl;

        switch(choice){
            case 1:
                obj.setData();
                break;

            case 2:
                Student :: display();
                break;
            
            case 3:
                Student :: searchData();
                break;

            case 4:
                Student :: updateData();
                break;

            case 5:
                Student :: deleteData();
                break;
        }
    }
    return 0;
}