#include "BFS.h"



_BFS::_BFS() {
    for (int i = 0; i < 9; i++)
        State[i] = i;
}


_BFS::STATUS _BFS::USER_INPUT() {
    for(int i = 0; i < 9; i++) {
        cin >> State[i];
    }
    return(_BFS::DONE);
}


vector<_BFS> _BFS::SearchSolution(_BFS &Initial, _BFS &Target) {
    vector<_BFS> Solution;
    if (Initial == Target) {
        Solution.push_back(Target);
        return(Solution);
    }
    
    queue <int> open;
    
    unordered_map<SERIAL,SERIAL> closed;
    const _BFS::SERIAL TargetSerial = Encode(Target);
    open.push(Encode(Initial));
    closed[Encode(Initial)] = 0;
    
    bool SolutionExistence = false;
    
    while (SolutionExistence == false && open.empty() == false)
    {
        _BFS Node = Decode(open.front()), NewNode;
        for (int move_i = 0; move_i < 4; move_i++)
        {
            NewNode = Node;
            if (NewNode.Move(move_i) == _BFS::DONE)
            {
                int NewSerial = Encode(NewNode);
                if (closed.find(NewSerial) == closed.end())
                {
                    closed[NewSerial] = open.front();
                    open.push(NewSerial);
                }
                if (NewNode == Target)
                {
                    SolutionExistence = true;
                    break;
                }
            }
        }
        open.pop();
    }
    
    if (SolutionExistence == false)
        return Solution;
    
    _BFS::SERIAL SolutionTrajectory = TargetSerial;
    
    while (SolutionTrajectory != 0) {
        Solution.insert(Solution.begin(), Decode(SolutionTrajectory));
        SolutionTrajectory = closed[SolutionTrajectory];
    }
    
    return(Solution);
}


void _BFS::PrintBFS() {
    for(int i=0; i<3; i++) {
        if (this->State[i] != 0)
            cout << "|" << this->State[i];
        else
            cout << "| ";
    }
    cout<<"|"<<endl<<"-------"<<endl;
    for(int i=3; i<6; i++) {
        if(this->State[i]!=0)
            cout << "|" << this->State[i];
        else
            cout << "| ";
    }
    cout << "|" << endl << "-------" << endl;
    for(int i=6; i<9; i++) {
        if(this->State[i]!=0)
            cout << "|" << this->State[i];
        else
            cout << "| ";
    }
    cout << "| "<<endl;
}


unsigned int _BFS::BlankSpace(_BFS Puzzle) {
    for(unsigned int i=0;i<9;i++)
    {
        if(Puzzle.State[i]==0)
            return(i+1);
    }
    
    return 0;
}


_BFS::STATUS _BFS::Move(_BFS::MOVE param) {
    
    switch (param) {
        case 0:
            return(this->MoveZeroUp());
        case 1:
            return(this->MoveZeroDown());
        case 2:
            return(this->MoveZeroLeft());
        case 3:
            return(this->MoveZeroRight());
        default:
            return _BFS::ERROR;
    }
}


_BFS::STATUS _BFS::MoveZeroUp() {
    unsigned int num;
    num = BlankSpace(*this);
    if(num > 3) {
        this->State[num-1] = this->State[num-4];
        this->State[num-4] = 0;
        
        return(_BFS::DONE);
    }
    else
        return(_BFS::ERROR);
}


_BFS::STATUS _BFS::MoveZeroDown() {
    unsigned int num;
    num = BlankSpace(*this);
    if(num > 0 && num < 7) {
        this->State[num-1] = this->State[num+2];
        this->State[num+2] = 0;
        
        return(_BFS::DONE);
    }
    else
        return(_BFS::ERROR);
}


_BFS::STATUS _BFS::MoveZeroLeft() {
    unsigned int num;
    num = BlankSpace(*this);
    if(num%3 != 1 && num != 0) {
        this->State[num-1] = this->State[num-2];
        this->State[num-2] = 0;
        
        return(_BFS::DONE);
    }
    else
        return(_BFS::ERROR);
}


_BFS::STATUS _BFS::MoveZeroRight() {
    unsigned int num;
    num = BlankSpace(*this);
    if(num%3 != 0) {
        this->State[num-1] = this->State[num];
        this->State[num] = 0;
        
        return(_BFS::DONE);
    }
    else
        return(_BFS::ERROR);
}


int _BFS::Encode(_BFS &Puzzle)
{
    unsigned int i;
    int PuzzleID = 0;
    int order = 1;
    for (i = 0; i < 9; i++)
    {
        PuzzleID = PuzzleID + Puzzle.State[i] * order;
        order *= 10;
    }
    return(PuzzleID);
}


_BFS _BFS::Decode(SERIAL serial)
{
    _BFS decode;
    for (int i = 0; i < 9; i++)
    {
        decode.State[i] = serial % 10;
        serial = serial / 10;
    }
    return(decode);
}


bool _BFS::operator == (_BFS &Table) {
    for (int i = 0; i < 9; i++) {
        if (this->State[i] != Table.State[i])
            return(false);
    }
    return(true);
}


bool _BFS::operator == (_BFS const &Table) {
    unsigned int i;
    for (i = 0; i < 9; i++) {
        if (this->State[i] != Table.State[i])
            return(false);
    }
    return(true);
}


bool _BFS::operator != (_BFS &Table) {
    return(!(*this == Table));
}


bool _BFS::operator != (_BFS const &Table) {
    return(!(*this == Table));
}
