#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utility>
#include <cstdlib>
#include <ctime>


//static Cell Empty

struct Cell {
	Cell(int id_=-1, int posic_=-1): id(id_), posic(posic_) {};
	int id;
	int posic;
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
	std::shared_ptr<Cell> current;
	bool foundExit;
	int countId=0;

	//TODO size refactorization!
	Dungeon(std::shared_ptr<DoorGenerator> & doorGenerator_, int size_=0): size(size_), doorGenerator(doorGenerator_){
		std::pair<Cell, Cell> doors = doorGenerator->make(size);
		this->entrance = doors.first;
		this->exit = doors.second;
		this->foundExit = false;

		//TODO refactor this code
		entrance.id=countId;
		countId++;
		std::shared_ptr<Cell> ptrEntrance = std::make_shared<Cell>(this->entrance);
		std::shared_ptr<Cell> parentCell = ptrEntrance;
		std::shared_ptr<Cell> nextCell = ptrEntrance;
		for (int index=0; index < (size-2); index++) {
			nextCell = std::make_shared<Cell>(countId,1);
			countId++;
			parentCell->connectedCells.push_back(nextCell);
		}
		exit.id=countId;
		//TODO hardcoded
		exit.posic=1;
		countId++;
		nextCell->connectedCells.push_back(std::make_shared<Cell>(this->exit));
	
		this->current = ptrEntrance;
	};


 	
	
	Cell getExit() {
		return this->exit;
	}

	Cell getEnter() {
		return this->entrance;
	}

	Cell getPlace() {
		return Cell(0);
	}

	bool isExit() {
		return foundExit;
	}

	void visit (int numDoor) {
		//TODO check to avoid wrong doors
		for (std::shared_ptr<Cell> cell: this->current->connectedCells) {
			if (cell->posic == numDoor) {
				this->current = cell;
				if (this->current->id == this->exit.id) {
					this->foundExit = true;
				}
				return;
			}
		}


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
	REQUIRE (exit.id == 1);
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
		Cell posic = dungeon.getPlace();
		REQUIRE(posic.id==0 );
	}

	SECTION("with enters in see available doors") {
		std::vector<door> doors = dungeon.getDoors();
		REQUIRE(doors.size()==4);
		REQUIRE(doors[0]==wall);
		REQUIRE(doors[1]==open);
		REQUIRE(doors[2]==open);
		REQUIRE(doors[3]==wall);

	}

	//TODO good practicei? force to implement 
	SECTION("with enters an choose first door") {
		REQUIRE(dungeon.isExit()==false);
		std::vector<door> doors = dungeon.getDoors();
		dungeon.visit(1);
		REQUIRE(dungeon.isExit()==true);
	}

	SECTION("with enters a choose first door and it arreives to the end") {
		dungeon.visit(1);
		REQUIRE(dungeon.isExit()==true);
	}

	SECTION("with enters choose first and first door and it arrives to the end") {
		REQUIRE(dungeon.isExit()==false);
		dungeon.visit(1);
		REQUIRE(dungeon.isExit()==true);
	}
	


 }

TEST_CASE("A dungeon with three cells should","[dungeon]") {
	std::shared_ptr<DoorGenerator> doorGenerator =  std::make_shared<FakeDoorGenerator>(Cell(0),Cell(1));
	Dungeon dungeon(doorGenerator,3);

	SECTION("with enters choose first and first door and it arrives to the end") {
		dungeon.visit(1);
		REQUIRE(dungeon.isExit()==false);
		dungeon.visit(1);
		REQUIRE(dungeon.isExit()==true);
	}
	

}

