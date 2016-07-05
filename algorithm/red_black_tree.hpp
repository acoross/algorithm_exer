//
//  red_black_tree.hpp
//  algorithm
//
//  Created by 신일환 on 2016. 7. 3..
//  Copyright © 2016년 acoross. All rights reserved.
//

#ifndef red_black_tree_hpp
#define red_black_tree_hpp

#include <iostream>
#include <memory>
#include <cassert>

namespace redblacktree {

class RedBlackBST
{
public:
	RedBlackBST()
	: root_(nullptr)
	{}

	void InsertAs23tree(int data)
	{
		root_ = insert_as_23tree(root_, data);
		root_->color = Color::Black;
	}

	void InsertAs234tree(int data)
	{
		root_ = insert_as_234tree(root_, data);
		root_->color = Color::Black;
	}

	void RemoveMin()
	{
		// 루트가 2노드고 자식둘이 다 2노드면 합쳐서 4노드로 만든다.
		if (!is_red(root_->left) && !is_red(root_->right))
		{
			flip_child_color_to_red(root_);
		}

		root_ = remove_min(root_);
		root_->color = Color::Black;
	}

	void RemoveMax()
	{
		// not implemented yet.
		assert(false);
	}

	void PrintInside()
	{
		print_inside(root_, 0);
	}

private:
	enum class Color : bool
	{
		Black = false,
		Red = true
	};

	struct Node
	{
		Node(int d, Color c)
		: data(d), color(c){}

		int data;
		Color color;
		std::shared_ptr<Node> left;
		std::shared_ptr<Node> right;
	};
	using NodeSP = std::shared_ptr<Node>;

	static bool is_red(NodeSP& n)
	{
		if (!n)
			return false;

		if (n->color == Color::Red)
			return true;

		return false;
	}

	static void flipColors(NodeSP& n)
	{
		if (!n)
			return;

		printf("flipColor, [%d,%d,%d]\n", n->data, n->left->data, n->right->data);

		n->color = Color::Red;

		if (n->left)
			n->left->color = Color::Black;

		if (n->right)
			n->right->color = Color::Black;
	}

	static NodeSP rotate_left(NodeSP n)
	{
		auto child = n->right;
		n->right = child->left;

		child->left = n;

		child->color = n->color;
		n->color = Color::Red;

		return child;
	}

	static NodeSP rotate_right(NodeSP n)
	{
		auto child = n->left;
		n->left = child->right;

		child->right = n;

		child->color = n->color;
		n->color = Color::Red;

		return child;
	}

	static NodeSP insert_as_23tree(NodeSP n, int data)
	{
		if (!n)
			return std::make_shared<Node>(data, Color::Red);

		// way down insertion
		if (data < n->data)
			n->left = insert_as_23tree(n->left, data);
		else if (data > n->data)
			n->right = insert_as_23tree(n->right, data);

		// way up balancing
		if (!is_red(n->left) && is_red(n->right)) n = rotate_left(n);
		if (is_red(n->left) && is_red(n->left->left)) n = rotate_right(n);
		if (is_red(n->left) && is_red(n->right)) flipColors(n);

		return n;
	}

	// 이거 왜 필요한 건데??
	static NodeSP insert_as_234tree(NodeSP n, int data)
	{
		if (!n)
			return std::make_shared<Node>(data, Color::Red);

		if (is_red(n->left) && is_red(n->right)) flipColors(n);

		// way down insertion
		if (data < n->data)
			n->left = insert_as_23tree(n->left, data);
		else if (data > n->data)
			n->right = insert_as_23tree(n->right, data);

		// way up balancing
		if (!is_red(n->left) && is_red(n->right)) n = rotate_left(n);
		if (is_red(n->left) && is_red(n->left->left)) n = rotate_right(n);

		return n;
	}

	static void flip_child_color_to_red(NodeSP n)
	{
		if (!n)
			return;

		n->color = Color::Black;

		if (n->left) n->left->color = Color::Red;
		if (n->right) n->right->color = Color::Red;
	}


	static NodeSP remove_way_down_left(NodeSP current)
	{
		if (!current->left)
			return current;

		// left child is not 2node
		if (is_red(current->left) || is_red(current->left->left))
			return current;

		// left child is 2node and its sibling is not 2node
		if (current->right && !is_red(current->right) && is_red(current->right->left))
		{
			// move a key to left child
			// current: red, leftmost in 3 or 4 node
			// left, right: black 2node. its all childs are also black.
			current->right = rotate_left(current->right);
			current = rotate_right(current);
			current->left->color = Color::Black;
			if (current->left->left)
				current->left->left->color = Color::Red;
		}
		// left child is 2node its sibling is 2node
		else
		{
			// make 4node (left child + one parent key + sibling child)
			flip_child_color_to_red(current);
		}

		return current;
	}

	// 삭제하려는 값을 가지는 node가 2node 면 안됨. (234 tree model)
	static NodeSP remove_min(NodeSP current)
	{
		if (!current)
			return current;

		// current is 2node and 2 childs are 2nodes. (root only)
			// make 4node
		if (!is_red(current->right) && !is_red(current->left))
			flip_child_color_to_red(current);

		//... current node is not 2node now.

		// no left child
			// delete current
		if (!current->left)
		{
			// current shoud not be 2node(black left-most node)
			//assert(is_red(current));
			return current->right;
		}

		current = remove_way_down_left(current);

		// inside this call, n is not 2node.
		current->left = remove_min(current->left);

		// way up balancing
		if (!is_red(current->left) && is_red(current->right)) current = rotate_left(current);
		if (is_red(current->left) && is_red(current->left->left)) current = rotate_right(current);
		if (is_red(current->left) && is_red(current->right)) flipColors(current);

		return current;
	}

	static NodeSP remove_way_down_right(NodeSP current)
	{
		if (!current->right)
			return current;

		// right child is not 2node
		if (is_red(current->right) || is_red(current->right->left))
			return current;

		// right child is 2node and its sibling is not 2node
		if (current->left && !is_red(current->left) && is_red(current->left->left))
		{
			// move a key to right child
			// current: red, right in 3 or 4 node
				// right: 2node
				// left: not 2node
			current->right = rotate_left(current->right);
			current = rotate_right(current);
			current->left->color = Color::Black;
			if (current->left->left)
				current->left->left->color = Color::Red;
		}
		// left child is 2node its sibling is 2node
		else
		{
			// make 4node (left child + one parent key + sibling child)
			flip_child_color_to_red(current);
		}

		return current;
	}

	static NodeSP remove_max(NodeSP current)
	{

		if (!current)
			return current;

		// current is 2node and 2 childs are 2nodes. (root only)
		// make 4node
		if (!is_red(current->right) && !is_red(current->left))
			flip_child_color_to_red(current);

		//... current node is not 2node now.

		// no left child
		// delete current
		if (!current->right)
		{
			// current shoud not be 2node(black left-most node)
			assert(is_red(current->left));
			return current->left;
		}

		current = remove_way_down_right(current);

		// inside this call, n is not 2node.
		current->right = remove_min(current->right);

		// way up balancing
		if (!is_red(current->left) && is_red(current->right)) current = rotate_left(current);
		if (is_red(current->left) && is_red(current->left->left)) current = rotate_right(current);
		if (is_red(current->left) && is_red(current->right)) flipColors(current);

		return current;
	}

	static void print_inside(NodeSP n, int level)
	{
		if (n)
		{
			print_inside(n->left, level+1);

			for (int i = 0; i < level; ++i)
			{
				std::cout << "\t";
			}
			std::cout << n->data << ((bool)n->color ? "r" : "b") << std::endl;

			print_inside(n->right, level+1);
		}
	}

	NodeSP root_;
};

} //namespace redblacktree
#endif /* red_black_tree_hpp */
