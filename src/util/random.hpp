// Reference: https://github.com/yosupo06/library-checker-problems/blob/master/common/random.h
// Modified

#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <random>
#include <set>

struct Random {
  public:
    Random(uint64_t seed = 0) {
        // http://xoshiro.di.unimi.it/splitmix64.c
        for (int i = 0; i < 4; i++) {
            uint64_t z = (seed += 0x9e3779b97f4a7c15);
            z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
            z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
            s[i] = z ^ (z >> 31);
        }
    }

    // {lower, lower+1, ..., upper}
    template <class T>
    T uniform(T lower, T upper) {
        assert(lower <= upper);
        return T(lower + next(uint64_t(upper - lower)));
    }

    // {false, true}
    bool uniform_bool() { return bool(uniform(0, 1)); }

    // [0., 1.]
    double uniform_real_01() {
        static constexpr uint64_t MAX = uint64_t(1) << 63;
        return double(next(MAX)) / MAX;
    }

    // length-n lowercase string
    std::string lowercase_string(size_t n) {
        std::string result;
        for (size_t i = 0; i < n; i++) {
            result += uniform('a', 'z');
        }
        return result;
    }

    std::string uppercase_string(size_t n) {
        std::string result;
        for (size_t i = 0; i < n; i++) {
            result += uniform('A', 'Z');
        }
        return result;
    }

    // shuffle the iterator range [first, last)
    template <class Iterator>
    void shuffle(Iterator first, Iterator last) {
        if (first == last) {
            return;
        }
        int cur = 1;
        for (auto it = first + 1; it != last; it++) {
            cur++;
            int j = uniform(0, cur - 1);
            if (j != cur - 1) {
                iter_swap(it, first + j);
            }
        }
    }

    // n-element permutation
    template <class T>
    std::vector<T> permutation(size_t n) {
        std::vector<T> result(n);
        std::iota(result.begin(), result.end(), T(0));
        shuffle(result.begin(), result.end());
        return result;
    }

    // sample n elements from {lower, lower+1, ..., upper}
    template <class T>
    std::vector<T> sample(size_t n, T lower, T upper) {
        assert(T(n) <= upper - lower + 1);
        std::set<T> result;
        while (result.size() < n) {
            result.insert(uniform(lower, upper));
        }
        return std::vector<T>{result.begin(), result.end()};
    }

  private:
    // http://xoshiro.di.unimi.it/xoshiro256starstar.c
    static uint64_t rotl(const uint64_t x, int k) {
        return (x << k) | (x >> (64 - k));
    }
    std::array<uint64_t, 4> s;
    uint64_t next() {
        const uint64_t result_starstar = rotl(s[1] * 5, 7) * 9;
        const uint64_t t = s[1] << 17;
        s[2] ^= s[0];
        s[3] ^= s[1];
        s[1] ^= s[2];
        s[0] ^= s[3];
        s[2] ^= t;
        s[3] = rotl(s[3], 45);
        return result_starstar;
    }

    // {0, 1, ..., upper}
    uint64_t next(uint64_t upper) {
        if (!(upper & (upper + 1))) {
            return next() & upper;
        }
        int lg = int(std::bit_width(upper)) - 1;
        uint64_t mask =
            (lg == 63 ? uint64_t(-1) : (uint64_t(1) << (lg + 1)) - 1);
        while (true) {
            uint64_t result = next() & mask;
            if (result <= upper) {
                return result;
            }
        }
    }
};