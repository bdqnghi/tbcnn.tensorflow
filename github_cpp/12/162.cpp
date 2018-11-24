#include <iostream>
#include <algorithm>

#define INFINITE 999999999
#define MAX_CITIES 501

int D[MAX_CITIES][MAX_CITIES];

int main(int argc, char const *argv[]) {
    int cities = 0, deals = 0;

    while ((std::cin >> cities >> deals) && (cities != 0 && deals != 0))
    {
        /* set matrix infinite and 0 on major diagonal */
        for (int i = 1; i <= cities; i++)
        {
            for (int j = 1; j <= cities; j++)
            {
                D[i][j] = (i == j) ? 0 : INFINITE;
            }
        }

        int orig = 0, dest = 0, hours = 0;
        for (int i = 1; i <= deals; i++)
        {
            std::cin >> orig >> dest >> hours;

            if (D[dest][orig] != INFINITE) {
                D[dest][orig] = D[orig][dest] = 0;
            } else {
                D[orig][dest] = hours;
            }
        }

        /* Floyd-Warshall */
        for (int k = 1; k <= cities; k++)
        {
            for (int i = 1; i <= cities; i++)
            {
                for (int j = 1; j <= cities; j++)
                {
                    D[i][j] = std::min(D[i][j], D[i][k] + D[k][j]);
                }
            }
        }

        int queries = 0;
        std::cin >> queries;
        for (int i = 1; i <= queries; i++)
        {
            std::cin >> orig >> dest;
            if (D[orig][dest] < INFINITE) {
                std::cout << D[orig][dest] << std::endl;
            } else {
                std::cout << "Nao e possivel entregar a carta" << std::endl;
            }
        }

        std::cout << std::endl;
    }

    return 0;
}
