#ifndef BTREE
#define BTREE
#include <cassert>
#include <memory>
#include <iostream>
#include <deque>

namespace collections {

		template <class T> class BTree {
			struct Node {
				Node(std::shared_ptr<const Node> const & _left
					, T _val
					, std::shared_ptr<const Node> const & _right)
					: left(_left), val(_val), right(_right) {}
				std::shared_ptr<const Node> left;
				T val;
				std::shared_ptr<const Node> right;		
			};

			explicit BTree(std::shared_ptr<const Node> const & node): root_(node) {}
		private:
			std::shared_ptr<const Node> root_;	
			
			std::pair<std::deque<std::shared_ptr<const Node>>,std::deque<int>> bfs() {
				std::deque<std::shared_ptr<const Node>> queue;
				queue.push_back(root_);
				std::deque<int> indexLevels;
				indexLevels.push_back(0);
				bfs_(queue,indexLevels);
				return std::make_pair(queue,indexLevels);
			}
			
			void bfs_(std::deque<std::shared_ptr<const Node>> &queue, std::deque<int> & indexLevels) {
				int newSize = (int)queue.size();
				int index =  indexLevels.back();
				//check if it is iterate all the queue
				if (index >=newSize) {
					return;
				}
				for (int i=index; i < newSize; i++) {
					std::shared_ptr<const Node> node = queue[i];
					if (node->left) {
						queue.push_back(node->left);
					}
					if (node->right) {
						queue.push_back(node->right);
					}
				}
				indexLevels.push_back(newSize);
				bfs_(queue,indexLevels);
			}

		public:
			BTree() {} //empty tree
			BTree(BTree const & left, T val, BTree const & right)
				: root_(std::make_shared<const Node>(
							left.root_, val, right.root_)) {		
				assert (left.isEmpty() || left.root() < val);
				assert (right.isEmpty() || val < right.root());
			}


			BTree (std::initializer_list<T> init) {
				BTree t;
				for (T v: init) {
					t = t.insert(v);
				}
				root_ = t.root_;
			}
			bool isEmpty() const {return !root_; };
			
		
			void print() {
				std::pair<std::deque<std::shared_ptr<const Node>>,std::deque<int>> result = bfs();	
				
				int previousIndex = 0;
				for (int index: result.second)  {
					for (int i = previousIndex; i < index; i++) {
						std::cout << "("<< result.first[i]->val<<")";
					}
					previousIndex = index;
					std::cout << std::endl;
				}
			}

			int height () {
					if (left().isEmpty() && right().isEmpty()) {
						return 1;
					}
					int leftHeight = -1;
					int rightHeight = -1;
					if (!left().isEmpty()) {
						leftHeight = left().height()+1;
					}
					if (!right().isEmpty()) {
						rightHeight = right().height()+1;
					}
					return leftHeight > rightHeight ? leftHeight : rightHeight;
			}


			
			bool isBalance() const {
				if (isEmpty()) {
					return true;
				}
				
				int leftHeight = 0;
				int rightHeight = 0;
				if (!left().isEmpty()) {
					leftHeight = left().height();
				}
				if (!right().isEmpty()) {
					rightHeight = right().height();
				}
				return (left().isBalance() && right().isBalance() && std::abs(leftHeight - rightHeight)<=1);

			}

			T root() const {
				assert ("Root is empty" && !isEmpty());
				return root_->val;
			}
			BTree left() const {
				assert("Left is empty" && !isEmpty());
				return BTree(root_->left);
			}
			BTree right() const {
				assert("Right is empty" && !isEmpty());
				return BTree(root_->right);
			}

			BTree insert(T x) const {
				if (isEmpty()) {
					return BTree(BTree<T>(),x,BTree<T>());
				}
				T y = root();
				if (x < y ) {
					return BTree<T>(left().insert(x),y,right());
				} else if (y < x) {
					return BTree<T>(left(),y,right().insert(x));
					
				} else {
					return *this ; //no duplicates
				}
			}



	};

}

#endif
