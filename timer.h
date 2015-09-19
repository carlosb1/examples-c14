#ifndef _TIMER_H
#define _TIMER_H

#include <cstdio>
#include <ctime>



namespace cvc {
	namespace utils {
		class Timer
		{
		private:
			std::clock_t startTime;
		public:
			inline void start() {		
				startTime = std::clock();
			}
 
			inline int stop() {
				return (int)((( std::clock() - startTime ) / (double) CLOCKS_PER_SEC)*1000);
			}
		};
	}

}

#endif



