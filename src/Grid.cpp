#include "Grid.hpp"

Grid::Grid(void)
{
	return ;
}

Grid::Grid(const Grid &src)
{
	*this = src;
	return ;
}

Grid::Grid(int size) : _size(size)
{
	_array_size = _size * _size;
	_array = new float[_array_size];
	fill_with(0.1);
	return ;
}

Grid::~Grid(void)
{
	delete [] _array;
	return ;
}

float
Grid::access(int x, int y)
{
	// out of boundaries will return 0.0
	if (x <= 0 || x > _size || y <= 0 || y > _size)
		return 0.0;
	x--;
	y--;
	return _array[y * _size + x];
}

void
Grid::fill_with(float n)
{
	int i;

	for (i = 0; i < _array_size; i++)
	{
		_array[i] = n;
		n += 0.1;
	}
}

void
Grid::print(void)
{
	int i;
	for (i = 0; i < _array_size; i++)
	{
		if (i % _size == 0)
			std::cout << std::endl;
		std::cout << "[" << _array[i] << "]";
	}
	std::cout << std::endl;
}

int
Grid::getSize(void) const
{
	return (this->_size);
}

Grid &Grid::operator=(const Grid &rhs)
{
	this->_size = rhs.getSize();
	return (*this);
}

std::ostream &operator<<(std::ostream &o, const Grid &i)
{
	o << "I am a " << i.getSize() << "x" << i.getSize() << " grid." << std::endl;
	return (o);
}