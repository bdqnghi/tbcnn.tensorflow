import java.io.*;
class Tower
{

void towerOfHanoi(int n, char fromrod, char torod, char auxrod)
{
    if (n == 1)
    {
        System.out.println("\n Move disk 1 from rod %c to rod %c", fromrod, torod);
        return;
    }
    towerOfHanoi(n-1, fromrod, auxrod, torod);
    Syatem.out.println("Move disk %d from rod %c to rod %c", n, fromrod, torod);
    towerOfHanoi(n-1, auxrod, torod, fromrod);
}}

class Hanoy{
public static void main(String args[])
{
Hanoy h=new Hanoy();
h.towerOfHanoi(5, 'A', 'C', 'B'); 
}}
