#include <vector>
#include <iostream>
#include "lexicon.h"



class Levenshtein{

private:
	int _height;
	int _width;
	
	std::vector<unsigned int>* reference; //braucht man noch für die Printfunktion
	std::vector<unsigned int>* guess;

	int min(int i, int j);
	void back(int& i, int& j, Lexicon* elex); //führt einen Schritt in der print-Methode aus


public:
	unsigned int* data;
	unsigned int** matrix;
	
	Levenshtein(std::vector<unsigned int>* reference, std::vector<unsigned int>* guess);//Eingabe sind die Referenzübersetzung und die zu bewertende Übersetzung, allerdings in ID's 
	~Levenshtein();
	
	void print(Lexicon* elex);//gibt die nötigen Veränderungen von guess auf reference aus, dabei wird von hinten angefangen, d.h wenn da als erstes steht einfügen, dann muss hinten eingefügt werden

	int distance(); //gibt die Levenshtein-Distance aus
};
