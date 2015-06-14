
#ifndef		CAMERA_HPP
# define	CAMERA_HPP

# include <iostream>

# ifdef linux
#  include <GL/glu.h>
#  include <GL/gl.h>
#  include <SDL2/SDL.h>
# endif

# ifdef __APPLE__
#  include <openGL/glu.h>
#  include <openGL/gl.h>
#  include <SDL.h>
# endif

# ifdef __WIN32__
#  include <GL/gl.h>
#  include <windows.h>
#  include <SDL.h>
# endif

class Camera
{
public:
	Camera(void);
	Camera(Camera const &src);
	virtual ~Camera(void);

	void				onMouseMotion(SDL_MouseMotionEvent const &e);
	void				onMouseButton(SDL_MouseButtonEvent const &e);
	void				onKeyboard(SDL_KeyboardEvent const &e);
	void				look(void);
	void				setMotionSensivity(double sensivity);
	double const		&getMotionSensivity(void) const;
	bool const			&getHold(void) const;
	float const			&getAngleX(void) const;
	float const			&getAngleY(void) const;

	Camera				&operator=(Camera const &rhs);
private:
	double				_motionSensivity;
	bool				_hold;
	float				_angleX;
	float				_angleY;
};

std::ostream				&operator<<(std::ostream &o, Camera const &i);

#endif
