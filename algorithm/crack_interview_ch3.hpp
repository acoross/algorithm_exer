//
//  crack_interview_ch3.hpp
//  algorithm
//
//  Created by 신일환 on 2016. 8. 2..
//  Copyright © 2016년 acoross. All rights reserved.
//

#ifndef crack_interview_ch3_hpp
#define crack_interview_ch3_hpp

#include <stdio.h>
#include <iostream>
#include <memory>
#include <string>
#include <cassert>
#include <exception>

namespace crack_coding_interview {
	namespace ch_3_stack_queue {

		class Stack {
		public:
			struct StackNode {
				StackNode(int d) : data(d) {}
				int data;
				std::shared_ptr<StackNode> next;
			};
			using NodeSP = std::shared_ptr<StackNode>;

			void Push(int data) {
				auto node = std::make_shared<StackNode>(data);
				node->next = top_;
				top_ = node;
			}

			NodeSP Pop() {
				auto ret = top_;
				if (top_)
					top_ = top_->next;
				return ret;
			}

			NodeSP Peek() {
				return top_;
			}

		private:
			NodeSP top_{nullptr};
		};

		class Queue {
		public:
			struct QueueNode {
				QueueNode(int d) : data(d) {};
				int data;
				std::shared_ptr<QueueNode> next;
			};
			using NodeSP = std::shared_ptr<QueueNode>;

			void Enqueue(int data) {
				auto node = std::make_shared<QueueNode>(data);
				last_->next = node;
				last_ = node;
				if (!first_) {
					first_ = node;
				}
			}

			NodeSP Dequeue() {
				auto ret = first_;
				if (first_) {
					first_ = first_->next;
					if (!first_) last_ = nullptr;
				}
				return ret;
			}

		private:
			NodeSP first_{nullptr};
			NodeSP last_{nullptr};
		};

		class Q3_1 {
			/* 배열 하나로 3개의 stack 을 표현 */
		public:
			template <size_t SIZ>
			class FreeList {
			public:
				struct Node {
					Node() : data(0), next_idx(-1) {};
					Node(int d) : data(d), next_idx(-1) {}
					int data;
					int next_idx;
				};

				FreeList() : first_(0) {
					for (int i = 0; i < SIZ - 1; ++i) {
						mem_blocks_[i].next_idx = i + 1;
					}
					mem_blocks_[SIZ - 1].next_idx = -1;
				}

				int Alloc() {
					int free = first_;
					if (first_ > -1) {
						first_ = mem_blocks_[first_].next_idx;
						mem_blocks_[free].next_idx = -1;
					}
					return free;
				}

				void Free(int idx) {
					mem_blocks_[idx].next_idx = first_;
					first_ = idx;
				}

				Node* operator[](int idx) {
					if (idx > -1 && idx < SIZ)
						return &mem_blocks_[idx];
					else
						return nullptr;
				}

			private:
				int first_{0};
				Node mem_blocks_[SIZ];
			};

			template <size_t SIZ>
			class FLStack {
			public:
				FLStack(FreeList<SIZ>& free_list)
				: free_list_(free_list) {}

				void Push(int data) {
					int free = free_list_.Alloc();
					if (free > -1) {
						auto* free_node = free_list_[free];
						free_node->data = data;
						free_node->next_idx = top_idx_;
						top_idx_ = free;
					} else {
						assert(false);
						throw std::exception();
					}
				}

				int Pop() {
					if (top_idx_ > -1) {
						auto* top_node = free_list_[top_idx_];
						int ret = top_node->data;
						int to_free_idx = top_idx_;
						top_idx_ = top_node->next_idx;
						free_list_.Free(to_free_idx);
						return ret;
					} else {
						//assert(false);
						throw std::exception();
					}
				}

				int* Peek() {
					if (top_idx_ > -1) {
						return &(free_list_[top_idx_]->data);
					} else {
						return nullptr;
					}
				}

			private:
				FreeList<SIZ>& free_list_;
				int top_idx_{-1};
			};

			static void Run() {
				FreeList<100> free_list;

				FLStack<100> stack1(free_list);
				FLStack<100> stack2(free_list);
				FLStack<100> stack3(free_list);

				for (int i = 0; i < 40; ++i) stack2.Push(i);
				for (int i = 0; i < 20; ++i) stack1.Push(i);
				for (int i = 0; i < 40; ++i) stack3.Push(i);

				for (int i = 0; i < 20; ++i) stack1.Pop();
				for (int i = 0; i < 40; ++i) stack2.Pop();
				for (int i = 0; i < 40; ++i) stack3.Pop();

				for (int i = 0; i < 40; ++i) stack2.Push(i);
				for (int i = 0; i < 20; ++i) stack1.Push(i);
				for (int i = 0; i < 40; ++i) stack3.Push(i);

				for (int i = 0; i < 100; ++i) {
					std::cout << i << ": " << free_list[i]->next_idx << std::endl;
				}
			}
		};

		class Q3_4 {
			/* 하노이 탑. 3개의 탑과 N 개의 원판이 있다. 
			 초기조건: 첫번째 탑에 N 개의 원판이 있다. 이 때 원판들은 지름이 작은 원판이 위쪽에 오도록 배열된다.
			 
			 제약조건들
			 (1) 한 번에 하나의 원판만 옮길 수 있다.
			 (2) 맨 꼭대기에 있는 원판은 옆에 있는 탑으로 이동 옮길 수 있다.
			 (3) 원판은 자기보다 지름이 큰 원판 위로만 옮길 수 있다.
			 
			 스택을 사용하여 첫 번째 탑의 모든 원판을 마지막 탑으로 옮겨라.
			*/
		public:
			using Stack = Q3_1::FLStack<100>;

			static void Run() {
				Q3_1::FreeList<100> free_list;
				Q3_1::FLStack<100> stack1(free_list);
				Q3_1::FLStack<100> stack2(free_list);
				Q3_1::FLStack<100> stack3(free_list);

				// 첫번째 탑에 원판을 세팅
				const int COUNT = 26;
				for (int i = COUNT - 1; i >= 0; --i) {
					stack1.Push(i);
				}

				// 이동
				Move(COUNT, stack1, stack3, stack2);

				// 출력
				PopAllAndPrint("stack1", stack1);
				PopAllAndPrint("stack2", stack2);
				PopAllAndPrint("stack3", stack3);
			}

			static void PopAllAndPrint(std::string title, Q3_1::FLStack<100>& stack) {
				std::cout << title.c_str() << std::endl;
				try {
					for (int i = 0; i < 100; ++i) {
						int n = stack.Pop();
						std::cout << n << std::endl;
					}
				} catch (std::exception& ex) {

				}
				std::cout << std::endl;
			}

			static void Move(int count, Stack& src, Stack& dest, Stack& buf) {
				if (count < 1) return;
				if (count == 1) {
					int n = src.Pop();
					auto* dest_pop = dest.Peek();
					if (dest_pop && *dest_pop <= n) {
						assert(false);
						throw std::exception();
					} else {
						dest.Push(n);
					}
				} else {
					Move(count - 1, src, buf, dest);
					Move(1, src, dest, buf);	// buf 필요 없음
					Move(count - 1, buf, dest, src);
				}
			}
		};
	}
}

#endif /* crack_interview_ch3_hpp */
