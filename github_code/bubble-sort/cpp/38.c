/*
 * This program computes averages.
 *
 * Author:  Bogdan DUMITRIU
 * Version: 1.0
 * Date:    28.10.2001
 */

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <math.h>

int avg(int *vector)
{
	long sum = 0;

	for (int i = 0; i < 10; i++)
	{
		sum += vector[i];
	}

	return floor(sum/10);
}

void main()
{
	FILE *f[8], *g1, *g2;
	int file_idx;
	char name[10], idx[2];
	int nr, atribs[10], comps[10];

	strcpy(name, "efic .dat");
	for (int i = 1; i <= 7; i++)
	{
		itoa(i, idx, 10);
		name[4] = idx[0];
		if ((f[i] = fopen(name, "r")) == NULL)
		{
			printf("Could not open file: %s", name);
			getch();
			exit(1);
		}
	}

	if ((g1 = fopen("comp_med.dat", "w")) == NULL)
	{
		printf("Could not open file: comp_med.dat", name);
		getch();
		exit(1);
	}

	if ((g2 = fopen("atrb_med.dat", "w")) == NULL)
	{
		printf("Could not open file: atrb_med.dat", name);
		getch();
		exit(1);
	}

	fprintf(g1, "insertie-directa insertie-binara selectie quicksort");
	fprintf(g1, " interclasare bubble-sort heapsort ");
	fprintf(g1, "Grafic-comparatii-mediu\n");
	fprintf(g2, "insertie-directa insertie-binara selectie quicksort");
	fprintf(g2, " interclasare bubble-sort heapsort ");
	fprintf(g2, "Grafic-atribuiri-mediu\n");
	while (!feof(f[1]))
	{
		for (int i = 1; i <= 7; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				fscanf(f[i], "%d", &nr);
				fscanf(f[i], "%d", &comps[j]);
				fscanf(f[i], "%d", &atribs[j]);
			}
			if (i == 1)
			{
				fprintf(g1, "%d\n", nr);
				fprintf(g2, "%d\n", nr);
			}
			if (i != 7)
			{
				fprintf(g1, "%d ", avg(comps));
				fprintf(g2, "%d ", avg(atribs));
			}
			else
			{
				fprintf(g1, "%d", avg(comps));
				fprintf(g2, "%d", avg(atribs));
				if (!feof(f[1]))
				{
					fprintf(g1, "\n");
					fprintf(g2, "\n");
				}
			}
		}
	}

	fclose(g1);
	fclose(g2);
	for (i = 1; i <= 7; i++)
	{
		fclose(f[i]);
	}
}