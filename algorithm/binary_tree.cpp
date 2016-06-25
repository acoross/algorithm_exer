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

		if (!root)
		{
			root = make_shared<BinaryTreeNode>(data);
			return;
		}

		q.push(root);

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

	std::shared_ptr<BinaryTreeNode> BinaryTree::Search(int data)
	{
		//조건에 맞는 node 와 부모 node 를 찾는다.
		using namespace std;

		if (!root)
			throw runtime_error("empty tree!");

		queue<shared_ptr<BinaryTreeNode>> q;
		q.push(root);

		auto node = root;

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

	// 조건에 맞는 node 를 찾는다.
	// 그 node 를 terminal node 와 위치를 바꾼다.
	// terminal node 를 제거한다.
	void BinaryTree::Remove(int data)
	{
		if (auto node = this->Search(data))
		{
			if (!root->RemoveChild(*node))
			{
				throw std::runtime_error("fuck");
			}
		}
	}

	int FindMaxValue(BinaryTree& tree)
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

		tree.Traverse(TraverseOrder::Preorder, f);

		return f.max;
	}

	int FindMaxValueNonRecursive(BinaryTree& tree)
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

		tree.Traverse(TraverseOrder::Levelorder, f);

		return f.max;
	}

}