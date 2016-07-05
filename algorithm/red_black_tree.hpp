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

#ifdef _RB_DEBUG_
	#define DEBUGF(f, x) printf("[DEBUG]%s( %d )\n", f, x);
#else
	#define DEBUGF(f, x) ;
#endif

namespace redblacktree {

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

class RedBlackBST
{
public:
	RedBlackBST()
	: root_(nullptr)
	{}

	int CountRedblackDepth()
	{
		return count_anscestor_black(root_);
	}

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
//		if (root_ && is_2node(root_) && root_->left && root_->right && is_2node(root_->left) && is_2node(root_->right))
//		{
//			flipColorsReverse(root_);
//		}

		root_ = remove_min(root_);

		if (root_) root_->color = Color::Black;
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
		if (!n) return;

		DEBUGF("flipColor", n->data);

		n->color = Color::Red;
		if (n->left) n->left->color = Color::Black;
		if (n->right) n->right->color = Color::Black;
	}

	static void flipColorsReverse(NodeSP& n)
	{
		if (!n) return;

		DEBUGF("flipColorReverse", n->data);

		n->color = Color::Black;
		if (n->left) n->left->color = Color::Red;
		if (n->right) n->right->color = Color::Red;
	}

	static NodeSP rotate_left(NodeSP n)
	{
		DEBUGF("rotate_left", n->data);

		auto child = n->right;
		assert(child);
		n->right = child->left;

		child->left = n;

		child->color = n->color;
		n->color = Color::Red;

		return child;
	}

	static NodeSP rotate_right(NodeSP n)
	{
		DEBUGF("rotate_right", n->data);

		auto child = n->left;
		assert(child);
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

	static bool is_2node(NodeSP n)
	{
		assert(n);

		if (!is_red(n) && !is_red(n->left))
			return true;

		return false;
	}

	// current->left 가 2node 가 아니도록 만든다.
	static NodeSP Preprocess_to_remove_min(NodeSP current)
	{
		// 234 tree 관점에서,
			// 1. left node 가 not 2node 면 넘어간다.
			// 2. left node 가 2node 고 immediate sibling 이 not 2node 면
				// key 를 하나 빌린다.
			// 3. left node 가 2node 고 immediate sibling 이 2node 면
				// 부모에게서 key를 하나 빌리고 left child, sibling 을 합쳐서
				// 4node 를 만든다.

		assert(current);
		if (!current) return current;

		auto left = current->left;
		if (!left)
		{
			assert(0);
			return current;
		}

		if (!is_2node(current->left))
		{
			return current;
		}
		else if (current->right && !is_2node(current->right))
		{
			current->right = rotate_right(current->right);
			flipColors(current->right);
			current = rotate_left(current);
			//flipColorsReverse(current->left);
			auto flip = [](auto n)
			{
				DEBUGF("flip lambda", n->data);
				n->color = Color::Black;
				if (n->left) n->left->color = Color::Red;
				//if (n->right) n->right->color = Color::Red;
			};
			flip(current->left);

			current->right = Postprocess_to_remove_min(current->right);
		}
		else
		{
			flipColorsReverse(current);
		}

		return current;
	}

	static NodeSP Postprocess_to_remove_min(NodeSP n)
	{
		assert(n);
		if (!n) return n;

		// way up balancing
		if (!is_red(n->left) && is_red(n->right)) n = rotate_left(n);
		if (is_red(n->left) && is_red(n->left->left)) n = rotate_right(n);
		if (is_red(n->left) && is_red(n->right)) flipColors(n);
		return n;
	}

	// input current 는 2node가 아니어야 한다.
	static NodeSP remove_min(NodeSP current)
	{
		if (!current)
			return current;

		if (!current->left)
		{
//			assert(is_red(current));
//			assert(!is_red(current->right));
			return current->right;
		}

		current = Preprocess_to_remove_min(current);
		current->left = remove_min(current->left);
		current = Postprocess_to_remove_min(current);

		return current;
	}

	// [DEBUG]
	static int count_anscestor_black(NodeSP& n)
	{
		if (!n) return 0;

		auto l = count_anscestor_black(n->left);
		auto r = count_anscestor_black(n->right);

		assert(l == r);
		if (l != r) return -1;

		if (!is_red(n)) return l + 1;
		else return l;
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
	// [DEBUG] end

	NodeSP root_;
};

} //namespace redblacktree
#endif /* red_black_tree_hpp */
