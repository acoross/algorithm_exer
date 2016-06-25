//
//  bin_tree_node.h
//  algorithm
//
//  Created by 신일환 on 2016. 6. 25..
//  Copyright © 2016년 acoross. All rights reserved.
//

#ifndef bin_tree_node_h
#define bin_tree_node_h

namespace bintree{
	
	class BinaryTree;

	class BinaryTreeNode
	{
	public:
		BinaryTreeNode(int data)
		: data_(data)
		, left_{nullptr}
		, right_{nullptr}
		{}

		~BinaryTreeNode() = default;

		int data_{0};
		
	private:
		template <class CallbackT>
		void Preorder(CallbackT& callback)
		{
			if (!callback(this)) return;

			if (left_)
				left_->Preorder(callback);

			if (right_)
				right_->Preorder(callback);
		}

		template <class CallbackT>
		void Inorder(CallbackT& callback)
		{
			if (left_)
				left_->Inorder(callback);

			if (!callback(this)) return;

			if (right_)
				right_->Inorder(callback);
		}

		bool IsTerminal() const
		{
			return !left_ && !right_;
		}

		bool RemoveChild(BinaryTreeNode& node)
		{
			if (left_)
			{
				if (left_->IsTerminal())
				{
					node.data_ = left_->data_;
					left_.reset();
					return true;
				}

				return left_->RemoveChild(node);
			}

			if (right_)
			{
				if (right_->IsTerminal())
				{
					node.data_ = right_->data_;
					right_.reset();
					return true;
				}

				return right_->RemoveChild(node);
			}

			return false;
		}

		std::shared_ptr<BinaryTreeNode> left_{nullptr};
		std::shared_ptr<BinaryTreeNode> right_{nullptr};
		
		friend class BinaryTree;
	};

}

#endif /* bin_tree_node_h */
