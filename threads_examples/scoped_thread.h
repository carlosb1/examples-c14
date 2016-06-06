#include <thread>
#ifndef SCOPED_THREAD
#define SCOPED_THREAD

class ScopedThread
{
	std::thread t;
	public:
		explicit ScopedThread(std::thread t_):
			t(std::move(t_))
			{
				if (!t.joinable()) {
					throw std::logic_error("No thread");
				}
			}
		~ScopedThread () {
			t.join();
		}
		ScopedThread(ScopedThread const&)=delete;
		ScopedThread operator=(ScopedThread const&)=delete;
};


#endif
