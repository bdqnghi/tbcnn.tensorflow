//from http://forums.devshed.com/c-programming-42/c-towers-of-hanoi-using-templates-424148.html
template<int height, int from, int to, int temp>
class Hanoi
{
public:
    Hanoi()
    {
        Hanoi<height-1, from, temp, to> before;
        Hanoi<height-1, temp, to, from> after;
        ostringstream os;
        os << before.instructions << "Move " <<
              from << " to " << to << endl << after.instructions;
        instructions = os.str();
    }
    string instructions;
};

template<int from, int to, int temp>
class Hanoi<0, from, to, temp>
{
public:
    string instructions;
};

int main()
{
    Hanoi<3, 1, 3, 2> h;
    cout << h.instructions << endl;
    return 0;
}