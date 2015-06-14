#ifndef ENGINE_HPP
# define ENGINE_HPP

# include <iostream>
# include <unistd.h>
# include "Camera.hpp"

# define VTAB 5000 // vertex_tab size
# define PARTY_START	36
# define PARTY_SIZE		300

class Engine
{
private:
	int _status;

public:
	SDL_Window			*window;
	SDL_GLContext		context;
	Camera				*camera;
	float				*vertex_tab;
	bool				moving;

	int					x_res;
	int					y_res;
	int					fov;
	double				z_near;
	double				z_far;

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
	void	renderShape(void);
	void	renderGround(void);
	void	switchLight(bool l0, bool l1, bool l2);
	void	moveYourBody(int start, int size);
	void	makeWTF(int start, int size);
	void	makeCube(float s);
	void	printArray(int start, int end);
	void	renderTriangleArray(int start, int size);
	void	renderPointArray(int start, int size);
	int		sdlError(int code);
	void	setFOV(int new_fov);
	void	initLight(void);
	bool	randomBool(void);
	void	randomLight(void);
};

std::ostream &operator<<(std::ostream &o, Engine const &i);

#endif
