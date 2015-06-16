#ifndef ENGINE_HPP
# define ENGINE_HPP

# include <iostream>
# include <unistd.h>
# include "Camera.hpp"
# include "Map.hpp"

# define MAP_SIZE	3

class Engine
{
private:
	int _status;

public:
	SDL_Window			*window;
	SDL_GLContext		context;
	Camera				*camera;
	Map					*map;
	float				*vertex_tab;

	int					x_res;
	int					y_res;
	int					fov;
	double				z_near;
	double				z_far;

	bool				light0status;
	bool				light1status;

	Engine(void);
	Engine(const Engine &src);
	Engine(int status);
	~Engine(void);
	int getStatus(void) const;
	void setStatus(int status);
	Engine &operator=(Engine const &rhs);

	int		init(void);
	void	printArray(float *array, int array_size);
	void	loop(void);
	void	render(void);
	void	renderAxes(void);
	void	renderGround(void);
	void	renderWater(void);
	void	fillRandomly(int start, int size);
	int		sdlError(int code);
	void	setFOV(int new_fov);
	void	initLight(void);
};

std::ostream &operator<<(std::ostream &o, Engine const &i);

#endif
