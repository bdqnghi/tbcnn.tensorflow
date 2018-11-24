#include <iostream>
#include "KnuthMorrisPratt.h"

KnuthMorrisPratt::KnuthMorrisPratt()
{
	setDefaultValues();
}

// Set the domain. Preprocessing.
void KnuthMorrisPratt::setDomain(const string& d)
{
	// Deletes the allocated stuff and makes it valid.
	free();
	setDefaultValues();

	// Set domain values.
	setDomainValues(d);

	// Allocate the memory for the preprocessing array - @domainLength
	kmpNext = new int[domainLength + 1];

	// The preprocessing.
	int i, j;

	i = 0;
	j = kmpNext[0] = -1;
	while (i < domainLength) 
	{
		while (j > -1 && domain[i] != domain[j])
			j = kmpNext[j];
		i++;
		j++;
		if (domain[i] == domain[j])
			kmpNext[i] = kmpNext[j];
		else
			kmpNext[i] = j;
	}
}

// The searching for the domain in the given url, returns true if it`s in the url, otherwise returns false.
bool KnuthMorrisPratt::searchInUrl(const char* url, size_t urlLength)
{
	int i = 0, j = 0;
	int count = 0; // Counts the number of '/', if it`s more than 3, stops

	while (j < urlLength) 
	{
		// If it`s after the url part for the domains, returns.
		if (url[j] == '/')
			++count;

		if (count >= 3)
			return false;

		while (i > -1 && domain[i] != url[j])
			i = kmpNext[i];
		i++;
		j++;
		if (i >= domainLength)
		{
			// check if the right side is the end of URL or it`s the end of the domain part. AND the left part is beginning of domain (and not just part) 
			// This is our schema: <scheme>://<host>:<port>/<url-path>
			// Thr right symbols of the domain are: ':' , '\' or end of the URL('\0')
			// The left symbols are '/' , '.' and @ (after username maybe, it`s in the example)
			if ((url[j] == '\0' || url[j] == '/' || url[j] == ':') && (url[j - domainLength - 1] == '.' || url[j - domainLength - 1] == '/' || url[j - domainLength - 1] == '@')) // && the start of the compared domain - 1(prev symbol).
				return true;
		}
	}

	return false;
}

// Destructor.
KnuthMorrisPratt::~KnuthMorrisPratt()
{
	free();
}

// Sets the default values.
void KnuthMorrisPratt::setDefaultValues()
{
	domain = NULL;
	domainLength = 0;
	kmpNext = NULL;
}

// Allocates the memory for the domain and the domain length.
void KnuthMorrisPratt::setDomainValues(const string& d)
{
	// Copy the domain string(array of chars).
	domainLength = d.length();
	domain = new char[domainLength + 1];
	strcpy(domain, d.c_str());
}

// Deletes the allocated memory and sets the default values.
void KnuthMorrisPratt::free()
{
	delete[] domain;
	delete[] kmpNext;
}