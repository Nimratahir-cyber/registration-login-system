#include<iostream>
#include<windows.h>
#include<sstream>
#include<fstream>
using namespace std;
// to remove starting and ending spaces from a string
string trim(string s)
{
    int start = 0, end = s.length() - 1;

    while (start <= end && s[start] == ' ')
        start++;

    while (end >= start && s[end] == ' ')
        end--;

    return s.substr(start, end - start + 1);
}

//-------------------class to login-----------------
class login{
private:
    string username, password;
public:
    void setter(string uname,string  pword)
     {
        username=uname;
        password=pword;
     }
     string getter(){
        return username +" | "+ password;
     }
     
};

//--------------------to register for a website-----------------
void registration()
{
    system("cls");
    login l;
    string uname, pword;
    cout<<"enter your name"<<endl;
    getline(cin,uname);
    cout<<"enter a strong password"<<endl;
    start:
    getline(cin,pword);
    if(pword.length()<8){
    cout<<"please enter password that has 8 or more characters"<<endl;
    goto start;
    }
    else{
        l.setter(uname,pword);
        ofstream outfile("thisfile.txt", ios::app);
        if(!outfile){
            cout<<"oops! there's an error in opening the file"<<endl;
        }
        outfile << l.getter()<<endl;
        outfile.close();
        cout<<"you have been registered successfully !"<<endl;
        Sleep(3000);
        system("cls");
    }

}

//--------------------to login to where you already registered--------------
void loginfunc(){
    system("cls");
    string uname, pword;
    cout<<"enter your name"<<endl;
    getline(cin,uname);
    cout<<"enter your password"<<endl;
    getline(cin,pword);
    ifstream infile("thisfile.txt");
    string line;
    bool found=false;
    while(getline(infile,line)){
        stringstream ss(line);
        string username, password;
        getline(ss,username, '|');
        getline(ss,password, '|');
        username=trim(username);
        password=trim(password);
        if(uname==username && pword==password){

            cout<<"please wait";
            for(int i=0;i<4;i++){
                cout<<". ";
                Sleep(1000);
            }
            cout<<"\nyou have logged in successfully" <<endl;
            cout<<"\n\n---------------Welcome to this page---------------"<<endl;
            found=true;
            break;
        }

    }
            if(!found){
            cout<<"incorrect username or password"<<endl;
        }
        infile.close();
        Sleep(2000);
        system("cls");           
}

//-------------exit from login page-------------
void exit(){
    cout<<"exiting the program";
     for(int i=0;i<4;i++){
                cout<<". ";
                Sleep(1000);
     }

}
int main(){
    int choice;
    while(choice!=3){
    cout<<"---------------registration page-----------"<<endl;
    cout<<"1. register to this website"<<endl;
    cout<<"2. login to this website"<<endl;
    cout<<"3. exit from this website"<<endl;
    cout<<"enter your choice :"<<endl;
    cin>>choice;
    cin.ignore();
    switch(choice){
        case 1:
        registration();
        break;
        case 2:
        loginfunc();
        break;
        case 3:
        exit();
        break;
        default:
        cout<<"invalid input"<<endl;
    }
    }
}