//*******************************************
//         PROJECT  HOTEL-MANAGEMENT
//****************************************

#include<iostream>
#include<conio.h>
#include<fstream>
#include<stdio.h>
#include<dos.h>
using namespace std;


// ***********************************************
//   THIS CLASS CONTAINS FUNCTIONS FOR HOTEL
//************************************************

class hotel
{
int room_no;
char name[30];
char address[50];
long phone;
public:
void main_menu();
void add();
void display();
void rooms();
void edit();
int check(int);
void modify(int);
void delete_rec(int);
}; // END OF CLASS HOTEL

//*********************************************
//   FUNCTION FOR DISPLAYING MAIN MENU
//*********************************************

void hotel::main_menu()
{
   int choice;
   while(choice!=5)
   {
    system("cls");
    cout<<"\n\t\t\t *********************";
    cout<<"\n\t\t\t   * MAIN Menu*";
    cout<<"\n\t\t\t *********************";
    cout<<"\n\n\n\t\t\t 1. Book A Room";
    cout<<"\n\t\t\t 2. Customer Record";
    cout<<"\n\t\t\t 3. Rooms Alloted";
    cout<<"\n\t\t\t 4.Edit Record";
    cout<<"\n\t\t\t 5. Exit";
    cout<<"\n\n\t\t Enter Your Choice:";
    cin>>choice;

    switch(choice)
    {
	case 1: add(); // CALLLING ADD FUNCTION
		break;
	case 2: display(); // CALLING DISPLAY FUNCTION
		break;
	case 3: rooms(); // CALLING ROOMS FUNCTION
		break;
	case 4: edit();  // CALLING EDIT FUNCTION
		break;
	case 5: break;
	default:
		   cout<<"\n\n\t\t Wrong Choice!!!";
		   cout<<"\n\t\t Press any key to continue!!!";
		   getch();

     }
   }
}

//***********************************************
//   FUNCTION TO ADD DETAILS OF A CUSTOMER
//***********************************************

void hotel::add()
{
   system("cls");
   int r,flag;
   ofstream fout("Record.dat",ios::app|ios::binary);

   cout<<"\n Enter Customer Details";
   cout<<"\n **********************";
   cout<<"\n\n Room no:";
   cin>>r;
   flag=check(r); // CALLING CHECK FUNCTION

   if(flag==1)
      cout<<"\n Sorry..!!!Room is already booked";
   else
   {
     room_no=r;
     cout<<" Name:";
     cin>>name;
     cout<<" Address:";
     cin>>address;
     cout<<" Phone no:";
    cin>>phone;
     fout.write((char*)this,sizeof(hotel));
     cout<<"\n Room is booked!!!";
   }

   cout<<"\n Press any key to continue!!";
   getch();
   fout.close();
}

//***************************************************
//   FUNCTION FOR DISPLAY THE DETAILS OF A CUSTOMER
//***************************************************

void hotel::display()
{
   system("cls");
   ifstream fin("Record.dat",ios::in|ios::binary);
   int r,flag;
   cout<<"\n Enter room no:";
   cin>>r;

   while(!fin.eof())
   {
      fin.read((char*)this,sizeof (hotel));
      if(room_no==r)
      {
	  system("cls");
	  cout<<"\n Customer Details";
	  cout<<"\n ****************";
	  cout<<"\n\n Room no:"<<room_no;
	  cout<<"\n Name:"<<name;
	  cout<<"\n Address:"<<address;
	  cout<<"\n Phone no:"<<phone;
	  flag=1;
	  break;
       }
    }
    if(flag==0)
	cout<<"\n Sorry Room no. not found or vacant!!!";

    cout<<"\n\n Press any key to continue!!!";
    getch();
    fin.close();
}

//***********************************************************
//   FUNCTION FOR DISPLAYING THE DETAILS OF ALL CUSTOMER
//***********************************************************

void hotel::rooms()
{
    system("cls");
    ifstream fin("Record.dat",ios::in|ios::binary);
    cout<<"\n\t\t List of Rooms Alloted";
    cout<<"\n\t\t\t *******************";
    cout<<"\n\n Room No.\tName\t\tAddress\t\tPhone No.\n";

    while( fin.read((char*)this,sizeof(hotel)))
    {
       cout<<"\n\n "<<room_no<<"\t\t"<<name;
       cout<<"\t\t"<<address<<"\t\t"<<phone;
    }

    cout<<"\n\n\n\t\t\t Press any key to continue!!!";
    getch();
    fin.close();
}

//****************************************************
//   FUNCTION TO EDIT THE DETAILS OF CUSTOMER
//****************************************************

void hotel::edit()
{
     system("cls"); 
     int choice,r;

     cout<<"\n EDIT MENU";
     cout<<"   *********";
     cout<<"\n\n 1. Modify Customer Record";
     cout<<"\n\n 2. Delete Customer Record";

     cout<<"\n Enter your choice:";
     cin>>choice;

     system("cls");
     cout<<"\n Enter room no.";
     cin>>r;

     switch(choice)
     {
	case 1: modify(r);
		break;
	case 2:	delete_rec(r);
		break;
	default: cout<<"\n Wrong Choice!!";
     }
     cout<<"\n Press any key to continue!!!";
     getch();
}

//**********************************************
//   FUNCTION FOR CHECK ABOUT ROOM
//**********************************************

int hotel::check(int r)
{
   int flag=0;
   ifstream fin("Record.dat",ios::in|ios::binary);
   while(!fin.eof())
   {
       fin.read((char*)this,sizeof(hotel));
       if(room_no==r)
       {
	 flag=1;
	 break;
       }
   }
   fin.close();
   return(flag);
}

//*******************************************************
//FUNCTION TO MODIFY THE DETAILS OF CUSTOMER
//*******************************************************

void hotel::modify(int r)
{
   long pos,flag=0;
   fstream file("Record.dat",ios::in|ios::out|ios::binary);

   while(!file.eof())
   {
      pos=file.tellg();
      file.read((char*)this,sizeof(hotel));
      if(room_no==r)
      {
	  cout<<"\n Enter New Details";
	  cout<<"\n *****************";
	  cout<<"\n Name:";
	 cin>>name;
	  cout<<" Address:";
	  gets(address);
	  cout<<" Phone no:";
	  cin>>phone;

	  file.seekg(pos);
	  file.write((char*)this, sizeof(hotel));
	  cout<<"\n Record is modified!!";
	  flag=1;
	  break;
      }
   }
   if(flag==0)
       cout<<"\n Sorry Room no. not found or vacant!!";
   file.close();
}

//******************************************************
//   FUNCTION TO DELETE THE DETAILS OF THE CUSTOMER
//******************************************************

void hotel::delete_rec(int r)
{
    int flag=0;
    char ch;
    ifstream fin("Record.dat",ios::in|ios::binary);
    ofstream fout("temp.dat",ios::out|ios::binary);

    while(!fin.eof())
    {
	fin.read((char*)this,sizeof(hotel));
	if(room_no==r)
	{
	    cout<<"\n Name:"<<name;
	    cout<<"\n Address:"<<address;
	    cout<<"\n Phone no:"<<phone;
	    cout<<"\n\n Do you to delete this record(y/n):";
	    cin>>ch;

	    if(ch=='n'|| ch=='N')
	    fout.write((char*)this, sizeof(hotel));
	    flag=1;
	}
	else
	    fout.write((char*)this, sizeof(hotel));
    }

    fin.close();
    fout.close();

    if(flag==0)
	cout<<"\n Sorry room no. not found or vacant!!";
    else
    {
       remove("Record.dat");
       rename("temp.dat","Record.dat");
    }
}

//******************************************************
//   THIS IS MAIN FUNCTION CALLING VARIOUS FUNCTIONS
//*******************************************************

int main()
{
   hotel h;
   system("cls");
   cout<<"\n\t\t\t****************************";
   cout<<"\n\t\t\t *HOTEL MANAGEMENT PROJECT*";
   cout<<"\n\t\t\t****************************";
   
   cout<<"\n\n\t\t\t Press any key to continue!!!";
   getch();
   h.main_menu();
   return 0;
}
// END OF MAIN FUNCTION
