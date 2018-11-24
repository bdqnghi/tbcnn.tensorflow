#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <math.h>

using namespace std;

struct student {
	char* fname;
	char* lname;
	int id;
	float gpa;
};

class HashTable {
private:
	int size;
	student** table;
public:
	HashTable(int i) {
		this->size = i;
		table = new student * [size];
		for (int i = 0; i < size; i++) {
			table[i] = NULL;
		}
	}
	int HashFunction(int id) {
		int i = id % size;
		int j = int(i);
		return j;
	}
	HashTable add_element(student* stu, HashTable &ht) {
		int i = HashFunction(stu->id);
		if (ht.table[i] == NULL) {
			ht.table[i] = stu;
		}
		else {
			while (ht.table[i] != NULL) {
				i++;
			}
			ht.table[i] = stu;
		}
		ht = ht.rehash(ht);
		return ht;
	}
	void delete_element(int delID, HashTable &ht) {
		int i = HashFunction(delID);
		if (ht.table[i] == NULL) {
			cout << "There is no student with those credentials\n";
			return;
		}
		else if (ht.table[i]->id == delID) {
			ht.table[i] = NULL;
		}
	}
	void display(HashTable ht) {
		for(int i = 0; i < ht.size; i++) {
			if (ht.table[i] != NULL) {
				cout << ht.table[i]->fname;
				cout << " " << ht.table[i]->lname;
				cout << " ID#: " << ht.table[i]->id;
				cout << " GPA: " << ht.table[i]->gpa << endl;
			}
		}
		cout << endl;
	}
	bool check_rehash(HashTable ht) {
		int counts = 0;
		for (int i = 0; i < ht.size; i++) {
			if (ht.table[i] != NULL) {
				counts++;
			}
		}
		if (counts >= (ht.size/2)) {
			return true;
		}
		else {
			return false;
		}
	}
	HashTable rehash(HashTable ht) {
		bool b = check_rehash(ht);
		if (b == false) {
			return ht;
		}
		else {
			HashTable ne(ht.size + 100);
			for (int i = 0; i < ht.size; i++) {
				ne.table[i] = ht.table[i];
			}
			return ne;
		}
	}
	float avg(HashTable ht) {
		float gpa = 0;
		int counts = 0;
		for (int i = 0; i < ht.size; i++) {
			if (ht.table[i] != NULL) {
				counts++;
				gpa = gpa + ht.table[i]->gpa;
			}
		}
		float i = gpa/counts;
		return i;
	}
};

void insert(HashTable&);
void remove(HashTable&);
void read(HashTable&);

int main() {
	srand(0);
	HashTable ht(100);
	int r = 0;
	while (r == 0){
		cout << " 1. Add a student";
		cout << "\n 2. Delete a student";
		cout << "\n 3. Create Random Students";
		cout << "\n 4. Print the students";
		cout << "\n 5. Return the Average GPA";
		cout << "\n 6. Quit the program\n";
		int i;
		while (!(cin >> i)) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Please enter a number\n";
		}
		switch(i) {
			case 1 : insert(ht);
				break;
			case 2 : remove(ht);
				break;
			case 3 : read(ht);
				break;
			case 4 : ht.display(ht);
				break;
			case 5 : cout << "Average: " << ht.avg(ht) << endl;
				break;
			case 6 : r = 1;
				break;
			default : cout << "Please enter a valid number\n";
				break;
		}
	}
	return 0;
}

void insert(HashTable &ht) {
		cin.ignore(1000, '\n');
		cin.clear();
		cout << endl <<  "Welcome to the Add Student Screen" << endl;
    	cout << "Please start by giving us the first name of the student!" << endl;
        char* fname = new char[100];
        cin.get(fname, 99);
        cin.ignore(1000, '\n');
        cout << "What is the last name of the student?" << endl;
        char* lname = new char[100];
        cin.get(lname, 99);
        cin.ignore(1000, '\n');
        cout << "What is this student's ID number?" << endl;
        int id = 0;
        while (!(cin >> id))  {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input, please enter a number" << endl;
        }
        cout << "What is this student's GPA? (Rounded to 2 decimal places)" << endl;
        float gpa = 0;
        while (!(cin >> gpa)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid GPA, please enter a number rounded to 2 decimal places";
        }
        cout << "This student has been successfully added!" << endl << endl;
        student* x = new student;
        x->fname = fname;
        x->lname = lname;
        x->id = id;
        x->gpa = gpa;
        ht = ht.add_element(x, ht);	
}

void remove(HashTable &ht) {
		cout << "What is the student ID number of the student you wish to remove?" << endl;
    	int num = 0;
        while (!(cin >> num))  {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input, please enter a number" << endl;
        }
        ht.delete_element(num, ht);
}

void read(HashTable &ht) {
	char** fnames = new char*[70];
	char** lnames = new char*[70];
	for (int i = 0; i < 70; i++) {
		char* name = new char[15];
		fnames[i] = name;
		lnames[i] = name;
	}
	ifstream fn;
	fn.open("names/firstNames.txt");
	ifstream ln;
	ln.open("names/lastNames.txt");
	int i = 0;
	while (i < 70) {
		fn >> fnames[i];
		i++;
	}
	int j = 0;
	while (j < 70) {
		ln >> lnames[j];
		j++;
	}
	fn.close();
	ln.close();
	int num;
	cout << "How many random kids would you like to generate? Max: 70\n";
	while (!(cin >> num))  {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input, please enter a number" << endl;
    }
    for (int p = 0; p < num; p++) {
    	int j = int(rand() % 70);
    	int k = int(rand() % 70);
    	char* fname = fnames[j];
    	char* lname = lnames[k];
    	int g = (rand() % 80000) + 10000;
    	student* x = new student;
    	x->fname = fname;
    	x->lname = lname;
    	x->id = g;
    	x->gpa = 3.79;
    	ht = ht.add_element(x, ht);
    }
}
