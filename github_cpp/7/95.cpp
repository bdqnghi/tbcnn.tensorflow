/// Recursion one
void towerOfHanoi(int n, char from_rod, char to_rod, char aux_rod)
{
    if (n == 1)
    {
        printf("\n Move disk 1 from rod %c to rod %c", from_rod, to_rod);
        return;
    }
    towerOfHanoi(n-1, from_rod, aux_rod, to_rod);
    printf("\n Move disk %d from rod %c to rod %c", n, from_rod, to_rod);
    towerOfHanoi(n-1, aux_rod, to_rod, from_rod);
}


/// Iterative one
vi v[3];
//Function to show the movement of disks
void moveDisk(char fromPeg, char toPeg, int disk)
{
//    trace(fromPeg, toPeg, disk);
    int from = fromPeg - 'A';
    int to = toPeg - 'A';
    v[from].pop_back();
    v[to].push_back(disk);
    printf("Move the disk %d from \'%c\' to \'%c\'\n", disk, fromPeg, toPeg);
}

inline int pop(stack <int> &x)
{
    if(x.empty()) return INT_MIN;
    int kk = x.top(); x.pop();
    return kk;
}

// Function to implement legal movement between two poles
void moveDisksBetweenTwoPoles(stack <int> &src, stack <int> &dest, char s, char d)
{
//    trace(s, d);
    int pole1TopDisk = pop(src);
    int pole2TopDisk = pop(dest);

    // When pole 1 is empty
    if (pole1TopDisk == INT_MIN)
    {
        src.push(pole2TopDisk);
        moveDisk(d, s, pole2TopDisk);
    }
    // When pole2 pole is empty
    else if (pole2TopDisk == INT_MIN)
    {
        dest.push(pole1TopDisk);
        moveDisk(s, d, pole1TopDisk);
    }
    // When top disk of pole1 > top disk of pole2
    else if (pole1TopDisk > pole2TopDisk)
    {
        src.push(pole1TopDisk);
        src.push(pole2TopDisk);
        moveDisk(d, s, pole2TopDisk);
    }
    // When top disk of pole1 < top disk of pole2
    else
    {
        dest.push(pole2TopDisk);
        dest.push(pole1TopDisk);
        moveDisk(s, d, pole1TopDisk);
    }
}

void tohIterative(int num_of_disks, int total_num_of_moves, stack <int> &src, stack <int> &dest, stack <int> &aux)
{
    /// Source, Destination, Auxiliary
    char s = 'A', d = 'C', a = 'B';

    //If number of disks is even, then interchange
    //destination pole and auxiliary pole
    if (num_of_disks % 2 == 0)
    {
        char temp = d;
        d = a;
        a  = temp;
    }

    //Larger disks will be pushed first
    for (int i = num_of_disks; i >= 1; i--)
        src.push(i);

    for (int i = 1; i <= total_num_of_moves; i++)
    {
        if (i % 3 == 1)
          moveDisksBetweenTwoPoles(src, dest, s, d);

        else if (i % 3 == 2)
          moveDisksBetweenTwoPoles(src, aux, s, a);

        else if (i % 3 == 0)
          moveDisksBetweenTwoPoles(aux, dest, a, d);
    }
}
