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

#include "binary_tree.hpp"
#include "bst.hpp"

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

		using std::cout;

		auto printF = [](BinaryTreeNode* node)->bool
		{
			cout << node->data_ << ", ";
			return true;
		};

		auto maxval = FindMaxValue(btree);
		cout << "maxval: " << maxval << endl;

		cout << "Levelorder\n";
		btree.Traverse(TraverseOrder::Levelorder, printF);

		btree.Remove(1);

		cout << "Levelorder\n";
		btree.Traverse(TraverseOrder::Levelorder, printF);

		btree.Remove(9);

		//		cout << "preorder\n";
		//		btree.Traverse(TraverseOrder::Preorder, printF);
		//
		//		cout << "Inorder\n";
		//		btree.Traverse(TraverseOrder::Inorder, printF);

		cout << "Levelorder\n";
		btree.Traverse(TraverseOrder::Levelorder, printF);

		auto maxval2 = FindMaxValueNonRecursive(btree);
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

int main(int argc, const char * argv[])
{
	TestBST();

    return 0;
}
