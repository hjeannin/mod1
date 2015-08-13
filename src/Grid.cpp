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
	allocate();
	return ;
}

Grid::~Grid(void)
{
	delete [] _array;
	return ;
}

void
Grid::allocate(void)
{
	int i;
	_array_size = _size * _size;
	_array = new float[_array_size];
	for (i = 0; i < _array_size; i++)
	{
		_array[i] = 0.4;
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