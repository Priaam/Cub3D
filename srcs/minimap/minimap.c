#include "Cub3d.h"

int	find_biggest(char **map_grid)
{
	int	i;
	int	biggest;
	int	len;

	i = 0;
	biggest = 0;
	while (map_grid[i])
	{
		len = ft_strlen(map_grid[i]);
		if (len > biggest)
			biggest = len;
		i++;
	}
	if (i > biggest)
		biggest = i;
	return (biggest);
}
