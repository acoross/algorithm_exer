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
#include <limits>
#include <map>

namespace avl{

	class AvlNode;
	using AvlNodeSP = std::shared_ptr<AvlNode>;

	class AvlNode
	{
	public:
		AvlNode(int data)
		: data_(data)
		{}

		~AvlNode(){}

		static void Insert(AvlNodeSP& root, int data)
		{
			if (!root)
				root = std::make_shared<AvlNode>(data);

			if (data < root->data_)
				Insert(root->left_, data);
			else if (data > root->data_)
				Insert(root->right_, data);
		}

		static AvlNodeSP FindMax(AvlNodeSP root)
		{
			if (!root)
				return root;

			if (root->right_)
				return root;

			return FindMax(root->right_);
		}

		static void RemoveNode(AvlNodeSP& root)
		{
			if (!root)
				return;
			
			// 자식이 둘 다 있음
			if (root->left_ && root->right_)
			{
				auto max_descestor = FindMax(root->left_);
				root->data_ = max_descestor->data_;
				Remove(root->left_, root->data_);
				return;
			}

			// 자식이 하나만 있음
			if (!root->left_)
			{
				root = root->right_;
				return;
			}
			else if (!root->right_)
			{
				root = root->left_;
				return;
			}

			// 자식이 없음
			root = nullptr;
			return;
		}

		// 제거할 위치의 data 를 찾는다.
		// 1. leaf 노드면 걍 제거
		// 2. 자식이 하나면 제거하고 자식을 자기 부모에 붙인다.
		// 3. 자식이 둘이면, 왼쪽 subtree 의 max 노드를 끌어올린다.
		static void Remove(AvlNodeSP& root, const int data)
		{
			if (!root)
				return;

			auto& node_to_remove = Search(root, data);
			RemoveNode(node_to_remove);

			return;
		}

		static void Inorder(AvlNodeSP root, std::function<void(int&)>& callback)
		{
			if (!root)
				return;

			Inorder(root->left_, callback);
			callback(root->data_);
			Inorder(root->right_, callback);
		}

		static void PrintInorder(AvlNodeSP root, int level)
		{
			if (!root)
				return;

			PrintInorder(root->left_, level + 1);

			for (int i = 0; i < level; ++i)
				std::cout << '\t';
			std::cout << root->data_ << std::endl;

			PrintInorder(root->right_, level + 1);
		}

		static AvlNodeSP& Search(AvlNodeSP& root, int data)
		{
			if (!root)
				return root;

			if (data < root->data_)
				return Search(root->left_, data);
			else if (data > root->data_)
				return Search(root->right_, data);
			else
				return root;
		}

		static void RotateLL(AvlNodeSP& root)
		{
			if (!root)
			{
				return;
			}

			if (!root->left_)
			{
				return;
			}

			auto node_to_root = root->left_;
			root->left_ = node_to_root->right_;
			node_to_root->right_ = root;
			root = node_to_root;
			return;
		}

		static void RotateRR(AvlNodeSP& root)
		{
			if (!root)
				return;

			if (!root->right_)
				return;

			auto node_to_root = root->right_;
			root->right_= node_to_root->left_;
			node_to_root->left_ = root;
			root = node_to_root;
			return;
		}

	private:
		int data_;
		AvlNodeSP left_{nullptr};
		AvlNodeSP right_{nullptr};
	};


	// balanced binary search tree
	class AvlTree
	{
	public:
		void Insert(int data)
		{
			AvlNode::Insert(root_, data);
		}

		void Remove(int data)
		{
			AvlNode::Remove(root_, data);
		}

		void PrintInorder(std::function<void(int&)> callback) const
		{
			AvlNode::Inorder(root_, callback);
		}

		void PrintWithFormat()
		{
			AvlNode::PrintInorder(root_, 0);
		}

		void RotateRR(int data)
		{
			auto& node = AvlNode::Search(root_, data);
			AvlNode::RotateRR(node);
		}

		void RotateLL(int data)
		{
			auto& node = AvlNode::Search(root_, data);
			AvlNode::RotateLL(node);
		}

	private:
		AvlNodeSP root_;
	};
}

#endif /* avl_hpp */
