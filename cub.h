#ifndef CUB3D_H
# define CUB3D_H
# define SIZE_MAP 10000
# define CHECK_R 1
# define CHECK_NO 2
# define CHECK_SO 4
# define CHECK_WE 8
# define CHECK_EA 16
# define CHECK_S 32
# define CHECK_F 64
# define CHECK_C 128

#include <fcntl.h>
#include <string.h>
//#include "Libft/libft.h"

typedef struct s_txt
{
	char *txt_no;
	char *txt_so;
	char *txt_we;
	char *txt_ea;
	char *txt_s;
}				t_txt;

typedef struct	s_map
{
	char *line;
	int index;
	int size;
	int reso_x;
	int reso_y;
	char *txt_no;
	char *txt_so;
	char *txt_we;
	char **txt;
}				t_map;


int 	check_map(char c);
//int 	parser_map(char *map, int size, map);

#endif