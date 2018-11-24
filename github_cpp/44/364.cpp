/* Jen Hanni [CS163] "prog2csairways.cpp" [Program #2] */

#include "prog1symtable.h"

/* Node */

node::node() 
{
	next = NULL;
	char * name;
	char * ticket;
	char * seat;
	int status;	// 1 = ticketed, 2 = aboard
}

node::node(char * newname, char * newtype, char * newvalue) 
{
	next = NULL;
	if(newname) {
		int namelen = strlen(newname) + 1;
		name = new char[namelen];
		strncpy(name, newname, namelen);
	}
	if(newticket) {
		int ticketlen = strlen(newticket) + 1;
		ticket = new char[ticketlen];
		strncpy(ticket, newticket, ticketlen);
	}
	if(newseat) {
		int seatlen = strlen(newseat) + 1;
		seat = new char[seatlen];
		strncpy(seat, newseat, seatlen);
	}
}

node::node(char * newname)
{
	next = NULL;
	if(newname) {
		int namelen;
		namelen = strlen(newname) + 1;
		name = new char[namelen];
		strncpy(name, newname, namelen);
	}
	char * type;
	char * value;
}

node::~node() {
	delete next; 
	delete[] name;
	delete[] type;
	delete[] value;
}

int node::compare(node& source) 
{
	int temp;
	temp = strcmp(name, source.name);
	return temp;
}

int node::set(node& source)
{
	if(source.name) {
		int namelen = strlen(source.name) + 1;
		name = NULL;
		name = new char[namelen];
		strncpy(name, source.name, namelen);
	}
	if(source.type) {
		int typelen = strlen(source.type) + 1;
		type = NULL;
		type = new char[typelen];
		strncpy(type, source.type, typelen);
	}
	if(source.value) {
		int valuelen = strlen(source.value) + 1;
		value = NULL;
		value = new char[valuelen];
		strncpy(value, source.value, valuelen);
	}
	return 0;
}

/****************/
/* Symbol Table */
/****************/

/* symbol table :: constructor */

symbolTable::symbolTable()
{
	node * head = NULL;
}

symbolTable::~symbolTable() {
	delete head;
}

/* symbol table :: creates a new symbol, adds it to the list */

// strcmp(str1,str2) returns 0 when the strings are equal
// strcmp(str1,str2) returns a negative integer when s1 < s2
// strcmp(str1,str2) returns a positive integer when s1 > s2

int symbolTable::add(char * newname, char * newtype, char * newvalue) 
{
	node * symtoadd = new node(newname, newtype, newvalue);
	node * current = head;
	if (!current) 
	{	// if an empty list, make the new symbol the head
		head = symtoadd; 
	}
	else if (current->compare(*symtoadd) == 0)
	{	// return the symbol already exists
		return 2;
	}
	else if (current->compare(*symtoadd) > 0)
	{	// if name of the first node is already more than the symtoadd
		symtoadd->next = current;
		head = symtoadd;
		return 0;
	}
	else if (current->next->compare(*symtoadd) < 0)
	{	// traverse if name of curr->next is less than symtoadd name
		current = current->next;
		return 0;
	}
	else if (current->next->compare(*symtoadd) > 0)
	{ 	// if name of curr->next is more than symtoadd name
		symtoadd->next = current->next;
		current->next = symtoadd;
		return 0;
	}
	else if (current->compare(*symtoadd) < 0 && current->next == '\0')
	{	// if current is less than symtoaddname but current->next is NULL
		current->next = symtoadd;
		symtoadd->next = '\0';
		return 0;
	}
	else { return 1; }
	
	return 0;
}

int symbolTable::drop(char * nametodrop) 
{
	node * symtodrop = new node(nametodrop);
	node * current = head;

	if (!current) 
	{ 
		return 1; 
	}
	else if (current->compare(*symtodrop) == 0)
	{
		return 0;
	}
	else if (find(current->next, symtodrop) == 0)
	{
		node * temp = current->next;
		current->next = current->next->next;
		delete temp;
		return 0;
	}
	else if (find(current->next, symtodrop) == 1)
	{
		return 1;
	}
}

void symbolTable::get(char * nametoget)
{
	node * symtoget = new node(nametoget);
	node * current = head;

	if (!current)
	{
	cout << "This is an empty list. " << endl;
	}
	else if (find(current, symtoget) == 0)
	{
	char name[20];
	current->displayname(*current);
	cout << "Name: " << name << endl;
	}
	else 
	{
	cout << "The symbol wasn't found." << endl;
	}
}

char node::displayname(node& source)
{
	name = source.name;
	return *name;
}

int symbolTable::set(char * newname, char * newtype, char * newvalue) 
{
	node * symtoset = new node(newname, newtype, newvalue);
	node * current = head;

	if (!current) 
	{ 
		return 1; // clean up error messages here
	}
	else if (find(current, symtoset) == 0)
	{
		if (current->set(*symtoset) == 0)
		{
		return 0;  // clean up error messages here
		}
		else
		{
		return 1;  // here as well
		}
	}
	else if (find(current, symtoset) == 1)
	{
		return 1;  // here as well
	}
}

int symbolTable::find(node * here, node * symtodrop) 
{
	int rVal = 1;
	if (here)
	{
		rVal = here->compare(*symtodrop);
		if (rVal == 1) 
		{
		return find(here->next, symtodrop);
		}
	}
	return rVal; // return 0;
}
