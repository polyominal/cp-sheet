#include <array>
#include <vector>

struct CartesianTree {
  public:
    int root;
    std::vector<int> par;
    std::vector<std::array<int, 2>> ch;

    template <typename T>
    explicit CartesianTree(const std::vector<T>& values) {
        initialize(values);
    }

  private:
    template <typename Range>
    void initialize(const Range& values) {
        const int n = static_cast<int>(std::size(values));
        root = 0;
        par.assign(n, -1);
        ch.assign(n, {-1, -1});
        if (n == 0) {
            return;
        }

        auto stk = std::vector<int>{0};
        stk.reserve(n);
        for (int i = 1; i < n; i++) {
            if (values[stk.back()] > values[i]) {
                while (std::size(stk) >= 2 &&
                       values[stk[std::size(stk) - 2]] > values[i]) {
                    stk.pop_back();
                }
                if (std::size(stk) == 1) {
                    root = i;
                    ch[i][0] = stk.back();
                    par[stk.back()] = i;
                } else {
                    ch[i][0] = stk.back();
                    par[stk.back()] = i;

                    int j = stk[std::size(stk) - 2];
                    ch[j][1] = i;
                    par[i] = j;
                }
                stk.back() = i;
            } else {
                int j = stk.back();
                ch[j][1] = i;
                par[i] = j;
                stk.push_back(i);
            }
        }
    }
};