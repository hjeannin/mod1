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
	std::cout << std::endl << "IN (2, 2) : " << my_grid.access(2, 2) << std::endl;
	std::cout << std::endl << "IN (0, 2) : " << my_grid.access(0, 2) << std::endl;
	std::cout << std::endl << "IN (1, 2) : " << my_grid.access(1, 2) << std::endl;
	std::cout << std::endl << "IN (0, 0) : " << my_grid.access(0, 0) << std::endl;
	std::cout << std::endl << "IN (2, -1) : " << my_grid.access(2, -1) << std::endl;
	return (0);
}
