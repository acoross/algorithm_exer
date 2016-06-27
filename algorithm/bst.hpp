//
//  bst.h
//  algorithm
//
//  Created by 신일환 on 2016. 6. 25..
//  Copyright © 2016년 acoross. All rights reserved.
//

#ifndef bst_h
#define bst_h

#include <iostream>
#include <memory>
#include <queue>

#include "binary_tree_node.hpp"

namespace bst{

	using BSTNode = bintree::BinaryNode;
	using BSTNodeSP = bintree::BinaryNodeSP;

	class BST
	{
	public:
		BSTNodeSP Search(int data);
		BSTNodeSP SearchMax();
		BSTNodeSP SearchMin();

		void Insert(int data);
		void Remove(int data);

		void Print();

		void PrintNonrecur()
		{
			auto func = [](BSTNode* node)->bool
			{
				std::cout << node->data_ << ", ";
				return true;
			};
			//bintree::preorder_non_recursive(root_, func);
			//bintree::inorder_non_recursive(root_, func);

			bintree::postorder(root_, func);
			std::cout << std::endl;
			
			bintree::postorder_non_recursive(root_, func);
			std::cout << std::endl;
		}

	private:
		BSTNodeSP root_;
	};
}

#endif /* bst_h */
