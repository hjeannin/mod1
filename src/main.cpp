#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Engine.hpp"
#include "Map.hpp"

int				main()
{
	Engine		engine;
	Map			*map = new Map(5);

	srandom(time(0));
	engine.init();
	engine.loop();
	map->print();
	delete(map);
	return (0);
}
