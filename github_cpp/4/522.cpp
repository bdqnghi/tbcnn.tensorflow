#include<jay.h>

class student
{
	char usn[10],name[10],sem[10],dept[10];

	public:
		void read();
		void search(char *usn);
		int hash(char *usn1);
		void pack();

};

fstream fd,fd1;

void student::read()
{
	cout<<"\n\nDetails\n";
	cin>>usn>>name>>sem>>dept;
     
}

void make()
{
     fd.open("file.txt",ios::out);
     if(!fd) { cout<<"\nerror in opening file!";
     exit(1);
     }
     char j='/';
     char k='!';
     for(int i=1;i<=1000;i++)
     {	  if(i%50==0) fd<<k;
	  else
	  fd<<j;
     }
	fd.close();
     return;
}

int student::hash(char *usn1)
{
	char ch1=usn1[0];
	char ch2=usn1[1];
	char ch=ch1+ch2;
	return ((ch%19)*50);
}

void student::pack()
{
	int pos;
	read();
	pos=hash(usn);
	char ch;

	fd.open("file.txt",ios::in|ios::out);
	fd1.open("x.txt",ios::app);
	fd.seekp(0,ios::beg);
	fd.seekp(pos-1,ios::beg);

	while(fd)
	{
		fd.get(ch);
		if(ch=='!')
		break;
		else
		{
		pos=pos+1;
		fd.seekp(pos,ios::beg);
		}
	}
	fd.seekp(pos-1,ios::beg);
	char buf[100];
	strcpy(buf,usn);
	strcat(buf,"|");
	strcat(buf,name);
	strcat(buf,"|");
	strcat(buf,sem);
	strcat(buf,"|");
	strcat(buf,dept);
	int x=strlen(buf);
	for(int i=x;i<49;i++)
	strcat(buf,"*");
	strcat(buf,"#");
	fd<<buf;
	strcpy(buf,usn);
	strcat(buf,"|");
	fd1<<buf;
	fd1.close();
	fd1.open("x.txt",ios::app);
	fd1<<pos;
	fd1.close();
	fd1.open("x.txt",ios::app);
	strcpy(buf,"#");
	fd1<<buf;
	fd.close();
	fd1.close();

}

void student::search(char *usn)
{

	fd.open("file.txt",ios::in);
	fd1.open("x.txt",ios::in);
	   char buf[100],buf1[100],buf2[100];
	   char buff[100],bufx[100];
	while(fd1)
	{
		fd1.getline(buf,10,'#');
		strcpy(buf1,buf);
		char *ptr=strtok(buf1,"|");
		char *ptr1=strtok(NULL,"#");
		if(strcmp(ptr,usn)==0)
		{
			cout<<"\n\nKey found\n\n";
			int pos=atoi(ptr1);
			fd.seekg(pos-1,ios::beg);
			fd.getline(bufx,100,'#');
			strtok(bufx,"*");
			cout<<bufx;

			fd1.close();fd.close();
			return;
		}
	}
	fd1.close();fd.close();
	cout<<"\n\nNo key";
}

int main()
{
	int ch,i;
	clrscr();
		student s;
		char key[100];
	for(;;)
	{

		cout<<"\n\n1.Pack\n2.Search\n3.exit\n\n";
		cin>>ch;
		switch(ch)
		{
			case 1:s.pack();
				break;
			case 2:cout<<"\n\nKey:";
				cin>>key;
				s.search(key);
				break;
			case 3:exit(0);

			case 4:make();
				break;

			case 9:remove("file.txt");
				remove("x.txt");
				break;
			
			}
	}
}