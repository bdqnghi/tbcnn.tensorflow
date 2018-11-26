/* 2016
 * Maciej Szeptuch
 * II UWr
 */
#include <algorithm>
#include <cstdio>

const int MAX_AREAS = 1048576;
int areas;
int bucket[MAX_AREAS];
int bucket_y[MAX_AREAS];
int from[MAX_AREAS];
int height;
int sort_me[MAX_AREAS];
int strip;
int tests;
int to[MAX_AREAS];
int width;
int y[MAX_AREAS];

inline
static bool compare_by_y(int a, int b);

inline
static void merge_connected();

//#define debug(...) fprintf(stderr, __VA_ARGS__)
#define debug(...) {}

int main(void)
{
    scanf("%d", &tests);
    for(int t = 0; t < tests; ++ t)
    {
        debug("##################\n");
        scanf("%d %d %d", &width, &height, &strip);
        scanf("%d", &areas);
        int max_level = 0;
        long long unsigned int result = 0;
        for(int a = 0; a < areas; ++ a)
        {
            scanf("%d %d %d", &from[a], &to[a], &y[a]);
            -- from[a], -- to[a], -- y[a];
            sort_me[a] = a;
            max_level = std::max(max_level, to[a]);
        }

        if(!areas)
        {
            puts("0");
            continue;
        }

        std::sort(sort_me, sort_me + areas, compare_by_y);
        merge_connected();
        bucket[0] = 0;
        bucket_y[0] = y[sort_me[0]];
        int buckets = 1;
        for(int s = 1; s < areas; ++ s)
        {
            int a = sort_me[s];
            if(y[a] != bucket_y[buckets - 1])
            {
                bucket_y[buckets] = y[a];
                bucket[buckets ++] = s;
            }
        }

        debug("%d\n", buckets);
        debug("%d\n", areas);

        int level = 0;
        int burnt[MAX_AREAS] = {};
        while(level <= max_level)
        {
            debug("# level %d:\n", level);
            for(int b = 0; b < buckets; ++ b)
            {
                while(bucket_y[b] == y[sort_me[bucket[b]]] && to[sort_me[bucket[b]]] < level)
                    ++ bucket[b];

                debug("%d, %d: %d\n", b, bucket_y[b], sort_me[bucket[b]]);
            }


            for(int b = 0; b < buckets - 2; ++ b)
            {
                int current_strip = strip;
                for(int s = 0; s < 3 && current_strip >= strip; ++ s)
                {
                    if(bucket_y[b + s] != y[sort_me[bucket[b + s]]] || from[sort_me[bucket[b + s]]] > level)
                        current_strip = 0;

                    else if(s > 0 && bucket_y[b + s] != bucket_y[b + s - 1] + 1)
                        current_strip = 0;

                    else
                    {
                        debug("%d: %d => %d\n", b, b + s, to[sort_me[bucket[b + s]]] - level + 1);
                        current_strip = std::min(current_strip, to[sort_me[bucket[b + s]]] - level + 1);
                    }
                }

                debug("%d: current_strip: %d\n", b, current_strip);
                if(current_strip < strip)
                    continue;

                debug("%d: burning %d\n", b, current_strip);
                for(int s = 0; s < 3; ++ s)
                {
                    debug("%d: %d burnt %d\n", b, b + s, burnt[b + s]);
                    debug("%d: %d => +%d\n", b, b + s, std::max(0, level + current_strip - std::max(level, burnt[b + s])));
                    result += std::max(0, level + current_strip - std::max(burnt[b + s], level));
                    burnt[b + s] = std::max(burnt[b + s], level + current_strip);
                }

                debug("result %llu\n", result);
            }

            ++ level;
        }

        printf("%llu\n", result);
    }

    return 0;
}

inline
static bool compare_by_y(int a, int b)
{
    if(y[a] < y[b])
        return true;

    if(y[a] > y[b])
        return false;

    if(from[a] < from[b])
        return true;

    if(from[a] > from[b])
        return false;

    return to[a] < to[b];
}

inline
static void merge_connected()
{
    int p = 0;
    for(int s = 1; s < areas; ++ s)
    {
        int a = sort_me[s];
        if(y[a] == y[sort_me[p]] && to[sort_me[p]] + 1 >= from[a])
        {
            debug("merge %d: %d %d with %d %d\n", y[a], from[sort_me[p]], to[sort_me[p]], from[a], to[a]);
            to[sort_me[p]] = std::max(to[a], to[sort_me[p]]);
        }

        else
            sort_me[++ p] = a;
    }

    areas = p + 1;
}
