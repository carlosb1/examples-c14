#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utility>
#include <cstdlib>
#include <ctime>



struct Cell {
	Cell(int id_=-1, int posic_=-1): id(id_), posic(posic_) {};
	int id;
	int posic;
	std::vector<std::shared_ptr<Cell>> connectedCells;
};



enum door {
	wall=0,
	open=1,
};



struct Dungeon  {
	int numberCells;
	
	std::shared_ptr<Cell>  entrance;
	std::shared_ptr<Cell>  exit;
	std::shared_ptr<Cell> current;
	bool foundExit;
	int countId=0;

	//TODO numberCells refactorization!
	Dungeon( int numberCells_=0): numberCells(numberCells_){
		this->entrance  = std::make_shared<Cell>(countId);
		countId++;

		this->foundExit = false;

		std::shared_ptr<Cell> parentCell = entrance;
		std::shared_ptr<Cell> nextCell = entrance;
		for (int index=0; index < numberCells; index++) {
			nextCell = std::make_shared<Cell>(countId,1);
			countId++;
			parentCell->connectedCells.push_back(nextCell);
			parentCell = nextCell;
		}
		this->exit = nextCell;
		this->current = entrance;
	};


 	
	
	Cell getExit() {
		return *this->exit.get();
	}

	Cell getEnter() {
		return *this->entrance.get();
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
				if (this->current->id == this->exit->id) {
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
	Dungeon dungeon(1);
	Cell exit = dungeon.getExit();
	REQUIRE (exit.id == 1);
}

TEST_CASE("A dungeon with only two cells should","[dungeon]") {
	Dungeon dungeon(2);
	
	SECTION("with a numberCells >=2, contains and enter and exit") {
		Cell enter = dungeon.getEnter();
		REQUIRE(enter.id==0);
		Cell  exit = dungeon.getExit();
		REQUIRE(exit.id==2);
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

	SECTION("with enters an choose first door") {
		REQUIRE(dungeon.isExit()==false);
		dungeon.visit(1);
		dungeon.visit(1);
		REQUIRE(dungeon.isExit()==true);
	}

	


 }

TEST_CASE("A dungeon with three cells should","[dungeon]") {
	Dungeon dungeon(3);

	SECTION("with enters choose first and first door and it arrives to the end") {
		dungeon.visit(1);
		REQUIRE(dungeon.isExit()==false);
		dungeon.visit(1);
		dungeon.visit(1);
		REQUIRE(dungeon.isExit()==true);
	}
	

}

