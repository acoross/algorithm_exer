//
//  count_num_under_1000.hpp
//  algorithm
//
//  Created by 신일환 on 2016. 7. 25..
//  Copyright © 2016년 acoross. All rights reserved.
//

#ifndef count_num_under_1000_hpp
#define count_num_under_1000_hpp

#include <iostream>
#include <chrono>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits>
#include <memory>

namespace CodingDojang {

	class CountNumberUnder1000 {
	public:
		class Counter {
		public:
			Counter()
			: counts_(10, 0){}

			void Accumulate(int num) {
				if (num <= 0)
					return;

				int mod = num % 10;
				++counts_[mod];

				Accumulate(num/10);
			}

			const std::vector<int>& GetCounts() const
			{
				return counts_;
			}

		private:
			// 0-9 counts
			std::vector<int> counts_;
		};

	public:
		static void Run() {
			Counter cnter;
			for (int i = 1; i <= 1000; ++i) {
				cnter.Accumulate(i);
			}

			auto& cnt = cnter.GetCounts();
			for (int i = 0; i < 10; ++i) {
				std::cout << i << ": " << cnt[i] << std::endl;
			}
		}
	};

	class SumMultiplyDivededNumbersUnder1000 {
	public:
		static void Run() {
			int sum = 0;
			for (int i = 10; i <= 1000; ++i) {
				sum += MultiplyDiveded(i);
			}

			std::cout << "SumMultiplyDivededNumbersUnder1000: " << sum << std::endl;
		}

	private:
		static int MultiplyDiveded(int num) {
			int multiply = 1;
			do {
				int remainder = num % 10;
				if (remainder == 0)
					return 0;

				num = num / 10;
				multiply *= remainder;
			} while (num > 0);

			return multiply;
		}
	};

	class TabToSpaceChanger {
	public:
		static void Run(std::string code) {
			std::cout << "original: \n" << code.c_str() << "//end\n";

			std::vector<char> buf(code.length() * 2);

			int i = 0;
			auto* p = code.c_str();
			while (p && *p != '\0') {
				if (*p == '\t') {
					buf[i] = ' ';
					buf[i + 1] = ' ';
					buf[i + 2] = ' ';
					buf[i + 3] = ' ';
					i += 3;
				} else {
					buf[i] = *p;
				}
				++i;
				++p;
			}

			std::string copied(buf.data());
			std::cout << "tab to space: \n" << copied.c_str() << "//end\n";
		}
	};

	class BoardPager {
	public:
		static void Test() {
			std::vector<int> articles_list{0, 1, 2, 1, 10, 11};
			std::vector<unsigned> n_per_pages_list{1, 1, 1, 10, 10, 10};

			for (int i = 0; i < 6; ++i) {
				int pages = CalcPages(articles_list[i], n_per_pages_list[i]);

				std::cout << articles_list[i] << ", " << n_per_pages_list[i]
					<< ": " << pages << std::endl;
			}
		}

		static int CalcPages(int articles, unsigned int n_per_pages) {
			if (n_per_pages == 0)
				return 0;

			return Ceil(articles, n_per_pages);
		}

	private:
		static int Ceil(int n, int m) {
			// overflow 위험이 있다...
			return (n + m - 1) / m;
		}
	};

	class Sum3or5 {
	public:
		static void Run() {
			auto last = std::chrono::system_clock::now();
			for (int i = 0; i < 100000; ++i) {
				int sum1 = sum_all_3_5_under_1(1000);
				//std::cout << "sum1: " << sum1 << std::endl;
			}
			auto current = std::chrono::system_clock::now();
			auto sum_time = (current - last);
			std::cout << "method1 time: " << sum_time.count() << std::endl;

			last = std::chrono::system_clock::now();
			for (int i = 0; i < 100000; ++i) {
				int sum2 = sum_all_3_5_under_2(1000);
				//std::cout << "sum2: " << sum2 << std::endl;
			}
			current = std::chrono::system_clock::now();
			sum_time = (current - last);
			std::cout << "method2 time: " << sum_time.count() << std::endl;
		}

	private:
		static int sum_all_3_5_under_1(int n) {
			int sum = 0;
			for(int i = 0;;++i) {
				int m = i * 3;
				if (m > n)
					break;
				sum += m;
			}

			for (int i = 0;;++i) {
				if (i % 3 == 0)
					continue;
				int m = i * 5;
				if (m > n)
					break;
				sum += m;
			}

			return sum;
		}

		static int sum_all_3_5_under_2(int n) {
			int sum = 0;
			for (int i = 0; i <= n; ++i) {
				if (i % 3 == 0 || i % 5 == 0) {
					sum += i;
				}
			}
			return sum;
		}
	};

	class SelfNumberFinder {
	public:
		static void Run() {
			int sum = calculate(5000);
			std::cout << "sum: " << sum << std::endl;
		}

	private:
		static int calculate(int limit) {
			std::vector<int> cnt_generator(limit, 0);

			for (int i = 0; i < cnt_generator.size(); ++i) {
				int dn = generate(i);
				if (dn < cnt_generator.size())
					++cnt_generator[dn];
			}

			int sum = 0;
			for (int i = 0; i < cnt_generator.size(); ++i) {
				if (cnt_generator[i] == 0) sum += i;
			}
			return sum;
		}

		static int generate(int n) {
			int sum = n;
			for (;;) {
				if (n <= 0)
					break;
				int remainder = n % 10;
				sum += remainder;
				n = n / 10;
			}
			return sum;
		}
	};

	class All8Counter {
	public:
		static void Run() {
			// 1부터 10,000까지 8이라는 숫자가 총 몇번 나오는가?
			int sum = 0;
			for (int i = 1; i <= 10000; ++i) {
				sum += count8in(i);
			}

			std::cout << "count 8 in 1 to 10000: " << sum << std::endl;
		}

	private:
		static int count8in(int n) {
			int cnt = 0;
			for (;;) {
				if (n <= 0) break;

				int remainder = n % 10;
				if (remainder == 8) ++cnt;
				n = n / 10;
			}
			return cnt;
		}
	};

	class ShortestDistPairFinder {
	public:
		static void Run() {
			//1차원의 점들이 주어졌을 때, 그 중 가장 거리가 짧은 것의 쌍을 출력하는 함수를 작성하시오. (단 점들의 배열은 모두 정렬되어있다고 가정한다.)

			// !!!!!!!!!!!!!!!!!!!!!!
			// -> 가정으로부터, 인접한 쌍 이외의 것은 조사할 필요가 없어짐.

			std::vector<int> points{1, 3, 4, 8, 13, 17, 20};
			auto ret = find_shortest_dist_pair_from_sorted(points);

			std::cout << "points: " << ret.first << ", " << ret.second << std::endl;
		}

	private:
		static std::pair<int, int> find_shortest_dist_pair_from_sorted(const std::vector<int>& points) {
			int mindist = std::numeric_limits<int>::max();
			std::pair<int, int> ret(0, 0);
			for (int i = 0; i < points.size() - 1; ++i) {
				int dist = points[i + 1] - points[i];
				if (dist < mindist) {
					mindist = dist;
					ret = std::make_pair(points[i], points[i+1]);
				}
			}
			return ret;
		}
	};

	class SpiralArrayPrinter {
	public:
		/*
		 문제는 다음과 같다:

		 6 6

		 0   1   2   3   4   5
		 19  20  21  22  23   6
		 18  31  32  33  24   7
		 17  30  35  34  25   8
		 16  29  28  27  26   9
		 15  14  13  12  11  10
		 위처럼 6 6이라는 입력을 주면 6 X 6 매트릭스에 나선형 회전을 한 값을 출력해야 한다.
		 */
		static void Run() {

			const int rsiz = 6;
			const int csiz = 6;

			std::vector<std::vector<int>> matrix;
			for (int i = 0; i < rsiz; ++i) {
				matrix.push_back(std::vector<int>(csiz, 0));
			}

			MatrixWrapper wrap(matrix, 0, 0, rsiz - 1, csiz - 1);
			wrap.Fill(0);

			for (int r = 0; r < rsiz; ++r) {
				for (int c = 0; c < csiz; ++c) {
					int val = wrap.Get(r, c);
					std::cout << val << ",\t";
				}
				std::cout << std::endl;
			}
		}

		class MatrixWrapper {
		public:
			MatrixWrapper(std::vector<std::vector<int>>& raw_matrix,
						  int top, int left, int bottom, int right)
			: raw_matrix_(raw_matrix), top_(top), left_(left), bottom_(bottom), right_(right)
			{}

			int Get(int r, int c) {
				return raw_matrix_[left_ + r][top_ + c];
			}

			void Set(int r, int c, int val) {
				raw_matrix_[left_ + r][top_ + c] = val;
			}

			void Fill(int add) {
				int n = add;
				for (int i = 0; i < c_siz(); ++i) {
					Set(0, i, n++);
				}

				for (int i = 1; i < r_siz(); ++i) {
					Set(i, c_siz() - 1, n++);
				}

				for (int i = c_siz() - 2; i >= 0; --i) {
					Set(r_siz() - 1, i, n++);
				}

				for (int i = r_siz() - 2; i >= 1; --i) {
					Set(i, 0, n++);
				}

				auto smaller = CreateSmaller();
				if (smaller){
					smaller->Fill(n);
				}
			}

		private:
			std::shared_ptr<MatrixWrapper> CreateSmaller() {
				if (bottom_ - top_ - 2 > 0 && right_ - left_ - 2 > 0)
					return std::make_shared<MatrixWrapper>(raw_matrix_, top_ + 1, left_ + 1, bottom_ - 1, right_ - 1);
				else
					return nullptr;
			}

			int c_siz() const {
				return right_ - left_ + 1;
			}

			int r_siz() const {
				return bottom_ - top_ + 1;
			}

			std::vector<std::vector<int>>& raw_matrix_;
			const int top_;
			const int left_;
			const int bottom_;
			const int right_;
		};
	};
}

#endif /* count_num_under_1000_hpp */
