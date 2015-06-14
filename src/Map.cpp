#include "Map.hpp"

Map::Map(void)
{
	return ;
}

Map::Map(Map const &src)
{
	*this = src;
	return ;
}

Map::Map(int map_size) : _map_size(map_size)
{
	int     i = 0;
    int     j = 0;

    this->map = new t_p * [map_size];
    while (i < map_size)
    {
        this->map[i] = new t_p[map_size];
        j = 0;
        while (j < map_size)
        {
            this->map[i][j].g = 0;
            this->map[i][j].w = 0;
            j++;
        }
        i++;
    }
    this->space = 1.0 / ((float)this->_map_size - 1);
    this->gpa_size = this->_map_size * this->_map_size * 3 * 6;
    this->wpa_size = this->_map_size * this->_map_size * 3 * 6;
    this->ground_point_array = new float[this->gpa_size];
    this->water_point_array = new float[this->wpa_size];
    return ;
	return;
}

Map::~Map(void)
{
	int		i = 0;

	while(i < this->_map_size)
	{
		delete [] this->map[i];
		i++;
	}
	delete [] this->map;
	delete [] this->ground_point_array;
	delete [] this->water_point_array;
	return ;
}

void
Map::print(void)
{
    int     i = 0;
    int     j = 0;

    std::cout << "[ground, water] : size = " << this->_map_size << std::endl;
    while (i < this->_map_size)
    {
     	j = 0;
        while (j < this->_map_size)
        {
            std::cout << "[" << this->map[i][j].g << ", " << this->map[i][j].w  <<\
 "]";
            j++;
	}
        std::cout << std::endl;
        i++;
    }
    return ;
}

int
Map::getMapSize(void) const
{
    return (this->_map_size);
}

void
Map::setMapSize(int map_size)
{
    this->_map_size = map_size;
    return ;
}

Map
&Map::operator=(Map const &rhs)
{
    this->_map_size = rhs.getMapSize();
    return (*this);
}

std::ostream &operator<<(std::ostream &o, Map const &i)
{
    o << "I'm a " << i.getMapSize() << " points large map." << std::endl;
    return (o);
}