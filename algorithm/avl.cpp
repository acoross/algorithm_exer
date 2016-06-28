//
//  avl.cpp
//  algorithm
//
//  Created by 신일환 on 2016. 6. 27..
//  Copyright © 2016년 acoross. All rights reserved.
//

#include "avl.hpp"
#include <algorithm>
#include <limits>

namespace avl{

	static const char* UnbalancedTypeName(UnbalancedType t)
	{
		switch(t)
		{
			case UnbalancedType::Balanced:
				return "b";
			case UnbalancedType::LL:
				return "LL";
			case UnbalancedType::LR:
				return "LR";
			case UnbalancedType::RL:
				return "RL";
			case UnbalancedType::RR:
				return "RR";
			default:
				return "null";
		}
	}

	AvlNodeSP SearchDoFeedbackRecursive(AvlNodeSP root,
										int data,
										std::function<AvlNodeSP(AvlNodeSP)> callback)
	{
		if (!root)
			return root;

		if (data < root->data_)
		{
			root->left_ = SearchDoFeedbackRecursive(root->left_, data, callback);
			update_height_no_propagate(root);
			return root;
		}
		else if (data > root->data_)
		{
			root->right_ = SearchDoFeedbackRecursive(root->right_, data, callback);
			update_height_no_propagate(root);
			return root;
		}

		return callback(root);
	}

	int height(AvlNodeSP root)
	{
		if (!root)
			return -1;

		return root->height_;
	}

	int update_height_no_propagate(AvlNodeSP root)
	{
		root->height_ = std::max(avl::height(root->left_), avl::height(root->right_)) + 1;
		return root->height_;
	}

	static AvlNodeSP Rotate(AvlNodeSP root, UnbalancedType type)
	{
		if (!root)
			return root;

		switch(type)
		{
			case UnbalancedType::LL:
				std::cout << root->data_ << ":t:" << UnbalancedTypeName(type) << std::endl;
				return avl::RotateLL(root);
			case UnbalancedType::LR:
				std::cout << root->data_ << ":t:" << UnbalancedTypeName(type) << std::endl;
				return avl::RotateLR(root);
			case UnbalancedType::RR:
				std::cout << root->data_ << ":t:" << UnbalancedTypeName(type) << std::endl;
				return avl::RotateRR(root);
			case UnbalancedType::RL:
				std::cout << root->data_ << ":t:" << UnbalancedTypeName(type) << std::endl;
				return avl::RotateRL(root);
			default:
				return root;
		}
	}

	AvlNodeSP Insert(AvlNodeSP root, int data)
	{
		if (!root)
			return std::make_shared<AvlNode>(data);

		if (data < root->data_)
			root->left_ = avl::Insert(root->left_, data);
		else if (data > root->data_)
			root->right_ = avl::Insert(root->right_, data);

		avl::update_height_no_propagate(root);
		return avl::Rotate(root, avl::CheckUnbalance(root));
	}

	AvlNodeSP FindMax(AvlNodeSP root)
	{
		if (!root)
			return root;

		if (!root->right_)
			return root;

		return FindMax(root->right_);
	}

	// 제거할 위치의 data 를 찾는다.
	// 1. leaf 노드면 걍 제거
	// 2. 자식이 하나면 제거하고 자식을 자기 부모에 붙인다.
	// 3. 자식이 둘이면, 왼쪽 subtree 의 max 노드를 끌어올린다.
	AvlNodeSP Remove(AvlNodeSP root, const int data)
	{
		if (!root)
			return root;

		return avl::SearchDoFeedbackRecursive(root, data,
		   [](AvlNodeSP root)->AvlNodeSP
		   {
			   // 자식이 둘 다 있음
			   if (root->left_ && root->right_)
			   {
				   auto max_descestor = FindMax(root->left_);
				   root->data_ = max_descestor->data_;
				   root->left_ = Remove(root->left_, root->data_);
				   update_height_no_propagate(root);
				   return root;
			   }

			   // 자식이 하나만 있음
			   if (!root->left_)
			   {
				   return root->right_;
			   }
			   else if (!root->right_)
			   {
				   return root->left_;
			   }
			   
			   // 자식이 없음
			   return nullptr;
		   });
	}

	AvlNodeSP RotateLL(AvlNodeSP root)
	{
		if (!root)
			return root;

		if (!root->left_)
			return root;

		auto node_to_root = root->left_;
		root->left_ = node_to_root->right_;
		node_to_root->right_ = root;

		update_height_no_propagate(root);
		update_height_no_propagate(node_to_root);

		return node_to_root; // 새 root 노드
	}

	AvlNodeSP RotateRR(AvlNodeSP root)
	{
		if (!root)
			return root;

		if (!root->right_)
			return root;

		auto node_to_root = root->right_;
		root->right_= node_to_root->left_;
		node_to_root->left_ = root;

		update_height_no_propagate(root);
		update_height_no_propagate(node_to_root);

		return node_to_root; // 새 root 노드
	}

	AvlNodeSP RotateLR(AvlNodeSP root)
	{
		root->left_ = RotateRR(root->left_);
		return RotateLL(root);
	}

	AvlNodeSP RotateRL(AvlNodeSP root)
	{
		root->right_ = RotateLL(root->right_);
		return RotateRR(root);
	}
	
	void Inorder(AvlNodeSP root, std::function<void(int&)>& callback)
	{
		if (!root)
			return;

		Inorder(root->left_, callback);
		callback(root->data_);
		Inorder(root->right_, callback);
	}

	void PrintInorder(AvlNodeSP root, int level)
	{
		if (!root)
			return;

		PrintInorder(root->left_, level + 1);

		for (int i = 0; i < level; ++i)
			std::cout << '\t';
		std::cout << root->data_ << ":" << root->height_ << ":"
			<< avl::UnbalancedTypeName(avl::CheckUnbalance(root)) << std::endl;
		
		PrintInorder(root->right_, level + 1);
	}

	UnbalancedType CheckUnbalance(AvlNodeSP root)
	{
		if (!root)
			return UnbalancedType::Balanced;

		int left_height = avl::height(root->left_) + 1;
		int right_height = avl::height(root->right_) + 1;
		int diff = left_height - right_height;
		if (std::abs(diff) < 2)
			return UnbalancedType::Balanced;

		if (diff > 0 && root->left_)
		{
			if (left_height == avl::height(root->left_->left_) + 2)
				return UnbalancedType::LL;
			else if (left_height == avl::height(root->left_->right_) + 2)
				return UnbalancedType::LR;
		}
		else if (diff < 0 && root->right_)
		{
			if (right_height == avl::height(root->right_->right_) + 2)
				return UnbalancedType::RR;
			else if (right_height == avl::height(root->right_->left_) + 2)
				return UnbalancedType::RL;
		}

		return UnbalancedType::Balanced;
	}
}