//
//  coding_dojang.hpp
//  algorithm
//
//  Created by 신일환 on 2016. 8. 2..
//  Copyright © 2016년 acoross. All rights reserved.
//

#ifndef coding_dojang_hpp
#define coding_dojang_hpp

#include <stdio.h>

#include <array>
#include <iostream>
#include <string>
#include <map>
#include <set>

namespace coding_dojang {

	class MinusPlusSorter {
	public:
		static void Run() {
			std::array<int, 9> arr{1, 2, -1, 0, -2, 0, 4, 5, -3};

			std::cout << "before\n";
			for (auto& i : arr) {
				std::cout << i << ", ";
			}
			std::cout << std::endl;

			Sort(arr);

			std::cout << "after\n";
			for (auto& i : arr) {
				std::cout << i << ", ";
			}
			std::cout << std::endl;
		}

		template <size_t Siz>
		static void Sort(std::array<int, Siz>& arr) {
			// pivot 숫자를 0으로 설정하고 quicksort 의 좌우정렬을 실행.

			// 일단 0을 오른쪽 끝에 모두 몰아 넣는다.
			for (int i = 0, j = 1; i < Siz; ++i) {
				if (arr[i] == 0) {
					swap(arr, i, Siz-j);
					++j;
				}
			}

			int stored = 0;
			for (int i = 0; i < Siz; ++i) {
				if (arr[i] <= 0) {
					swap(arr, i, stored++);
				}
			}
		}

	private:
		template <size_t Siz>
		static void swap(std::array<int, Siz>& arr, size_t i1, size_t i2) {
			int tmp = arr[i1];
			arr[i1] = arr[i2];
			arr[i2] = tmp;
		}
	};

	namespace k_palindrome {

		class KPalindromeChecker {
		public:
			KPalindromeChecker(const std::string& str, int k)
			: str_(str), is_k_palindrome_(false) {
				if (!breif_check_can_be_palindrome(k))
					return;
				if (str_.size() > 20000)
					return;
				if (k > 30)
					return;

				is_k_palindrome_ = is_k_palindrome(k, 0, (int)str_.size() - 1);
			}

			bool is_k_palindrome() const {
				return is_k_palindrome_;
			}

			void print_stat() {
				std::cout << "size: " << cache_.Size() << std::endl;
				std::cout << "op_count: " << op_count_ << std::endl;
			}

		private:
			class KPalindromeCache {
			public:
				bool IsCached(int s, int e) const {
					if (cache_.find(std::make_pair(s, e)) != cache_.end())
						return true;

					return false;
				}

				void SetCache(int s, int e) {
					cache_.insert(std::make_pair(s, e));
				}

				int Size() const {
					return (int)cache_.size();
				}

			private:
				using IsPalindromeSet = std::set<std::pair<int, int>>;
				IsPalindromeSet cache_;
			};

			// s: 시작 인덱스
			// e: 마지막 인덱스 (null terminating 빼고)
			bool is_k_palindrome(int k, int s, int e) {
				if (k < 0)
					return false;
				if (s >= e)
					return false;
				if (cache_.IsCached(s, e))
					return false;

				++op_count_;

				const char* const c_str = str_.c_str();
				while (c_str[s] == c_str[e]) {
					++s;
					--e;
					if (s >= e)
						return true;
				}

				if(is_k_palindrome(k - 1, s + 1, e))
					return true;
				if (is_k_palindrome(k - 1, s, e - 1))
					return true;

				cache_.SetCache(s, e);
				return false;
			}

			// 미리 한 번 글자 수로 조건 체크.
			bool breif_check_can_be_palindrome(int k) const {
				std::array<int, 256> counts{0,};

				const char* const c_str = str_.c_str();
				for (int i = 0; i < str_.size(); ++i) {
					++counts[c_str[i]];
				}

				int count_odd = 0;
				for (int i = 0; i < 256; ++i) {
					if (counts[i] & 0x01)
						++count_odd;
				}

				if (count_odd > k)
					return false;

				return true;
			}

			const std::string& str_;
			bool is_k_palindrome_{false};
			KPalindromeCache cache_;
			int op_count_{0};
		};

		static inline void run_k_palindrome_check(const std::string& str, int k) {
			std::cout << str.c_str() << ", " << k << ": ";

			KPalindromeChecker checker(str, k);
			if (checker.is_k_palindrome())
				std::cout << "true\n";
			else
				std::cout << "false\n";

			checker.print_stat();
		}

		inline void Test() {
			run_k_palindrome_check("abxa", 1);
			run_k_palindrome_check("0123456789012345678 abaabaabaabaabaabaabaabaabaabaabaabaabaabaabaaba 0123456789012345678", 30);
		}
	}// namespace k_palindrome
}

#endif /* coding_dojang_hpp */
