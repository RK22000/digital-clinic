#include<fstream.h>
#include<ctype.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<process.h>
//=================================
int ainb(char a[], char b[]);
void op(char *p,int a);
//===========================================================================
class sicko
 {
	char nme[25];
	int AG,gndr,registrationNo;
	public:
	void reg();

	int regNo()
	 {	
		return registrationNo;
	 }

	char* name()
	 {	
	 	return nme;
	 }

	int age()
	 {	
	 	return AG;
	 }

	int gender()
	 {	
		return gndr;
	 }
 };

void sicko::reg()
 {
	ofstream outlink("patlist.dat",ios::binary|ios::ate);
	ifstream inlink("patlist.dat",ios::binary);
	inlink.seekg(0,ios::beg);
	int i=1;
	while(inlink.read((char*)this,sizeof(sicko)))
		i++;
	clrscr();
	cout<<"===========================================\n";
	cout<<"REGISTRATION\n";
	strcpy(nme,"NNNNNNNNNNNNNNNNNNNNNNNNN");
	cout<<"Enter Name : ";
	gets(nme);
	char ans[10];
	rpt:
	cout<<"Enter your age : ";
	cin>>AG;
	if(AG>100)
	 {
		cout<<"Are u sure you "<<AG<<" years old (yes/no)";
		gets(ans);
		if(!ainb("yes",ans))
			goto rpt;
	 }
	else if(AG<1)
		goto rpt;
	rpt1:
	cout<<"Select your gender (Male=1,Female=2) : ";
	cin>>gndr;
	if(gndr!=1&&gndr!=2)
		goto rpt1;
	gndr--;
	registrationNo=i;
	cout<<"Your registration number is "<<i<<endl;
	outlink.write((char*)this,sizeof(sicko));
	outlink.close();
	inlink.close();
 }

sicko s;

//======================
struct medList
 {
	char med[10];
	int cost;
 };
medList mL[]={
	{"Panadol" ,4},
	{"Otrovin" ,2},
	{  "gel"   ,5},
	{"Vicks"   ,2},
	{"Eye drop",6}
};

class appt
 {
	int department, apptStat, registrationNo, fee, expence,appointmentNo;   //apptStat,0=not done 1=done
	char symptom[20],prescription[20];
	public:
	void book();

	void assignDept()
	 {
		if(ainb("ear",symptom)||ainb("nose",symptom)||ainb("throat",symptom)||ainb("cough",symptom))
			department=1;
		else if(ainb("heart",symptom)||ainb("chest",symptom))
			department=3;
		else if(ainb("eye",symptom)||ainb("blind",symptom))
			department=4;
		else
			department=2;
	 }
	void loadSicko();

	void appShow(char c);
	void exp();

	void sympt()
	 {
		cout<<"Enter symptoms : ";
		gets(symptom);
	 }
	void pres();
	int dpt()
	 {
		return department;
	 }
	int appStat()
	 {
		return apptStat;
	 }
	int apptNo()
	 {
		return appointmentNo;
	 }
	int regNo()
	 {
		return registrationNo;
	 }
	void save();
	long search(int apNo);
 };
//===================

void appt::pres()
 {
	for(int i=0;i<5;i++)
	 {
		cout<<mL[i].med<<'\t';
	 }
		cout<<"\nEnter prescription : ";
		gets(prescription);
		apptStat=1;
 }

//===================
void appt::exp()
 {
	expence = 50;
	for(int i=0;i<5;i++)
	 {
		if(ainb(mL[i].med,prescription))
			expence+=mL[i].cost;
	 }
 }

//===============
long appt::search(int apNo)//input appointmentNumber and the corresponding appointment will be loaded at this pointer
 {
	ifstream in("apptlist.dat",ios::binary|ios::in);
	in.seekg(0,ios::beg);
	while(in.read((char*)this,sizeof(appt)))
	 {
		if(appointmentNo==apNo)
		 {
			return(in.tellg()-sizeof(appt));
		 }
	 }
	in.close();
	return(-1);
 }
//=============
void appt::save()
 {
	ofstream out("apptlist.dat",ios::binary|ios::ate); //create new obj
	appt tmp;
	long loc=tmp.search(appointmentNo); //use new obj to search pos
	if(loc>=0)
	{
		out.seekp(loc,ios::beg); // set pointer at position
		//cout<<loc<<endl;
	}
	out.write((char*)this,sizeof(appt)); ///write object at position
	out.close();
 }
//==============
void appt::appShow(char c)
 {
	loadSicko();
	cout<<"====================================================\n";
	cout<<"APPOINTMENT "<<appointmentNo;
	cout<<"\nStatus : "<<((apptStat)?"done":"not done");
	cout<<"\nName : ";
	op(s.name(),1);
	cout<<"Registration no. "<<registrationNo;
	cout<<"\nAge : "<<s.age();
	cout<<"\nGender : "<<((s.gender())?"Female":"Male");
	cout<<"\nSymptoms : "<<symptom;
	cout<<"\nDepartment : ";
	switch(department)
	 {
		case 1 : cout<<"ENT";
			break;
		case 2 : cout<<"GP";
			break;
		case 3 : cout<<"Cardiology";
			break;
		case 4 : cout<<"Opthermology";
			break;
		default: cout<<"unknown";
	 }
	 cout<<endl;

	if(apptStat)
	 {
		cout<<"Doctor prescription : "<<prescription<<endl;
		cout<<"Expence : "<<expence<<endl;
	 }
	else if (c=='p')
	 {
		char tmp[10];
		agn :
		cout<<"Do you wish to edit the symptoms : ";
		gets(tmp);
		if(ainb("yes",tmp))
		 {
			sympt();
			save();

		 }
		else if(ainb("no",tmp));
		else
			goto agn;
	 }
	if(c=='d')
	 {
		char tmp[10];
		again:
		cout<<"Do you wish to "<<(apptStat?"edit ":"give ")<<"prescription (yes/no): ";
		gets(tmp);
		if(ainb("yes",tmp))
		 {
			pres();
			exp();
			save();

		 }
		else if(ainb("no",tmp));
		else
			goto again;
	 }
	getch();
 }
//==============
void appt::loadSicko()
 {
	ifstream in("patlist.dat",ios::binary);
	while(in.read((char*)&s,sizeof(s)))
	{
		if(registrationNo==s.regNo())
		{
			break;
		}
	}
	in.close();
 }
void appt::book()
 {
	ofstream out("apptlist.dat",ios::binary|ios::ate);
	ifstream in("apptlist.dat",ios::binary);
	int i=1;
	in.seekg(0,ios::beg);
	while(in.read((char*)this,sizeof(appt)))
		i++;
	apptStat=0;
	registrationNo=s.regNo();
	appointmentNo=i;
	cout<<"your apointment number is : "<<appointmentNo<<endl;
	strcpy(symptom,"ssssssssssssssssssss");
	sympt();
	assignDept();
	strcpy(prescription,"pppppppppppppppppppp");
	expence=0;
	save();
	in.close();
 }
//========
appt a;
//==============================
void login();
//==========================================================================
int ainb(char a[], char b[])
 {	int A=strlen(a),B=strlen(b),k;
	for(int i=0;i<(B-A)+1;i++)
	 {	k=0;
		for(int j=0;j<A;j++)
		 {	if(tolower(a[j])==tolower(b[i+j]))
			 {	k++;
				if(k==A)
					return(1);
			 }
			else
			break;
		 }
	 }
	return(0);
 }
//==========================================================================
void op(char *p,int a=0) //int a will decide weather to use endl ant the end
 {
	for(int i=0;*(p+i)!='\0';i++)
	 {
		cout<<*(p+i);
	 }
	cout<<' ';
	if(a)
		cout<<endl;
 }
//==========================================================================
void logout()
 {
	char ch[3];
	cout<<endl;
	rpt:
	cout<<"Would you like to exit (yes/no) : ";
	gets(ch);
	if(ainb("yes",ch))
		exit(0);
	else if(ainb("no",ch))
		login();
	else
	 {
		cout<<"Please specify ";
		goto rpt;
	 }
 }
//=========================================================================
void apptList(int chk,char c)
 {
	int k,aNo;
	char ckc[10];
	ifstream fin;
	start:
	k=0;
	fin.open("apptlist.dat",ios::binary);
	fin.seekg(0,ios::beg);
	while(fin.read((char*)&a,sizeof(a)))
	{
		if(c=='d')
			if(a.dpt()==chk)
			{	k++;
				cout<<k<<')'<<" appointment number "<<a.apptNo()<<((a.appStat())?((char)251):' ')<<endl;
			}
		if(c=='p')
		{
			if(a.regNo()==chk)
			{	k++;
				cout<<k<<')'<<" appointment number "<<a.apptNo()<<((a.appStat())?((char)251):' ')<<endl;
			}
		}
	}
	fin.close();

	if(k==0)
	{
		cout<<"<No appointments in your record>\n";
		getch();
	}
	else
	{	cout<<"\nselect appointment number : ";
		cin>>aNo;
		a.search(aNo);
		a.appShow(c);
	}

	if(c=='d')
	{
		cout<<"===========================================================\n";
		rpt:
		cout<<"would you like to logout (yes/no) : ";
		gets(ckc);
		if(ainb("yes",ckc))
			logout();
		else if(ainb("no",ckc))
			goto start;
		else
		{
			cout<<"Please specify ";
			goto rpt;
		}
	}
 }
//==========================================================================
void patient()
 {
	int appNo;
	char ans[50];
	start :
	clrscr();
	cout<<"===========================================================\n";
	cout<<"Welcom ";
	op(s.name(),1); //op  is function that will out put string from base address
	cout<<"Would you like to \n\t(1)book appointment \n\t(2)check appointment report \n\t(3)logout\n\t: ";
	gets(ans);
	if(ainb("check",ans)||(!strcmp("2",ans)))
	 {
		apptList(s.regNo(),'p');
	 }
	else if(ainb("book",ans)||(!strcmp("1",ans)))
	 {
		a.book();
		cout<<"Your appointment has been booked";
		getch();
	 }
	else if(ainb("logout",ans)||(!strcmp("3",ans)))
		logout();
	goto start;
 }
//==========================================================================
void lkup(int regNo)
 {
	ifstream fin("pat list.dat",ios::binary);
	while(fin.read((char*)&s,sizeof(s)))
	 {
		if(regNo==s.regNo())
		 {
			fin.close();
			patient();
		 }
	 }
	cout<<"liar liar pants on fire\n";
	fin.close();
	s.reg();
	patient();
 }
//==========================================================================
void patChk()
 {
	char ans[10];
	int regNo;
	start :
	cout<<"\nAre you registered with us? : ";
	gets(ans);
	if(ainb("yes",ans))
	 {
		cout<<"Enter your registration number : ";
		cin>>regNo;
		lkup(regNo);
	 }
	else if(ainb("no",ans))
	 {
		s.reg();
		patient();
	 }
	else
	 {
		cout<<"please answer yes or no\n";
		goto start;
	 }
 }
//=========================================================================
void doctor()
 {
	int ch;
	char ans[10];
	start:
	cout<<"\n\t\t1)ENT\n\t\t2)GP\n\t\t3)Cardiologist\n\t\t4)Opthermalogist\nWhat doctor are you : ";
	gets(ans);
	ch=((int)*ans)-((int)'0');
	if(0<ch&&ch<5)
	 {
		apptList(ch,'d');
	 }
	cout<<"Please specify number";
	goto start;
 }
//============================================================================
void login()
 {
	char ch[10];
	clrscr();
	start :
	cout<<"===========================================================\n";
	cout<<"Are you a doctor(1) or a patient(2) : ";
	gets(ch);
	if(ainb("patient",ch)||(!strcmp(ch,"2")))
	 {
		patChk();
	 }
	else if(ainb("doctor",ch)||ainb("dr",ch)||(!strcmp(ch,"1")))
	 {
		doctor();
	 }
	else
	 {	cout<<"please repeat\n";
		goto start;
	 }
	getch();
	goto start;
 }
//=========================================================================
void main()
 {
	clrscr();
	login();
 }

