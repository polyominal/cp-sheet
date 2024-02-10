#include <catch2/catch_test_macros.hpp>

#include "algebra/modint.hpp"
#include "algebra/nft.hpp"
#include "util/random.hpp"

template <class T> V<T> multiply_textbook(const V<T>& a, const V<T> b) {
	if (a.empty() || b.empty()) return {};
	V<T> res(a.size() + b.size() - 1);
	for (int i = 0; i < int(a.size()); i++) {
		for (int j = 0; j < int(b.size()); j++) {
			res[i+j] += a[i] * b[j];
		}
	}
	return res;
}

TEST_CASE("NFT multiply mod 998244353 simple", "[nft]") {
	constexpr uint mod = 998244353;
	using num = modint<mod>;
	V<num> A = {1,2,3,4};
	V<num> B = {5,6,7,8,9};
	REQUIRE(multiply(A, B) == V<num>{5,16,34,60,70,70,59,36});
}

TEST_CASE("NFT multiply mod 998244353", "[nft]") {
	auto rng = Random(1145141);

	constexpr uint mod = 998244353;
	using num = modint<mod>;
	V<num> A(123);
	for (num& v : A) v = rng.uniform<ll>(0, mod-1);
	V<num> B(233);
	for (num& v : B) v = rng.uniform<ll>(0, mod-1);
	REQUIRE(multiply(A, B) == multiply_textbook(A, B));
}

template <class num> void retromorphic_test_single() {
	uint32_t mod = num::get_mod();
	auto rng = Random(mod);

	for (int N : {1, 3, 9, 11, 28, 128, 245}) {
		V<num> A(N);
		for (num& v : A) v = rng.uniform<ll>(0, mod-1);

		int S = 1 << (N <= 1 ? 0 : 32 - __builtin_clz(N-1));
		auto fa = A;
		fa.resize(S);
		nft(fa, S);
		inft(fa, S);
		REQUIRE(int(fa.size()) == S);
		fa.resize(N);
		REQUIRE(A == fa);
	}
}

TEST_CASE("NFT retromorphic test multiple mods (essentially A == inft(nft(A)))", "[nft]") {
	// make sure static things don't collide
	retromorphic_test_single<modint<998244353>>();
	retromorphic_test_single<modint<1053818881>>();
}
