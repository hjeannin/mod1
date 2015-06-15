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
            this->map[i][j].g = -0.5;
            this->map[i][j].w = 0;
            j++;
        }
        i++;
    }
    this->gpa_size = POINT * SQUARE * MAPSIZE * MAPSIZE;
    this->wpa_size = POINT * SQUARE * MAPSIZE * MAPSIZE;
    this->sa_size = POINT * SQUARE * MAPSIZE * 4;
    this->fa_size = this->gpa_size + this->wpa_size + this->sa_size;

    this->space = 1.0 / ((float)this->_map_size - 1);

    this->ground_array = new float[this->gpa_size];
    this->water_array = new float[this->wpa_size];
    this->sides_array = new float[this->sa_size];
	return ;
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
	delete [] this->ground_array;
	delete [] this->water_array;
	return ;
}

void
Map::print(void)
{
    int     i = 0;
    int     j = 0;

    std::cout << std::endl;
    std::cout << "Ground point Array: " << this->gpa_size << std::endl;
    std::cout << "Water point Array: " << this->wpa_size << std::endl;
    std::cout << "Sides point Array: " << this->sa_size << std::endl;
    std::cout << "Full Array: " << this->fa_size << std::endl;
    std::cout << "Space between 2 points: " << this->space << std::endl;
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