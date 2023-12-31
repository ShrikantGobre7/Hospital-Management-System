/*
	Project Info:
		This program can maintain the record of patients. This program is log-in based and password-protected.
		Option to change password is in the main menu.
		Users can add Patient Info, delete Patient Info, delete and replace a particular field of a Patient
		Info, search Patient Info by using filters, and change the Password.

		This program is intended to be used by the hospital staff who maintain Patient Records.
*/

//PROGRAM BEGINS HERE
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
////////////////////////////////////////////////////////////////////////////////
struct Patient
{
	char name[30];
	char disease[30],address[30];
	int cabin,phone,age;
} x[100];			//Modify max Patient Strength here

void add();
void view();
void search();
void edit();
void del();
////////////////////////////////////////////////////////////////////////////////
struct User
{
	char password[30];
	char userName[30];
} y[5];				//Modify max User Strength here

void editSelf();
void removeSelf();
void addUser();
void viewUsers();
void delUsers();
////////////////////////////////////////////////////////////////////////////////
struct Admin
{
	char hospName[30];
	char hospAdrs[30];
	int hospContact;
	char adminKey[6];
} admin0[1];

void addAdmin();
void editAdmin();
void changeKey();
void viewAdmin();
void removeUser();


////////////////////////////////////////////////////////////////////////////////
int in1;						//for input
int i,j=0;						//primary variables of methods, except main()
int a=0,sum=0,g;
int patCount;
int userCount;
int adminCount;					//must be 1

time_t mytime;
//int flag;

void authorize(int);
int activeUser=-1;				//stores index no of active User
int isUser=
    -1;					//will be used to log out the user immediately if he deletes himself
int isAdmin=
    -1;					//will store 1 if user is authorized as admin, 0 if fails to authorize
const int maxLoginCount=3;


void import();
void backup();
void wait(int);
void screenReset();				//clears the screen and puts header again

void encrypt(char*);
void decrypt(char*);
int encryptInt(int);
int decryptInt(int);

int main()
{
	//following lines before blank line are FOR TEST ONLY
//	char u[10]="hello";
//	encrypt(u);
//	printf("\nEncrypted = %s",u);
//	decrypt(u);
//	printf("\nDecrypted = %s",u);
//	int uu=12390;
//	uu=encryptInt(uu);
//	printf("\nEncrypted = %d",uu);
//	printf("\nEnter any no to continue = ");
//	int v;
//	scanf("%d",&v);
	
	
	screenReset();

	import();

	int m;		//for input below
	printf("\n\n\nLog in as?\n");
	printf("\n1. User");
	printf("\n2. Administrator");
	printf("\n\nEnter Your Choice = ");
	scanf("%d",&m);
	if(m==1||m==2)
		authorize(m);

	int c,d,e;
	if(isUser==1||isAdmin==1)
	{
		printf("\nWelcome to Hospital Records Manager!");
		wait(2);
		screenReset();
	}

	c=-1;

	if(m==1)//USER SECTION
	{
		while(c!=0)
		{
			//wait(1);
			screenReset();

			if(isUser==1)
			{
				printf("\n\t\t\t/////MAIN MENU/////");
				printf("\n\t\t\t1.Show Patient Menu");
				printf("\n\t\t\t2.Show User Menu");
				printf("\n\t\t\t0.SAFELY CLOSE THE PROGRAM\n");
				printf("\n\n\t\t\tWhat do you want to be done? = ");
				scanf("%d",&d);
				fflush(stdin);
			}
			else
				d=-1;	//to move user out of the program as he/she is unauthorized now

			if(d==1)
			{
				//printf("\ncame back to the d=1 part");		//TEST STATEMENT
				//system("cls");

				e=-1;
				while(e!=0)
				{
					wait(1);
					screenReset();
					if(isUser==1)
					{
						printf("\n\t\t\t/////PATIENT MENU/////\n");
						printf("\n\t\t\t1.Add Patients");
						printf("\n\t\t\t2.View Patients List");
						printf("\n\t\t\t3.Search Patients");
						printf("\n\t\t\t4.Edit Patient Details");
						printf("\n\t\t\t5.Delete Patient Details");
						printf("\n\t\t\t0.Go Back To Main Menu\n");
						printf("\n\n\t\t\tEnter your choice = ");
						scanf("%d",&e);//choice for option
						fflush(stdin);//making it clear
					}
					else
						e=0;		//isUserty action

					if(e==1)   //add
					{
						add();
					}
					else if(e==2)     //view
					{
						view();
					}
					else if(e==3)     //search
					{
						search();
					}
					else if(e==4)     //edit
					{
						edit();
					}
					else if(e==5)     //delete
					{
						del();
					}
					else if(e==0)
					{
						printf("\nRedirecting to Main Menu...");
					}
					else
					{
						printf("\nOops! %d is an Invalid input!",e);
					}
				}//inner while closed
			}
			else if(d==2)
			{
				e=-1;
				while(e!=0)
				{
					wait(1);
					screenReset();
					if(isUser==1)
					{
						printf("\n\t\t\t/////USER MENU/////\n");
						printf("\n\t\t\t1.Change username/password");
						printf("\n\t\t\t2.Delete my User Account");
						printf("\n\t\t\t0.BACK TO MAIN MENU");
						printf("\n\n\t\t\tEnter your choice = ");
						fflush(stdin);
						scanf("%d",&e);
						fflush(stdin);
					}
					else
						e=0;


					if(e==1)
					{
						editSelf();
						printf("\nDirecting to the User Menu...");
					}
					else if(e==2)
					{
						removeSelf();
						printf("\nDirecting to the User Menu...");
					}
					else if(e==0)
					{
						printf("\nRedirecting to Main Menu...");
					}
					else
					{
						printf("\nOops! %d is an invalid input.",e);
						printf("\nDirecting to the User Menu...");
					}
				}

			}
			else if(d==0)
			{
				wait(1);
				screenReset();

				if(isUser==1)
					printf("\nSee You Soon!");
				else
				{
					printf("\nWE COULDN'T VALIDATE YOUR AUTHORISATION.\nYou can restart the program and try again.");
					isUser=0;
				}

				backup();
				break;
			}
			else
			{
				printf("\nOops! %d is an invalid input.",d);
			}

		}//end of while(MAIN ONE)
	}
    
	else if(m==2)//ADMIN SECTION
	{   c=-1;
		while(c!=0)
		{
			//wait(1);
			screenReset();

			if(isAdmin==1)
			{
				printf("\n\t\t\t/////ADMIN MENU/////\n");
				printf("\n\t\t\t1.Show Patient Menu");
				printf("\n\t\t\t2.Show Admin Menu");
				printf("\n\t\t\t0.SAFELY CLOSE THE PROGRAM\n");
				printf("\n\t\t\tWhat do you want to be done? = ");
				scanf("%d",&d);
				fflush(stdin);
			}
			else
				d=0;	//to move user out of the program as he/she is unauthorized now

			if(d==1)
			{
				//printf("\ncame back to the d=1 part");		//TEST STATEMENT
				//system("cls");

				e=-1;
				while(e!=0)
				{
					wait(1);
					screenReset();
					if(isAdmin==1)
					{
						printf("\n\t\t\t/////PATIENT MENU/////\n");
						printf("\n\t\t\t1.Add Patients");
						printf("\n\t\t\t2.View Patients List");
						printf("\n\t\t\t3.Search Patients");
						printf("\n\t\t\t4.Edit Patient Details");
						printf("\n\t\t\t5.Delete Patient Details");
						printf("\n\t\t\t0.Go Back To Main Menu\n");
						printf("\n\n\t\t\tEnter your choice = ");
						scanf("%d",&e);//choice for option
						fflush(stdin);//making it clear
					}
					else
						e=0;		//isUserty action

					if(e==1)   //add
					{
						add();
					}
					else if(e==2)     //view
					{
						view();
					}
					else if(e==3)     //search
					{
						search();
					}
					else if(e==4)     //edit
					{
						edit();
					}
					else if(e==5)     //delete
					{
						del();
					}
					else if(e==0)
					{
						printf("\nRedirecting to Main Menu...");
					}
					else
					{
						printf("\nOops! %d is an Invalid input!",e);
					}
				}//inner while closed
			}
			else if(d==2)
			{
				e=-1;
				while(e!=0)
				{
					wait(1);
					screenReset();
					if(isAdmin==1)
					{
						printf("\n\t\t\t/////USER MENU/////\n");
						printf("\n\t\t\t1.Add new User");
						printf("\n\t\t\t2.View Users");
						printf("\n\t\t\t3.Delete Users");
						printf("\n\t\t\t4.View Admin Details");
						printf("\n\t\t\t5.EditAdminDetails");
						printf("\n\t\t\t6.CHANGE ADMIN KEY");
						printf("\n\t\t\t0.BACK TO MAIN MENU\n");
						printf("\n\n\t\t\tEnter your choice = ");
						fflush(stdin);
						scanf("%d",&e);
						fflush(stdin);
					}
					else
						e=0;


					if(e==1)
					{
						addUser();
						printf("\nDirecting to the User Menu...");
					}
					else if(e==2)
					{
						viewUsers();
						printf("\nDirecting to the User Menu...");
					}
					else if(e==3)
					{
						delUsers();
						printf("\nDirecting to the User Menu...");
					}
					else if(e==4)
					{
						viewAdmin();
						printf("\nDirecting to the User Menu...");
					}
					else if(e==5)
					{
						editAdmin();
						printf("\nDirecting to the User Menu...");
					}
					else if(e==6)
					{
						changeKey();
						printf("\nDirecting to the User Menu...");
					}

					else if(e==0)
					{
						printf("\nRedirecting to Main Menu...");
					}
					else
					{
						printf("\nOops! %d is an invalid input.",e);
					}
				}

			}
			else if(d==0)
			{
				wait(1);
				screenReset();

				if(isAdmin==1)
					printf("\nSee You Soon!");
				else
				{
					printf("\nWE COULDN'T VALIDATE YOUR AUTHORISATION.\nYou can restart the program and try again.");
					isAdmin=0;
				}

				backup();
				break;
			}
			else
			{
				printf("\nOops! %d is an invalid input.",d);
			}

		}//end of while(MAIN ONE)
	}

	printf("\nClosing the application...");
	printf("\n------------------------------------------------------------------------------------------------------------------------");

	return 0;
}//main closed
////////////////////////////////////////////////////////////////////////////////
void authorize(int m)
{
	wait(2);
	screenReset();

	char uName[30],uPass[30],admKey[6];
	int i,f=0,count=0;	//count is for no of times user has tried to access


	if(m==1)
	{
		printf("\nAUTHORISATION AS USER:");

		while(count<maxLoginCount&&isUser!=1)
		{
			if(userCount!=0)
			{
				printf("\nEnter Your Credentials below:");

				fflush(stdin);
				printf("\nUserName : ");
				gets(uName);
				fflush(stdin);

				printf("\nPassword : ");
				gets(uPass);
				fflush(stdin);

				//count++;

				for(i=0; i<userCount; i++)
				{
					if(strcmp(uName,y[i].userName)==0)
						if(strcmp(uPass,y[i].password)==0)
						{
							f=1;
							break;
						}
				}
				if(f==1)
				{
					isUser=1;
					break;
				}
				else
				{
					printf("\nUSERNAME OR PASSWORD IS INCORRECT!");

					if(count<maxLoginCount-1)
						printf("\n%d CHANCES LEFT",(maxLoginCount-count));
					wait(2);
					screenReset();
				}
			}
			else
			{
				printf("\nNO USERS FOUND! ASK YOUR ADMIN TO ADD YOU AS A USER.");
			}
			count++;
		}

		if(f==1)
		{
			activeUser=i;
			printf("\nLogged in as %s",y[activeUser].userName);
			wait(2);
			screenReset();
		}
		else
		{
			printf("\nToo Many Unsuccessful Attempts!");
			isUser=0;
			wait(2);
		}
	}
	else if(m==2)
	{
		count=0;
		printf("\nAUTHORISATION AS ADMIN:");
		if(adminCount==1)
		{
			while(count<3&&isAdmin!=1)
			{
				printf("\nEnter Admin Key = ");
				fflush(stdin);
				gets(admKey);
				count++;
				if(strcmp(admKey,admin0[0].adminKey)==0)
				{
					isAdmin=1;
					printf("\nLOGGED IN AS ADMIN");
				}
				else
				{
					printf("\nINCORRECT ADMIN KEY ENTERED!");
					printf("\n%d CHANCES LEFT!",(maxLoginCount-count));
				}
			}
		}
		else
		{
			printf("\nNO ADMINS FOUND!\nDIRECTING TO ADD ADMIN RECORDS...");
			addAdmin();
		}
	}
	else
	{
		printf("\nInvalid Input!");
	}
}
////////////////////////////////////////////////////////////////////////////////
void add()
{
	wait(1);
	screenReset();
	printf("\nPATIENT ADDITION:");

	printf("\nNo of Patients already in the database = %d\n\n",
	       patCount);//how many inputs
	printf("How many entries to make? = \n");
	scanf("%d",&in1);
	sum=in1+patCount;

	for(i=patCount,j=0; i<sum; i++)
	{
		printf("\n");
		fflush(stdin);
		printf("Enter patient's Name = ");
		gets(x[i].name);
		fflush(stdin);
		printf("Enter patient's Address =");
		gets(x[i].address);
		fflush(stdin);
		printf("Enter disease = ");
		gets(x[i].disease);
		fflush(stdin);
		printf("Enter the age = ");
		scanf("%d",&x[i].age);
		fflush(stdin);
		printf("Enter cabin no = ");
		scanf("%d",&x[i].cabin);
		fflush(stdin);
		printf("Enter phone number = ");
		scanf("%d",&x[i].phone);
		fflush(stdin);
		printf("\n");
		j++;
		a++;
		patCount++;
	}
}

void view()
{
	//char useless[1];
	wait(1);
	screenReset();
	printf("\nPATIENT LIST:");

	for(i=0; i<patCount; i++)
	{
		printf("\n");
		printf("Serial Number :\t%d\n",i);
		printf("Name :\t\t");
		puts(x[i].name);
		printf("Address :\t");
		puts(x[i].address);
		printf("Disease :\t");
		puts(x[i].disease);
		printf("Cabin no :\t%d\nPhone number :\t%d\nAge :\t\t%d",x[i].cabin,x[i].phone,
		       x[i].age);
		printf("\n");
	}
	printf("\nEnter any no to continue = ");
	fflush(stdin);
	//gets(useless);
	int useless;
	scanf("%d",&useless);
	fflush(stdin);
}

void edit()
{
	wait(1);
	screenReset();
	printf("\nPATIENT RECORD EDIT:");

	fflush(stdin);
	printf("\nWhat do you want to edit ?\n");
	printf("Enter your option\n");
	printf("1.Name\n2.Address\n3.Disease\n4.Age\n5.Cabin\n6.Phone no.\n");
	printf("Option=");
	scanf("%d",&j);//option
	if(j<=6)
	{
		printf("Enter the serial no of that patient= (0 - %d)=",patCount-1);
		scanf("%d",&i);//serial number
		if(i<patCount)
		{
			if(j==1)
			{
				fflush(stdin);
				printf("Enter the new name=");
				gets(x[i].name);

			}
			else if(j==2)
			{
				fflush(stdin);
				printf("Enter the new address=");
				gets(x[i].address);

			}
			else if(j==3)
			{
				fflush(stdin);
				printf("Enter the new Disease=");
				gets(x[i].disease);
			}
			else if(j==4)
			{
				fflush(stdin);
				printf("Enter the new Age=");
				scanf("%d",&x[i].age);
			}

			else if(j==5)
			{
				fflush(stdin);
				printf("Enter the new Cabin no=");
				scanf("%d",&x[i].cabin);
			}

			else if(j==6)
			{
				fflush(stdin);
				printf("Enter the new Phone no =");
				scanf("%d",&x[i].phone);
			}
		}
		else
		{
			printf("\n\nInvalid Serial \nTry Again !!\n\n");
		}
	}
	else
	{
		printf("\n\nInvalid option\nTry Again!!\n\n");
	}
}

void search()
{
	wait(1);
	screenReset();
	printf("\nPATIENT SEARCH:");

	int f;
	char u[100];

	printf("\nBy what do you want to search ?\n");
	printf("1.Serial no.\n2.Name\n3.Addres\n4.Disease\n5.Cabin no.\n6.Phone no.\n7.Age\n0. Go back\n\nOption = ");
	scanf("%d",&j);

	if(j==1)
	{
		printf("Enter Serial number of the patient=");
		scanf("%d",&i);
		if(i<patCount)
		{
			printf("\n");
			printf("Serial Number=%d\n",i);
			printf("Name = ");
			puts(x[i].name);
			printf("Address = ");
			puts(x[i].address);
			printf("Disease = ");
			puts(x[i].disease);
			printf("Cabin no = %d\nPhone number = 0%d\nAge = %d",x[i].cabin,x[i].phone,
			       x[i].age);
			printf("\n\n");
		}
		else
			printf("\n\nNot Found\n\n");
	}

	else if(j==2)
	{
		f=1;
		fflush(stdin);
		printf("Enter your name=");
		gets(u);
		fflush(stdin);
		for(g=0; g<patCount; g++)
		{
			if(strcmp(u,x[g].name)==0)
			{
				printf("\n");
				printf("Serial Number=%d\n",g);
				printf("Name = ");
				puts(x[g].name);
				printf("Address = ");
				puts(x[i].address);
				printf("Disease = ");
				puts(x[g].disease);
				printf("Cabin no = %d\nPhone number = 0%d\nAge = %d",x[g].cabin,x[g].phone,
				       x[g].age);
				printf("\n\n");
				f=0;

			}
		}
		if(f==1)
			printf("\nNot Found\n");



	}
	else if(j==3)
	{
		printf("Enter Address of the patient=");
		gets(u);
		fflush(stdin);
		if(strcmp(u,x[g].address)==0)
		{
			printf("\n");
			printf("Serial Number=%d\n",i);
			printf("Name = ");
			puts(x[i].name);
			printf("Disease = ");
			puts(x[i].disease);
			printf("Cabin no = %d\nPhone number = 0%d\nAge = %d",x[i].cabin,x[i].phone,
			       x[i].age);
			printf("\n\n");
		}
		else
			printf("\n\nNot Found\n\n");
	}
	else if(j==4)
	{
		f=1;
		fflush(stdin);
		printf("Enter Disease = ");
		gets(u);
		fflush(stdin);
		for(g=0; g<patCount; g++)
		{
			if(strcmp(u,x[g].disease)==0)
			{
				printf("\n");
				printf("Serial Number=%d\n",g);
				printf("Name = ");
				puts(x[g].name);
				printf("Address = ");
				puts(x[i].address);
				printf("Disease = ");
				puts(x[g].disease);
				printf("Cabin no = %d\nPhone number = 0%d\nAge = %d",x[g].cabin,x[g].phone,
				       x[g].age);
				printf("\n\n");
				f=0;
			}


		}
		if(f==1)
			printf("\nNot Found\n");


	}
	else if(j==5)
	{
		f=1;
		printf("Enter Cabin number = ");
		scanf("%d",&f);
		for(g=0; g<patCount; g++)
		{
			if(f==x[g].cabin)
			{
				printf("\n");
				printf("Serial Number=%d\n",g);
				printf("Name = ");
				puts(x[g].name);
				printf("Address =");
				puts(x[g].address);
				printf("Disease = ");
				puts(x[g].disease);
				printf("Cabin no = %d\nPhone number = 0%d\nAge = %d",x[g].cabin,x[g].phone,
				       x[g].age);
				printf("\n\n");
				f=0;
			}

		}
		if(f==1)
			printf("Not Found\n\n");

	}
	else if(j==6)
	{
		f=1;
		printf("Enter Phone number = ");
		scanf("%d",&f);
		for(g=0; g<patCount; g++)
		{
			if(f==x[g].phone)
			{
				printf("\n");
				printf("Serial Number=%d\n",g);
				printf("Name = ");
				puts(x[g].name);
				printf("Address =");
				puts(x[g].address);
				printf("Disease = ");
				puts(x[g].disease);
				printf("Cabin no = %d\nPhone number = 0%d\nAge = %d",x[g].cabin,x[g].phone,
				       x[g].age);
				printf("\n\n");
				f=0;
			}

		}
		if(f==1)
			printf("Not Found");
	}
	else if(j==7)
	{
		f=1;
		printf("Enter Age = ");
		scanf("%d",&f);
		for(g=0; g<patCount; g++)
		{
			if(f==x[g].age)
			{
				printf("\n");
				printf("Serial Number=%d\n",g);
				printf("Name = ");
				puts(x[g].name);
				printf("Address=");
				puts(x[g].address);
				printf("Disease = ");
				puts(x[g].disease);
				printf("Cabin no = %d\nPhone number = 0%d\nAge = %d",x[g].cabin,x[g].phone,
				       x[g].age);
				printf("\n\n");
				f=0;
			}

		}
		if(f==1)
			printf("Not Found\n\n");

	}
	else if(j==0)
	{
		printf("\n");
	}
	else
	{
		printf("\n\nInvalid input\n\n");
	}

	int useless;
	printf("\nEnter any no to continue = ");
	scanf("%d",&useless);
}

void del()
{
	wait(1);
	screenReset();
	printf("\nPATIENT RECORD DELETE:");

	printf("nEnter the serial number of the patient that you want to delete=");
	scanf("%d",&i);
	if(i<patCount)
	{
		printf("What do you want ?\n");
		printf("1.Remove the whole record\n2.Remove Name\n3.Remove Address\n4.Remove Disease\n5.Remove age\n6.Remove Cabin\n7.Remove phone number\nOption = ");
		scanf("%d",&j);
		if(j==1)
		{
			while(i<patCount)
			{
				strcpy(x[i].name,x[i+1].name);
				strcpy(x[i].disease,x[i+1].disease);
				x[i].age=x[i+1].age;
				x[i].cabin=x[i+1].cabin;
				x[i].phone=x[i+1].phone;
				i++;
			}
			patCount--;
		}
		else if(j==2)
		{
			strcpy(x[i].name,"Cleared");

		}
		else if(j==3)
		{
			strcpy(x[i].address,"Cleared");

		}
		else if(j==4)
		{
			strcpy(x[i].disease,"Cleared");
		}
		else if(j==5)
		{
			x[i].age=0;
		}
		else if(j==6)
		{
			x[i].cabin=0;
		}
		else if(j==7)
		{
			x[i].phone=0;
		}

	}
	else
		printf("\n\nInvalid Serial number\n");

}
////////////////////////////////////////////////////////////////////////////////
void import()
{
	//importing from PatientRecords1024.txt
	FILE *fp = fopen("PatientRecords1024.txt","r");
	if(fp == NULL)
	{
		printf("\nPatients' Backup Not Found!");
		fp = fopen("PatientRecords1024.txt","w");
		printf("\nNew Patient's Backup File has been created.");
		fclose(fp);
	}
	patCount = fread(x, sizeof(struct Patient),100, fp);
	printf("\nPatient data imported successfully.");
	fclose(fp);


	//importing from User1024.txt
	FILE *fp2 = fopen("User1024.txt","r");
	if(fp2 == NULL)
	{
		printf("\nUser Backup Not Found!");
		fp2 = fopen("User1024.txt","w");
		printf("\nNew User Backup File has been created.");
		fclose(fp2);
	}
	userCount=fread(y, sizeof(struct User),5, fp2);
	printf("\nUser data imported successfully.");
	fclose(fp2);


	//importing from AdminDetails1024.txt
	FILE *fp3 = fopen("AdminDetails1024.txt","r");
	if(fp3 == NULL)
	{
		printf("\nAdmin Details' Backup Not Found!");
		fp3 = fopen("AdminDetails1024.txt","w");
		printf("\nNew Admin Detail's Backup File has been created.");
		fclose(fp3);
	}
	adminCount=fread(admin0, sizeof(struct Admin),1, fp3);
	printf("\nAdmin Records imported successfully.");
	fclose(fp3);
	
	//Decrypting all data
	
	for(int i=0;i<patCount;i++)
	{
		decrypt(x[i].name);
		decrypt(x[i].disease);
		decrypt(x[i].address);
		x[i].age=decryptInt(x[i].age);
		x[i].cabin=decryptInt(x[i].cabin);
		x[i].phone=decryptInt(x[i].phone);
	}
	
	for(int i=0;i<userCount;i++)
	{
		decrypt(y[i].password);
		decrypt(y[i].userName);
	}
	
	for(int i=0;i<adminCount;i++)
	{
		decrypt(admin0[i].adminKey);
		decrypt(admin0[i].hospAdrs);
		decrypt(admin0[i].hospName);
		admin0[i].hospContact=decryptInt(admin0[i].hospContact);
	}
	//DECRYPTION COMPLETED
}
void backup()
{
	//Encrypting all data
	
	for(int i=0;i<patCount;i++)
	{
		encrypt(x[i].name);
		encrypt(x[i].disease);
		encrypt(x[i].address);
		x[i].age=encryptInt(x[i].age);
		x[i].cabin=encryptInt(x[i].cabin);
		x[i].phone=encryptInt(x[i].phone);
	}
	
	for(int i=0;i<userCount;i++)
	{
		encrypt(y[i].password);
		encrypt(y[i].userName);
	}
	
	for(int i=0;i<adminCount;i++)
	{
		encrypt(admin0[i].adminKey);
		encrypt(admin0[i].hospAdrs);
		encrypt(admin0[i].hospName);
		admin0[i].hospContact=encryptInt(admin0[i].hospContact);
	}
	//ENCRYPTION COMPLETED
	
	//updating PatientRecords1024.txt
	FILE *fp = fopen("PatientRecords1024.txt","w");
	if(fp == NULL)
	{
		printf("/nPatient Records Backup File is empty!");
		exit(1);
	}
	fwrite(x, sizeof(struct Patient),patCount, fp);
	printf("\nPatient Records Backup File updated successfully.");
	fclose(fp);


	//updating User1024.txt
	FILE *fp2 = fopen("User1024.txt","w");
	if(fp2 == NULL)
	{
		printf("/nUser Backup File is empty!");
		exit(1);
	}
	fwrite(y, sizeof(struct User),userCount, fp2);
	printf("\nUser Backup File updated successfully.");
	fclose(fp2);

	//updating AdminDetails1024.txt
	FILE *fp3 = fopen("AdminDetails1024.txt","w");
	if(fp3 == NULL)
	{
		printf("/nAdmin Details Backup File is empty!");
		exit(1);
	}
	fwrite(admin0, sizeof(struct Admin),adminCount, fp3);
	printf("\nAdmin Details Backup File updated successfully.");
	fclose(fp3);
}
////////////////////////////////////////////////////////////////////////////////
void wait(int noSec)
{
	int f=0;
	clock_t start_wait;
	clock_t end_wait;

	start_wait = clock();
	end_wait = clock () + noSec * CLK_TCK ;

	printf("\nLoading.");

	while (clock() < end_wait)
	{
		if((clock()-start_wait)%400==0)
		{
			if(f!=(clock()-start_wait))
				printf(".");
			f=(clock()-start_wait);
		}
	}
}

void screenReset()
{
	system("cls");
	printf("\n--------------------------------------------------------");

	mytime=time(NULL);
	printf(ctime(&mytime));
	printf("\n\t\t\t***Welcome to %s Hospital***\n",admin0[0].hospName);

	if(activeUser!=-1&&isUser==1)
		printf("\nLogged in as : %s",y[activeUser].userName);
	else if(isAdmin==1)
		printf("\nLogged in as Admin");
	else
		printf("\nNot logged in!");

	printf("\n----------------------------------------------------------------------------------------------------------------------------------------------------------------");
}

void encrypt(char *S)
{
	/*
		Logic for encryption
		
		FOR STRING
		if alphabet, first, case is changed then considering the alphabets forming a circle, the opposite letter is chosen
		if digit, again, opposite digit is chosen, for ex, 0 replaced by 9, 1 replaced by 8
		Other symbols kept as it is
	*/
	int l=strlen(S);
	for(int i=0;i<l;i++)
	{
		if(S[i]>=65&&S[i]<=90)//UPPER CASE LETTERS
		{
			S[i]+=32;
			S[i]=122-(S[i]-97);
			
		}
		else if(S[i]>=97&&S[i]<=122)//LOWER CASE LETTERS
		{
			S[i]-=32;
			S[i]=90-(S[i]-65);
		}
		else if(S[i]>=48&&S[i]<=57)//DIGITS
		{
			S[i]=57-(S[i]-48);
		}
	}
}
////////////////////////////////////////////////////////////////////////////////
void decrypt(char *S)
{
	int l=strlen(S);
	for(int i=0;i<l;i++)
	{
		if(S[i]>=65&&S[i]<=90)//UPPER CASE LETTERS
		{
			S[i]+=32;
			S[i]=122-(S[i]-97);
			
		}
		else if(S[i]>=97&&S[i]<=122)//LOWER CASE LETTERS
		{
			S[i]-=32;
			S[i]=90-(S[i]-65);
		}
		else if(S[i]>=48&&S[i]<=57)//DIGITS
		{
			S[i]=57-(S[i]-48);
		}
	}
}
////////////////////////////////////////////////////////////////////////////////
int encryptInt(int a)
{
	int b=0;
	
	while(a!=0)
	{
		b=b*10+(9-a%10);
		a/=10;
	}
	
	a=0;		//for confirmation
	
	while(b!=0)
	{
		a=a*10+b%10;
		b/=10;
	}
	
	return a;
}
////////////////////////////////////////////////////////////////////////////////
int decryptInt(int a)
{
	int b=0;
	
	while(a!=0)
	{
		b=b*10+(9-a%10);
		a/=10;
	}
	
	a=0;		//for confirmation
	
	while(b!=0)
	{
		a=a*10+b%10;
		b/=10;
	}
	
	return a;
}
////////////////////////////////////////////////////////////////////////////////
void addUser()
{
	wait(1);
	screenReset();
	printf("\nADD USER:");

	int f1,f2;	//f1=account created?	f2=username already exists?
	char uName[30],uPass[30];
	int count=0;	//counts no of attempts
	printf("\nNo of Users already in the database = %d",userCount);

	f1=0;
	while(f1!=1&&count<3)
	{
		f2=0;
		fflush(stdin);
		printf("\nEnter new username = ");
		gets(uName);
		fflush(stdin);

		printf("\nEnter new password =");
		gets(uPass);
		fflush(stdin);

		count++;

		for(i=0; i<userCount; i++)
		{
			if(strcmp(y[i].userName,uName)==0)
			{
				f2=1;
				break;
			}
		}
		if(f2==1&&count!=3)
		{
			printf("\nUsername already exists! Try a different username.");
		}
		else if(count!=3)
		{
			strcpy(y[userCount].userName,uName);
			strcpy(y[userCount].password,uPass);
			userCount++;
			f1=1;

			printf("\nUser added successfully.");
			printf("\nNo of Users now = %d",userCount);
			wait(3);
		}
	}

	if(f1!=1)
	{
		printf("Too many unsuccessful attempts!\n");
		wait(2);
	}


//	backup();
//	import();
}

void viewUsers()
{
	//char useless[1];
	wait(1);
	screenReset();
	printf("\nVIEW USER LIST:");

	if(userCount!=0&&isAdmin==1)
	{
		printf("\n--------------------");
		for(i=0; i<userCount; i++)
		{
			printf("\n");
			printf("%d",i);
			printf("\t");
			puts(y[i].userName);
		}
		printf("--------------------");
		printf("\nEnter any no to continue = ");
		fflush(stdin);
		//gets(useless);
		int useless;
		scanf("%d",&useless);
		fflush(stdin);
	}
	else if(isAdmin==1)
	{
		printf("\nNo Users found!");
	}
	else
	{
		printf("\nUNAUTHORISED ACCESS DETECTED!");
		isAdmin=0;
	}
}

void delUsers()
{
	printf("\nNOT DESIGNED YET");

	char check[30];

	wait(1);
	screenReset();
	printf("\nREMOVE USERS:");

	int f=-1;
	if(userCount!=0&&isAdmin==1)
	{
		while(f!=0)
		{
			printf("\nEnter Index No. of user to remove(0 to go back, -1 to show User list) = ");
			scanf("%d",&f);
			if(f>0)
			{

				i=f;
				strcpy(check,y[i].userName);

				while(i<userCount)
				{
					strcpy(y[i].userName,y[i+1].userName);
					strcpy(y[i].password,y[i+1].password);
					i++;
				}
				if(f-1<activeUser)
					activeUser--;
				userCount--;

				printf("\nUser No. %d(%s) removed successfully.",f,check);
				printf("\nNo of users now = %d",userCount);
			}
			else if(f==-1)
			{
				viewUsers();
			}
			else if(f!=0)
			{
				printf("\nINVALID INPUT! TRY AGAIN!");
			}
		}
	}
	else if(isAdmin==1)
	{
		system("cls");
		printf("\n No Users found!");
	}
	else
	{
		printf("\nUNAUTHORISED ACCESS DETECTED");
		isAdmin=0;
	}
}


void removeSelf()
{
	wait(1);
	screenReset();
	printf("\nREMOVE SELF(USER):");

	int f=0;
	if(userCount!=0)
	{
		printf("\nYou are going to remove yourself.\nYou will no longer be able to access the application.\nAre you sure?(1 or 0) = ");
		scanf("%d",&f);
		if(f==1)
		{

			i=activeUser;
			while(i<userCount)
			{
				strcpy(y[i].userName,y[i+1].userName);
				strcpy(y[i].password,y[i+1].password);
				i++;
			}
			if(in1<activeUser)
				activeUser--;
			userCount--;

			printf("\nUser removed successfully.");
			printf("\nNo of users now = %d",userCount);

			if(in1==activeUser)
			{
				printf("\nSince you have removed yourself from the User List, the application will be terminated.");
				isUser=0;
			}
		}
	}
	else
	{
		system("cls");
		printf("\n No Users found!\nUnauthorized access detected...");
		isUser=0;
	}

}

void editSelf()
{
	wait(1);
	screenReset();
	if(isUser==1)
	{
		printf("\nEDIT USERNAME AND PASSWORD:");

		int f1=0,f2=1;
		char check[30];

		printf("\nChange username?(1 or 0)");
		scanf("%d",&f1);
		if(f1==1)
		{
			printf("\nEnter new username = ");
			//scanf("%s",&check);
			gets(check);

			//checking if username already exists
			for(i=0; i<userCount; i++)
			{
				if(i!=activeUser)
					if(strcmp(y[i].userName,check)==0)
					{
						f2=1;
						break;
					}
			}
			if(f2!=1)
				strcpy(y[activeUser].userName,check);
			else
				printf("\nUSERNAME ALREADY EXISTS!");
		}
		else
		{
			printf("\nUsername unchanged.");
		}

		f1=0;
		printf("\nChange password?(1 or 0)");
		scanf("%d",&f1);
		if(f1==1)
		{
			printf("\nOkay, but first enter your current password_");
			scanf("%s",check);
			if(strcmp(check,y[activeUser].password)==0)
			{
				printf("\nEnter new password = ");
				//scanf("%s",&check);
				gets(check);
				strcpy(y[activeUser].password,check);
			}
			else
			{
				printf("\nCURRENT PASSWORD ENTERED IS INCORRECT!");
			}
		}
		else
		{
			printf("\nPassword unchanged.");
		}
	}

	else
	{
		printf("UNAUTHORISED ACCESS DETECTED!");
		isUser=0;
	}
}
////////////////////////////////////////////////////////////////////////////////
void editAdmin()
{
	if(isAdmin==1)
	{
		int f1=1,f2=1,f3=1,f9=0;
		char check[30];
		int checkN;

		wait(1);
		screenReset();
		printf("\nEDIT HOSPITAL DETAILS(ADMIN):");

		if(adminCount!=1)
			f9=1;

		if(f9==0)
		{
			printf("\nChange Hospital Name?(1 or 0)");
			scanf("%d",&f1);
		}
		if(f1==1)
		{
			printf("\nEnter new hospital name = ");
			//scanf("%s",&check);
			gets(check);
			strcpy(admin0[0].hospName,check);
		}
		else
		{
			printf("\nHospital Name unchanged.");
		}

		if(f9==0)
		{
			printf("\nChange Hospital Address?(1 or 0)");
			scanf("%d",&f2);
		}
		if(f2==1)
		{
			printf("\nEnter new hospital name = ");
			//scanf("%s",&check);
			gets(check);
			strcpy(admin0[0].hospAdrs,check);
		}
		else
		{
			printf("\nHospital Address unchanged.");
		}

		if(f9==0)
		{
			printf("\nChange Hospital Contact?(1 or 0)");
			scanf("%d",&f3);
		}
		if(f3==1)
		{
			printf("\nEnter new hospital contact = ");
			//scanf("%s",&check);
			scanf("%d",&checkN);
			admin0[0].hospContact=checkN;
		}
		else
		{
			printf("\nHospital Name unchanged.");
		}
	}

	else
	{
		printf("UNAUTHORISED ACCESS DETECTED!");
		isAdmin=0;
	}
}

void changeKey()
{
	if(isAdmin==1)
	{
		char check[30];

		wait(1);
		screenReset();
		printf("\nCHANGE ADMIN KEY:");

		printf("\nFirst, lets verify if its really you, please enter your present key = ");
		gets(check);

		if(strcmp(check,admin0[0].adminKey)==0)
		{
			printf("\nEnter new key = ");
			gets(check);
			strcpy(admin0[0].adminKey,check);
			printf("\nADMIN KEY UPDATED SUCCESSFULLY!");
		}
		else
		{
			printf("\nWRONG ADMIN KEY ENTERED!UNABLE TO CHANGE KEY!\nTRY A FEW MOMENTS LATER.");
		}

	}

	else
	{
		printf("\nUNATHORISED ACCESS DETECTED!");
		isAdmin=0;
	}
	wait(3);
}

void viewAdmin()
{
	int checkN;

	if(isAdmin==1)
	{
		printf("\nVIEW ADMIN DETAILS");
		printf("\nHospital Name : %s",admin0[0].hospName);
		printf("\nAddress : %s",admin0[0].hospAdrs);
		printf("\nContact : %d",admin0[0].hospContact);
		printf("\nEnter any no to continue = ");
		scanf("%d",&checkN);
	}
	else
	{
		printf("\nUNAUTHORISED ACCESS DETECTED!");
		isAdmin=0;
	}
	printf("\n");
}

void addAdmin()
{
	char check[30];
	char keyIn[6];
	int checkN;

	wait(1);
	screenReset();
	printf("\nEDIT HOSPITAL DETAILS(ADMIN):");

	printf("\nEnter Hospital Name = ");
	//scanf("%s",&check);
	fflush(stdin);
	gets(check);
	strcpy(admin0[0].hospName,check);


	printf("\nEnter Hospital Address = ");
	//scanf("%s",&check);
	fflush(stdin);
	gets(check);
	strcpy(admin0[0].hospAdrs,check);


	printf("\nEnter Contact No. = ");
	//scanf("%s",&check);
	scanf("%d",&checkN);
	admin0[0].hospContact=checkN;

	printf("\nEnter Admin Key(exactly 6 lettered) = ");
	//scanf("%s",&check);
	fflush(stdin);
	gets(keyIn);
	strcpy(admin0[0].adminKey,keyIn);

	isAdmin=1;
	adminCount=1;
	printf("\nADMIN DETAILS ADDED SUCCESSFULLY!");
}
//END OF PROGRAM
