#ifndef ENGINE_HPP
# define ENGINE_HPP

# include <iostream>
# include <unistd.h>
# include "Camera.hpp"

# define VTAB 5000 // vertex_tab size

class Engine
{
private:
	int _status;

public:
	SDL_Window			*window;
	SDL_GLContext		context;
	Camera				*camera;
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
	void	loop(void);
	void	render(void);
	void	renderAxes(void);
	void	fillRandomly(int start, int size);
	void	printArray(int start, int end);
	void	renderTriangleArray(int start, int size);
	void	renderPointArray(int start, int size);
	int		sdlError(int code);
	void	setFOV(int new_fov);
	void	initLight(void);
};

std::ostream &operator<<(std::ostream &o, Engine const &i);

#endif
