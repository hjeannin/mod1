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
            if (i == 0 || i == map_size - 1 || j == 0 || j == map_size - 1)
                this->map[i][j].g = -0.5;
            else
                this->map[i][j].g = ((float)random() / (float)RAND_MAX) - 0.5;
            this->map[i][j].w = -0.2;
            j++;
        }
        i++;
    }
    this->ga_size = POINT * SQUARE * MAPSIZE * MAPSIZE + 18;
    this->wa_size = (POINT * SQUARE * MAPSIZE * MAPSIZE) + (POINT * SQUARE * MAPSIZE * 4);

    this->space = 1.0 / ((float)this->_map_size - 1);

    this->ground_array = new float[this->ga_size];
    this->water_array = new float[this->wa_size];
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
Map::fillGroundArray(void)
{
    float   x = -0.5;
    float   y = 0;
    float   z = -0.5;
    int     cur = 0;
    int     i, j;

    for (i = 0; i < this->_map_size - 1; i++)
    {
        for (j = 0; j < this->_map_size - 1; j++)
        {
            // main point
            this->ground_array[cur] = x;
            cur++;
            this->ground_array[cur] = this->map[i][j].g;
            cur++;
            this->ground_array[cur] = z;
            cur++;
            // right
            this->ground_array[cur] = x + this->space;
            cur++;
            this->ground_array[cur] = this->map[i][j + 1].g;
            cur++;
            this->ground_array[cur] = z;
            cur++;
            // bot right
            this->ground_array[cur] = x + this->space;
            cur++;
            this->ground_array[cur] = this->map[i + 1][j + 1].g;
            cur++;
            this->ground_array[cur] = z + this->space;
            cur++;
            // main again
            this->ground_array[cur] = x;
            cur++;
            this->ground_array[cur] = this->map[i][j].g;
            cur++;
            this->ground_array[cur] = z;
            cur++;
            // bot left
            this->ground_array[cur] = x;
            cur++;
            this->ground_array[cur] = this->map[i + 1][j].g;
            cur++;
            this->ground_array[cur] = z + this->space;
            cur++;
            // bot right
            this->ground_array[cur] = x + this->space;
            cur++;
            this->ground_array[cur] = this->map[i + 1][j + 1].g;
            cur++;
            this->ground_array[cur] = z + this->space;
            cur++;
            x += this->space;
        }
        x = -0.5;
        z += this->space;
    }
    // ground bottom
    // up left
    this->ground_array[cur] = -0.5;
    cur++;
    this->ground_array[cur] = -0.5;
    cur++;
    this->ground_array[cur] = -0.5;
    cur++;
    // up right
    this->ground_array[cur] = 0.5;
    cur++;
    this->ground_array[cur] = -0.5;
    cur++;
    this->ground_array[cur] = -0.5;
    cur++;
    // down left
    this->ground_array[cur] = -0.5;
    cur++;
    this->ground_array[cur] = -0.5;
    cur++;
    this->ground_array[cur] = 0.5;
    cur++;
    // up right
    this->ground_array[cur] = 0.5;
    cur++;
    this->ground_array[cur] = -0.5;
    cur++;
    this->ground_array[cur] = -0.5;
    cur++;
    // down right
    this->ground_array[cur] = 0.5;
    cur++;
    this->ground_array[cur] = -0.5;
    cur++;
    this->ground_array[cur] = 0.5;
    cur++;
    // down left
    this->ground_array[cur] = -0.5;
    cur++;
    this->ground_array[cur] = -0.5;
    cur++;
    this->ground_array[cur] = 0.5;
    cur++;
}

void
Map::fillWaterArray(void)
{
    float   x = -0.5;
    float   y = 0;
    float   z = -0.5;
    int     cur = 0;
    int     i, j;

    for (i = 0; i < this->_map_size - 1; i++)
    {
        for (j = 0; j < this->_map_size - 1; j++)
        {
            // main point
            this->water_array[cur] = x;
            cur++;
            this->water_array[cur] = this->map[i][j].w;
            cur++;
            this->water_array[cur] = z;
            cur++;
            // right
            this->water_array[cur] = x + this->space;
            cur++;
            this->water_array[cur] = this->map[i][j + 1].w;
            cur++;
            this->water_array[cur] = z;
            cur++;
            // bot right
            this->water_array[cur] = x + this->space;
            cur++;
            this->water_array[cur] = this->map[i + 1][j + 1].w;
            cur++;
            this->water_array[cur] = z + this->space;
            cur++;
            // main again
            this->water_array[cur] = x;
            cur++;
            this->water_array[cur] = this->map[i][j].w;
            cur++;
            this->water_array[cur] = z;
            cur++;
            // bot left
            this->water_array[cur] = x;
            cur++;
            this->water_array[cur] = this->map[i + 1][j].w;
            cur++;
            this->water_array[cur] = z + this->space;
            cur++;
            // bot right
            this->water_array[cur] = x + this->space;
            cur++;
            this->water_array[cur] = this->map[i + 1][j + 1].w;
            cur++;
            this->water_array[cur] = z + this->space;
            cur++;
            x += this->space;
        }
        x = -0.5;
        z += this->space;
    }

    //TODO add sides for water.

    // First row config
    x = -0.5;
    y = 0;
    z = -0.5;
    i = 0;
    j = 0;

    for (i = 0; i < this->_map_size - 1; i++)
    {
        // main point
        this->water_array[cur] = x;
        cur++;
        this->water_array[cur] = this->map[i][j].w;
        cur++;
        this->water_array[cur] = z;
        cur++;
        // ground point
        this->water_array[cur] = x;
        cur++;
        this->water_array[cur] = this->map[i][j].g;
        cur++;
        this->water_array[cur] = z;
        cur++;
        // ground point next
        this->water_array[cur] = x + this->space;
        cur++;
        this->water_array[cur] = this->map[i + 1][j].g;
        cur++;
        this->water_array[cur] = z;
        cur++;
        // main point again
        this->water_array[cur] = x;
        cur++;
        this->water_array[cur] = this->map[i][j].w;
        cur++;
        this->water_array[cur] = z;
        cur++;
        // main point next
        this->water_array[cur] = x + this->space;
        cur++;
        this->water_array[cur] = this->map[i + 1][j].w;
        cur++;
        this->water_array[cur] = z;
        cur++;
        // ground point next
        this->water_array[cur] = x + this->space;
        cur++;
        this->water_array[cur] = this->map[i + 1][j].g;
        cur++;
        this->water_array[cur] = z;
        cur++;
        x += this->space;
    }

    // Last row config
    x = -0.5;
    y = 0;
    z = 0.5;
    i = 0;
    j = this->_map_size - 1;

    for (i = 0; i < this->_map_size - 1; i++)
    {
        // main point
        this->water_array[cur] = x;
        cur++;
        this->water_array[cur] = this->map[i][j].w;
        cur++;
        this->water_array[cur] = z;
        cur++;
        // ground point
        this->water_array[cur] = x;
        cur++;
        this->water_array[cur] = this->map[i][j].g;
        cur++;
        this->water_array[cur] = z;
        cur++;
        // ground point next
        this->water_array[cur] = x + this->space;
        cur++;
        this->water_array[cur] = this->map[i + 1][j].g;
        cur++;
        this->water_array[cur] = z;
        cur++;
        // main point again
        this->water_array[cur] = x;
        cur++;
        this->water_array[cur] = this->map[i][j].w;
        cur++;
        this->water_array[cur] = z;
        cur++;
        // main point next
        this->water_array[cur] = x + this->space;
        cur++;
        this->water_array[cur] = this->map[i + 1][j].w;
        cur++;
        this->water_array[cur] = z;
        cur++;
        // ground point next
        this->water_array[cur] = x + this->space;
        cur++;
        this->water_array[cur] = this->map[i + 1][j].g;
        cur++;
        this->water_array[cur] = z;
        cur++;
        x += this->space;
    }

    // Left column config
    x = -0.5;
    y = 0;
    z = -0.5;
    i = 0;
    j = 0;

    for (j = 0; j < this->_map_size - 1; j++)
    {
        // main point
        this->water_array[cur] = x;
        cur++;
        this->water_array[cur] = this->map[i][j].w;
        cur++;
        this->water_array[cur] = z;
        cur++;
        // ground point
        this->water_array[cur] = x;
        cur++;
        this->water_array[cur] = this->map[i][j].g;
        cur++;
        this->water_array[cur] = z;
        cur++;
        // ground point next
        this->water_array[cur] = x;
        cur++;
        this->water_array[cur] = this->map[i][j + 1].g;
        cur++;
        this->water_array[cur] = z + this->space;
        cur++;
        // main point again
        this->water_array[cur] = x;
        cur++;
        this->water_array[cur] = this->map[i][j].w;
        cur++;
        this->water_array[cur] = z;
        cur++;
        // main point next
        this->water_array[cur] = x;
        cur++;
        this->water_array[cur] = this->map[i][j + 1].w;
        cur++;
        this->water_array[cur] = z + this->space;
        cur++;
        // ground point next
        this->water_array[cur] = x;
        cur++;
        this->water_array[cur] = this->map[i][j + 1].g;
        cur++;
        this->water_array[cur] = z + this->space;
        cur++;
        z += this->space;
    }

    // Right column config
    x = 0.5;
    y = 0;
    z = -0.5;
    i = this->_map_size - 1;
    j = 0;

    for (j = 0; j < this->_map_size - 1; j++)
    {
        // main point
        this->water_array[cur] = x;
        cur++;
        this->water_array[cur] = this->map[i][j].w;
        cur++;
        this->water_array[cur] = z;
        cur++;
        // ground point
        this->water_array[cur] = x;
        cur++;
        this->water_array[cur] = this->map[i][j].g;
        cur++;
        this->water_array[cur] = z;
        cur++;
        // ground point next
        this->water_array[cur] = x;
        cur++;
        this->water_array[cur] = this->map[i][j + 1].g;
        cur++;
        this->water_array[cur] = z + this->space;
        cur++;
        // main point again
        this->water_array[cur] = x;
        cur++;
        this->water_array[cur] = this->map[i][j].w;
        cur++;
        this->water_array[cur] = z;
        cur++;
        // main point next
        this->water_array[cur] = x;
        cur++;
        this->water_array[cur] = this->map[i][j + 1].w;
        cur++;
        this->water_array[cur] = z + this->space;
        cur++;
        // ground point next
        this->water_array[cur] = x;
        cur++;
        this->water_array[cur] = this->map[i][j + 1].g;
        cur++;
        this->water_array[cur] = z + this->space;
        cur++;
        z += this->space;
    }
}

void
Map::print(void)
{
    int     i = 0;
    int     j = 0;

    std::cout << std::endl;
    std::cout << "Ground point Array: " << this->ga_size << std::endl;
    std::cout << "Water point Array: " << this->wa_size << std::endl;
    std::cout << "Space between 2 points: " << this->space << std::endl;
    std::cout << "[ground, water] : size = " << this->_map_size << std::endl;
    while (i < this->_map_size)
    {
     	j = 0;
        while (j < this->_map_size)
        {
            std::cout << "[" << this->map[i][j].g << ", " << this->map[i][j].w  << "]";
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