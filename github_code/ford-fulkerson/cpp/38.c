/* 2014
 * Maciej Szeptuch
 * IIUWr
 */
#include <cstdio>
#include <vector>
#define _(h, w) ((h) * width + (w))
#define __(hash) (std::pair<int, int>((hash) / width, (hash) % width))

int height,
    width,
    level,
    sink,
    cost[4096][4096],
    visited[4096],
    flg;
std::vector<std::pair<int, int> > sources;

int fordFulkerson(int from, int to, int want);
int fordFulkersonDFS(int from, int to, int flow, int flag);

int main(void)
{
    scanf("%d %d", &height, &width);
    for(int h = 0; h < height; ++ h)
        for(int w = 0; w < width; ++ w)
        {
            scanf("%d", &level);
            if(level == -1)
            {
                sink = _(h, w);
                if(h > 0)
                    cost[_(h - 1, w)][_(h,w)] = 1000000;

                if(w > 0)
                    cost[_(h, w - 1)][_(h,w)] = 1000000;

                if(w < width - 1)
                    cost[_(h, w + 1)][_(h,w)] = 1000000;

                if(h < height - 1)
                    cost[_(h + 1, w)][_(h,w)] = level;
                continue;
            }

            if(level == 0)
                continue;

            if(h == 0 || h == height - 1 || w == 0 || w == width - 1)
                sources.push_back(std::make_pair(_(h, w), level));

            if(h > 0)
                cost[_(h - 1, w)][_(h,w)] = level;

            if(w > 0)
                cost[_(h, w - 1)][_(h,w)] = level;

            if(w < width - 1)
                cost[_(h, w + 1)][_(h,w)] = level;

            if(h < height - 1)
                cost[_(h + 1, w)][_(h,w)] = level;
        }

    int result = 0;
    for(unsigned int s = 0; s < sources.size(); ++ s)
        result += fordFulkerson(sources[s].first, sink, sources[s].second);

    printf("%d\n", result);
    return 0;
}

inline
int fordFulkerson(int from, int to, int want)
{
    int flow    = 0,
        act     = 0;
    do
    {
        flow += act = fordFulkersonDFS(from, to, want, ++ flg);
        want -= act;
        printf("Pushed %d\n", act);
    }
    while(act && want);

    return flow;
}

int fordFulkersonDFS(int from, int to, int flow, int flag)
{
    std::pair<int, int> p = __(from);
    printf("Hi from (%d, %d) with %d\n", p.first, p.second, flow);

    if(!flow)
        return 0;

    if(from == to)
        return flow;

    visited[from] = flag;
    int res = 0,
        act = 0;
    if(p.first > 0 && visited[_(p.first - 1, p.second)] != flag)
    {
        res += act = fordFulkersonDFS(_(p.first - 1, p.second), to, std::min(flow, cost[from][_(p.first - 1, p.second)]), flag);
        cost[from][_(p.first - 1, p.second)] -= act;
        cost[_(p.first - 1, p.second)][from] += act;
        flow -= act;
    }

    if(p.first < height - 1 && visited[_(p.first + 1, p.second)] != flag)
    {
        res += act = fordFulkersonDFS(_(p.first + 1, p.second), to, std::min(flow, cost[from][_(p.first + 1, p.second)]), flag);
        cost[from][_(p.first + 1, p.second)] -= act;
        cost[_(p.first + 1, p.second)][from] += act;
        flow -= act;
    }

    if(p.second > 0 && visited[_(p.first, p.second - 1)]!= flag)
    {
        res += act = fordFulkersonDFS(_(p.first, p.second - 1), to, std::min(flow, cost[from][_(p.first, p.second - 1)]), flag);
        cost[from][_(p.first, p.second - 1)] -= act;
        cost[_(p.first, p.second - 1)][from] += act;
        flow -= act;
    }

    if(p.second < width - 1 && visited[_(p.first, p.second + 1)] != flag)
    {
        res += act = fordFulkersonDFS(_(p.first, p.second + 1), to, std::min(flow, cost[from][_(p.first, p.second + 1)]), flag);
        cost[from][_(p.first, p.second + 1)] -= act;
        cost[_(p.first, p.second + 1)][from] += act;
        flow -= act;
    }

    return res;
}
