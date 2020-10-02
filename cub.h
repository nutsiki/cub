#ifndef CUB3D_H
# define CUB3D_H
# define SIZE_MAP 10000

#include <fcntl.h>
#include <string.h>
//#include "Libft/libft.h"

typedef struct	s_map
{
	char *line;
	int index;
	int size;
}				t_map;

int 	check_map(char c);
//int 	parser_map(char *map, int size, map);

#endif