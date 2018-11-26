#include <iostream>

using namespace std;

void multiply(int a[10][10], int b[10][10], int c[10][10], int m, int n, int p, int q, int row, int col)
{
  if(n != p)
  {
    return;
  }

  row = m;
  col = q;
 int sum;

 for(int x = 0; x < m; x++)
 {
   for(int y = 0; y < q; y++)
   {
     sum = 0;

     for(int j = 0, i = 0; j < n && i < p; j++, i++)
     {
       sum += a[x][j] * b[i][y];
     }

     c[x][y] = sum;
   }
 }
}
void print(int m[10][10], int rows, int cols)
{
  for(int i = 0; i < rows; i++)
  {
    for(int j = 0; j < cols; j++)
    {
      cout << m[i][j] << "\t";
    }
    cout << endl;
  }
}
void input(int m[10][10], int &rows, int &cols)
{
  cout << "Enter rows : ";  cin >> rows;
  cout << "Enter columns : ";  cin >> cols;

  for(int i = 0; i < rows; i++)
  {
    for(int j = 0; j < cols; j++)
    {
      cin >> m[i][j];
    }
  }
}

int main()
{
  int a[10][10], b[10][10], c[10][10];
   int m, n, p, q, x, y;

   cout << "Enter a : " << endl;
   input(a, m, n);
   cout << "Enter b : " << endl;
   input(b, p, q);


   multiply(a, b, c, m, n, p, q, x, y);

   cout << "Result : " << endl;
   print(c, x, y);

 return 0;
}
