#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<fstream.h>
#include<process.h>
class bus
{ int id;
  char from[50];
  char dest[50];
  int timeA,timeD;
  int maxseats;
  int booked;
  int fare;
  public:
  bus()
  { id=0;
    maxseats=50;
    booked=0;
    fare=0;
    timeA=0;
    timeD=0;
    strcpy(dest,"");
  }
  void input();
  void show();
  void display();
  int getid()
  {
    return id;
  }
  void book()
  {
    booked++;
  }
  char* getfrom()
  {
    return from;
  }
  char* getdest()
  {
    return dest;
  }
  int gettimeA()
  {
    return timeA;
  }
  int gettimeD()
  {
    return timeD;
  }
  int getbooked()
  {
    return booked;
  }
  int getfare()
  {
    return fare;
  }
};
class ticket
{ char name[25];
  bus b;
  public:
  void generate(char cname[],bus tb)
  {
     strcpy(name,cname);
     b=tb;
  }
  void display()
  {
    cout<<"Customer Name:"<<name<<endl;
    cout<<"Details of Bus:"<<endl;
    b.show();
  }
};
void bus::input()
{
  cout<<"Enter bus id:";
  cin>>id;
  cout<<"Enter starting point:";
  gets(from);
  cout<<"Enter destination:";
  gets(dest);
  cout<<"Enter time of departure:";
  cin>>timeD;
  cout<<"Enter time of arrival:";
  cin>>timeA;
  cout<<"Enter fare of bus:";
  cin>>fare;
}
void bus::display()
{
  cout<<"\t"<<id<<"\t"<<from<<"\t"<<dest<<"\t"<<timeD<<"\t"<<timeA<<"\t"<<maxseats<<"\t"<<booked<<"\t"<<fare<<"\n";
}
void bus::show()
{
   cout<<"BUS ID.-"<<id<<endl
       <<"From- "<<from<<" To- "<<dest<<endl
       <<"Departure- "<<timeD<<"\tArrival-"<<timeA<<endl
       <<"Seats Remaining:"<<maxseats-booked<<endl;
}
void admin()
{  bus b;
   int ch;
   fstream f1,f2;
   do
   {   clrscr();
       cout<<"\n\t\t\t***********************\n";
       cout<<"\t\t\t\tWELCOME";
       cout<<"\n\t\t\t***********************\n";
       cout<<"\t\t\t  1.Add a new bus"<<endl
	      <<"\t\t\t  2.Show selected bus"<<endl
	      <<"\t\t\t  3.Display all bus"<<endl
	      <<"\t\t\t  4.Delete a bus"<<endl
	      <<"\t\t\t  5.Exit"<<endl
	      <<"\t\t\t\n  Enter your choice:";
       cin>>ch;
       switch(ch)
       {
	   case 1 :
			 f1.open("tourism.dat",ios::app|ios::binary);
			 b.input();
			 f1.write((char*)&b,sizeof(b));
			 f1.close();
			 cout<<"Bus added successfully"<<endl;
			 getch();
			 clrscr();
			 break;
	   case 2 :
			int bid,ck=0;
			cout<<"Enter the bus id:";
			cin>>bid;
			f1.open("tourism.dat",ios::in|ios::binary);
			if(f1.fail())
			   cout<<"Cant open file"<<endl;
			else
			{
				while(f1.read((char*)&b,sizeof(b)))
				 {
					 if(b.getid()==bid)
					 {
					       b.show();
					       ck=1;

					 }
				 }
				 if(ck==0)
				      cout<<"Bus not found"<<endl;
			 }
			 f1.close();
			 break;
	   case 3 :
			 f1.open("tourism.dat",ios::in|ios::binary);
			 if(f1.fail())
			    cout<<"Can't open file"<<endl;
			 else
			 {    clrscr();
			      cout<<"\n       **************************************************************\n";
			      cout<<"\t\t\t   BUS TRAVEL AGENCY\n\n";
			      cout<<"\tBUS ID.\tFROM\tDEST\tDEP\tARRV\tSEATS\tBOOKED\tFARE\n";
			      cout<<"       **************************************************************\n";
			      while(f1.read((char*)&b,sizeof(b)))
			       b.display();
			 }
			 f1.close();
			 cout<<"\nPress a key to continue";
			 getch();
			 clrscr();
			 break;
	   case 4 :
			 ck=0;
			 cout<<"Enter the bus ID:";
			 cin>>bid;
			 f1.open("tourism.dat",ios::in|ios::binary);
			 f2.open("temp.dat",ios::out|ios::binary);
			 if(f1.fail())
			     cout<<"Can't open file"<<endl;
			 else
			 {
			       while(f1.read((char*)&b,sizeof(b)))
				{
				      if(b.getid()!=bid)
				      {
					 f1.write((char*)&b,sizeof(b));
				      }
				      else
				      {
					  b.show();
					  ck=1;
				       }
				 }
				 if(ck==0)
				      cout<<"Bus not found"<<endl;
				 else
				      cout<<"Bus deleted"<<endl;
			 }
			 f1.close();
			 f2.close();
			 remove("tourism.dat");
			 rename("temp.dat","tourism.dat");
			 cout<<"\nPress a key to continue";
			 getch();
			 clrscr();
			 break;
       }
  }while(ch!=5);
}
void customer()
{
   int ch;
   fstream f1,f2;
   bus b;
   ticket t;
   do
   {   clrscr();
       cout<<"\t\t\t  WELCOME" ;
       cout<<"\n       ***********************\n";
       cout<<"\t\t\t  1.Book a ticket"<<endl
	      <<"\t\t\t  2.Show ticket"<<endl
	      <<"\t\t\t  3.Display all bus"<<endl
	      <<"\t\t\t  4.Display selected bus"<<endl
	      <<"\t\t\t  5.Exit"<<endl
	      <<"\t\t\t\n  Enter your choice:";
       cin>>ch;
       switch(ch)
       {
	  case 1 :  char destination[50],cname[25];
		    int ck=0,bid;
		    cout<<"Enter destination:";
		    gets(destination);
		    f1.open("tourism.dat",ios::in|ios::out|ios::binary);
		    if(f1.fail())
		      cout<<"Can't open file!"<<endl;
		    else
		    {
		       while(f1.read((char*)&b,sizeof(b)))
		       {
			  if(strcmp(b.getdest(),destination)==0)
			  {
			      b.show();
			      ck=1;
			      cout<<"Enter the customer name:";
			      gets(cname);
			      b.book();
			      t.generate(cname,b);
			      f2.open("ticket.dat",ios::app|ios::binary);
			      f2.write((char*)&t,sizeof(t));
			      f2.close();
			     f1.seekp(f1.tellg()-sizeof(b),ios::beg);
			     f1.write((char*)&b,sizeof(b));
			     cout<<"\nTicket booked"<<endl;
			     cout<<"\nPress a key to continue"<<endl;
			     getch();
			     break;
			  }
		       }
			  if(ck==0)
			     cout<<"No record of bus found"<<endl;
		     }
		     f1.close();
		     break;
	  case 2 :
		     cout<<"\nBooked TIckets\n\n";
		     f2.open("ticket.dat",ios::in|ios::binary);
		     if(f2.fail())
		       cout<<"Can't open file!"<<endl;
		     else
		     {
		       while(f2.read((char*)&t,sizeof(t)))
		       t.display();
		     }
		     f2.close();
		     cout<<"\nPress a key to continue\n";
		     getch();
		     break;
	   /* case 3 :   f1.open("tourism.dat",ios::in|ios::binary);
			 if(f1.fail())
			    cout<<"Can't open file"<<endl;
			 else
			 {    clrscr();
			      cout<<"\t\t\t   BUS TRAVEL AGENCY";
			      cout<<"\n       **************************************************************\n";
			      cout<<"\tBUS ID.\tFROM\tDEST\tDEP\tARRV\tSEATS\tBOOKED\tFARE\n";
			      cout<<"       **************************************************************\n";
			      while(f1.read((char*)&b,sizeof(b)))
			       b.display;
			 }
			 f1.close();
			 cout<<"\nPress a key to continue";
			 getch();
			 clrscr();
			 break;
	  case 4 :
			cout<<"Enter the bus id:";
			cin>>bid;
			f1.open("tourism.dat",ios::in|ios::binary);
			if(f1.fail())
			   cout<<"Cant open file"<<endl;
			else
			{
				while(f1.read((char*)&b,sizeof(b))
				 {
					 if(b.getid()==bid)
					 {
					       b.show();
					       ck=1;
					       break;
					 }
				 }
				 if(ck==0)
				      cout<<"Bus not found"<<endl;
			 }
			 f1.close();
			 break; */
	       }
		}while(ch!=3);
}

void main()
{  clrscr();
   int ch;
   do
   {  clrscr();
      cout<<"\n       **************************************************************\n";
      cout<<"\t\t\t   BUS TRAVEL AGENCY";
      cout<<"\n       **************************************************************\n";
      cout<<"\t\t\t   1.Admin\n"
	  <<"\t\t\t   2.Customer\n"
	  <<"\t\t\t   3.Exit\n"
	  <<"\t\t\t\n   Enter your choice:";
      cin>>ch;
      switch(ch)
      {
	 case 1 :
		  char pwd[20];
		  char pswd[]="212173314";
		  cout<<"Enter password:";
		  for(int i=0;i<9;i++)
		  { pwd[i]=getch();
		     cout<<"*";
		  }
		  pwd[i]='\0';
		  if(strcmp(pwd,pswd)==0)
		   { admin();
		   }
		  else
		   cout<<"\nInvalid password!!!";
		   getch();

		  break;
	 case 2 :
		  customer();
		  break;
      }
   }while(ch!=3);
}