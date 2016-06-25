//
//  binary_tree.h
//  algorithm
//
//  Created by 신일환 on 2016. 6. 25..
//  Copyright © 2016년 acoross. All rights reserved.
//

#ifndef binary_tree_h
#define binary_tree_h

#include <memory>
#include <queue>
#include <exception>
#include <string>
#include <iostream>
#include <functional>

#include "binary_tree_node.hpp"

namespace bintree{

	enum class TraverseOrder
	{
		Preorder,
		Inorder,
		Postorder,
		Levelorder
	};

	class BinaryTree
	{
	public:
		void Insert(int data);

		void Remove(int data);
		
		std::shared_ptr<BinaryTreeNode> Search(int data);

		template <class CallbackT>
		void Traverse(TraverseOrder to, CallbackT& callback)
		{
			if (!root)
			{
				return;
			}

			switch(to)
			{
				case TraverseOrder::Preorder:
				{
					root->Preorder(callback);
					break;
				}
				case TraverseOrder::Inorder:
				{
					root->Inorder(callback);
					break;
				}
				case TraverseOrder::Levelorder:
				{
					level_order_traverse(callback);
					break;
				}
				default:
					break;
			}

			std::cout << std::endl;
			
			return;
		}

	private:
		template <class CallbackT>
		void level_order_traverse(CallbackT& callback) const
		{
			using namespace std;

			queue<shared_ptr<BinaryTreeNode>> q;

			if (!root)
			{
				return;
			}

			q.push(root);

			while (!q.empty())
			{
				auto node = q.front();
				q.pop();

				callback(node.get());

				if (node->left_)
				{
					q.push(node->left_);
				}

				if (node->right_)
				{
					q.push(node->right_);
				}
			}
			
			return;
		}

		std::shared_ptr<BinaryTreeNode> root;
	};

	// 최대값을 가지는 node 를 return;
	// 중복될 경우 처음 찾은 것을 return;
	// empty tree 인 경우 nullptr return;
	int FindMaxValue(BinaryTree& tree);

	// level order 방식으로 해볼까?
	int FindMaxValueNonRecursive(BinaryTree& tree);

}//namespace bintree
#endif /* binary_tree_h */
