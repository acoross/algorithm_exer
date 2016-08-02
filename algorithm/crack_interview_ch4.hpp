//
//  crack_interview_ch4.hpp
//  algorithm
//
//  Created by 신일환 on 2016. 8. 3..
//  Copyright © 2016년 acoross. All rights reserved.
//

#ifndef crack_interview_ch4_hpp
#define crack_interview_ch4_hpp

#include <stdio.h>
#include <memory>
#include <list>
#include <queue>
#include <functional>
#include <iostream>

namespace crack_coding_interview {
	namespace ch_4_tree_graph {

		class BinTree {
		public:
			struct Node {
				using NodeSP = std::shared_ptr<Node>;
				Node(int d) : data(d) {}

				int data {0};
				NodeSP left_;
				NodeSP right_;
			};
			using NodeSP = Node::NodeSP;

			static NodeSP bst_insert(NodeSP root, NodeSP node) {
				if (!root) return node;
				if (!node) return root;

				if (root->data > node->data) {
					root->left_ = bst_insert(root->left_, node);
					return root;
				} else {
					root->right_ = bst_insert(root->right_, node);
					return root;
				}
			}

			static void print(NodeSP root, int level) {
				if (!root) return;

				for (int i = 0; i < level; ++i)
					std::cout << "\t";
				std::cout << root->data << "\n";

				print(root->left_, level + 1);
				print(root->right_, level + 1);
			}
		};

		class Graph {
		public:
			struct Node {
				using NodeSP = std::shared_ptr<Node>;
				int data {0};
				std::list<NodeSP> neighbors_;
				bool visit{false};
			};
			using NodeSP = Node::NodeSP;

			static void BFS(NodeSP node, std::function<bool(NodeSP)> visit) {
				std::queue<NodeSP> q;
				q.push(node);
				while (auto n = q.front()) {
					q.pop();

					if ((n->visit = true, !n->visit) && visit(n)) {
						return;
					}

					for (auto ng : n->neighbors_) {
						if (!ng->visit)
							q.push(ng);
					}
				}
			}
		};

		class Q4_2 {
		public:
			static void Run() {

			}

		private:
			static void check_route(Graph::NodeSP n1, Graph::NodeSP n2) {
				Graph::BFS(n1,
						   [n2](Graph::NodeSP n)->bool {
							   if (n == n2) return true;
							   return false;
						   });
			}
		};

		class Q4_3 {
		public:
			static void Run() {
				// 정렬된 배열에서 높이가 가장 낮은 이진 탐색 트리를 생성하라.
				std::vector<int> arr{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

				auto root = make_tree(arr, 0, (int)arr.size() - 1);

				BinTree::print(root, 0);
			}

			static BinTree::NodeSP make_tree(std::vector<int> arr, int s, int e) {
				if (e - s < 0) return nullptr;

				int m = (e + s + 1) / 2;
				auto root = std::make_shared<BinTree::Node>(arr[m]);

				auto t1 = make_tree(arr, s, m - 1);
				auto t2 = make_tree(arr, m + 1, e);

				BinTree::bst_insert(root, t1);
				BinTree::bst_insert(root, t2);
				return root;
			}
		};

		
	}
}

#endif /* crack_interview_ch4_hpp */
