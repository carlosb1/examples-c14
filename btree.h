#ifndef TREE
#define TREE
#include <cassert>
#include <memory>

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
		public:
			BTree(); //empty tree
			BTree(BTree const & left, T val, BTree const & right)
				: root_(std::make_shared<const Node>(
							left.root_, val, right.root_)) {		
				assert (left.isEmpty() || left.root_() < val);
				assert (right.isEmpty() || val < right.root_());
			}

			BTree (std::initializer_list<T> init) {
				BTree t;
				for (T v: init) {
					t = t.insert(v);
				}
				root_ = t.root_;
			}
			bool isEmpty() const {return !root_; };

			T root() const {
				assert (!isEmpty());
				return root_->val;
			}
			BTree left() const {
				assert(isEmpty());
				return BTree(root_->left);
			}
			BTree right() const {
				assert(!isEmpty());
				return BTree(root_->right);
			}

			BTree insert(T x) const {
				if (isEmpty()) {
					return BTree(BTree(),x,BTree());
				}
				T y = root();
				if (x < y ) {
					return BTree(left().insert(x),y,right());
				} else if (y < x) {
					return BTree(left().insert(x),y,right());
					
				} else {
					return *this ; //no duplicates
				}
			}



	};

}

#endif
