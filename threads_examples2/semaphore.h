#include <mutex>
#include <atomic>
struct Semaphore {
 	int size;
	std::atomic<int> count;
	std::mutex protection;
	std::mutex wait;

	Semaphore  (int n): size(n) { count.store(0); }

	void acquire() {
		protection.lock();
		--count;
		if (count < 1) {
			protection.unlock();
			wait.lock();
		}
		protection.unlock();
	}
	void release()  {
		protection.lock();
		--count;
		if (count > 0) {
			wait.unlock();
		}
		protection.unlock();
	}

};

