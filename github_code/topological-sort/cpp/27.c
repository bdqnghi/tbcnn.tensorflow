/**
 * @brief トポロジカルソートの実装
 * @date  @date  2016/02/14 ~ 2016/03/12
 */



//****************************************
// 必要なヘッダファイルのインクルード
//****************************************

#include <functional>
#include "tsort.hpp"



//****************************************
// 名前空間の始端
//****************************************

GRAPH_BEGIN



//****************************************
// 関数の定義
//****************************************

/**
 * @brief  トポロジカルソートを行います
 *
 * @note   有向非巡回グラフG = (V, E)のトポロジカルソート(topological sort)は頂点集合上の線形順序で、
 *         Gが辺(u, v)を含むならば、この線形順序でuがvより先に現れるものである. (グラフに巡回路があればこのような線形順序は存在しない)
 *         グラフのトポロジカルソートは、すべての有向辺が左から右へ向かう、水平線上での頂点の並べ方である
 *
 * @note   つぎの簡単なアルゴリズムは有向非巡回グラフをトポロジカルソートする
 *
 *         TOPOLOGICAL-SORT(G)
 *         1 各頂点の終了時刻v.fを計算するためにDFS(G)を呼び出す
 *         2 ある頂点の探索が終了するたびに、この頂点を連結リストの先頭に挿入する
 *         3 return 頂点の連結リスト
 *
 * @note   深さ優先探索にΘ(V + E)時間かかり、|V|個の頂点のそれぞれを連結リストの先頭に挿入するのにΟ(1)時間かかるので、
 *         トポロジカルソートはΘ(V + E)時間で実行できる
 *
 * @param  const graph_t& G 有向非巡回グラフ
 * @return 既ソートリスト
 */
array_t tsort(const graph_t& G)
{
    index_t n = G.size();
    std::vector<vcolor> color(n, vcolor::white);
    array_t lst(n);

    // 白節点を訪れる
    std::function<bool(index_t)> dfs_visit = [&](index_t u) {
        color[u] = vcolor::gray;    // uを灰に彩色する
        for (auto&& e : G[u]) {     // vと隣接する各頂点wを調べ、
            index_t w = e.dst;

            // wが白なら再帰的にwを調べる
            if (color[w] == vcolor::white && !dfs_visit(w)) {
                 return false;
            }
        }
        color[u] = vcolor::black;   // uを黒に彩色する
        lst.emplace_back(u);        // リストの末尾に挿入する
        return true;
    };


    // 各頂点vの終了時刻v.fを計算するためにDFS(G)を呼び出す
    for (index_t v = 0; v < n; ++v) {
        if (color[v] == vcolor::white && !dfs_visit(v)) {
            return { };
        };
    }
    reverse(lst.begin(), lst.end());  // リストが逆順にソートされているのでreverseを行う
    return lst;     // 頂点のリストを返す
}



//****************************************
// 名前空間の終端
//****************************************

GRAPH_END
