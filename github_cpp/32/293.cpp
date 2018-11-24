// Compile with new compiler: g++ -std=c++14  or g++ -std=c++11

#include<bits/stdc++.h>
#include <GL/glut.h>
#include<unistd.h>

using namespace std;

struct lis
{
  int data,distance,par;
  lis *next;
};

struct edge
{
	int e1,e2,weight;
};
class vertex
{
	public:
	int data,distance,color,x,y,parent;
};

vertex V[20];

lis *adj[20], *makev[20], *node, *temp;

edge e_sort[20],A[20],stemp;

int N,E;

int Asize=0;  //Counter for Non-cyclic edge list A
int esize=0;  //Counter for total number of edges

int flag=0;

string str;
GLvoid *font_style = GLUT_BITMAP_HELVETICA_18;

void display();

void drawstr(GLuint x, GLuint y, const char* format, int length)
{
  glRasterPos2i(x, y);  
  for(int i=0; i<length; ++i)
  {
    glutBitmapCharacter(font_style, *(format+i) );
  }
}

void drawCircle(double a,int x,int y)
{
    glLoadIdentity();
    glColor3f(a,a,a);
    glTranslatef(x,y,-1);
    glutSolidSphere(30,100,100);
    glTranslatef(-x-5,-y-5,0);
    glColor3f(0.8,0.4,0.3);
    drawstr(x,y, str.c_str(), str.length());
}

void connectGraph(int a,int b)
{
  glLoadIdentity();
  int found=0;
  for(int i=0;i<Asize;i++)
  {
  	if((A[i].e1==a+1)&&(A[i].e2==b+1))
  	{	
      found=1;
      break;
     }
   }
  if(found==1) 
   glColor3f(0,1,0);            //Non Cyclic edges are coloured green
  else
   glColor3f(0,0,0);            //Cyclic edges are coloured black
  glBegin(GL_LINES);
   glVertex3f(V[a].x,V[a].y,-80);
   glVertex3f(V[b].x,V[b].y,-80);
  glEnd();

}

void union_set(int u,int v)      //Union is to merge two disjoint sets u and v with unique elements 
{
     	 lis *utemp1,*vtemp1,*tempnode,*tempnode1;
  	 utemp1=makev[u-1];
	 vtemp1=makev[v-1];
	 lis *node,*node1;
	 node=makev[vtemp1->data-1];
	 while(node!=NULL)
	 {
		tempnode=new lis;
		tempnode->data=node->data;
		tempnode->next=NULL;
		while(utemp1->next!=NULL)
		   utemp1=utemp1->next;
		utemp1->next=tempnode;
		node=node->next;
	 }
   	 utemp1=makev[u-1];
	 vtemp1=makev[v-1];
	 node1=makev[utemp1->data-1];
   	 while(node1!=NULL)
	  {
		 tempnode1=new lis;
		 tempnode1->data=node1->data;
		 tempnode1->next=NULL;
		 while(vtemp1->next!=NULL) 
		    vtemp1=vtemp1->next;
		 vtemp1->next=tempnode1;
		 node1=node1->next;
	  }
}

int find_set(int u,int v)     //Find is to check if two sets u and v are disjoint and unique
{
	int found=0;
	lis *utemp,*vtemp;
	utemp=makev[u-1];
	vtemp=makev[v-1];
	while(utemp!=NULL)
	{
         while(vtemp!=NULL)
          {
       	   if(utemp->data==vtemp->data)
       		found=1;
       	    vtemp=vtemp->next;
           }
         utemp=utemp->next;
         vtemp=makev[v-1];
        }
   if(found==1)
     return 0;
   else
     return 1;
}

void Kruskal()
{

  for(int i=0;i<esize;i++)                       // Sort of edges by non-decreasing weight
  { 
    for(int j=i+1;j<esize;j++)
     {
       if(e_sort[i].weight>e_sort[j].weight)
           {
               stemp=e_sort[i];
               e_sort[i]=e_sort[j];
               e_sort[j]=stemp;
            }
       }
  }

	 for(int i=0;i<esize;i++)
  	   {
  	   	if(find_set(e_sort[i].e1,e_sort[i].e2)==1)       //If find(u)!=find(v) then Union(u,v) and add (u,v) to A
  	   		 {
                 union_set(e_sort[i].e1,e_sort[i].e2);
                 A[Asize++]=e_sort[i];
                 display();
                 sleep(2);
  	   		 }
  	   }
  	 cout<<"\nNon Cyclic Edges: \n";
  	    for(int i=0;i<Asize;i++)
  	    	cout<<A[i].e1<<'\t'<<A[i].e2<<'\n';
}
void display()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.4f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for(int i=0;i<N;i++)
    {
    	str=std::to_string(V[i].data);
    	drawCircle(V[i].color,V[i].x,V[i].y);
    }

    for(int i=0;i<N;i++)
    {
        temp=adj[i]->next;
        while(temp!=NULL)
        {
            connectGraph(i,temp->data-1);
            temp=temp->next;
        }
    }
    
    glutSwapBuffers();
    
    if(flag==0)     // Needs to be called only once.
     {
       flag=1;	     
       display();
       sleep(2);	     
       Kruskal();
     }
}

void handleResize(int w, int h)
{
    glMatrixMode(GL_PROJECTION);   // Transformations being applied to Projection Matrix
    glLoadIdentity();   // Always call after changing matrix
    glViewport(0,0,w,h);
    glOrtho(0,w,0,h,1,200); // Here clipping range is zNear=1,zFar=-200
    glMatrixMode(GL_MODELVIEW); // Transformations on ModelView Matrix(default)
}


int main(int argc,char *argv[])
{
    int dis,j,posx,posy,e1,e2;

    cout<<"Enter the no of vertices: ";
    cin>>N;
    
   for(int i=0;i<N;i++)
    { 
      V[i].data=i+1;
      V[i].color=1;
      cout<<"\nEnter the co-ordinates of vertes "<<i+1<<" : ";
      cin>>V[i].x>>V[i].y;
      adj[i]=new lis;
      makev[i]=new lis;
      adj[i]->data=0;
      adj[i]->next=NULL;
      makev[i]->data=i+1;
      makev[i]->next=NULL;
      cout<<"\nEnter the vertex "<<i+1<<" is linked to: ";
      cin>>j;
      if(j!=0)
      {
        temp=adj[i];
        while(j!=0)
         {
          node=new lis;
          node->data=j;
          node->next=NULL;
          if(j!=0)
          {
          	cout<<"\nEnter the weight of edge("<<i+1<<','<<j<<") :";
          	cin>>dis;
          }
          node->distance=dis;
          e_sort[esize].e1=i+1;
          e_sort[esize].e2=j;
          e_sort[esize++].weight=dis;
          cout<<"\nEnter the vertex "<<i+1<<" is linked to: ";
          cin>>j;
          temp->next=node;
          temp=temp->next;
         }
       }
     }
 
   
   cout<<"\nAdjacency List: \n";
   for(int i=0;i<N;i++)
  	{
		 cout<<"\n";
		 temp=adj[i]->next;
		 while(temp!=NULL)
		 {
			cout<<temp->data<<" ";
			temp=temp->next;
		 }
		 cout<<"\n";
	  }
 
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
 glutInitWindowSize(700, 700);
 glutInitWindowPosition(100, 100);
 glutCreateWindow("Kruskal's Algorithm");
 glutDisplayFunc(display);
 glutReshapeFunc(handleResize);
 glutMainLoop();


}
