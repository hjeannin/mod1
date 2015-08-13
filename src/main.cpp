#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Engine.hpp"
#include "Grid.hpp"

int				main()
{
//	Engine		engine;

//	srandom(time(0));
//	engine.loop();

	Grid		my_grid(3);

	std::cout << my_grid;
	my_grid.print();
	return (0);
}
