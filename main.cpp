#include <bits/stdc++.h>
#include <mysql.h>
#include <mysqlerror.h>
#include <windows.h>

using namespace std;

const char *HOST = "localhost"; // MySQL server host
const char *USER = "root";
const char *PW = " ";
const char *DB = "verification"; // Database name

class login
{
private:
    string userId, userPW;

public:
    login() : userId(""), userPW("") {}

    void setID(string id)
    {
        userId = id;
    }

    void setPW(string pw)
    {
        userPW = pw;
    }

    string getID() const
    {
        return userId;
    }
    string getPW() const
    {
        return userPW;
    }
};

char encryptch(char ch,int shift){
    if(isalpha(ch)){
        char base = isupper(ch) ? 'A' : 'a';
        char encrypted_ch = (ch-base+shift+26)%26+base;
        return encrypted_ch;
    }
    if(Digit(ch)){
        char encrypted_ch = (ch-'0'+shift+10)%10+'0';
        return encrypted_ch;
    }
    return ch;
}

string encrypt(const string &password, int shift ){
    string encrypted=" ";
    for(int i=0;i<password.length();i++){
        char ch=password[i];
        char encryptedChar=encryptch(ch,shift);
        encrypted+=encryptedChar;
    }
    return encrypted;
}

int main()
{
    login l;

    MYSQL *conn;
    conn=mysql_init(NULL);
    if(!mysql_real_connect(conn,HOST,USER,PW,DB,3306,NULL,0)){
        cout<<"ERROR: "<<mysql_error(conn)<<endl;
    }
    else{
        cout<<"logged in database"<<endl;
    }

    Sleep(3000);
    int shift = 3;
    bool exit = false;
    while(!exit){
        system("cls");
        cout<<"1.Sign Up"<<endl;
        cout<<"2.Login"<<endl;
        cout<<"0. Exit"<<endl;
        cout<<"Enter your choice: ";
        int val;
        cin>>val;
        if(val==1){
            system("cls");
            string id, pw;
            cout<<"Enter your ID: ";
            cin>>id;
            l.setID(id);
            cout<<"Enter your Password: ";
            cin>>pw;
            l.setPW(pw);
            string encryptPW=encrypt(l.getPW(),shift);
            string Sup="INSERT INTO password (Id,PW) VALUES ('"+l.getID()+"','"+encryptPW+"')";
            if(mysql_query(conn,Sup.c_str())){
                cout<<"ERROR: "<<mysql_error(conn)<<endl;
            }
            else{
                cout<<"Sign Up Successful!"<<endl;
            }
        }//if 1
    }//while end
    return 0;
}