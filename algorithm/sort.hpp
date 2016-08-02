//
//  sort.hpp
//  algorithm
//
//  Created by 신일환 on 2016. 8. 2..
//  Copyright © 2016년 acoross. All rights reserved.
//

#ifndef sort_hpp
#define sort_hpp

#include <stdio.h>

#include <vector>
#include <list>
#include <iostream>

namespace sort {

	static void print(std::vector<int>& arr, size_t s, size_t e) {
		for (size_t i = s; i <= e; ++i) {
			std::cout << arr[i] << ", ";
		}
		std::cout << std::endl;
	}

	static void swap(std::vector<int>& arr, size_t i1, size_t i2) {
		int tmp = arr[i1];
		arr[i1] = arr[i2];
		arr[i2] = tmp;
	}

	class QuickSorter {
	public:

		static void Sort(std::vector<int>& arr) {
			print(arr, 0, arr.size() - 1);
			sort(arr, 0, arr.size() - 1);
			print(arr, 0, arr.size() - 1);
		}

	private:
		// s: start index
		// e: end index
		static void sort(std::vector<int>& arr, size_t s, size_t e) {
			if (e - s <= 1) return;

			int pivot = (int)(s + e) / 2;
			swap(arr, pivot, e);

			int stored = 0;
			for (int i = 0; i <= e; ++i) {
				if (arr[i] <= arr[e]) {
					swap(arr, stored, i);
					++stored;
				}
			}

			sort(arr, s, stored - 1);
			sort(arr, stored, e);
		}
	};

	class MergeSorter {
	public:
		static void Sort(std::vector<int>& arr) {
			print(arr, 0, arr.size() - 1);
			sort(arr, 0, arr.size() - 1);
			print(arr, 0, arr.size() - 1);
		}

	private:
		static void sort(std::vector<int>& arr, size_t s, size_t e) {
			if (e - s <= 0) return;

			size_t m = (e + s)/2;
			sort(arr, s, m);
			sort(arr, m + 1, e);
			merge(arr, s, m, e);
		}

		static void merge(std::vector<int>& arr, size_t s, size_t m, size_t e) {
			if (e - s <= 0) return;

			std::vector<int> tmp;

			size_t s1 = s;
			size_t s2 = m + 1;
			while (s1 <= m && s2 <= e) {
				if (arr[s1] < arr[s2]) {
					tmp.push_back(arr[s1++]);
				} else {
					tmp.push_back(arr[s2++]);
				}
			}

			while (s1 <= m) {
				tmp.push_back(arr[s1++]);
			}
			while (s2 <= e) {
				tmp.push_back(arr[s2++]);
			}

			int ti = 0;
			for (size_t i = s; i <= e; ++i) {
				arr[i] = tmp[ti++];
			}
		}


	};

	class BubbleSorter {
	public:
		static void Sort(std::vector<int>& arr) {
			print(arr, 0, arr.size() - 1);
			for (int i = 0; i < arr.size(); ++i) {
				for (int j = 0; j < arr.size() - 1; ++j) {
					if (arr[j] > arr[j + 1])
						swap(arr, j, j + 1);
				}
			}
			print(arr, 0, arr.size() - 1);
		}
	};
}
#endif /* sort_hpp */
