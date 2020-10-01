#include "cub.h"

int 	check_map(char c)
{
	char *str;
	int i;

	i = -1;
	str = "012NSEW\n ";
	while (str[++i])
	{
		if(c == str[i])
			return (1);
	}
	return (0);
}

int 	parser_map(char *map, int size)
{
	char map_t[SIZE_MAP + 1];
	int i;
	char t;

	i = 0;
	map_t[size] = '\0';
	while (check_map(*map))
	{
		if (!i && *map == '1')
			i = 1;
		else if (i && *map == '1' && t != '1')
			i = 0;
		if (ft_check_is_space(*map) && i)
			*map_t++ = '0';
		else
			*map_t++ = *map;
		t = *map;
		map++;
	}
	return (1);

}