//
//  avl_tree.hpp
//  algorithm
//
//  Created by 신일환 on 2016. 6. 29..
//  Copyright © 2016년 acoross. All rights reserved.
//

#ifndef avl_tree_hpp
#define avl_tree_hpp

#include <stdio.h>
#include "avl.hpp"

namespace avl{

	// balanced binary search tree
	class AvlTree
	{
	public:
		void Insert(int data)
		{
			root_ = avl::Insert(root_, data);
		}

		void Remove(int data)
		{
			root_ = avl::Remove(root_, data);
		}

		void Inorder(std::function<void(int&)> callback) const
		{
			avl::Inorder(root_, callback);
		}

		void PrintWithFormat()
		{
			std::cout << "\n[print]\n";
			avl::PrintInorder(root_, 0);
		}

		void RotateRR(int data)
		{
			root_ = avl::SearchDoFeedbackRecursive(root_,
												   data,
												   [](AvlNodeSP node)->auto
												   {
													   return avl::RotateRR(node);
												   });
		}

		void RotateLL(int data)
		{
			root_ = avl::SearchDoFeedbackRecursive(root_,
												   data,
												   [](AvlNodeSP node)->auto
												   {
													   return avl::RotateLL(node);
												   });
		}

	private:
		AvlNodeSP root_;
	};

}
#endif /* avl_tree_hpp */
