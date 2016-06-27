//
//  bin_tree_node.h
//  algorithm
//
//  Created by 신일환 on 2016. 6. 25..
//  Copyright © 2016년 acoross. All rights reserved.
//

#ifndef bin_tree_node_h
#define bin_tree_node_h

#include <stack>
#include <utility>

namespace bintree{

	struct BinaryNode
	{
		BinaryNode(int data)
		: data_(data)
		, left_{nullptr}
		, right_{nullptr}
		{}

		~BinaryNode() = default;

		int data_{0};
		std::shared_ptr<BinaryNode> left_{nullptr};
		std::shared_ptr<BinaryNode> right_{nullptr};
	};

	using BinaryNodeSP = std::shared_ptr<BinaryNode>;


	inline bool is_leaf(BinaryNodeSP node)
	{
		if (!node) return true;

		return !node->left_ && !node->right_;
	}

	template <class CallbackT>
	void preorder(BinaryNodeSP root, CallbackT& callback)
	{
		if (!root) return;

		callback(root.get());

		preorder(root->left_, callback);
		preorder(root->right_, callback);
	}

	template <class CallbackT>
	void preorder_non_recursive(BinaryNodeSP root, CallbackT&& func)
	{
		if (!root) return;

		std::stack<BinaryNodeSP> stack;

		func(root.get());
		stack.push(root);

		auto node = root->left_;
		for(;;)
		{
			while (node)
			{
				func(node.get());
				stack.push(node);
				node = node->left_;
				continue;
			}

			if (stack.empty())
				break;

			node = stack.top()->right_;
			stack.pop();
		}
	}

	template <class CallbackT>
	void inorder(BinaryNodeSP root, CallbackT& callback)
	{
		if (!root) return;

		inorder(root->left_, callback);

		callback(root.get());

		inorder(root->right_, callback);
	}

	template <class CallbackT>
	void inorder_non_recursive(BinaryNodeSP root, CallbackT&& callback)
	{
		if (!root) return;

		std::stack<BinaryNodeSP> stack;

		stack.push(root);

		auto node = root->left_;
		for(;;)
		{
			while (node)
			{
				stack.push(node);
				node = node->left_;
				continue;
			}

			if (stack.empty())
				break;

			node = stack.top();
			stack.pop();

			callback(node.get());
			node = node->right_;
		}
	}

	template <class CallbackT>
	void postorder(BinaryNodeSP root, CallbackT&& callback)
	{
		if (!root) return;

		postorder(root->left_, std::forward<CallbackT>(callback));
		postorder(root->right_, std::forward<CallbackT>(callback));

		callback(root.get());
	}

	template <class CallbackT>
	void postorder_non_recursive(BinaryNodeSP root, CallbackT&& callback)
	{
		std::stack<BinaryNodeSP> stack;

		auto node = root;
		for(;;)
		{
			if (node)
			{
				stack.push(node);
				node = node->left_;
				continue;
			}
			else
			{
				if (stack.empty())
					return;

				if (!stack.top()->right_)
				{
					node = stack.top();
					stack.pop();

					callback(node.get());

					while (!stack.empty() && stack.top()->right_ == node)
					{
						node = stack.top();
						callback(node.get());
						stack.pop();
					}
				}

				if (!stack.empty())
					node = stack.top()->right_;
				else
					node = nullptr;
			}
		}
	}

	template <class CallbackT>
	void level_order_traverse(BinaryNodeSP root, CallbackT& callback)
	{
		using namespace std;

		queue<shared_ptr<BinaryNode>> q;

		if (!root)
		{
			return;
		}

		q.push(root);

		while (!q.empty())
		{
			auto node = q.front();
			q.pop();

			if (!callback(node.get()))
				return;

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
}

#endif /* bin_tree_node_h */
