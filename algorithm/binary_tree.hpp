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
		
		BinaryTreeNodeSP Search(int data);

		template <class CallbackT>
		void Traverse(TraverseOrder to, CallbackT& callback)
		{
			switch(to)
			{
				case TraverseOrder::Preorder:
				{
					preorder(root_, callback);
					break;
				}
				case TraverseOrder::Inorder:
				{
					inorder(root_, callback);
					break;
				}
				case TraverseOrder::Levelorder:
				{
					level_order_traverse(root_, callback);
					break;
				}
				default:
					break;
			}

			std::cout << std::endl;
			
			return;
		}

		// 최대값을 가지는 node 를 return;
		// 중복될 경우 처음 찾은 것을 return;
		// empty tree 인 경우 nullptr return;
		int FindMaxValue();

		// level order 방식으로 해볼까?
		int FindMaxValueNonRecursive();

	private:
		static BinaryTreeNodeSP RemoveChild(BinaryTreeNodeSP root, BinaryTreeNodeSP node);

		std::shared_ptr<BinaryTreeNode> root_;
	};

}//namespace bintree
#endif /* binary_tree_h */
