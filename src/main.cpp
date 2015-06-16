#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Engine.hpp"

int				main()
{
	Engine		engine;

	srandom(time(0));
	engine.loop();
	return (0);
}
