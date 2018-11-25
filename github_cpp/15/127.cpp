

#include <GL/glut.h>
using namespace std;

GLdouble mModel[16];
float rotaX=0.0;
float rotaY=0.0;
float rotaZ=0.0;

double *A=new double[4];
double *B=new double[4];
double *C=new double[4];

double **Transform=new double*[4];
double **Traslate=new double*[4];



double * MatrixMultiplication(double **mat,int sizeMat ,double *vec,int sizeVec)
{
	double *value=new double[sizeVec];
	
	for(int i=0; i< sizeMat ;i++)
		for(int j=0;j< sizeMat ;j++)
		value[i]+= mat[i][j]*vec[j];
	
	return value;
}


void setPixel(double *points)
{	
	
	glPointSize(3);
	glColor3f (1,1,1); 
	glBegin(GL_POINTS);
	glVertex3dv(points);
	glEnd();
}


void XYZ(void)
{
	glLineWidth(1);
	glBegin (GL_LINES);
	glColor3f (1,0,0); 
	glVertex3f(-10,0,0);
	glVertex3f(10,0,0 ); 
	
	glColor3f (0,1,0); 
	glVertex3f(0,0,0);
	glVertex3f(0,10,0);
	
	glColor3f (0,0,1); 
	glVertex3f(0,0,-10);
	glVertex3f(0,0,10 ); 
	glEnd();
	glLineWidth(1);
}


void shape(double *A,double *B, double *C,int indice)
{
	glLineWidth(1);
	glColor3f (0,indice,1); 
	glBegin (GL_LINES);
	glVertex3dv(A);
	glVertex3dv(B); 
	
	glVertex3dv(B);
	glVertex3dv(C);
	glEnd();
	
	setPixel(A);
	setPixel(B);
	setPixel(C);
}


void show()
{
	glPushMatrix();
	glRotatef( rotaX, 1.0, 0.0, 0.0 );
	glRotatef( rotaY, 0.0, 1.0, 0.0 );
	glRotatef( rotaZ, 0.0, 0.0, 1.0 );
	
	
	glClear(GL_COLOR_BUFFER_BIT);
	XYZ();
	
	
	shape(A,B,C,5);
	
	
	double *Aprima = MatrixMultiplication(Traslate,4,A,4);
	double *Bprima = MatrixMultiplication(Traslate,4,B,4);
	double *Cprima = MatrixMultiplication(Traslate,4,C,4);
	
	
	double *tranA = MatrixMultiplication(Transform,4,Aprima,4);
	double *tranB = MatrixMultiplication(Transform,4,Bprima,4);
	double *tranC =	MatrixMultiplication(Transform,4,Cprima,4);
	
	
	shape( tranA,tranB,tranC,1);
	
	glPopMatrix();	
	glFlush();
	
}

void reshape(int width, int height) 
{
	
	glGetDoublev (GL_MODELVIEW_MATRIX, mModel);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)height / (GLfloat)width, 1.6, 128.0);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}



int main(int argc, char** argv)
{
	
	A[0]=-1.;	A[1]=2.;	A[2]=3.;	A[3]=1.;
	B[0]=1.;	B[1]=1.; 	B[2]=1.;	B[3]=1.;
	C[0]=3.;	C[1]=2.;	C[2]=1.;	C[3]=1.;
	
	
	for(int i=0;i<4;i++)
	{
		Transform[i] = new double[4];
		Traslate[i] = new double[4];
	}
	
	
	Transform[0][0]=-2./3.;	Transform[0][1]=1./3.;	Transform[0][2]=2./3.;	Transform[0][3]=0.;
	Transform[1][0]=2./3.;	Transform[1][1]=2./3.; 	Transform[1][2]=1./3.;	Transform[1][3]=0.;
	Transform[2][0]=-1./3.;	Transform[2][1]=2./3.;	Transform[2][2]=-2./3.;	Transform[2][3]=0.;
	Transform[3][0]=0.;		Transform[3][1]=0.;		Transform[3][2]=0.;		Transform[3][3]=1.;
	
	
	Traslate[0][0]=1.;	Traslate[0][1]=0.;	Traslate[0][2]=0.;	Traslate[0][3]=-1.;
	Traslate[1][0]=0.;	Traslate[1][1]=1.;	Traslate[1][2]=0.;	Traslate[1][3]=-1.;
	Traslate[2][0]=0.;	Traslate[2][1]=0.;	Traslate[2][2]=1.;	Traslate[2][3]=-1.;
	Traslate[3][0]=0.;	Traslate[3][1]=0.;	Traslate[3][2]=0.;	Traslate[3][3]=1.;
	
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(330,100);
	glutInitWindowSize(400,400);
	glutCreateWindow("Proyeccion Ortogonal");
	glMatrixMode(GL_PROJECTION);
	glutDisplayFunc(show);
	glutReshapeFunc(reshape);
	glutMainLoop();
	
	return 0;
}
