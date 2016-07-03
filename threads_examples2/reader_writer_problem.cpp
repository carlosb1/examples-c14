#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>
#include <mutex>


std::atomic_bool finish_reader(false);
std::atomic_bool finish_writer(false);


void reader() {
	while (!finish_reader) {
		std::cout  <<"I am reading" << '\n';
//		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	std::cout << "It is finished reader" << '\n';
}
void writer() {
	while(!finish_writer) {
		std::cout << "I am writing" << '\n';
//		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	std::cout << "It is finished writer" << '\n';
}
std::mutex mutex;

void lock_reader() {
	mutex.lock();	
	reader();
	mutex.unlock();


}
void lock_writer() {
	mutex.lock();
	writer();
	mutex.unlock();

}

std::mutex mutex_reader;
std::mutex mutex_writer;

int count_readers=0;
void multiple_lock_reader(int num_reader) {
	
	while (!finish_reader) {
		mutex_reader.lock();
		count_readers++;
		if (count_readers==1) {
			mutex_writer.lock();	
		}
		mutex_reader.unlock();	
		
		std::cout  <<"I am reading  reader: "<< num_reader << '\n';
	
		mutex_reader.lock();
		count_readers--;
		if (count_readers==0) {
			mutex_writer.unlock();	
		}
		mutex_reader.unlock();	
	}


}
void multiple_lock_writer() {
	while(!finish_writer) {
		mutex_writer.lock();	
		std::cout << "I am writing" << '\n';
		mutex_writer.unlock();
	}

}


void versionWithoutSync() {
	std::thread tReader(reader);
	std::thread tWriter(writer);
	std::this_thread::sleep_for(std::chrono::seconds(2));
		
	finish_reader = true;
	finish_writer = true;
	tReader.join();
	tWriter.join();
}

void versionLockSync() {
	std::thread tWriter(lock_writer);
	std::thread tReader(lock_reader);
	std::this_thread::sleep_for(std::chrono::seconds(4));
		
	finish_reader = true;
	finish_writer = true;
	tReader.join();
	tWriter.join();
}

void versionMultipleLockSync() {
	std::thread tReader(multiple_lock_reader,1);
	std::thread tReader2(multiple_lock_reader,2);
	std::thread tReader3(multiple_lock_reader,3);
	std::thread tWriter(multiple_lock_writer);
	std::this_thread::sleep_for(std::chrono::seconds(4));
		
	finish_reader = true;
	finish_writer = true;
	tReader.join();
	tReader2.join();
	tReader3.join();
	tWriter.join();
}





int main () {
//	versionWithoutSync();
//	versionLockSync();
	versionMultipleLockSync();
}




