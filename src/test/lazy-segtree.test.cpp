#include <catch2/catch_test_macros.hpp>

#include "data-structure/lazy-segtree.hpp"
#include "algebra/modint.hpp"

#include "util/random.hpp"

TEST_CASE("Lazy segtree: range affine range sum", "[seglazy]") {
	auto rng = Random(54321);

	for (int N : {0, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 214}) {
		const uint32_t mod = uint32_t(1e9) + 7;
		using num = mint<mod>;

		V<num> A(N);
		for (num& a : A) {
			a = rng.uniform<uint32_t>(0, mod-1);
		}

		struct RangeAffineMonoid {
			using S = pair<num, int>;
			using F = pair<num, num>;

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

		auto st = LazySegtree(N, [&](int i) -> S {
			return S(A[i], 1);
		}, m);

		int Q = 233;
		for (int q = 0; q < Q; q++) {
			int op = rng.uniform(0, 1);
			int l, r;
			while (true) {
				l = rng.uniform(0, N);
				r = rng.uniform(0, N);
				if (l <= r) break;
			}

			if (op == 0) {
				num b = rng.uniform<uint32_t>(0, mod-1);
				num c = rng.uniform<uint32_t>(0, mod-1);
				for (int i = l; i < r; i++) {
					A[i] = b * A[i] + c;
				}
				st.apply(l, r, {b, c});
			} else if (op == 1) {
				num tot_naive = 0;
				for (int i = l; i < r; i++) {
					tot_naive += A[i];
				}
				REQUIRE(tot_naive == st.prod(l, r).first);

				{
					num tot = 0;
					st.enumerate(l, r, [&](const RangeAffineMonoid::S& s) -> void {
						tot += s.first;
					});
					REQUIRE(tot_naive == tot);
				}

				{
					num tot = 0;
					st.enumerate_in_order<true>(l, r, [&](const RangeAffineMonoid::S& s) -> void {
						tot += s.first;
					});
					REQUIRE(tot_naive == tot);
				}

				{
					num tot = 0;
					st.enumerate_in_order<false>(l, r, [&](const RangeAffineMonoid::S& s) -> void {
						tot += s.first;
					});
					REQUIRE(tot_naive == tot);
				}
			} else assert(false);

			REQUIRE(st.prod(0, N) == st.all_prod());
		}
	}
}

TEST_CASE("Lazy segtree: runtime polymorphism example", "[seglazy]") {
	auto rng = Random(20240111);

	const uint32_t mod = uint32_t(1e9) + 7;
	using num = mint<mod>;

	struct StrConcatMonoid {
		using S = V<num>;
		using F = num;

		function<S(S, S)> str_op;

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
		V<S> init(N);
		for (S& x : init) {
			x = S{rng.uniform<uint32_t>(0, mod-1)};
		}

		auto st = LazySegtree(init, m);
		auto rst = LazySegtree(init, rm);
		REQUIRE(int(st.all_prod().size()) == N);
		REQUIRE(int(rst.all_prod().size()) == N);

		constexpr int Q = 20;
		for (int q = 0; q < Q; q++) {
			{
				for (int l = 0; l <= N; l++) {
					for (int r = l; r <= N; r++) {
						auto s = st.prod(l, r);
						auto rs = rst.prod(l, r);
						reverse(rs.begin(), rs.end());
						REQUIRE(s == rs);
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
				num f = rng.uniform<uint32_t>(0, mod-1);
				st.apply(l, r, f);
				rst.apply(l, r, f);
			}

			REQUIRE(st.prod(0, N) == st.all_prod());
			REQUIRE(rst.prod(0, N) == rst.all_prod());
		}
	}
}

TEST_CASE("Segtree: single set and range affine composition", "[segtree]") {
	auto rng = Random(20240119);

	const uint32_t mod = 998244353;
	using num = mint<mod>;

	struct Monoid {
		using S = pair<num, num>;
		using F = char;

		constexpr S e() { return S(1, 0); }
		S op(S f, S g) {
			return {f.first * g.first, f.second * g.first + g.second};
		}
		S mapping(F, S f) {
			return f;
		}

		F id() { return F(); }
		F composition(F, F) { return F(); }
	};

	for (int N : {0, 1, 2, 3, 5, 8, 13, 21, 34}) {
		using S = Monoid::S;
		auto uniform_affine = [&]() -> S {
			return S(rng.uniform<uint32_t>(0, mod-1), rng.uniform<uint32_t>(0, mod-1));
		};
		V<S> A(N);
		for (S& f : A) {
			f = uniform_affine();
		}
		Monoid m;
		auto st = LazySegtree(A, m);

		constexpr int Q = 20;
		for (int q = 0; q < Q; q++) {
			for (int l = 0; l <= N; l++) {
				auto f = m.e();
				for (int r = l; r <= N; r++) {
					{
						REQUIRE(f == st.prod(l, r));
					}
					{
						auto g = m.e();
						st.enumerate_in_order(l, r, [&](const S& a) -> void {
							g = m.op(g, a);
						});
						REQUIRE(f == g);
					}
					{
						auto g = m.e();
						st.enumerate_in_order<false>(l, r, [&](const S& a) -> void {
							g = m.op(a, g);
						});
						REQUIRE(f == g);
					}

					if (r < N) {
						f = m.op(f, A[r]);
					}
				}
			}

			if (N > 0) {
				int p = rng.uniform(0, N-1);
				auto f = uniform_affine();
				st.set(p, f);
				A[p] = f;
			}
		}
	}
}

/*
TEST_CASE("Lazy segtree: max_right and min_left", "[segtree]") {
	struct SumMonoid {
		using S = pair<int, int>;
		using F = int;

		S e() { return S(0, 0); }
		S op(S a, S b) { return S(a.first + b.first, a.second + b.second); }
		S mapping(F f, S a) { return S(a.first + f * a.second, a.second); }

		F id() { return F(0); }
		F composition(F a, F b) { return a + b; }
	} m;
	using S = SumMonoid::S;
	const int N = 5;
}
*/