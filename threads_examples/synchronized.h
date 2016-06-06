#include <thread>
#include <shared_mutex>
#include <utility>
template <class T> struct synchronized {

	template <class F> std::result_of_t< F(T const&)> read (F&& f) const {
			auto && lock = read_lock();
			return std::forward<F>(f)(t);
	}

	template <class F> std::result_of_t< F(T&)> write (F&& f) {
			auto && lock = write_lock();
			return std::forward<F>(f)(t);
	}

	T copy() const& { 
		return (*this).read([&](auto&&t)->T{return t;});
	}
	T copy() && { return move(); }
	T move() { 
		return std::move(
				(*this).write([&](auto&&t)->T {return std::move(t);})
				);
		}

	private:
		mutable std::shared_timed_mutex mutex;
		std::shared_lock<std::shared_timed_mutex> read_lock() const {
			return std::shared_lock<std::shared_timed_mutex>(mutex);
		}
		
		std::unique_lock<std::shared_timed_mutex> write_lock() {
			return std::unique_lock<std::shared_timed_mutex>(mutex);	
		}
		T t;

	public:
		//relatively uninteresting boilerplate
		////ctor:
		

		template<class ...Args> explicit synchronized( Args&&... args): t(std::forward<Args>(args)...) {}

		synchronized( synchronized const& o): t(std::forward<decltype(o)>(o).copy()) {}
		synchronized( synchronized const&& o): t(std::forward<decltype(o)>(o).copy()) {}
		synchronized( synchronized & o): t(std::forward<decltype(o)>(o).copy()) {}
		synchronized( synchronized && o): t(std::forward<decltype(o)>(o).copy()) {}

		synchronized ( T const& o): t(std::forward<decltype(o)>(o)) {}
		synchronized ( T const&& o): t(std::forward<decltype(o)>(o)) {}
		synchronized ( T & o): t(std::forward<decltype(o)>(o)) {}
		synchronized ( T && o): t(std::forward<decltype(o)>(o)) {}
};
