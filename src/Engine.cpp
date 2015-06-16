#include "Engine.hpp"

Engine::Engine(void)
{
	this->init();
	return ;
}

Engine::Engine(Engine const &src)
{
	*this = src;
	return ;
}

Engine::Engine(int status) : _status(status)
{
	return ;
}

Engine::~Engine(void)
{
	delete [] this->vertex_tab;
	delete(this->map);
	SDL_Quit();
	return ;
}

int Engine::getStatus(void) const
{
	return (this->_status);
}

void Engine::setStatus(int status)
{
	this->_status = status;
	return ;
}

Engine &Engine::operator=(Engine const &rhs)
{
	this->_status = rhs.getStatus();
	return (*this);
}

std::ostream &operator<<(std::ostream &o, Engine const &i)
{
	o << i.getStatus() << std::endl;
	return (o);
}

int
Engine::sdlError(int code)
{
	std::cerr << "Code: " << code << " SDL Error: " << SDL_GetError() << std::endl;
	return (code);
}

void
Engine::setFOV(int new_fov)
{
	if (new_fov >= 20 && new_fov <= 160)
	{
		this->fov = new_fov;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(this->fov, (double)this->x_res / (double)this->y_res, this->z_near, this->z_far);
	}
}

void
Engine::initLight(void)
{
	this->light0status = true;
	this->light1status = true;

	// Blue Water
	glEnable(GL_LIGHT0);
	float ambientLight_0[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float diffuseLight_0[] = { 0.0f, 0.6f, 0.0f, 1.0f };
	float specularLight_0[] = { 0.0f, 0.9f, 0.0f, 1.0f };
	float position_0[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight_0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight_0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight_0);
	glLightfv(GL_LIGHT0, GL_POSITION, position_0);


	// Green Ground
	glEnable(GL_LIGHT1);
	float ambientLight_1[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float diffuseLight_1[] = { 0.0f, 0.0f, 0.6f, 1.0f };
	float specularLight_1[] = { 0.0f, 0.0f, 0.9f, 1.0f };
	float position_1[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight_1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight_1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight_1);
	glLightfv(GL_LIGHT1, GL_POSITION, position_1);

	float mcolor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float shine[] = { 0.1f };
	float specular[] = { 1.0f };
	glMaterialfv(GL_FRONT, GL_SHININESS, shine);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);
}

int
Engine::init(void)
{
	this->x_res = 1920;
	this->y_res = 1080;
	this->fov = 70;
	this->z_near = 0.01;
	this->z_far = 100;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return (sdlError(0));
	this->window = SDL_CreateWindow("mod1",
									SDL_WINDOWPOS_UNDEFINED,
									SDL_WINDOWPOS_UNDEFINED,
									this->x_res,
									this->y_res,
									SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (this->window == NULL)
		return (sdlError(0));
	if (!(this->context = SDL_GL_CreateContext(this->window)))
		return (sdlError(0));
	this->camera = new Camera();
	this->map = new Map(MAP_SIZE);
	this->vertex_tab = new float [this->map->fa_size];
	map->print();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(this->fov, (double)this->x_res / (double)this->y_res, this->z_near, this->z_far);

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	// Vertex reader
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, this->vertex_tab);

	initLight();

	// Generate and print points
	fillRandomly(0, 128);
	// printArray(0, 128);
	return (0);
}

void
Engine::printArray(int start, int end)
{
	int i;

	for (i = start; i < end; i++)
	{
		if (i % 10 == 0)
			std::cout << std::endl;
		std::cout << "(" << i << ")[" << this->vertex_tab[i] << "] ";
	}
}

void
Engine::loop(void)
{
	SDL_Event		event;
	int				quit;

	quit = 0;
	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				quit = 1;
				break;
			case SDL_MOUSEBUTTONDOWN:
				camera->onMouseButton(event.button);
				break;
			case SDL_MOUSEBUTTONUP:
				camera->onMouseButton(event.button);
			case SDL_MOUSEMOTION:
				camera->onMouseMotion(event.motion);
				break;
			case SDL_KEYUP:
				camera->onKeyboard(event.key);
				// if (event.key.keysym.scancode == SDL_SCANCODE_K)
				if (event.key.keysym.scancode == SDL_SCANCODE_PAGEUP)
					this->setFOV(this->fov + 10);
				if (event.key.keysym.scancode == SDL_SCANCODE_PAGEDOWN)
					this->setFOV(this->fov - 10);
				break;
			case SDL_KEYDOWN:
				camera->onKeyboard(event.key);
				if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					quit = 1;
				break;
			}
		}
		this->render();
		SDL_Delay(60 / 1000);
		SDL_GL_SwapWindow(this->window);
	}
}

void
Engine::render(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	this->camera->look();

	renderAxes();

 	glEnable(GL_LIGHTING); // light ON

 	glDisable(GL_LIGHT0);
 	glDisable(GL_LIGHT1);

 	glEnable(GL_LIGHT0);
	renderTriangleArray(0, 36);
	glDisable(GL_LIGHT0);

	glEnable(GL_LIGHT1);
	renderTriangleArray(36, 128);
	glDisable(GL_LIGHT1);


 	glDisable(GL_LIGHTING); // light OFF

	glFlush();
}

void
Engine::fillRandomly(int start, int size)
{
	int			i = start;
	int			end = start + size;

	while (i < end)
	{
		this->vertex_tab[i] = ((float)random() / (float)RAND_MAX) - 0.5;
		i++;
	}
}

void
Engine::renderTriangleArray(int start, int size)
{
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, start, size/3);
	glDisableVertexAttribArray(0);
}

void
Engine::renderAxes(void)
{
	glBegin(GL_LINES);

	// RED X RIGHT
    glColor3f(0.5f, 0.0f, 0.0f);
	glVertex3f(-0.5f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);

	// GREEN Y UP
    glColor3f(0.0f, 0.5f, 0.0f);
	glVertex3f(0.0f, -0.5f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	// BLUE Z FRONT
    glColor3f(0.0f, 0.0f, 0.5f);
	glVertex3f(0.0f, 0.0f, -0.5f);
	glVertex3f(0.0f, 0.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);

	glEnd();
}


