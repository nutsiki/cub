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


typedef struct	s_rgb
{
	int r;
	int g;
	int b;

}				t_rgb;

typedef struct s_pos
{
	int x;
	int y;
}				t_pos;

typedef struct s_line
{
	char *str;
	int index;
	int size;
}				t_line;

typedef struct	s_map
{
//	char *line;
//	int index;
//	int size;
	t_line *line;
	double reso_x;
	double reso_y;
	char **txt;
	t_pos pos;
	t_rgb color_f;
	t_rgb color_c;
	void	*mlx_ptr;
	void 	*win_ptr;
	void 	*img_ptr;
	int		*data;

	int 	width;
	int 	height;
	int		id;
	double dir_v_x;
	double dir_v_y;
	double plan_2d_x;
	double plan_2d_y;
	double dirX, dirY; //initial direction vector (a modifier en fonction de la direction du player)
	double planeX;
	double planeY;
}				t_map;


int 	check_map(char c);
//int 	parser_map(char *map, int size, map);

#endif