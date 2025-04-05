#include "contest/base.hpp"
#include "data-structure/unionfind.hpp"

namespace kruskal_impl {

template <class T>
struct E {
    int a, b;
    T w;
};

template <class T, class F>
void mst(int n, const Vec<E<T>>& edges, F f) {
    auto idx = Vec<int>(edges.size());
    std::iota(begin(idx), end(idx), 0);
    std::ranges::sort(
        idx, [&](int i, int j) -> bool { return edges[i].w < edges[j].w; });
    auto uf = UnionFind(n);
    for (int i : idx) {
        const auto& e = edges[i];
        if (uf.unite(e.a, e.b)) {
            f(i);
        }
    }
}

}  // namespace kruskal_impl