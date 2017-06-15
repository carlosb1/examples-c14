#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utility>


//static std::pair<int,int> Empty

struct Dungeon  {

	int size;
	Dungeon(int size_=0): size(size_) {};

 	std::pair <int,int> getExit() {
		return std::make_pair(0,0);
	}

};


//TODO Check incorrect dungeons (negative)

TEST_CASE ("An empty dungeon is initialised correctly", "[empty_dungeon]")  {
	Dungeon dungeon(1);
	std::pair<int,int> exit = dungeon.getExit();
	REQUIRE (exit.first == 0);
	REQUIRE (exit.second == 0);
}

TEST_CASE("A dungeon should","[dungeon]") {
	SECTION("with a size 2, contains and enter and exit") {
		Dungeon dungeon(2);
		std::pair<int,int>  exit = dungeon.getExit();
		//TODO refact. creating abstraction class
		REQUIRE (exit.first>=0 );
		REQUIRE (exit.second>=0 );

			
	
	}
 }	

