//
//  crack_coding_interview.hpp
//  algorithm
//
//  Created by 신일환 on 2016. 8. 4..
//  Copyright © 2016년 acoross. All rights reserved.
//

#ifndef crack_interview_ch9_hpp
#define crack_interview_ch9_hpp

#include <stdio.h>
#include <iostream>
#include <list>
#include <map>
#include <vector>

namespace crack_coding_interview {
	namespace ch_9_recursion_dynamic {

		class Q9_2 {
		public:
			static void Test() {

			}

			using Route = std::list<std::pair<int, int>>;

			static int count_route(int sx, int sy, int ex, int ey) {
				if (sx > ex || sy > ey)
					return 0;

				if ((sx == ex && sy + 1 == ex) ||
					(sx + 1 == ex && sy == ex)) {
					return 1;
				}

				int count = count_route(sx + 1, sy, ex, ey);
				count += count_route(sx, sy + 1, ex, ey);

				return count;
			}

			static Route find_route(int** map, int sx, int sy, int ex, int ey) {
				if (sx > ex || sy > ey)
					return Route();

				if (map[sx][sy] == 1) // blocked.
					return Route();	// cannot enter here.

				if ((sx == ex && sy + 1 == ex) ||
					(sx + 1 == ex && sy == ex)) {
					Route ret;
					ret.emplace_back(std::make_pair(ex, ey));
					return ret;
				}

				auto route = find_route(map, sx + 1, sy, ex, ey);
				if (route.size() > 0) {
					return route;
				} else {
					auto route2 = find_route(map, sx, sy + 1, ex, ey);
					return route;
				}
			}
		};

		class Q9_3 {
		public:
			static void Test() {
				std::vector<int> arr;
				for (int i = 0; i < 10; ++i) {
					arr.push_back(3 * (i - 4) + 4);
				}

				int idx = find_magic_index(arr, 0, (int)arr.size() - 1);
				std::cout << "idx: " << idx << std::endl;
			}

			// 배열에 중복된 값 없는 경우
			static int find_magic_index(std::vector<int>& arr, int s, int e) {
				if (s > e) return -1;

				// 범위 내에 magic_index 없음.
				if (arr[s] > e) return -1;
				if (arr[e] < s) return -1;

				int m = (s + e) / 2;

				if (arr[m] == m)
					return m;

				int i1 = find_magic_index(arr, s, m);
				if (i1 > -1)
					return i1;

				return find_magic_index(arr, m + 1, e);
			}

			// 배열에 중복 있는 경우?
		};
	}
}

#endif /* crack_interview_ch9_hpp */
