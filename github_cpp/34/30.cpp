// *****************************************************************
// This file is part of the CYBERMED Libraries
//
// Copyright (C) 2007 LabTEVE (http://www.de.ufpb.br/~labteve),
// Federal University of Paraiba and University of São Paulo.
// All rights reserved.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public
// License along with this program; if not, write to the Free
// Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
// Boston, MA 02110-1301, USA.
// *****************************************************************

#include "cybNaiveBayes.h"

char c;

//CONSTRUCTOR	
CybNaiveBayes::CybNaiveBayes(int variablesNumber)
{
	if (variablesNumber > 3)
	{
		cout << "variablesNumber > 3! Error!";
		exit(0);
	}
	this->intersectionTable = NULL;
	this->table = NULL;
	this->variablesNumber = variablesNumber;
	this->sturges = 0;
	this->intersections = 0;

}

//DESTRUCTOR
CybNaiveBayes::~CybNaiveBayes()
{

}

void CybNaiveBayes::training()
{
	initData();
}

//THIS METHOD KEEPS TRAINING USING EXISTING TABLES
void CybNaiveBayes::training2(float*** RefTable_2, float*** RefTable)
{

	int sturges;
	int intersections = 0;

	//STURGES NUMBER
	if (this->getData()->size() > 10000)
	{
		sturges = rintf(1 + 3.3 * log10(10000));
	}
	else
	{
		sturges = rintf(1 + 3.3 * log10(this->getData()->size()));
	}
	cout << "sturges: " << sturges << "\n";
	this->setSturges(sturges);

	//AUXILIARY TABLES
	float*** auxRefTable = RefTable;
	float*** auxRefTable_2 = RefTable_2;

	//INDEX ARRAY
	int* sturgesIndex = new int[this->getVariablesNumber()];

	//AUXILIARY VECTORS
	float* vector = new float[this->getData()->size()];
	float* vector_2 = new float[this->getVariablesNumber()];

	//SETTING A DISTRIBUTION TABLE USING STURGES INTERVALS
	for(int i=0; i<this->getVariablesNumber(); i++)
	{
		for (int j=0; j<this->getData()->size(); j++)
		{
			vector[j] = this->data->pos(j)->operator[](i);

		}
	
		auxRefTable[i] = reDistributeSturges(vector, RefTable[i]);

	}
	this->setTable(auxRefTable);
	
	//COPYING THE DATA VECTOR TO THE AUXILIARY VECTOR AND LOCATING STURGES INTERVALS INDEXES FOR EACH VALUE
	for (int j=0; j<this->getData()->size(); j++)
	{
		for(int i=0; i<this->getVariablesNumber(); i++)
		{
			//THIS VECTOR WILL HAVE ONE VALUE FOR EACH VARIABLE
			vector_2[i] = this->data->pos(j)->operator[](i);
		}

		sturgesIndex = locateSturgesIndexes(vector_2, auxRefTable);

		if (sturgesIndex == NULL)
		{
			continue;
		}
		//INCREMENTING THE TABLE FROM STURGES INTERVAL INDEXES
		auxRefTable_2[sturgesIndex[0]][sturgesIndex[1]][sturgesIndex[2]] += 1;
	}
	this->setIntersectionTable(auxRefTable_2);

	//SIMPLE COUNT INTERSECTIONS
	for(int i=0; i<sturges; i++)
	{
		for(int j=0; j<sturges; j++)
		{
			for(int k=0; k<sturges; k++)
			{
				if(auxRefTable_2[i][j][k] > 0) 
				{
					intersections++;
				} 

			}

		}
	}
	this->setIntersections(intersections);
}

//THIS METHOD STARTS THE TRAIN TABLES CALLED BY training()
void CybNaiveBayes::initData()
{	

	int sturges;
	//STURGES NUMBER
	if (this->getData()->size() > 10000)
	{
		sturges = rintf(1 + 3.3 * log10(10000));
	}
	else
	{
		sturges = rintf(1 + 3.3 * log10(this->getData()->size()));
	}
	cout << "sturges: " << sturges << "\n";
	this->setSturges(sturges);

	//AUXILIARY TABLES
	float*** auxRefTable;
	float*** auxRefTable_2;
	auxRefTable = alocRefMatrix(this->getVariablesNumber(), sturges, TABLE_SIZE);
	auxRefTable_2 = alocRefMatrix(sturges, sturges, sturges);
	
	//INDEX ARRAY
	int* sturgesIndex = new int[this->getVariablesNumber()];

	//AUXILIARY VECTORS
	float* vector = new float[this->getData()->size()];
	float* vector_2 = new float[this->getVariablesNumber()];

	//COUNTER
	int intersections = 0;


	//STARTING ALL INTERSECTION TABLE VALUES AS ZEROS
	for(int i=0; i<sturges; i++)
	{
		for(int j=0; j<sturges; j++)
		{
			for(int k=0; k<sturges; k++)
			{
				auxRefTable_2[i][j][k] = 0;
			}
		}
	}

	//SETTING A DISTRIBUTION TABLE USING STURGES INTERVALS
	for(int i=0; i<this->getVariablesNumber(); i++)
	{
		for (int j=0; j<this->getData()->size(); j++)
		{
			vector[j] = this->data->pos(j)->operator[](i);

		} //end for j data size
	
		auxRefTable[i] = distributeSturges(vector);

	} //end for i variables number
	this->setTable(auxRefTable);

	//COPYING THE DATA VECTOR TO THE AUXILIARY VECTOR AND LOCATING STURGES INTERVALS INDEXES FOR EACH VALUE
	for (int j=0; j<this->getData()->size(); j++)
	{
		for(int i=0; i<this->getVariablesNumber(); i++)
		{
			//THIS VECTOR WILL HAVE ONE VALUE FOR EACH VARIABLE
			vector_2[i] = this->data->pos(j)->operator[](i);
		}

		sturgesIndex = locateSturgesIndexes(vector_2, auxRefTable);

		if (sturgesIndex == NULL)
		{
			//cout << "\nSturges index NULL";
			continue;
		}
		//INCREMENTING THE TABLE FROM STURGES INTERVAL INDEXES
		auxRefTable_2[sturgesIndex[0]][sturgesIndex[1]][sturgesIndex[2]] += 1;
	}
	this->setIntersectionTable(auxRefTable_2);

	for(int i=0; i<sturges; i++)
	{
		for(int j=0; j<sturges; j++)
		{
			for(int k=0; k<sturges; k++)
			{
				if(auxRefTable_2[i][j][k] > 0) 
				{
					intersections++;
				} 

			}
		}
	}
	this->setIntersections(intersections);
}

double CybNaiveBayes::assessment(CybVectorND<>* data)
{
	float* aux = data->toArray(); //one data for each variable
	float ***table = this->getTable();
	float ***intersectionTable = this->getIntersectionTable();
	int* sturgesIndex;
	

	//LOCATING STURGES INTERVALS INDEXES FOR EACH VALUE
	sturgesIndex = locateSturgesIndexes(aux, table);
	if (sturgesIndex == NULL)
	{
		//cout << "sturgesIndex NULL";
		return 0;
	}

	//THE FREQUENCY WILL BE AT intersectionTable[sturgesIndex[0]][sturgesIndex[1]][sturgesIndex[2]]
	return (intersectionTable[sturgesIndex[0]][sturgesIndex[1]][sturgesIndex[2]] / this->getData()->size());
}

/* Gets */

int CybNaiveBayes::getVariablesNumber()
{
	return this->variablesNumber;
}

int CybNaiveBayes::getSturges()
{
	return this->sturges;
}

int CybNaiveBayes::getIntersections()
{
	return this->intersections;
}

float*** CybNaiveBayes::getTable()
{
	return this->table;
}

float*** CybNaiveBayes::getIntersectionTable()
{
	return this->intersectionTable;
}


/* Sets */


void CybNaiveBayes::setTable(float*** table)
{
	this->table = table;
}

void CybNaiveBayes::setIntersectionTable(float*** table)
{
	this->intersectionTable = table;
}

void CybNaiveBayes::setSturges(int sturges)
{
	this->sturges = sturges;
}

void CybNaiveBayes::setIntersections(int intersections)
{
	this->intersections = intersections;
}

/* Extra methods */
float*** CybNaiveBayes::alocRefMatrix(int quantity, int lines, int columns)
{
	float ***matrix;
	int l,y;

	if (lines < 1 || columns < 1 || quantity < 1)
	{
		printf ("** Error: Wrong parameter **\n");
		return (NULL);
	}
	
	matrix = (float ***) calloc (quantity, sizeof(float **));
	
	if (matrix == NULL)
	{
		printf ("** Error: Not enough memory **");
		return (NULL);
	}

	for (l=0; l<quantity; l++ )
	{
		matrix[l] = (float**) calloc (lines, sizeof(float *));
		if (matrix[l] == NULL)
		{
			printf ("** Error: Not enough memory **");
			return (NULL);
		}
        }

	for (l=0; l<quantity; l++ )
	{
		for (y=0; y<lines; y++)
		{
			matrix[l][y] = (float*) calloc (columns, sizeof(float));
			if (matrix[l][y] == NULL)
			{
				printf ("** Error: Not enough memory **");
				return (NULL);
			}
	        }
	}
	return (matrix);
}

float*** CybNaiveBayes::freeRefMatrix (int quantity, int lines, int columns, float ***matrix)
{
	int l,y;

	if (matrix == NULL)
	{
		return (NULL);
	}
	
	if (lines < 1 || columns < 1 || quantity < 1)
	{
		printf ("** Error: Wrong parameter **\n");
		return (matrix);
	}


	for (l=0; l<quantity; l++)
	{
		freeMatrix(lines, columns, matrix[l]);
	}

	free (matrix);
	
	return (NULL);
}


float** CybNaiveBayes::freeMatrix (int lines, int columns, float **matrix)
{
	int l;

	if (matrix == NULL)
	{
		return (NULL);
	}
	
	if (lines < 1 || columns < 1)
	{
		printf ("** Erro: Wrong parameter **\n");
		return (matrix);
	}


	for (l=0; l<lines; l++)
	{
		free(matrix[l]);
	}

	free (matrix);
	
	return (NULL);
}


float** CybNaiveBayes::alocMatrix (int lines, int columns)
{
	float **matrix; 
	int l;

	if (lines < 1 || columns < 1)
	{
		printf ("** Erro: Wrong parameter **\n");
		return (NULL);
	}
	
	matrix = (float **) calloc (lines, sizeof(float *));
	
	if (matrix == NULL)
	{
		printf ("** Erro: Not enough memory **");
		return (NULL);
	}

	for (l=0; l<lines; l++ )
	{
		matrix[l] = (float*) calloc (columns, sizeof(float));
		if (matrix[l] == NULL)
		{
			printf ("** Erro: Not enough memory **");
			return (NULL);
		}
    }

	return (matrix);
}

//METHOD USED BY initData() THAT CREATES THE TABLE INTERVALS
float** CybNaiveBayes::distributeSturges (float* auxArray)
{

	float lower = LOWER;
	float higher = HIGHER;
	float last;
	float sampleAmplitude;
	float classAmplitude;
	float accumulator;
	int freqCounter = 0;
	float** auxTable;
	auxTable = alocMatrix(this->getSturges(), TABLE_SIZE);
	

	for(int i=0; i<this->getData()->size(); i++)
	{
		if (lower > auxArray[i])
		{
			lower = auxArray[i];
		}
		if (higher < auxArray[i])
		{
			higher = auxArray[i];
		}
	}

	sampleAmplitude = higher - lower;
	classAmplitude = sampleAmplitude / this->getSturges();
	accumulator = lower;

	for(int i=0; i<this->sturges; i++)
	{
		//writes the class intervals
		for(int j=0; j<2; j++)
		{
			auxTable[i][j] = accumulator;
			accumulator += classAmplitude;
		} //end for j<table
		accumulator -= classAmplitude;

		//rounds up the last interval
		if(i == (sturges-1))
		{
			auxTable[i][1] = ceil(auxTable[i][1]); //auxTable[i][1]+1
			last = auxTable[i][1];
		}

		//checking the interval
		for(int j=0; j<this->getData()->size(); j++)
		{
			if (auxArray[j] >= auxTable[i][0] && auxArray[j] < auxTable[i][1])
			{
				freqCounter++;
			}
		} //end for j<size	

		//writing the frequency
		auxTable[i][2] = freqCounter;
		freqCounter = 0;

	} //end for i<sturges

	return auxTable;
}

//METHOD USED BY training2() WORKS ON THE EXISTING TABLE INTERVALS
float** CybNaiveBayes::reDistributeSturges (float* auxArray, float** table)
{

	int freqCounter = 0;
	float** auxTable = table;

	for(int i=0; i<this->getSturges(); i++)
	{
		//checking the interval
		for(int j=0; j<this->getData()->size(); j++)
		{
			if (auxArray[j] >= auxTable[i][0] && auxArray[j] < auxTable[i][1])
			{
				freqCounter++;
			}
		} //end for j<size	

		//writing the frequency
		auxTable[i][2] += freqCounter;
		freqCounter = 0;

	} //end for i<sturges

	for(int i=0; i<this->getSturges(); i++)
	{
		freqCounter += auxTable[i][2];
	} //end for i<sturges

	return auxTable;
}

//METHOD USED TO FIND OUT THE INDEXES FROM THE auxVector IN THE auxRefTable
int* CybNaiveBayes::locateSturgesIndexes(float* auxVector, float*** auxRefTable)
{
	int* indexes = new int[this->getVariablesNumber()];
	int usedIndexes = 0;

	for(int i=0; i<this->getVariablesNumber(); i++)
	{
		for(int j=0; j<this->sturges; j++)
		{
			if (auxVector[i] >= auxRefTable[i][j][0] && auxVector[i] < auxRefTable[i][j][1])
			{
				indexes[i] = j;
				usedIndexes++;
			}
		}
	}

	//checks if all indexes were used
	if (usedIndexes != this->getVariablesNumber())
		return NULL;

	return indexes;
}
