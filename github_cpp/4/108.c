#include "TowerOfHanoi.hpp"



TowerOfHanoi::TowerOfHanoi()
{
	disk_array = nullptr;
}

TowerOfHanoi::TowerOfHanoi(int num_of_disks)
{
	this->num_of_disks = num_of_disks;

	
	disk_array = new Disk[num_of_disks];
	for (int i = 0; i < num_of_disks; i++) {
		disk_array[i].size = i;
	}

	
	for (int i = num_of_disks - 1; i >= 0; i--) {
		Source.disks_on_peg.push(disk_array[i]);
	}
}

TowerOfHanoi::~TowerOfHanoi()
{
	if (disk_array != nullptr) {
		delete disk_array;
	}
}

void TowerOfHanoi::Solve_Hanoi()
{
	Solve_Hanoi_Recursive(num_of_disks, Source, Destination, Temp);
}

void TowerOfHanoi::Solve_Hanoi_Recursive(int currentSize, Peg& Source, Peg& Destination, Peg& temp)
{
	if (currentSize == 1) {
		Move_Disks(Source, Destination);
	}
	else {
		Solve_Hanoi_Recursive(currentSize - 1, Source, temp, Destination);
		Move_Disks(Source, Destination);
		Solve_Hanoi_Recursive(currentSize - 1, temp, Destination, Source);
	}
}


void TowerOfHanoi::Move_Disks(Peg& Source, Peg& Destination)
{
	Destination.disks_on_peg.push(Source.disks_on_peg.top());
	Source.disks_on_peg.pop();
}
