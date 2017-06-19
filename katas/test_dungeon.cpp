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
		//TODO It can not be repeated
		return doorGenerator->make(size);
	}

	void enter() {
	
	}

	std::pair<int,int> getPlace() {
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
	SECTION("with a size >=2, contains and enter and exit") {

		//TODO set up for the creation of doors
		std::shared_ptr<FakeDoorGenerator> fakeDoorGenerator =  std::make_shared<FakeDoorGenerator>();
		std::shared_ptr<DoorGenerator> doorGenerator =  std::dynamic_pointer_cast<DoorGenerator>(fakeDoorGenerator);
		Dungeon dungeon(doorGenerator,2);
		fakeDoorGenerator->door = std::make_pair<int,int>(0,0);
		std::pair<int,int>  exit = dungeon.getExit();
		REQUIRE(exit.first==0 );
		REQUIRE(exit.second==0 );
		fakeDoorGenerator->door = std::make_pair<int,int>(1,1);
		std::pair<int,int> enter = dungeon.getEnter();
		
		REQUIRE(enter.first==1);
		REQUIRE(enter.second==1);
	}

	SECTION("with permits enter a new explorer in the position 0, 0") {
		std::shared_ptr<FakeDoorGenerator> fakeDoorGenerator =  std::make_shared<FakeDoorGenerator>();
		std::shared_ptr<DoorGenerator> doorGenerator =  std::dynamic_pointer_cast<DoorGenerator>(fakeDoorGenerator);
		Dungeon dungeon(doorGenerator,2);
		fakeDoorGenerator->door = std::make_pair<int,int>(0,0);

		dungeon.enter();
		std::pair<int,int> posic = dungeon.getPlace();
		
		REQUIRE(posic.first==0 );
		REQUIRE(posic.second==0 );

		



	}


	

 }	

