#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <utility>

struct Dungeon  {

	int size;
	Dungeon(int size_=0): size(size_) {};

 	std::pair <int,int> getExit() {
		return std::make_pair(0,0);
	}

};


//TODO Check incorrect dungeons (negative)

TEST_CASE ("An empty dungeon is initialised correctly ", "[dungeon]")  {
	Dungeon dungeon(1);
	std::pair<int,int> exit = dungeon.getExit();
	REQUIRE (exit.first == 0);
	REQUIRE (exit.second == 0);
		
}

