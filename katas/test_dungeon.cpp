#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utility>
#include <cstdlib>
#include <ctime>


//static Cell Empty

struct Cell {
	Cell(int id_=-1): id(id_) {};
	int id;
	std::vector<std::shared_ptr<Cell>> connectedCells;
};



//TODO check random door generator
struct DoorGenerator {
	virtual std::pair<Cell,Cell> make(int size)  = 0;
};

struct FakeDoorGenerator: DoorGenerator {
	Cell entrance;
	Cell exit;
	FakeDoorGenerator(Cell entrance_, Cell exit_): entrance(entrance_), exit(exit_) {};
	std::pair<Cell, Cell> make(int size) {
		return std::make_pair(entrance,exit); 
	};
};

//TODO pending to test and finish
struct RandomDoorGenerator: DoorGenerator {
	RandomDoorGenerator() {
	
	};

	std::pair<Cell,Cell> make(int size) {
		std::srand(std::time(0));
		int random_variable = (int)(std::rand() % size);	
	}




};

enum door {
	wall=0,
	open=1,
};


struct Dungeon  {
	int size;
	std::shared_ptr<DoorGenerator> doorGenerator;

	Cell entrance;
	Cell exit;
	bool foundExit;
	Dungeon(std::shared_ptr<DoorGenerator> & doorGenerator_, int size_=0): size(size_), doorGenerator(doorGenerator_){
		std::pair<Cell, Cell> doors = doorGenerator->make(size);
		this->entrance = doors.first;
		this->exit = doors.second;
		this->foundExit = false;
	};

 	Cell getExit() {
		return this->exit;
	}

	Cell getEnter() {
		return this->entrance;
	}

	void enter() {
	
	}

	Cell getPlace() {
		return Cell(0);
	}

	bool isExit() {
		return foundExit;
	}

	void visit (int numDoor) {
		this->foundExit = true;
	}

	std::vector<door>  getDoors() {
		std::vector<door> doors { wall,open,open,wall };
		return doors; 
	}

};


//TODO Check incorrect dungeons (negative)

TEST_CASE ("An empty dungeon is initialised correctly", "[empty_dungeon]")  {
	std::shared_ptr<DoorGenerator> fakeDoorGenerator =  std::make_shared<FakeDoorGenerator>(Cell(0),Cell(0));
	Dungeon dungeon(fakeDoorGenerator,1);
	Cell exit = dungeon.getExit();
	REQUIRE (exit.id == 0);
}

TEST_CASE("A dungeon with only two cells should","[dungeon]") {
	std::shared_ptr<DoorGenerator> doorGenerator =  std::make_shared<FakeDoorGenerator>(Cell(0),Cell(1));
	Dungeon dungeon(doorGenerator,2);
	
	SECTION("with a size >=2, contains and enter and exit") {
		Cell enter = dungeon.getEnter();
		REQUIRE(enter.id==0);
		Cell  exit = dungeon.getExit();
		REQUIRE(exit.id==1);
	}

	SECTION("with permits enter a new explorer in the position 0") {
		dungeon.enter();
		Cell posic = dungeon.getPlace();
		REQUIRE(posic.id==0 );
	}

	SECTION("with enters in see available doors") {
		dungeon.enter();
		std::vector<door> doors = dungeon.getDoors();
		REQUIRE(doors.size()==4);
		REQUIRE(doors[0]==wall);
		REQUIRE(doors[1]==open);
		REQUIRE(doors[2]==open);
		REQUIRE(doors[3]==wall);

	}

	//TODO good practice force to implement 
	SECTION("with enters an choose first door") {
		dungeon.enter();
		REQUIRE(dungeon.isExit()==false);
		std::vector<door> doors = dungeon.getDoors();
		dungeon.visit(0);
		REQUIRE(dungeon.isExit()==true);
	}


	


 }



