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
}

#endif /* coding_dojang_hpp */
