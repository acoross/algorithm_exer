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
#include <functional>

#ifdef _RB_DEBUG_
	#define DEBUGF(f, x) printf("[DEBUG]%s( %d )\n", f, x);\
		if (debugPrintOn) PrintInside();
#else
	#define DEBUGF(f, x) ;
#endif

#define static

namespace redblacktree {

class Printer
{
public:
	Printer(bool run, std::function<void(void)> f)
	: run_(run), func(f)
	{}
	~Printer()
	{
		if (run_)
			func();
	}

	bool run_;
	std::function<void(void)> func;
};

class RedBlackBST
{
public:
	bool debugPrintOn{false};

	enum class Color : bool
	{
		Black = false,
		Red = true
	};

	struct Node
	{
		Node(int d, Color c)
		: data(d), color(c){}

		bool is_2node() const
		{
			if (!is_red(this) && !is_red(left.get()))
				return true;

			return false;
		}

		bool is_red(const Node* n) const
		{
			if (!n) return false;
			return color == Color::Red;
		}

		int data;
		Color color;
		std::shared_ptr<Node> left;
		std::shared_ptr<Node> right;
	};
	using NodeSP = std::shared_ptr<Node>;


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
		if (!root_)
			return;
		if (!is_red(root_->left) && !is_red(root_->right))
			root_->color = Color::Red;
		root_ = remove_min(root_);
		if (root_)
			root_->color = Color::Black;
	}

	void RemoveMax()
	{

	}

	void Remove(int data)
	{

	}

	void PrintInside()
	{
		print_inside(root_, 0);
	}

private:
	static bool is_red(const NodeSP& n)
	{
		if (!n)
			return false;

		if (n->color == Color::Red)
			return true;

		return false;
	}

	static void flipColor(NodeSP& n)
	{
		if (!n) return;
		n->color = (n->color == Color::Black) ? Color::Red : Color::Black;
	}

	static void flipColors(NodeSP& n)
	{
		DEBUGF("flipColor", n->data);

		flipColor(n);
		flipColor(n->left);
		flipColor(n->right);
	}

	static NodeSP rotate_left(NodeSP n)
	{
		DEBUGF("rotate_left", n->data);

		auto child = n->right;
		if (!child)
			return n;

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
		if (!child)
			return n;

		n->left = child->right;
		child->right = n;

		child->color = n->color;
		n->color = Color::Red;

		return child;
	}

	static NodeSP balance(NodeSP n)
	{
		DEBUGF("balance", n->data);

		assert(n);
		if (!n) return nullptr;

		if (!is_red(n->left) && is_red(n->right)) n = rotate_left(n);
		if (is_red(n->left) && is_red(n->left->left)) n = rotate_right(n);
		if (is_red(n->left) && is_red(n->right)) flipColors(n);

		return n;
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
		return n = balance(n);
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

	static NodeSP moveRedLeft(NodeSP n)
	{
		DEBUGF("moveRedLeft", n->data);

		flipColors(n);
		if (n->right && is_red(n->right->left))
		{
			n->right = rotate_right(n->right);
			n = rotate_left(n);
		}

		return n;
	}

	static NodeSP remove_min(NodeSP n)
	{
		// n is not 2node,
		// and n exists.

		DEBUGF("remove_min", n->data);

		assert(n);

		if (!n->left)
		{
			return nullptr;	//left 가 없으면 right 도 없어야 함.
		}

		if (n->left->is_2node())
		{
			n = moveRedLeft(n);
		}

		n->left = remove_min(n->left);

		return balance(n);
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

	static void print_inside(const NodeSP& n, int level)
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
