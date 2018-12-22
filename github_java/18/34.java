/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package sort.methods;

/**
 *
 * @author LeopardProMK
 */
public class Selectionsort {
private static int tablica[];
private static int ile_liczb;
 
private static void selectionsort(double tablica[], int ile_liczb) {
    int min,i,j;
    double temp;
    for (i=0;i<ile_liczb-1;i++)  {
    min=i;
    for (j=i+1;j<ile_liczb;j++)
    if (tablica[j]<tablica[min])
    min=j;
    temp=tablica[min];
    tablica[min]=tablica[i];
    tablica[i]=temp;
    }
}
}
