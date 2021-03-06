#include <exception>
#include <memory>
#include <stack>
#include <mutex>

struct empty_stack: std::exception {
	const char * what() const throw();
};

template <typename T> class ThreadSafeStack {
	private:
		std::stack<T> data;
		mutable std::mutex m;

	public:
		ThreadSafeStack(){}

		ThreadSafeStack(const ThreadSafeStack& other) {
			std::lock_guard<std::mutex> lock(other.m);
			data=other.data;
		}
		
		ThreadSafeStack& operator=(const ThreadSafeStack&)= delete;

		void push(T new_value){
			std::lock_guard<std::mutex> lock(m);
			data.push(new_value);
		}
		std::shared_ptr<T> pop() {
			std::lock_guard<std::mutex> lock(m);
			if (data.empty()) throw empty_stack();
			//value = data.top();
			std::shared_ptr<T> const res (std::make_shared<T>(data.top()));
			data.pop();
			return res;
		}
		
		void pop (T&value) {
			std::lock_guard<std::mutex> lock(m);
			if (data.empty()) throw empty_stack();
			value = data.top();
			data.pop();
		}
		
		bool empty() const {
			std::lock_guard<std::mutex> lock(m);
			return data.empty();
		}


};
