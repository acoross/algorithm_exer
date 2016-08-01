//
//  crack_coding_interview.cpp
//  algorithm
//
//  Created by 신일환 on 2016. 7. 29..
//  Copyright © 2016년 acoross. All rights reserved.
//

#include "crack_interview_ch1.hpp"

#include <iostream>

namespace crack_coding_interview {
	namespace ch_1_array_string {

		void Q1_1() {
			/* 1.1 문자열에 포함된 문자들이 전부 유일한지를 검사하는 알고리즘을 구현하라. 
			 다른 자료구조를 사용할 수 없는 상황이라면 어떻게 하겠는가? */

			class StringCheckerForUniqueChar {
			public:
				StringCheckerForUniqueChar(const char* const input)
				: input_(input) {
					for (const char* p = input;
						 p != nullptr && *p != '\0';
						 ++p) {
						if (++counts_[(int)(*p)] > 1) {
							is_unique_ = false;
							first_not_unique_ = *p;
						}
					}
				}
				bool IsUnique() const {
					return is_unique_;
				}
				char FirstNotUnique() const {
					return first_not_unique_;
				}

			private:
				const char* const input_;
				int counts_[256]{0,};

				bool is_unique_{true};
				char first_not_unique_{'\0'};
			};

			std::string input("abcde12345a~!#");
			StringCheckerForUniqueChar checker(input.c_str());

			if (checker.IsUnique()) {
				std::cout << input.c_str() << ": " << "unique" << std::endl;
			} else {
				std::cout << input.c_str() << ": " << "not unique [" << checker.FirstNotUnique() << "]" << std::endl;
			}
		}

		void Q1_2() {
			/* 1.2 널 문자로 끝나는 문자열을 뒤집는 reverse(char* str) 함수를 C나 C++로 구현하라. */

			class StringReverser {
			public:
				static void Reverse(char* str) {
					// 맨 뒤를 찾고, 맨 앞이랑 하나씩 바꾼다.

					if (str == nullptr) return;

					//find end position
					char* end = nullptr;
					for (end = str; *(end + 1) != '\0'; ++end) {
						;
					}

					//reverse
					char* start = str;
					while (start < end) {
						char tmp = *start;
						*start = *end;
						*end = tmp;

						++start;
						--end;
					}
				}
			};

			char input[] {"hello, acoross"};
			StringReverser::Reverse(input);

			std::cout << input << std::endl;
		}

		void Q1_3() {
			/* 1.3 문자열 두 개를 입력으로 받아 그중 하나가 다른 하나의 순열인지 판별하는 메서드를 작성하라. */

			/* A: 더 짧은 쪽을 가지고, 한칸한칸 이동시키며 패턴매칭... */

			class SubStringChecker {
			public:
				SubStringChecker(const char* const str1, const char* const str2)
				: str1_(str1), str2_(str2), is_sub_string_(-1)
				{
					check();
				}

				// 0: 동일, 1: 1이 2의 sub, 2: 2가 1의 sub
				// -1: 서브스트링이 아님
				int IsSubString() const {
					return is_sub_string_;
				}

			private:
				void check() {
					const int len1 = SubStringChecker::strlen(str1_);
					const int len2 = SubStringChecker::strlen(str2_);

					if (len1 < len2) {
						if (check_sub_string(str2_, str2_))
							is_sub_string_ = 1;
					} else if (len1 > len2) {
						if (check_sub_string(str1_, str2_))
							is_sub_string_ = 2;
					} else {
						if (compare_string(str1_, str2_) == 0)
							is_sub_string_ = 0;
					}
				}

				// null 문자 제외한 크기
				static int strlen(const char* const str) {
					int len = 0;

					const char* p = str;
					while (*p) {
						++len;
						++p;
					}

					return len;
				}

				// sub가 bigger 의 sub-string 이면 return true
				// 아니면 false
				static bool check_sub_string(const char* const bigger, const char* const sub) {
					bool is_sub = false;

					const char* bp = bigger;
					while (*bp) {
						int cp = compare_string(bp, sub);
						if (cp == 0 || cp == 1) return true;
						if (cp == 2) return false;
						++bp;
					}

					return is_sub;
				}

				// 동일하면 0
				// 다르면 -1
				// 1이 더 길면 1
				// 2가 더 길면 2
				static int compare_string(const char* const str1, const char* const str2) {
					auto* p1 = str1;
					auto* p2 = str2;

					for(;;) {
						if (*p1 == '\0' && *p2 == '\0') return 0;
						if (*p1 == '\0') return 2;
						if (*p2 == '\0') return 1;
						if (*p1 != *p2) return -1;

						++p1;
						++p2;
					}

					return -1;
				}


				const char* const str1_;
				const char* const str2_;
				int is_sub_string_ {-1};
			};

			SubStringChecker checker("aaacoro s", "acoro s");
			std::cout << checker.IsSubString() << std::endl;
		}
	}
}