//
//  binary_tree.cpp
//  algorithm
//
//  Created by 신일환 on 2016. 6. 25..
//  Copyright © 2016년 acoross. All rights reserved.
//

#include "binary_tree.hpp"
#include <iostream>
#include <limits>

namespace bintree{

	// level order traverse 하면서
	// left_ 혹은 right_ 가 nullptr 인 곳을 찾아서
	// 해당 위치에 새 node 삽입한다.
	void BinaryTree::Insert(int data)
	{
		using namespace std;

		queue<shared_ptr<BinaryTreeNode>> q;

		if (!root_)
		{
			root_ = make_shared<BinaryTreeNode>(data);
			return;
		}

		q.push(root_);

		while (!q.empty())
		{
			auto node = q.front();
			q.pop();

			if (!node->left_)
			{
				node->left_ = make_shared<BinaryTreeNode>(data);
				return;
			}
			q.push(node->left_);

			if (!node->right_)
			{
				node->right_ = make_shared<BinaryTreeNode>(data);
				return;
			}
			q.push(node->right_);
		}

		throw std::runtime_error("bintree insert failed");
	}

	// 조건에 맞는 node 를 찾는다.
	// 그 node 를 terminal node 와 위치를 바꾼다.
	// terminal node 를 제거한다.
	void BinaryTree::Remove(int data)
	{
		if (auto node = this->Search(data))
		{
			root_ = BinaryTree::RemoveChild(root_, node);
		}
	}

	BinaryTreeNodeSP BinaryTree::Search(int data)
	{
		using namespace std;

		if (!root_) return nullptr;

		queue<shared_ptr<BinaryTreeNode>> q;
		q.push(root_);

		auto node = root_;

		while (!q.empty())
		{
			node = q.front();
			q.pop();

			if (node->left_) q.push(node->left_);
			if (node->right_) q.push(node->right_);

			if (node->data_ == data)
				return node;
		}

		return nullptr;
	}

	int BinaryTree::FindMaxValue()
	{
		class MaxFinder
		{
		public:
			bool operator()(BinaryTreeNode* node)
			{
				if (node->data_ > max)
					max = node->data_;

				return true;
			}

			int max{std::numeric_limits<int>::min()};
		};
		auto f = MaxFinder();

		preorder(root_, f);
		return f.max;
	}

	int BinaryTree::FindMaxValueNonRecursive()
	{
		class MaxFinder
		{
		public:
			bool operator()(BinaryTreeNode* node)
			{
				if (node->data_ > max)
					max = node->data_;

				return true;
			}

			int max{std::numeric_limits<int>::min()};
		};
		auto f = MaxFinder();

		level_order_traverse(root_, f);
		return f.max;
	}

	////////////////////////////////////
	// static

	BinaryTreeNodeSP BinaryTree::RemoveChild(BinaryTreeNodeSP root, BinaryTreeNodeSP node)
	{
		if (!root) return nullptr;
		if (is_leaf(root)) return nullptr;

		if (root->left_)
		{
			root->left_ = RemoveChild(root->left_, node);
			return root;
		}

		if (root->right_)
		{
			root->right_ = RemoveChild(root->right_, node);
			return root;
		}

		return root;
	}
}