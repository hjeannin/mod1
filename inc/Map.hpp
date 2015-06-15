#ifndef MAP_HPP
# define MAP_HPP

# define SQUARE 6
# define POINT	3
# define MAPSIZE this->_map_size

#include <iostream>
#include <cstdlib>

class Map
{
private:
	int		_map_size;

public:
    typedef struct      s_p
    {
        float     g;      // ground
        float     w;      // water
    }                   t_p;

    t_p     **map;

    float   *ground_array;
    float   *water_array;
    float	*sides_array;

    int		gpa_size; // grount array
    int		wpa_size; // water array
    int		sa_size; // sides array
    int     fa_size; // full array size needed

    float   space; // space between 2 points of the map, range(-0.5, 0.5)

	Map(void);
	Map(const Map &src);
	Map(int map_size);
	~Map(void);

	int		getMapSize(void) const;

	void	setMapSize(int map_size);

	void	print(void);

	Map &operator=(Map const &rhs);
};

std::ostream	&operator<<(std::ostream &o, Map const &i);

#endif