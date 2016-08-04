//
//  crack_interview_ch5.hpp
//  algorithm
//
//  Created by 신일환 on 2016. 8. 3..
//  Copyright © 2016년 acoross. All rights reserved.
//

#ifndef crack_interview_ch5_hpp
#define crack_interview_ch5_hpp

#include <stdio.h>
#include <cassert>
#include <vector>
#include <iostream>

namespace crack_coding_interview {
	namespace ch_5_bit_operation {

		// &: and
		// |: or
		// ^: xor
		// ~: not

		class Q5_1 {
		public:
			/* 두 개의 32비트 수 N과 M이 주어지고, 비트 위치 i와 j가 주어졌을 때,
			 M을 N에 삽입하는 메서드를 구현하라.
			 M은 N의 j번째 비트에서 시작하여 i번째 비트에서 끝나야 한다. */
			static void Test() {
				int N = make_bitint({1,0,0,0,0,0,0,0,0,0,0});
				print_bitint(N);

				int M = make_bitint({1,0,0,1,1});
				print_bitint(M);

				int N2 = insert_bitwise(N, M, 2, 6);
				print_bitint(N2);
			}

			static int make_bitint(std::vector<int> num) {
				int ret = 0;
				for (auto n : num) {
					if (n != 0 && n != 1)
						assert(false);

					ret <<= 1;
					ret |= n;
				}
				return ret;
			}

			static void print_bitint(int bitint) {
				bool started = false;
				for (int i = 31; i >= 0; --i) {
					if ((bitint >> i) & 0x01){
						started = true;
						printf("1");
					} else if (started)
						printf("0");
				}
				printf("(2)\n");
			}

			// i~j 까지 0이고 나머지는 1 인 bit mask
			static int make_mask(int i, int j) {
				int allone = ~0;
				int mask = allone << (j + 1);
				mask |= ((1 << i) - 1);
				return mask;
			}

			static int insert_bitwise(int N, int M, int i, int j) {
				unsigned mask = make_mask(i, j);
				print_bitint(mask);
				N &= mask;
				M <<= i;
				M &= (~mask);
				N |= M;
				return N;
			}
		};


		class Q5_3 {
		public:
			/* 양의 정수 x 를 이진수로 표현했을 때 1인 비트의 개수가 n 이라고 하자.
			 1인 비트수가 n 인 다른 정수 중 x 보다 작은 것 중 가장 큰 정수와,
			 x 보다 큰 것 중 가장 작은 정수를 찾아다. */

			/* 아래 해법은 틀렸다. 하지만 귀찮으므로 내버려 두겠다. */

			static void Test() {
				int x = Q5_1::make_bitint({1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0});
				Q5_1::print_bitint(x);

				int cnt1 = count_1_bit(x);
				std::cout << "count: " << cnt1 << std::endl;

				int x_max_smaller = max_of_smaller(x);
				Q5_1::print_bitint(x_max_smaller);

				int cnt2 = count_1_bit(x_max_smaller);
				std::cout << "count: " << cnt2 << std::endl;

				int x_min_bigger = min_of_bigger(x);
				Q5_1::print_bitint(x_min_bigger);

				int cnt3 = count_1_bit(x_min_bigger);
				std::cout << "count: " << cnt3 << std::endl;
			}

			static int count_1_bit(int x) {
				int n = 0;
				for (int i = 0; i < 32; ++i) {
					if (x & 0x01) ++n;
					x >>= 1;
				}
				return n;
			}

			static int find_max_0(int x) {
				bool started = false;
				for (int i = 31; i >= 0; --i) {
					if ((x >> i) & 0x01)
						started = true;
					else if (started && !(x & 0x01))
						return i;
				}
				return -1;
			}

			static int find_min_0(int x) {
				for (int i = 0; i < 32; ++i) {
					if (!(x & 0x01)) return i;
					x >>= 1;
				}
				return 32;
			}

			static int max_of_smaller(int x) {
				int idx = find_max_0(x);
				int ret = x;
				ret &= ~(1 << (idx + 1));
				ret |= (1 << idx);
				return ret;
			}

			static int min_of_bigger(int x) {
				int idx = find_min_0(x);
				int ret = x;
				ret &= ~(1 << (idx - 1));
				ret |= (1 << idx);
				return ret;
			}
		};

		class Q5_5 {
		public:
			/* 정수 A를 B로 변환하기 위해 바꿔야 하는 비트 개수를 계산하는 함수를 작성하라. 
				-> A와 B 간에 다른 비트들의 수를 센다.
			*/

			static int count_different_bits(int A, int B) {
				int x = A ^ B;

				return Q5_3::count_1_bit(x);
			}

		};

		class Q5_8 {
			/* 흑백 모니터 */

		public:
			// 이 함수는 (x1, y) 에서 (x2, y) 로 수평선을 긋는다.
			static void drawHorizontalLine(std::vector<char>& screen, int width, int x1, int x2, int y) {
				int idx_for_y = width / 8 * y;
				int idx_for_x1 = x1 / 8;
				int idx_for_x2 = x2 / 8;

				for (int i = idx_for_y + idx_for_x1 + 1; i <= idx_for_y + idx_for_x2; ++i) {
					screen[i] = 1;
				}


			}
		};
	}
}
#endif /* crack_interview_ch5_hpp */