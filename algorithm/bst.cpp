//
//  bst.cpp
//  algorithm
//
//  Created by 신일환 on 2016. 6. 26..
//  Copyright © 2016년 acoross. All rights reserved.
//

#include <stdio.h>

#include "bst.hpp"

namespace bst{
	using namespace bintree;
	
	static BSTNodeSP SearchMin(BSTNodeSP root)
	{
		if (!root)
			return nullptr;

		if (root->left_)
			return SearchMin(root->left_);

		return root;
	}

	static BSTNodeSP SearchMax(BSTNodeSP root)
	{
		if (!root)
			return nullptr;

		if (root->right_)
			return SearchMax(root->right_);

		return root;
	}

	static BSTNodeSP Search(BSTNodeSP root, int data)
	{
		if (!root)
			return nullptr;

		if (data < root->data_)
		{
			return Search(root->left_, data);
		}
		else if (data > root->data_)
		{
			return Search(root->right_, data);
		}

		return root;
	}

	static BSTNodeSP Insert(BSTNodeSP root, int data)
	{
		if (!root)
			return std::make_shared<BSTNode>(data);

		if (data < root->data_)
		{
			root->left_ = Insert(root->left_, data);
			return root;
		}
		else if (data > root->data_)
		{
			root->right_ =  Insert(root->right_, data);
			return root;
		}

		return root;
	}

	static BSTNodeSP Remove(BSTNodeSP root, int data)
	{
		if (!root)
			return nullptr;

		if (data < root->data_)
		{
			root->left_ = Remove(root->left_, data);
			return root;
		}
		else if (data > root->data_)
		{
			root->right_ = Remove(root->right_, data);
			return root;
		}

		// root 를 삭제하는 경우
		if (is_leaf(root))
			return nullptr;
		else if (!root->left_)
			return root->right_;
		else if (!root->right_)
			return root->left_;

		// root 를 삭제하며, child 가 둘 다 있을 경우
		// left subtree 의 rightmost node 를 찾아서 root 와 바꾸고, rightmost node 제거
		auto terminal = SearchMax(root->left_);
		root->data_ = terminal->data_;
		terminal->data_ = data;

		root->left_ = Remove(root->left_, data);
		return root;
	}

	static void PrintInorderRightToLeft(BSTNodeSP root, int level)
	{
		using namespace std;

		if (!root)
			return;

		PrintInorderRightToLeft(root->left_, level + 1);

		for (int i = 0; i < level; ++i)
			cout << '\t';
		cout << root->data_ << "\n";

		PrintInorderRightToLeft(root->right_, level + 1);
	}

	//////////////////////////////
	//BST

	BSTNodeSP BST::Search(int data)
	{
		return bst::Search(root_, data);
	}

	BSTNodeSP BST::SearchMax()
	{
		return bst::SearchMax(root_);
	}

	BSTNodeSP BST::SearchMin()
	{
		return bst::SearchMin(root_);
	}

	void BST::Insert(int data)
	{
		root_ = bst::Insert(root_, data);
	}

	void BST::Remove(int data)
	{
		root_ = bst::Remove(root_, data);
	}

	void BST::Print()
	{
		std::cout << "BST\n";
		bst::PrintInorderRightToLeft(root_, 0);
	}
}