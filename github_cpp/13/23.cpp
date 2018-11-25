

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <math.h>

void main()
{
	FILE *f[5], *g1, *g2;
	int file_idx;
	char name[10], idx[2];
	int nr, atribs, comps;

	strcpy(name, "efic .dat");
	for (int i = 1; i <= 4; i++)
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

	if ((g1 = fopen("comp_fav.dat", "w")) == NULL)
	{
		printf("Could not open file: comp_med.dat", name);
		getch();
		exit(1);
	}

	if ((g2 = fopen("atrb_fav.dat", "w")) == NULL)
	{
		printf("Could not open file: atrb_med.dat", name);
		getch();
		exit(1);
	}

	fprintf(g1, "insertie-directa insertie-binara selectie");
	fprintf(g1, " bubble-sort ");
	fprintf(g1, "Grafic-comparatii-favorabil\n");
	fprintf(g2, "insertie-directa insertie-binara selectie");
	fprintf(g2, " bubble-sort ");
	fprintf(g2, "Grafic-atribuiri-favorabil\n");
	while (!feof(f[1]))
	{
		for (int i = 1; i <= 4; i++)
		{
			fscanf(f[i], "%d", &nr);
			fscanf(f[i], "%d", &comps);
			fscanf(f[i], "%d", &atribs);
			if (i == 1)
			{
				fprintf(g1, "%d\n", nr);
				fprintf(g2, "%d\n", nr);
			}
			if (i != 4)
			{
				fprintf(g1, "%d ", comps);
				fprintf(g2, "%d ", atribs);
			}
			else
			{
				fprintf(g1, "%d", comps);
				fprintf(g2, "%d", atribs);
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
	for (i = 1; i <= 4; i++)
	{
		fclose(f[i]);
	}
}