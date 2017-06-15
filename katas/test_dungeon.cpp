#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utility>
#include <cstdlib>
#include <ctime>


//static std::pair<int,int> Empty


//TODO check random door generator
struct DoorGenerator {
	virtual std::pair<int,int> make(int size) = 0;
};

struct FakeDoorGenerator: DoorGenerator {
	std::pair<int,int> door;
	FakeDoorGenerator() {};
	std::pair<int,int> make(int size) {
		return door; 
	};
};

//TODO pending to test
struct RandomDoorGenerator: DoorGenerator {
	
	RandomDoorGenerator() {
	
	};

	std::pair<int,int> make(int size) {
		std::srand(std::time(0));
		int random_variable = (int)(std::rand() % size);
		
	}


};



struct Dungeon  {
	int size;
	std::shared_ptr<DoorGenerator> doorGenerator;
	Dungeon(std::shared_ptr<DoorGenerator> & doorGenerator_, int size_=0): size(size_), doorGenerator(doorGenerator_){};

 	std::pair <int,int> getExit() {
		//TODO it can be repetead
		return doorGenerator->make(size);
	}

	std::pair <int,int> getEnter() {
		return std::make_pair(0,0);
	}

};


//TODO Check incorrect dungeons (negative)

TEST_CASE ("An empty dungeon is initialised correctly", "[empty_dungeon]")  {
	std::shared_ptr<DoorGenerator> fakeDoorGenerator =  std::make_shared<FakeDoorGenerator>();
	Dungeon dungeon(fakeDoorGenerator,1);
	std::pair<int,int> exit = dungeon.getExit();
	REQUIRE (exit.first == 0);
	REQUIRE (exit.second == 0);
}

TEST_CASE("A dungeon should","[dungeon]") {
	SECTION("with a size 2, contains and enter and exit") {
		std::shared_ptr<DoorGenerator> fakeDoorGenerator =  std::make_shared<FakeDoorGenerator>();
		Dungeon dungeon(fakeDoorGenerator,2);
		std::pair<int,int>  exit = dungeon.getExit();
		//TODO refact. creating abstraction class
		REQUIRE(exit.first>=0 );
		REQUIRE(exit.second>=0 );
		std::pair<int,int> enter = dungeon.getEnter();
		REQUIRE(enter.first >=0);
		REQUIRE(enter.second >=0);
	}

 }	

