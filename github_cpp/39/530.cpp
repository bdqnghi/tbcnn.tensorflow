/**
 *
 * Convex Hull (Brute Force)
 * Author: Lucky Baar
 *
 */
#include <iostream>
#include <vector>
using namespace std;


struct point
{
    int x;
    int y;
};

struct extreme
{
    point p1;
    point p2;
};

class convex_hull
{
private:
    vector<point> points;
    vector<extreme> extremes;

public:
    void run();
    void get_set();
    void print_extremes();
};


void convex_hull::run()
{
    int a, b, c, ans;
    char sym;
    bool pos, neg;
    extreme e;

    cout << "\nStarting...\n\n";

    for (int i = 0; i < (points.size()); i++)
    {
        cout << "#### Reference Point: (" << points[i].x << ", " << points[i].y << ") ####\n";

        for (int j = 0; j < (points.size()); j++)
        {
            cout << "Line (" << points[i].x << ", " << points[i].y << ") -> " << "(" << points[j].x << ", " << points[j].y << ")\n-------------------\n";

            neg = pos = false;

            if ((points[i].x != points[j].x) || (points[i].y != points[j].y))
            {
                a = points[j].y - points[i].y;
                b = points[i].x - points[j].x;
                c = (points[i].x * points[j].y) - (points[i].y * points[j].x);

                for (int k = 0; k < (points.size()); k++)
                {
                    if (i != k && j != k)
                    {
                        ans = (a * points[k].x) + (b * points[k].y) - c;

                        if (ans >= 0)
                        {
                            sym = '>';
                            pos = true;
                        }
                        else
                        {
                            sym = '<';
                            neg = true;
                        }

                        cout << "For k(x, y) = (" << points[k].x << ", " << points[k].y << "), ax + by - c = " << ans << " which is " << sym << " 0\n";
                    }
                }

                if ((!pos && neg) || (pos && !neg))
                {
                    cout << "THIS LINE IS AN EXTREME.\n\n";

                    e.p1.x = points[i].x;
                    e.p1.y = points[i].y;
                    e.p2.x = points[j].x;
                    e.p2.y = points[j].y;

                    extremes.push_back(e);
                }
                else
                {
                    cout << "THIS LINE IS NOT AN EXTREME.\n\n";
                }
            }
            else
            {
                cout << "SAME POINT. SKIPPING THIS CHECK.\n\n";
            }
        }
    }
}


void convex_hull::print_extremes()
{

    cout << "\n\nEXTREMES:\n---------------\n";
    for (int i = 0; i < extremes.size(); i++)
    {
        cout << "(" << extremes[i].p1.x << ", " << extremes[i].p1.y << ") -> (" << extremes[i].p2.x << ", " << extremes[i].p2.y << ")\n";
    }

}


void convex_hull::get_set()
{
    int x, y, i = 0;
    char o;
    bool more_input;
    point p;

    do
    {
        more_input = false;
        i++;

        cout << "Enter x(" << i << "): ";

        while (!(cin >> x))
        {
            cin.clear();
            cin.ignore(1, '\n');
            cout << "x(" << i << ") must be an integer.\n";
            cout << "Enter x(" << i << "): ";
        }

        cout << "Enter y(" << i <<"): ";
        while(!(cin >> y))
        {
            cin.clear();
            cin.ignore('\n');
            cout << "y(" << i << ") must be an iteger.\n";
            cout << "Enter y(" << i <<"): ";
        }

        p.x = x;
        p.y = y;

        points.push_back(p);

        cout << "Continue adding pairs? (y or n): ";
        while (!(cin >> o) && (o != 'y' && o!= 'n'))
        {
            cin.clear();
            cin.ignore('\n');
            cout << "Continue adding pairs? (y or n): ";
        }

        if (o == 'y')
        {
            more_input = true;
        }
        else if (o == 'n')
        {
            if (points.size() < 3)
            {
                throw "\nEXCEPTION: n < 3\nn must be at least 3 to have a convex hull.\n";
            }
        }


    } while (more_input);
}


int main()
{
    convex_hull* ch;

    cout << "Convex Hull\n\n";

    do
    {
        try
        {
            ch = new convex_hull();
            ch->get_set();
            ch->run();
            ch->print_extremes();
        }
        catch (const char* msg)
        {
            cout << msg << endl;
            ch = NULL;
        }
    } while (ch == NULL);


    return 0;
}
