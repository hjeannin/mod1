#include "Engine.hpp"

Engine::Engine(void)
{
	this->vertex_tab = new float [VTAB];
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
	float ambientLight_0[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float diffuseLight_0[] = { 0.6f, 0.0f, 0.0f, 1.0f };
	float specularLight_0[] = { 0.9f, 0.0f, 0.0f, 1.0f };
	float position_0[] = { -0.4f, 0.0f, 0.6f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight_0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight_0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight_0);
	glLightfv(GL_LIGHT0, GL_POSITION, position_0);


	glEnable(GL_LIGHT1);
	float ambientLight_1[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float diffuseLight_1[] = { 0.0f, 0.6f, 0.0f, 1.0f };
	float specularLight_1[] = { 0.0f, 0.9f, 0.0f, 1.0f };
	float position_1[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight_1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight_1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight_1);
	glLightfv(GL_LIGHT1, GL_POSITION, position_1);

	glEnable(GL_LIGHT2);
	float ambientLight_2[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	float diffuseLight_2[] = { 0.0f, 0.0f, 0.6f, 1.0f };
	float specularLight_2[] = { 0.0f, 0.0f, 0.9f, 1.0f };
	float position_2[] = { 0.4f, 0.0f, 0.6f, 1.0f };
	glLightfv(GL_LIGHT2, GL_AMBIENT, ambientLight_2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseLight_2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specularLight_2);
	glLightfv(GL_LIGHT2, GL_POSITION, position_2);

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
	int i;
	this->x_res = 1920;
	this->y_res = 1080;
	this->fov = 70;
	this->z_near = 0.01;
	this->z_far = 100;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return (sdlError(0));
	this->window = SDL_CreateWindow("Pouet",
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
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(this->fov, (double)this->x_res / (double)this->y_res, this->z_near, this->z_far);

	glEnable(GL_DEPTH_TEST);

	glPointSize(16);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glShadeModel(GL_SMOOTH);

	// Vertex reader
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, this->vertex_tab);

	initLight();
	this->moving = false;

	// Generate and print points
	makeCube(0.4);
	makeWTF(PARTY_START, PARTY_SIZE);
	printArray(0, 336);
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
				if (event.key.keysym.scancode == SDL_SCANCODE_L)
					this->randomLight();
				if (event.key.keysym.scancode == SDL_SCANCODE_M)
					this->moving = !this->moving;
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

//	this->renderShape();

 	renderPointArray(0, PARTY_START);

 	glEnable(GL_LIGHTING); // light ON
	renderTriangleArray(PARTY_START, PARTY_SIZE);

	if (this->moving == true)
		moveYourBody(PARTY_START, PARTY_SIZE);

 	glDisable(GL_LIGHTING); // light OFF

	glFlush();
}

bool
Engine::randomBool(void)
{
	return rand() % 2 == 1;
}

void
Engine::switchLight(bool l0, bool l1, bool l2)
{
	if (l0 == true)
		glEnable(GL_LIGHT0);
	else
		glDisable(GL_LIGHT0);
	if (l1 == true)
		glEnable(GL_LIGHT1);
	else
		glDisable(GL_LIGHT1);
	if (l2 == true)
		glEnable(GL_LIGHT2);
	else
		glDisable(GL_LIGHT2);
}

void
Engine::randomLight(void)
{
	bool		tab_bool[3] = {randomBool(), randomBool(), randomBool()};
	if (tab_bool[0] == false && tab_bool[1] == false && tab_bool[2] == false)
	{
		tab_bool[0] = true;
		tab_bool[1] = true;
		tab_bool[2] = true;
	}
	this->switchLight(tab_bool[0], tab_bool[1], tab_bool[2]);
}

void
Engine::moveYourBody(int start, int size)
{
	int			i;
	int			end = start + size;
	float		encrease = 0.02;
	static int	growth = -10;

	growth++;
	if (growth <= 0)
	{
		// size--
		i = start;
		while (i < end)
		{
			if (this->vertex_tab[i] < 0)
				this->vertex_tab[i] = this->vertex_tab[i] + encrease;
			else
				this->vertex_tab[i] = this->vertex_tab[i] - encrease;
			i++;
		}
	}
	else
	{
		// size++
		i = start;
		while (i < end)
		{
			if (this->vertex_tab[i] < 0)
				this->vertex_tab[i] = this->vertex_tab[i] - encrease;
			else
				this->vertex_tab[i] = this->vertex_tab[i] + encrease;
			i++;
		}
	}
	if (growth >= 10)
	{
		growth = -10;
		this->makeWTF(start, size);
	}
}

void
Engine::makeWTF(int start, int size)
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
Engine::renderPointArray(int start, int size)
{
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_POINTS, start, size/3);
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

void
Engine::makeCube(float s)
{
	this->vertex_tab[0] = s;
	this->vertex_tab[1] = s;
	this->vertex_tab[2] = s;

	this->vertex_tab[3] = s;
	this->vertex_tab[4] = -s;
	this->vertex_tab[5] = s;

	this->vertex_tab[6] = s;
	this->vertex_tab[7] = s;
	this->vertex_tab[8] = -s;


	this->vertex_tab[9] = s;
	this->vertex_tab[10] = -s;
	this->vertex_tab[11] = -s;

	this->vertex_tab[12] = s;
	this->vertex_tab[13] = -s;
	this->vertex_tab[14] = s;

	this->vertex_tab[15] = s;
	this->vertex_tab[16] = s;
	this->vertex_tab[17] = -s;


	this->vertex_tab[18] = -s;
	this->vertex_tab[19] = s;
	this->vertex_tab[20] = s;

	this->vertex_tab[21] = -s;
	this->vertex_tab[22] = -s;
	this->vertex_tab[23] = s;

	this->vertex_tab[24] = -s;
	this->vertex_tab[25] = s;
	this->vertex_tab[26] = -s;


	this->vertex_tab[27] = -s;
	this->vertex_tab[28] = -s;
	this->vertex_tab[29] = -s;

	this->vertex_tab[30] = -s;
	this->vertex_tab[31] = -s;
	this->vertex_tab[32] = s;

	this->vertex_tab[33] = -s;
	this->vertex_tab[34] = s;
	this->vertex_tab[35] = -s;
}


void
Engine::renderShape(void)
{
    glBegin(GL_TRIANGLES);

    glColor3f(0.9f, 0.3f, 0.2f);
    glVertex3f(0.2f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.2f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.2f);

    glColor3f(0.2f, 0.3f, 0.9f);
    glVertex3f(0.4f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.4f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.4f);

	glColor3f(1, 1, 1);
 	glVertex3f(-0.6, 0, -0.6);
 	glVertex3f(0.6, 0, -0.6);
 	glVertex3f(0.6, 0, 0.6);

 	glVertex3f(-0.6, 0, -0.6);
 	glVertex3f(-0.6, 0, 0.6);
 	glVertex3f(0.6, 0, 0.6);

    glEnd();
}
