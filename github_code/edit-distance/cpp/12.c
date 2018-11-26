/*
* Plik levenshteindistance.cpp zawiera
* definicje funkcji uzytych w programie
*/

//#include "stdafx.h"
#include "levenshteindistance.h"
int levenshtein(int **dist, int w, int k, string s1, string s2)
{
	int t, l, d;
	// Wypelnianie pierwszej kolumny/wiersza od 0 do len1+1/len2+1
	for (int i = 0; i < w + 1; i++)
		dist[i][0] = i;
	for (int i = 1; i < k + 1; i++)
		dist[0][i] = i;

	// Obliczanie odleglosci Levenshteina, uzupelnianie macierzy kosztow
	for (int i = 1; i <= w; i++)
		for (int j = 1; j <= k; j++)
		{
			if (s1[i - 1] == s2[j - 1])
			{
				dist[i][j] = dist[i - 1][j - 1];
			}
			else
			{
				t = dist[i - 1][j]; // top
				l = dist[i][j - 1]; // left
				d = dist[i - 1][j - 1]; // diagonal
				dist[i][j] = min(t, l, d) + 1;
			}
		}

	return dist[w - 1][k - 1];
}

void show_matrix(int **dist, int w, int k, string s1, string s2)
{
	// Wypisywanie macierzy kosztow
	printf("\n\n%5.c", 32); // odstêp miêdzy krawêdzi¹ a liter¹ pierwszego s³owa [s2](w poziomie)
	for (int i = 0; i <= k; i++)
		printf("%4.c", s2[i]);
	for (int i = 0; i <= w; i++)
	{
		printf("\n\n");
		if (i == 0) printf(" ");
		else printf("%c", s1[i - 1]);
		for (int j = 0; j <= k; j++)
			printf("%4.1d", dist[i][j]);
	}
}

void edits(int **dist, int w, int k, string s1, string s2) // s1 = asdfgh, s2 = asdgh
{// Przekszta³canie s³owa pierwszego (s1) na s³owo drugie (s2)
	char *_s1 = NULL;
	int len1 = s1.length(), len2 = s2.length(), len_s1 = s1.length(), tmp, i, j;
	_s1 = (char*)malloc((len_s1 + 1) * sizeof(char));
	for (int i = 0; i <= len_s1; i++) _s1[i] = s1[i];
	cout << "\n\nTrzeba wykonac " << dist[len1][len2] << " operacji na ciagu " << s1
		<< "\n aby przeksztalcic go na " << s2 << "\n\n";

	i = len1; // Liczba wierszy
	j = len2; // Liczba kolumn
	while (i && j)
	{	if (s1[i - 1] == s2[j - 1])
		{	i--; j--;
		}else
		{	tmp = dist[i][j] - 1;
			if (dist[i-1][j] == tmp) // DELETE JEŚLI DO GÓRY
			{	i--;
				cout << "Usun '" << s1[i] << "' na pozycji " << i + 1 << endl;
				cout << _s1 << " -> ";
				for (int k = i; k < len_s1; k++)	_s1[k] = _s1[k + 1];
				_s1[len_s1] = '\0';
				len_s1--;
				cout << _s1 << endl << endl;
			}
			else if (dist[i - 1][j - 1] == tmp)
			{	i--; j--;
				cout << "Zamien '" << s1[i] << "' na pozycji " << i + 1 << " na '" << s2[j] << "'" << endl;
				cout << _s1 << " -> ";
				_s1[i] = s2[j];
				cout << _s1 << endl << endl;
			}else
			{	j--;
				cout << "Dodaj '" << s2[j] << "' na pozycji " << i + 1 << endl;
				cout << _s1 << " -> ";
				len_s1++;
				realloc(_s1, (len_s1 + 1) * sizeof(char));
				for (int k = len_s1; k > i; k--)	_s1[k] = _s1[k - 1];
				_s1[i] = s2[j];
				cout << _s1 << endl << endl;
			}
		}
	}
	if (j>0)
	{	for (int _j = 0; _j < j; _j++)
		{	cout << "Dodaj '" << s2[_j] << "' na pozycji " << _j + 1 << endl;
			cout << _s1 << " -> ";
			len_s1++;
			realloc(_s1, (len_s1 + 1) * sizeof(char));
			for (int k = len_s1; k>_j; k--) _s1[k] = _s1[k - 1];
			_s1[_j] = s2[_j];
			cout << _s1 << endl << endl;
		}
	}else if (i>0)
	{	for (int _i = 0; _i < i; _i++)
		{	cout << "Usun '" << s1[_i] << "' na pozycji " << _i + 1 << endl;
			cout << _s1 << " -> ";
			for (int k = _i;k < len_s1; k++) _s1[k] = _s1[k + 1];
			_s1[len_s1] = '\0';
			len_s1--;
			cout << _s1 << endl << endl;
		}
	}
	free(_s1);
	_s1 = NULL;
}

int min(int a, int b, int c)
{
	int t[] = { a,b,c }, tmp;
	for (int i = 1; i < 3; i++)
		for (int j = 0; j < 3 - i; j++)
			if (t[i] < t[j])
			{
				tmp = t[i];
				t[i] = t[j];
				t[j] = tmp;
			}
	return t[0];
}
