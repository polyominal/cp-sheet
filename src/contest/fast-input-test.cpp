#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <contest/base.hpp>
#include <contest/fast-input.hpp>
#include <util/random.hpp>

using namespace fast_input;

TEST(FastInputTest, ThreeIntegers) {
	auto rng = Random(20240822);

	auto tmpf = tmpfile();
	auto A = Vec<int>();
	for (int z = 0; z < 3; z++) {
		int a = rng.uniform<int>(-1234, +1234);
		A.push_back(a);
		auto t = std::to_string(a) + "\n";
		fputs(t.c_str(), tmpf);
	}
	rewind(tmpf);

	Scanner sc(tmpf);
	int x, y, z;
	sc >> x >> y >> z;
	EXPECT_THAT(A, testing::ElementsAre(x, y, z));
}

TEST(FastInputTest, Integers) {
	auto rng = Random(20240115);

	constexpr int N = 1234;
	using T = int64_t;
	const T bound = 1e18;
	Vec<T> A(N);
	for (T& a : A) {
		a = rng.uniform<T>(-bound, +bound);
	}

	auto tmpf = tmpfile();
	for (T a : A) {
		auto t = std::to_string(a) + "\n";
		fputs(t.c_str(), tmpf);
	}
	rewind(tmpf);

	auto sc = Scanner(tmpf);
	for (T a : A) {
		T v;
		sc >> v;
		EXPECT_EQ(a, v);
	}
}

TEST(FastInputTest, AlphabeticStrings) {
	auto rng = Random(20240115);

	constexpr int N = 1234;
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
			EXPECT_TRUE(isalpha(c));
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
		sc >> v;
		EXPECT_EQ(a, v);
	}
}

TEST(FastInputTest, FloatStrings) {
	auto tmpf = tmpfile();
	fputs("12345.678", tmpf);
	rewind(tmpf);

	Scanner sc(tmpf);
	string r;
	sc >> r;
	EXPECT_EQ(r, "12345.678");
}

TEST(FastInputTest, Doubles) {
	auto tmpf = tmpfile();
	fputs("12345.678", tmpf);
	rewind(tmpf);

	Scanner sc(tmpf);
	double r;
	sc >> r;
	EXPECT_TRUE(std::abs(r - 12345.678) < double(1e-9));
}