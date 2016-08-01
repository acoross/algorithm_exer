//
//  crack_interview_ch2.hpp
//  algorithm
//
//  Created by 신일환 on 2016. 8. 1..
//  Copyright © 2016년 acoross. All rights reserved.
//

#ifndef crack_interview_ch2_hpp
#define crack_interview_ch2_hpp

#include <stdio.h>
#include <iostream>
#include <list>

namespace crack_coding_interview {
	namespace ch_2_linked_list {

		class Q2_5 {
			/* 연결 리스트로 표현된 두 개의 수가 있다고 하자. 리스트의 각 노드는 해당 수의 각 자릿수를 표현한다.
			 이때 자릿수들은 역순으로 배열되는데, 1의 자릿수가 리스트의 맨 앞에 오도록 배열된다는 뜻이다.
			 이 두 수를 더하여 그 합을 연결 리스트로 반환하는 함수를 작성하라.
			 예
			 입력: (7->1->6) + (5->9->2) 즉 617 + 295.
			 출력: 2->1->9. 즉 912.
			 */

		public:
			using List = std::list<int>;

			static void Run() {
				std::list<int> l1;
				l1.push_back(7);
				l1.push_back(1);
				l1.push_back(6);

				std::list<int> l2;
				l2.push_back(5);
				l2.push_back(9);
				l2.push_back(2);

				auto l3 = list_adder(l1, l2);
				print(l3);
			}

			static void RunDash() {
				/* 리스트가 정상 순서대로 배열되어있다고 가정. */

				std::list<int> l1;
				l1.push_back(6);
				l1.push_back(1);
				l1.push_back(7);

				std::list<int> l2;
				l2.push_back(2);
				l2.push_back(9);
				l2.push_back(5);

				auto l3 = list_adder_dash(l1, l2);
				print(l3);
			}

		private:
			static List list_adder(List l1, List l2) {
				std::list<int> ret;

				int add = 0;
				auto it1 = l1.begin();
				auto it2 = l2.begin();

				for (;;) {
					if (it1 == l1.end() && it2 == l2.end())
						break;

					int i1 = 0, i2 = 0;

					if (it1 != l1.end()) {
						i1 = *it1;
						++it1;
					}
					if (it2 != l2.end()) {
						i2 = *it2;
						++it2;
					}

					int n = i1 + i2 + add;
					ret.push_back(n % 10);

					add = n / 10;
				}
				
				return ret;
			}

			static List list_adder_dash(List l1, List l2) {
				int n1 = 0;
				for (auto& n : l1) {
					n1 = n1 * 10 + n;
				}

				int n2 = 0;
				for (auto& n : l2) {
					n2 = n2 * 10 + n;
				}

				//////
				std::list<int> ret;
				for (int n3 = n1 + n2; n3 > 0; n3 /= 10) {
					ret.push_back(n3 % 10);
				}

				return ret;
			};

			static void print(List& lst) {
				for (auto it = lst.begin(); it != lst.end(); ++it) {
					std::cout << *it << "<-";
				}
				std::cout << std::endl;
			}
		};
	}
}

#endif /* crack_interview_ch2_hpp */
