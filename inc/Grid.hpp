#ifndef GRID_HPP
# define GRID_HPP

# include <iostream>

class Grid
{
private:
	Grid(void);
	
	int		_size;
	float	*_array;
	int		_array_size;


public:
	Grid(const Grid &src);
	Grid(int size);
	~Grid(void);

	void	print(void);
	void	fill_with(float n);
	float	access(int x, int y);

	int	getSize(void) const;
	Grid &operator=(const Grid &rhs);
};

std::ostream &operator<<(std::ostream &o, const Grid &i);

#endif