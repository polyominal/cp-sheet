#include <catch2/catch_test_macros.hpp>

#include "contest/base.hpp"
#include "contest/fast-input.hpp"
#include "util/random.hpp"

using namespace fast_input;

TEST_CASE("Fast input: not-so-large integers", "[fast-input]") {
	auto rng = Random(20240115);

	const int N = 1234;
	using T = int64_t;
	const T bound = 1e18;
	Vec<T> A(N);
	for (T& a : A) {
		a = rng.uniform<T>(-bound, +bound);
	}

	auto tmpf = tmpfile();
	for (T a : A) {
		auto t = to_string(a) + "\n";
		fputs(t.c_str(), tmpf);
	}
	rewind(tmpf);

	auto sc = Scanner(tmpf);
	for (T a : A) {
		T v;
		sc.read(v);
		REQUIRE(a == v);
	}
}

TEST_CASE("Fast input: sequence of alphabetic strings", "[fast-input]") {
	auto rng = Random(20240115);

	const int N = 1234;
	using T = string;
	Vec<T> A(N);
	for (T& a : A) {
		int len = rng.uniform(1, 100);
		for (int i = 0; i < len; i++) {
			int x = rng.uniform(0, 51);
			char c;
			if (x < 26) {
				c = char('A' + x);
			} else {
				x -= 26;
				c = char('a' + x);
			}
			REQUIRE(isalpha(c));
			a += c;
		}
	}

	auto tmpf = tmpfile();
	for (T a : A) {
		auto t = a + "\n";
		fputs(t.c_str(), tmpf);
	}
	rewind(tmpf);

	auto sc = Scanner(tmpf);
	for (T a : A) {
		T v;
		sc.read(v);
		REQUIRE(a == v);
	}
}

TEST_CASE("Fast input: float string", "[fast-input]") {
	auto tmpf = tmpfile();
	fputs("12345.678", tmpf);
	rewind(tmpf);

	Scanner sc(tmpf);
	string r;
	sc.read(r);
	REQUIRE(r == "12345.678");
}

TEST_CASE("Fast input: doubles", "[fast-input]") {
	auto tmpf = tmpfile();
	fputs("12345.678", tmpf);
	rewind(tmpf);

	Scanner sc(tmpf);
	double r;
	sc.read(r);
	REQUIRE(abs(r - 12345.678) < double(1e-9));
}