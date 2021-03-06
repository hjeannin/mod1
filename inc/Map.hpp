#ifndef MAP_HPP
# define MAP_HPP

# define SQUARE 6
# define POINT	3
# define MAPSIZE (this->_map_size - 1)
# define MAPBOTTOM 18
# define WATER_START_LEVEL -0.2


#include <iostream>
#include <cstdlib>

class Map
{
private:
	int		_map_size;
    float   *_source_map;

public:
    typedef struct      s_p
    {
        float     g;      // ground
        float     w;      // water
    }                   t_p;

    t_p     **map;

    float     *ground_array;
    float     *water_array;

    int		ga_size; // ground array
    int		wa_size; // water array

    float   space; // space between 2 points of the map, range(-0.5, 0.5)

	Map(void);
	Map(const Map &src);
	Map(int map_size);
	~Map(void);

	int		getMapSize(void) const;

	void	setMapSize(int map_size);

	void	print(void);
    void    readSourceMap(void);
    void    generateRandomMap(void);
    void    raiseWaterLevel(void);
    void    resetWaterLevel(void);
    void    generateWaterNoise(float power);
    void    fillGroundArray(void);
    void    fillWaterArray(void);

	Map &operator=(Map const &rhs);
};

std::ostream	&operator<<(std::ostream &o, Map const &i);

#endif