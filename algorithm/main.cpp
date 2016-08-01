//
//  main.cpp
//  algorithm
//
//  Created by 신일환 on 2016. 6. 23..
//  Copyright © 2016년 acoross. All rights reserved.
//

#include <iostream>
#include <memory>
#include <random>
#include <time.h>
#include <vector>

#include "binary_tree.hpp"
#include "bst.hpp"
#include "avl_tree.hpp"

#define _RB_DEBUG_
#include "red_black_tree.hpp"

#include "count_num_under_1000.hpp"

#include "crack_interview_ch1.hpp"
#include "crack_interview_ch2.hpp"
#include "crack_interview_ch3.hpp"

void TestBinaryTree()
{
	using namespace std;
	using namespace bintree;

	try
	{
		BinaryTree btree;

		for (int i = 0; i < 14; ++i)
		{
			btree.Insert(i);
		}

		auto cb = [](BinaryNode* node)->bool
		{
			cout << node->data_ << ", ";
			if (node->data_ == 3)
				return false;
			return true;
		};
		btree.Traverse(TraverseOrder::Preorder, cb);

		using std::cout;

		auto printF = [](BinaryNode* node)->bool
		{
			cout << node->data_ << ", ";
			return true;
		};

		auto maxval = btree.FindMaxValue();
		cout << "maxval: " << maxval << endl;

		cout << "Levelorder\n";
		btree.Traverse(TraverseOrder::Levelorder, printF);

		btree.Remove(1);

		cout << "Levelorder\n";
		btree.Traverse(TraverseOrder::Levelorder, printF);

		btree.Remove(9);

		cout << "Levelorder\n";
		btree.Traverse(TraverseOrder::Levelorder, printF);

		auto maxval2 = btree.FindMaxValueNonRecursive();
		cout << "maxval2: " << maxval2 << endl;
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

void TestBST()
{
	try
	{
		bst::BST bstree;
		bstree.Insert(0);
		bstree.Remove(0);
		bstree.Print();

		bstree.Insert(6);

		std::vector<int> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

		std::default_random_engine re((unsigned)time(nullptr));
		std::shuffle(arr.begin(), arr.end(), re);

		for (int i = 0; i < 14; ++i)
		{
			bstree.Insert(arr[i]);
		}

		bstree.PrintNonrecur();
		bstree.Print();

		for (int i = 7; i >= 0; --i)
		{
			bstree.Remove(i);

			std::cout << std::endl;
			bstree.Print();
		}

	}
	catch (std::exception& ex)
	{
		std::cout << ex.what();
	}
}

void TestAvl()
{
	avl::AvlTree avltree;

	//std::vector<int> arr = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
//	std::vector<int> arr = {8, 5, 9, 3, 6, 7};
	//std::vector<int> arr = {4, 2, 7, 8, 6, 5};
	std::vector<int> arr;
	arr.reserve(100);
	for (int i = 0; i < 100; ++i)
		arr.push_back(i);

	{
		std::default_random_engine re((unsigned)time(nullptr));
		std::shuffle(arr.begin(), arr.end(), re);
	}

	int i = 0;
	for (auto& n : arr)
	{
		++i;
		avltree.Insert(n);
//		if (i % 10 == 0)
//			avltree.PrintWithFormat();
	}

	avltree.PrintWithFormat();

	for (;;)
	{
		char cmd = 0;
		int val = 0;
		printf("enter:\n");
		scanf("%1c %d", &cmd, &val);
		printf("input: %c %d\n", cmd, val);
		switch (cmd)
		{
			case 'l':
			{
				avltree.RotateLL(val);
				break;
			}
			case 'r':
			{
				avltree.RotateRR(val);
				break;
			}
			case 'i':
			{
				avltree.Insert(val);
				break;
			}
			case 'd':
			{
				avltree.Remove(val);
				break;
			}
			default:
			{
				continue;
			}
		}

		avltree.PrintWithFormat();
	}
}

void RedBlack()
{
	using namespace redblacktree;
	RedBlackBST tree;

	//char arr[] = "EASYQUTION";
	//char arr[] = "YLPMXHCRAES";
	//char arr[] = "ASERCHXM";

	for (int i = 0; i < 10; ++i)
	{
		tree.InsertAs23tree(i);
	}

	std::cout << "print tree\n";
	tree.PrintInside();
	std::cout << std::endl;

	//tree.debugPrintOn = true;
	for (int i = 9; i >= 0; --i)
	{
		//tree.RemoveMax();
		tree.Remove(i);
		std::cout << "print " << i << "\n";
		tree.PrintInside();
		std::cout << "depth: " << tree.CountRedblackDepth() << std::endl;
		std::cout << std::endl;
	}
}

void CodingDojangQuiz()
{
//	CodingDojang::CountNumberUnder1000::Run();
//	CodingDojang::SumMultiplyDivededNumbersUnder1000::Run();

//	CodingDojang::TabToSpaceChanger::Run(
//R"(	for (int i = 9; i >= 0; --i)
//	 {
//		 //tree.RemoveMax();
//		 tree.Remove(i);
//		 std::cout << "print " << i << "\n";
//		 tree.PrintInside();
//		 std::cout << "depth: " << tree.CountRedblackDepth() << std::endl;
//		 std::cout << std::endl;
//	 }
//)"
//	);

	//CodingDojang::BoardPager::Test();

	//CodingDojang::Sum3or5::Run();

	//CodingDojang::SelfNumberFinder::Run();

	//CodingDojang::All8Counter::Run();

	//CodingDojang::ShortestDistPairFinder::Run();

	//CodingDojang::SpiralArrayPrinter::Run();

	//CodingDojang::StringCompressorTest::Run();
}

void CrackInterview() {
	using namespace crack_coding_interview;

//	ch_1_array_string::Q1_1();
//	ch_1_array_string::Q1_2();
//	ch_1_array_string::Q1_3();

//	ch_2_linked_list::Q2_5::Run();
//	ch_2_linked_list::Q2_5::RunDash();

//	ch_3_stack_queue::Q3_1::Run();
	ch_3_stack_queue::Q3_4::Run();
}

int main(int argc, const char * argv[])
{
	//TestBST();
	//TestBinaryTree();
	//TestAvl();
	//RedBlack();
	//CodingDojangQuiz();

	CrackInterview();

    return 0;
}
