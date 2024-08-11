#include "util/random.hpp"
#include "contest/base.hpp"
#include "gtest/gtest.h"

class TestRandom : public ::testing::Test {
protected:
	Random rng;
	TestRandom() : rng(20240107) {}
};

TEST_F(TestRandom, TestUniform) {
	for (int z = 0; z < 123; z++) {
		int x = rng.uniform(0, 123);
		EXPECT_GE(x, 0);
		EXPECT_LE(x, 123);
	}
}

TEST_F(TestRandom, TestLowercaseString) {
	for (int z = 0; z < 123; z++) {
		std::string s = rng.lowercase_string(123);
		EXPECT_EQ(ssize(s), 123);
		for (char c : s) {
			assert(std::islower(c));
		}
	}
}

TEST_F(TestRandom, TestUppercaseString) {
	for (int z = 0; z < 123; z++) {
		std::string s = rng.uppercase_string(123);
		EXPECT_EQ(ssize(s), 123);
		for (char c : s) {
			assert(std::isupper(c));
		}
	}
}

TEST_F(TestRandom, TestShuffle) {
	for (int z = 0; z < 123; z++) {
		const int n = rng.uniform(0, 123);
		auto v = Vec<int>();
		v.reserve(n);
		for (int i = 0; i < n; i++) {
			v.push_back(rng.uniform(0, 10));
		}
		auto v_shuffled = v;
		rng.shuffle(begin(v), end(v));

		// Compare the multisets of the two vectors
		std::ranges::sort(v);
		std::ranges::sort(v_shuffled);
		EXPECT_EQ(v, v_shuffled);
	}
}

TEST_F(TestRandom, TestSample) {
	for (int z = 0; z < 123; z++) {
		// Sample m elements from 0, ..., n
		const int n = rng.uniform(0, 123);
		const int m = rng.uniform(0, n + 1);
		auto samp = rng.sample(m, 0, n);
		auto samp_set = std::set<int>(begin(samp), end(samp));
		EXPECT_EQ(ssize(samp_set), m);
	}
}
