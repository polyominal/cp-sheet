#include <gtest/gtest.h>
#include <algebra/modint.hpp>
#include <data-structure/lazy-segtree.hpp>
#include <util/random.hpp>

namespace testing {

TEST(LazySegtreeTest, RangeAffineRangeSum) {
	auto rng = Random(54321);

	for (int N : {0, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 214}) {
		const u32 mod = u32(1e9) + 7;
		using Z = ModInt<mod>;

		Vec<Z> A(N);
		for (Z& a : A) {
			a = rng.uniform<u32>(0, mod - 1);
		}

		struct RangeAffineMonoid {
			using S = pair<Z, int>;
			using F = pair<Z, Z>;

			constexpr S e() { return {0, 0}; }
			S op(S a, S b) { return {a.first + b.first, a.second + b.second}; }
			S mapping(F f, S a) {
				return {a.first * f.first + a.second * f.second, a.second};
			}

			constexpr F id() { return {1, 0}; }
			F composition(F f, F g) {
				return {f.first * g.first, f.second * g.first + g.second};
			}
		} m;
		using S = RangeAffineMonoid::S;

		auto st = LazySegtree(N, [&](int i) -> S { return S(A[i], 1); }, m);

		constexpr int Q = 233;
		for (int q = 0; q < Q; q++) {
			int op = rng.uniform(0, 1);
			int l, r;
			while (true) {
				l = rng.uniform(0, N);
				r = rng.uniform(0, N);
				if (l <= r) break;
			}

			if (op == 0) {
				Z b = rng.uniform<u32>(0, mod - 1);
				Z c = rng.uniform<u32>(0, mod - 1);
				for (int i = l; i < r; i++) {
					A[i] = b * A[i] + c;
				}
				st.apply(l, r, {b, c});
			} else if (op == 1) {
				Z tot_naive = 0;
				for (int i = l; i < r; i++) {
					tot_naive += A[i];
				}
				EXPECT_EQ(tot_naive, st.prod(l, r).first);

				{
					Z tot = 0;
					st.enumerate(l, r,
								 [&](const RangeAffineMonoid::S& s) -> void {
									 tot += s.first;
								 });
					EXPECT_EQ(tot_naive, tot);
				}

				{
					Z tot = 0;
					st.enumerate_in_order<true>(
						l, r, [&](const RangeAffineMonoid::S& s) -> void {
							tot += s.first;
						});
					EXPECT_EQ(tot_naive, tot);
				}

				{
					Z tot = 0;
					st.enumerate_in_order<false>(
						l, r, [&](const RangeAffineMonoid::S& s) -> void {
							tot += s.first;
						});
					EXPECT_EQ(tot_naive, tot);
				}
			} else
				assert(false);

			EXPECT_EQ(st.prod(0, N), st.all_prod());
		}
	}
}

TEST(LazySegtreeTest, RuntimePolymorphismExample) {
	auto rng = Random(20240111);

	const u32 mod = u32(1e9) + 7;
	using Z = ModInt<mod>;

	struct StrConcatMonoid {
		using S = Vec<Z>;
		using F = Z;

		std::function<S(S, S)> str_op;

		S e() { return S(); }
		S op(S a, S b) { return str_op(a, b); }
		S mapping(F f, S a) {
			for (auto& x : a) x += f;
			return a;
		}

		F id() { return 0; }
		F composition(F f, F g) { return f + g; }
	} m, rm;
	using S = StrConcatMonoid::S;
	m.str_op = [](S a, S b) -> S {
		for (auto x : b) a.push_back(x);
		return a;
	};
	rm.str_op = [](S a, S b) -> S {
		for (auto x : a) b.push_back(x);
		return b;
	};

	for (int N : {0, 1, 2, 3, 5, 8, 13, 21, 34}) {
		Vec<S> init(N);
		for (S& x : init) {
			x = S{rng.uniform<u32>(0, mod - 1)};
		}

		auto z = [&](int i) { return init[i]; };
		auto st = LazySegtree(N, z, m);
		auto rst = LazySegtree(N, z, rm);
		EXPECT_EQ(int(size(st.all_prod())), N);
		EXPECT_EQ(int(size(rst.all_prod())), N);

		constexpr int Q = 20;
		for (int q = 0; q < Q; q++) {
			{
				for (int l = 0; l <= N; l++) {
					for (int r = l; r <= N; r++) {
						auto s = st.prod(l, r);
						auto rs = rst.prod(l, r);
						reverse(rs.begin(), rs.end());
						EXPECT_EQ(s, rs);
					}
				}
			}

			{
				int l, r;
				while (true) {
					l = rng.uniform(0, N);
					r = rng.uniform(0, N);
					if (l <= r) break;
				}
				Z f = rng.uniform<u32>(0, mod - 1);
				st.apply(l, r, f);
				rst.apply(l, r, f);
			}

			EXPECT_EQ(st.prod(0, N), st.all_prod());
			EXPECT_EQ(rst.prod(0, N), rst.all_prod());
		}
	}
}

}  // namespace testing