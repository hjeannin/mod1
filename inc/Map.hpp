#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include <cstdlib>

class Map
{
private:
	int _map_size;

public:
	typedef struct		s_p
	{
		int		g;		// ground
		int		w;		// water
	}					t_p;

	t_p		**map;
	float	*ground_point_array;
	int		gpa_size;

	Map(void);
	Map(const Map &src);
	Map(int map_size);
	~Map(void);

	void print(void);
	void read_file(void);
	void make_ground_point_array(void);
	int getMap_Size(void) const;

	void setMap_Size(int map_size);

	Map &operator=(Map const &rhs);
};

std::ostream &operator<<(std::ostream &o, Map const &i);

#endif
