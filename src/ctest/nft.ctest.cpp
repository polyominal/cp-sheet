#include <catch2/catch_test_macros.hpp>

#include "algebra/modint.hpp"
#include "algebra/nft.hpp"
#include "util/random.hpp"

template <class T> Vec<T> multiply_textbook(const Vec<T>& a, const Vec<T> b) {
	if (a.empty() || b.empty()) return {};
	Vec<T> res(a.size() + b.size() - 1);
	for (int i = 0; i < int(a.size()); i++) {
		for (int j = 0; j < int(b.size()); j++) {
			res[i+j] += a[i] * b[j];
		}
	}
	return res;
}

TEST_CASE("NFT multiply mod 998244353 simple", "[nft]") {
	constexpr uint mod = 998244353;
	using num = ModInt<mod>;
	Vec<num> A = {1,2,3,4};
	Vec<num> B = {5,6,7,8,9};
	REQUIRE(multiply(A, B) == Vec<num>{5,16,34,60,70,70,59,36});
}

TEST_CASE("NFT multiply mod 998244353", "[nft]") {
	auto rng = Random(1145141);

	constexpr uint mod = 998244353;
	using num = ModInt<mod>;
	Vec<num> A(123);
	for (num& v : A) v = rng.uniform<i64>(0, mod-1);
	Vec<num> B(233);
	for (num& v : B) v = rng.uniform<i64>(0, mod-1);
	REQUIRE(multiply(A, B) == multiply_textbook(A, B));
}

template <class num> void retromorphic_test_single() {
	uint32_t mod = num::get_mod();
	auto rng = Random(mod);

	for (int N : {1, 3, 9, 11, 28, 128, 245}) {
		Vec<num> A(N);
		for (num& v : A) v = rng.uniform<i64>(0, mod-1);

		int S = std::bit_ceil<u32>(N);
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
	retromorphic_test_single<ModInt<998244353>>();
	retromorphic_test_single<ModInt<1053818881>>();
}
