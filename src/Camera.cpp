
#include "Camera.hpp"

Camera::Camera(void)
	:	_motionSensivity(0.01),
		_hold(false),
		_angleX(0),
		_angleY(0)
{
	return ;
}

Camera::Camera(Camera const &src)
	:	_motionSensivity(src.getMotionSensivity()),
		_hold(src.getHold()),
		_angleX(src.getAngleX()),
		_angleY(src.getAngleY())
{
	*this = src;
	return ;
}

Camera::~Camera(void)
{
	return ;
}

void
Camera::onMouseMotion(SDL_MouseMotionEvent const &e)
{
	if (_hold)
	{
		_angleX += e.xrel * _motionSensivity;
		_angleY += e.yrel * _motionSensivity;
		if (_angleY > 1.55)
			_angleY = 1.55;
		if (_angleY < -1.55)
			_angleY = -1.55;
	}
}

void
Camera::onMouseButton(SDL_MouseButtonEvent const &e)
{
	if (e.button == SDL_BUTTON_LEFT)
	{
		if (_hold && e.type == SDL_MOUSEBUTTONUP)
			_hold = false;
		else if (!_hold && e.type == SDL_MOUSEBUTTONDOWN)
			_hold = true;
	}
}

void
Camera::onKeyboard(SDL_KeyboardEvent const &e)
{
	if (e.type == SDL_KEYDOWN && e.keysym.sym == SDLK_HOME)
	{
		_angleX = 0;
		_angleY = 0;
	}
}

void
Camera::look()
{
	double		rayon = cos(_angleY);
	gluLookAt(sin(_angleX) * rayon, sin(_angleY), cos(_angleX) * rayon, 0, 0, 0, 0, 1, 0);
}

double const
&Camera::getMotionSensivity(void) const
{
	return (_motionSensivity);
}

bool const
&Camera::getHold(void) const
{
	return (_hold);
}

float const
&Camera::getAngleX(void) const
{
	return (_angleX);
}

float const
&Camera::getAngleY(void) const
{
	return (_angleY);
}

Camera
&Camera::operator=(Camera const &rhs)
{
	if (this != &rhs)
	{
		// copy members here
	}
	return (*this);
}

std::ostream
&operator<<(std::ostream &o, Camera const &i)
{
	o	<< "Camera: " << &i;
	return (o);
}
