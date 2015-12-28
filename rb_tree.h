#ifndef TREE
#define TREE
#include <cassert>
#include <memory>
/*
Our implementation of the persistent red-black tree follows the Chris Okasaki’s book. As Chris asserts, 
this is one of the fastest implementations there is, and he offers hints to make it even faster. Of course 
there are many imperative implementations of red-black trees, including STL’s std::set and std::map. 
Persistent RB-trees match their performance perfectly when it comes to searching. Insertion and deletion, 
which are O(log(N)) for either implementation, are slower by a constant factor because of the need to 
copy the path from root to leaf. On the other hand, the persistent implementation is thread-safe and 
synchronization-free (except for reference counting in shared_ptr — see discussion in my previous blog).
 */
namespace collections {

		template <class T> class RBTree {
			enum  Color {R, B};

			struct Node {
				Node(
					Color _c
					,std::shared_ptr<const Node> const & _left
					, T _val
					, std::shared_ptr<const Node> const & _right)
					: c(_c), left(_left), val(_val), right(_right) {}
				Color c;
				std::shared_ptr<const Node> left;
				T val;
				std::shared_ptr<const Node> right;		
			};

			explicit RBTree(std::shared_ptr<const Node> const & node): root_(node) {}
			Color rootColor() const {
				assert(!isEmpty());
				return root_->_c;
			}
		private:
			std::shared_ptr<const Node> root_;
			Color c;
		public:
			RBTree(); //empty tree
			RBTree(Color c_, RBTree const & left, T val, RBTree const & right)
				: root_(std::make_shared<const Node>(c_,left.root_, val, right.root_)) {		
				assert (left.isEmpty() || left.root_() < val);
				assert (right.isEmpty() || val < right.root_());
			}

			RBTree (std::initializer_list<T> init) {
				RBTree t;
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
			RBTree left() const {
				assert(isEmpty());
				return RBTree(root_->left);
			}
			RBTree right() const {
				assert(!isEmpty());
				return RBTree(root_->right);
			}
			RBTree insert(T x) const {
				RBTree t = ins(x);
				return RBTree(B,t.left(),t.root(),t.right());
			}

			RBTree ins(T x) const {
				
				if (isEmpty()) {
					return RBTree(R,RBTree(),x,RBTree());
				}
				T y = root();
				Color c = rootColor();
				
				if (x < y ) {
					return balance(c,left().ins(x),y,right());
				} else if (y < x) {
					return balance(c,left(),y,right().ins(x));
				} else {
					return *this ; //no duplicates
				}

			}

			RBTree balance (Color c
					, RBTree const & left
					, T x
					, RBTree const & right) {
				if (c==B && left.doubleLeft()) {
					return RBTree(R,left.left().paint(B),left.root(), RBTree(B,left.right(),x,right));
				} else if (c==B && left.doubleRight()) {
					return RBTree(R,RBTree(B,left.left(),left.root(),left.right().left()),left.right().root(),RBTree(B,left.right().right(),x,right));
				} else if (c==B && right.doubleLeft()) {
					return RBTree(B,left,x,right.left().left(),right.left().root(),RBTree(B,right.left().rigth(),right.root(),right.right()));
				} else if (c==B && right.doubleRight()) {
					return RBTree(R,RBTree(B,left,x,right.left()),right.root(),right.right().paint(B));
				} else {
					return RBTree(c,left,x,right);

				}
			}

			bool doubleLeft() const {
				return !isEmpty() && rootColor() ==R && !left().isEmpty() && left().rootColor() == R;
			}	
			
			bool doubleRight() const {
				return !isEmpty() && rootColor() == R && !right().isEmpty() && right().rootColor() == R;
			}
			RBTree paint(Color c) const {
				assert(!isEmpty());
				return RBTree(c,left(),root(),right());
			}





	};

}

#endif
