#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utility>
#include <cstdlib>
#include <ctime>


//static std::pair<int,int> Empty


//TODO check random door generator
struct DoorGenerator {
	virtual std::pair<std::pair<int,int>,std::pair<int,int>> make(int size)  = 0;
};

struct FakeDoorGenerator: DoorGenerator {
	std::pair<int,int> entrance;
	std::pair<int,int> exit;
	FakeDoorGenerator(std::pair<int,int> entrance_, std::pair<int,int> exit_): entrance(entrance_), exit(exit_) {};
	std::pair<std::pair<int,int>,std::pair<int,int>> make(int size) {
		return std::make_pair(entrance,exit); 
	};
};

//TODO pending to test
struct RandomDoorGenerator: DoorGenerator {


	RandomDoorGenerator() {
	
	};

	std::pair<std::pair<int,int>,std::pair<int,int>> make(int size) {
		std::srand(std::time(0));
		int random_variable = (int)(std::rand() % size);
		
	}


};



struct Dungeon  {
	int size;
	std::shared_ptr<DoorGenerator> doorGenerator;

	std::pair<int,int> entrance;
	std::pair<int,int> exit;
	Dungeon(std::shared_ptr<DoorGenerator> & doorGenerator_, int size_=0): size(size_), doorGenerator(doorGenerator_){
		std::pair<std::pair<int,int>, std::pair<int,int>> doors = doorGenerator->make(size);
		this->entrance = doors.first;
		this->exit = doors.second;
	};

 	std::pair <int,int> getExit() {
		return this->exit;
	}

	std::pair <int,int> getEnter() {
		return this->entrance;
	}

	void enter() {
	
	}

	std::pair<int,int> getPlace() {
		return std::make_pair(0,0);
	}

};


//TODO Check incorrect dungeons (negative)

TEST_CASE ("An empty dungeon is initialised correctly", "[empty_dungeon]")  {
	std::shared_ptr<DoorGenerator> fakeDoorGenerator =  std::make_shared<FakeDoorGenerator>(std::make_pair(0,0),std::make_pair(0,0));
	Dungeon dungeon(fakeDoorGenerator,1);
	std::pair<int,int> exit = dungeon.getExit();
	REQUIRE (exit.first == 0);
	REQUIRE (exit.second == 0);
}

TEST_CASE("A dungeon should","[dungeon]") {
	std::shared_ptr<DoorGenerator> doorGenerator =  std::make_shared<FakeDoorGenerator>(std::make_pair(0,0),std::make_pair(1,1));
	Dungeon dungeon(doorGenerator,2);
	SECTION("with a size >=2, contains and enter and exit") {

		std::pair<int,int> enter = dungeon.getEnter();
		REQUIRE(enter.first==0);
		REQUIRE(enter.second==0);
		std::pair<int,int>  exit = dungeon.getExit();
		REQUIRE(exit.first==1);
		REQUIRE(exit.second==1);
	}

	SECTION("with permits enter a new explorer in the position 0, 0") {
		dungeon.enter();
		std::pair<int,int> posic = dungeon.getPlace();
		REQUIRE(posic.first==0 );
		REQUIRE(posic.second==0 );

		



	}


	

 }	

