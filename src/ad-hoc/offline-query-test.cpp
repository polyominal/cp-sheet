#include <gtest/gtest.h>
#include <ad-hoc/offline-query.hpp>
#include <util/random.hpp>

namespace testing {

TEST(TestOfflineQuery, XorSum) {
	auto rng = Random(20240920);
	for (int n : {0, 1, 2, 3, 5, 8, 13, 21, 34, 1234}) {
		struct Update {
			int idx;
			u64 timestamp;

			bool operator<(const Update& other) const {
				return timestamp < other.timestamp;
			}
		};
		auto val = Vec<u64>();
		auto updates = Vec<Update>();
		for (int k = 0; k < n; k++) {
			val.push_back(rng.uniform<u64>(0, std::numeric_limits<u64>::max()));
			u64 timestamp_open =
				rng.uniform<u64>(0, std::numeric_limits<u64>::max());
			u64 timestamp_close =
				rng.uniform<u64>(0, std::numeric_limits<u64>::max());
			if (timestamp_open > timestamp_close) {
				std::swap(timestamp_open, timestamp_close);
			}
			updates.push_back(Update{k, timestamp_open});
			updates.push_back(Update{~k, timestamp_close});
		}

		auto oq = OfflineQuery<u64, u8>();
		auto prv_idx = Vec<int>(n, -1);
		u64 cur_sum_naive = 0;
		auto res_naive = Vec<u64>();
		auto do_query = [&]() -> void {
			oq.ask({});
			res_naive.push_back(cur_sum_naive);
		};
		do_query();
		std::sort(begin(updates), end(updates));
		for (auto [idx, _] : updates) {
			if (idx >= 0) {
				prv_idx[idx] = oq.add(val[idx]);
			} else {
				idx = ~idx;
				assert(prv_idx[idx] != -1);
				oq.del(prv_idx[idx]);
			}
			cur_sum_naive ^= val[idx];
			do_query();
		}

		u64 cur_sum = 0;
		auto res = Vec<u64>();
		auto stk = Vec<u64>();
		oq.exec(
			[&](u64 a) {
				cur_sum ^= a;
				stk.push_back(a);
			},
			[&]() {
				u64 a = stk.back();
				stk.pop_back();
				cur_sum ^= a;
			},
			[&](u8) { res.push_back(cur_sum); });
		EXPECT_EQ(res, res_naive);
	}
}

}  // namespace testing