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

namespace bst{

	struct BSTNode;
	using BSTNodeSP = std::shared_ptr<BSTNode>;

	struct BSTNode
	{
		BSTNode(int data)
		: data_(data){}

		bool IsTerminal() const
		{
			return !left_ && !right_;
		}

		int data_;
		std::shared_ptr<BSTNode> right_{nullptr};
		std::shared_ptr<BSTNode> left_{nullptr};
	};

	class BST
	{
	public:
		void Insert(int data);
		void Remove(int data);
		void Print();
		
	private:
		BSTNodeSP root_;
	};
}

#endif /* bst_h */
