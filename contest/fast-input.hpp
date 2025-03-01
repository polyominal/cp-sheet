#pragma once

/**
 * Author: Hanfei Chen
 * Description: Fast scanner implementation based on \texttt{fread}
 * Status: Tested with
 * - https://judge.yosupo.jp/problem/associative_array (uint64_t)
 */

#include "contest/base.hpp"

namespace fast_input {

struct Scanner {
    FILE* f;
    Scanner(FILE* f_ = stdin) : f(f_) {}

    char get() {  /// start-hash
        static array<char, 1 << 16> buf;
        static size_t s = 0, e = 0;
        if (s >= e) {
            buf[0] = 0;
            s = 0;
            e = fread(data(buf), 1, sizeof(buf), f);
        }
        return buf[s++];
    }  /// end-hash

    using Self = Scanner;

    char skip_whitespaces() {
        char c;
        while ((c = get()) <= ' ') {
        }
        return c;
    }

    template <class T>
    Self& operator>>(T& x) {
        char c = skip_whitespaces();
        bool neg = false;
        if (c == '-') {
            neg = true;
            c = get();
        }
        x = 0;
        do {
            x = 10 * x + (c & 15);
        } while ((c = get()) >= '0');
        if (neg) {
            x = -x;
        }
        return *this;
    }

    Self& operator>>(string& x) {
        char c = skip_whitespaces();
        x = {};
        do {
            x += c;
        } while ((c = get()) > ' ');
        return *this;
    }

    Self& operator>>(double& x) {
        string z;
        *this >> z;
        x = stod(z);
        return *this;
    }
};

}  // namespace fast_input
