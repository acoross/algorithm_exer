//
//  avl.hpp
//  algorithm
//
//  Created by 신일환 on 2016. 6. 27..
//  Copyright © 2016년 acoross. All rights reserved.
//

#ifndef avl_hpp
#define avl_hpp

#include <iostream>
#include <memory>
#include <functional>

namespace avl{

	class AvlNode;
	using AvlNodeSP = std::shared_ptr<AvlNode>;

	struct AvlNode
	{
		AvlNode(int data) : data_(data) {}

		int data_;
		AvlNodeSP left_{nullptr};
		AvlNodeSP right_{nullptr};
		int height_{0};
	};

	AvlNodeSP SearchDoFeedbackRecursive(AvlNodeSP root,
										int data,
										std::function<AvlNodeSP(AvlNodeSP)> callback);

	int height(AvlNodeSP root);
	int update_height_no_propagate(AvlNodeSP root);

	AvlNodeSP FindMax(AvlNodeSP root);
	AvlNodeSP Insert(AvlNodeSP root, int data);

	// 제거할 위치의 data 를 찾는다.
	// 1. leaf 노드면 걍 제거
	// 2. 자식이 하나면 제거하고 자식을 자기 부모에 붙인다.
	// 3. 자식이 둘이면, 왼쪽 subtree 의 max 노드를 끌어올린다.
	AvlNodeSP Remove(AvlNodeSP root, const int data);

	AvlNodeSP RotateLL(AvlNodeSP root);
	AvlNodeSP RotateRR(AvlNodeSP root);

	AvlNodeSP RotateLR(AvlNodeSP root);
	AvlNodeSP RotateRL(AvlNodeSP root);

	void Inorder(AvlNodeSP root, std::function<void(int&)>& callback);
	void PrintInorder(AvlNodeSP root, int level);

	enum class UnbalancedType
	{
		Balanced,
		LL,
		RR,
		LR,
		RL
	};

	UnbalancedType CheckUnbalance(AvlNodeSP root);
}

#endif /* avl_hpp */
