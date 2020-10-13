#include "cub.h"
#include <stdio.h>
#include "minilibx/mlx.h"
#include <string.h>
#include <math.h>

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (*s++)
		i++;
	return (i);
}

int		check_is_space(char str)
{
	if (str == '\f' || str == '\r'
		|| str == '\t' || str == '\v' || str == ' ' || str == '\n' || str == '\0')
		return (1);
	return (0);
}

static char				*ft_skipspace(char *str)
{
//	printf("bojour\n");
	while (check_is_space(*str))
		str++;
//	printf("aurevoir\n");
	return (str);
}

static char				*ft_checkspace(char *str)
{
	while (*str == '\n' || *str == '\f' || *str == '\r'
		   || *str == '\t' || *str == '\v' || *str == ' ')
		str++;
	return (str);
}

static int				ft_checkull(const char *str, int j)
{
	int					i;
	char				*tab;
	int					k;
	int					m;

	m = 0;
	tab = "18446744073709551615";
	i = ft_strlen(str);
	k = ft_strlen(tab);
	if (i < k)
		return (1);
	while (m++ < i)
	{
		if (!(str[m] >= '0' && str[m] <= '9'))
			return (1);
		if (str[m] > tab[m] && j == 1)
			return (-1);
		if (str[m] > tab[m] && j == -1)
			return (0);
	}
	return (1);
}

int						ft_atoi(const char *str)
{
	int					j;
	int					k;
	unsigned long long	nb;

	j = 1;
	nb = 0;
	str = ft_checkspace((char*)str);
	if (*str == '-')
		j = -1;
	if (*str == '+' || *str == '-')
		str++;
	if ((k = ft_checkull(str, j)) != 1)
		return (k);
	while (*str && *str >= '0' && *str <= '9')
	{
		nb = (nb * 10) + (*str - '0');
		if (nb > 9223372036854775807 && j == 1)
			return (-1);
		if (nb > 9223372036854775807 && j == -1)
			return (0);
		str++;
	}
	return ((int)(nb * j));
}

int		ft_isalnum(int c)
{
	return ((c >= 97) && (c <= 122)) || ((c >= 65) && (c <= 90)) ||
		   ((c >= 48) && (c <= 57));
}

int		is_cardinal(char c)
{
	char *str;
	int i;

	i = 0;
	str = "NSEW";
	while (str[++i])
	{
		if(c == str[i])
			return (1);
	}
	return (0);

}

int 	check_map(char c)
{
	char *str;
	int i;

	i = -1;
	str = "012NSEW\n\f\r\t\v ";
	while (str[++i])
	{
		if(c == str[i])
			return (1);
	}
	return (0);
}



int ft_realloc(char **tab, int elem_size, int nb_elem, int new_size)
{
	char *new_tab;

	if (nb_elem == new_size) // si on veut reallouer de la mm taille que precedement on quitte
		return (new_size);
	if (!(new_tab = (char*)calloc(new_size * elem_size, sizeof(char))))
		return (-1);
	if (nb_elem)
	{
		if (nb_elem * elem_size < new_size * elem_size)
			memcpy(new_tab, *tab, nb_elem * elem_size);
		else
			memcpy(new_tab, *tab, new_size * elem_size);
		free(*tab);
	}

	*tab = new_tab;
	return (new_size);
}

char 	**init_tab(void)
{
	char **tab;
	int i;

	i = -1;
	tab = (char**)malloc(sizeof(char*)*9);
	while (++i < 9)
		tab[i] = calloc(sizeof(char),4);
	strcpy(tab[i - 1],"\0");
	strcpy(tab[0],"NO");
	strcpy(tab[1],"SO");
	strcpy(tab[2],"WE");
	strcpy(tab[3],"EA");
	strcpy(tab[4],"S ");
	strcpy(tab[5],"R ");
	strcpy(tab[6],"F ");
	strcpy(tab[7],"C ");
	return (tab);
}

int 	check_txt(char a, char b, char **tab)
{
	int i;

	i = -1;

	while (++i < 8)
	{
		if (tab[i][0] == a && tab[i][1] == b)
			return (i + 1);
//		printf("yo\n");
	}

	return (0);
}

char 	*check_r(char *buf, int size, t_map **map)
{
	char *buf_temp;
	int i;

	i = 0;
	buf = ft_skipspace(buf);
	if (*buf++ == 'R')
	{
		buf_temp = (char*)calloc(sizeof(char),size);
		buf = ft_skipspace(buf);
		while (ft_isalnum(*(buf)))
			buf_temp[i++] = (*buf++);
		(*map)->reso_x = ft_atoi(buf_temp);
		i = 0;
		buf = ft_skipspace(buf);
		while (ft_isalnum(*buf))
			buf_temp[i++] = *buf++;
		(*map)->reso_y = ft_atoi(buf_temp);
	}
	else
		return (NULL);
	free((void*)buf_temp);
	return (buf);
}

char	*fill_rgb(char *buf, t_rgb *color, char c, char buf_temp[])
{
	int i;
//	printf("0 buf vaut [%c]\n", *buf);

	buf_temp[0] = '\0';
	buf_temp[1] = '\0';
	buf_temp[2] = '\0';
	if (!(*(buf + 1)))
		return (buf);
	i = 0;
	buf = ft_skipspace(buf);
	while (ft_isalnum(*(buf)))
		buf_temp[i++] = (*buf++);
	i = ft_atoi(buf_temp);
	if (i >= 0 && i <= 255)
	{
		if (c == 'r')
			color->r = i;
		else if (c == 'g')
			color->g = i;
		else if (c == 'b')
			color->b = i;

	}
	else
		return (NULL);
	return (++buf);
}

void	*ft_memset(void *s, int c, size_t n)
{
	char *p;

	p = (char *)s;
	while (n-- > 0)
		p[n] = (unsigned char)c;
	return (s);
}

char 	*fill_color(char *buf, int size, t_map **map)
{
	char buf_temp[size];

	buf_temp[size - 1] = '\0';
	buf = ft_skipspace(buf);
	if (*buf == 'F')
	{
		buf++;
//		printf("0 coucou %c\n", *buf);
		buf = fill_rgb(buf+1, &(*map)->color_f, 'r', buf_temp);
//		printf("1 coucou %c\n", *buf);
		buf = fill_rgb(buf+1, &(*map)->color_f, 'g', buf_temp);
//		printf("2 coucou %c\n", *buf);
//		printf("2 coucou %s\n", buf);
		buf = fill_rgb(buf+1, &(*map)->color_f, 'b', buf_temp);
//		printf("3 coucou %s\n", buf);

	}
	else if (*buf == 'C')
	{
		buf++;
		buf = fill_rgb(buf+1, &(*map)->color_c, 'r', buf_temp);
		buf = fill_rgb(buf+1, &(*map)->color_c, 'g', buf_temp);
		buf = fill_rgb(buf+1, &(*map)->color_c, 'b', buf_temp);
	}
//	printf("0 coucou %c\n", *buf);

	return (buf);
}


char 	*fill_txt(char *buf, int size, t_map **map)
{
	int i;
	int t;
	char **tab;
	int cpt;

	cpt = 8;
	buf = ft_skipspace(buf);
	tab = init_tab();
	if (!((*map)->txt=(char**)calloc(sizeof(char*),6)))
		return (NULL);
	while ((buf && (t = check_txt(*buf, *(buf+1), tab))))
	{
		if (t == 6)
			buf = check_r(buf, size, map);
		else if (t == 7 || t == 8)
			buf = fill_color(buf, size, map);
		else
		{
			buf = buf + 2;
			printf("add [%p]\n", (*map)->txt[t - 1]);
			if ((*map)->txt[t - 1])
				return (NULL);
			(*map)->txt[t - 1] = (char *) calloc(sizeof(char), size);
			buf = ft_skipspace(buf);
			i = 0;
			while (!(check_is_space(*(buf))))
				(*map)->txt[t - 1][i++] = *buf++;
		}
		if (cpt-- && buf)
		{
			if (cpt)
				buf = ft_skipspace(buf);
		}
		else
		{
			return (NULL);
		}


	}
	if (cpt)
		return (NULL);
	return (buf);
}


char 	*parser_premap(char *buf, int size, t_map **map)
{
//	if (!(buf = check_r(buf, size, map)))
//		return (0);
	if (!(buf = fill_txt(buf, size, map)))
	{
		printf("color->r vaut [%d]\n", (*map)->color_f.r);
		printf("color->g vaut [%d]\n", (*map)->color_f.g);
		printf("color->b vaut [%d]\n", (*map)->color_f.b);
		printf("color->r vaut [%d]\n", (*map)->color_c.r);
		printf("color->g vaut [%d]\n", (*map)->color_c.g);
		printf("color->b vaut [%d]\n", (*map)->color_c.b);

//		printf("yo %s\n", buf);

		return (0);
	}

	return (buf);
}

int 	parser_map(char *buffer, int size, t_map **map)
{
	int k;
	int x;
	int size_map;
	int max_size = 0;

	k = 2;
	x = 0;
	size_map = 20;
	while (check_map(*buffer) && k)
	{
		if ((*map)[x].index == (*map)[x].size)
			(*map)[x].size = ft_realloc(&(*map)[x].line, sizeof(char), (*map)[x].size, (*map)[x].size + 20);
		k -= is_cardinal(*buffer);
		(*map)[x].line[(*map)[x].index++] = *buffer;
		if (*buffer++ == '\n')
		{
			(*map)[x].line[(*map)[x].index - 1] = 0;
			if (max_size < (*map)[x].index)
				max_size = (*map)[x].index;
			if (++x == size_map)
				size_map = ft_realloc((char **) &(*map), sizeof(t_map), size_map, size_map + 20);
		}
	}
	if (*buffer || k != 1)
		return (0);
	k = -1;
	while (++k < x)
		(*map)[k].size = ft_realloc(&(*map)[k].line, sizeof(char), (*map)[k].size, max_size);
	return (x);
}

int	flood_fill(t_map **map, int j, int i, int x)
{
	if ((i - 1 >= 0) && ((check_is_space((*map)[j].line[i - 1]))))
		return (0);
	if ((i + 1 < (*map)[j].index) && ((check_is_space((*map)[j].line[i + 1]))))
		return (0);
	if ((j - 1 >= 0) && ((check_is_space((*map)[j - 1].line[i]))))
		return (0);
	if ((j + 1 < x) && ((check_is_space((*map)[j + 1].line[i]))))
		return (0);
	return (1);
}

int check_wall(t_map **map, int x)
{
	int i;
	int j;

	j = -1;
	while (++j < x)
	{
		i = -1;
//		printf("(*map)[%d].line vaut [%s]\n", j, (*map)[j].line);

		while (++i < (*map)->size && (*map)[j].line[i])
		{
			if (is_cardinal((*map)[j].line[i]))
			{
				printf("position en (*map)[%d].line[%d] vaut [%c]\n", j, i, (*map)[j].line[i]);

				(*map)->pos.x = j;
				(*map)->pos.y = i;
			}
//			printf("(*map)[%d].line[%d] vaut [%s]\n", j, i, (*map)[j].line);
			if ((*map)[j].line[i] == '0')
				if(!(flood_fill(map, j, i, x)))
				{
					printf("erreur en (*map)[%d].line[%d] vaut [%c]\n", j, i, (*map)[j].line[i]);

					return (0);
				}
		}
	}
	return (1);
}

t_map 	*init_map()
{
	t_map *map;
	int size_map;

	size_map = 20;
	if (!(map = calloc(size_map, sizeof(t_map))))
		return (NULL);
	map->size = 0;
	map->index = 0;
	map->line = calloc(size_map, sizeof(char));
	map->line[0] = 0;
	map->reso_x = 0;
	map->reso_y = 0;
	return (map);
}

int		main(void)
{
	void	*mlx_ptr;
	void 	*win_ptr;
	void 	*img_ptr;
	int		size_x;
	int 	size_y;
	char 	*title;
	int 	width;
	int 	height;
	int i;
	int j;
	int id;
	double pos_p_x;
	double pos_p_y;
	double dir_v_x;
	double dir_v_y;
	double plan_2d_x;
	double plan_2d_y;
	double time;
	double oldtime;
	double dirX = -1, dirY = 0; //initial direction vector (a modifier en fonction de la direction du player)
	double planeX = 0, planeY = 0.66;

	char *buf;
	int size;
	int fd;
	int x;
	t_map *map;

	if ((fd = open("map.cub2", O_RDONLY)) == -1)
		printf("erreur dans le fichier");
	map = init_map();
	buf = calloc(sizeof(char), SIZE_MAP);
	while ((size = read(fd, buf, SIZE_MAP)) > 0)
	{
		buf[size] = '\0';

		if (!(buf = parser_premap(buf, size, &map)))
			return (1);
		if (!(x = parser_map(buf, size, &map)))
			return (1);
		if (!(check_wall(&map, x)))
		{
//			printf("(*map)[%d].line[%d] vaut [%s]\n", 1, 76, map[1].line);
			return (1);
		}
		// int k = -1;
		// printf("color->r vaut [%d]\n", map->color_f.r);
		// printf("color->g vaut [%d]\n", (map)->color_f.g);
		// printf("color->b vaut [%d]\n", (map)->color_f.b);
		// printf("color->r vaut [%d]\n", (map)->color_c.r);
		// printf("color->g vaut [%d]\n", (map)->color_c.g);
		// printf("color->b vaut [%d]\n", (map)->color_c.b);
		// printf("reso->y vaut [%d]\n", (map)->reso_y);
		// printf("reso->x vaut [%d]\n", (map)->reso_x);
		// printf("txt[0] vaut [%s]\n", (map)->txt[0]);
		// printf("txt[1] vaut [%s]\n", (map)->txt[1]);
		// printf("txt[2] vaut [%s]\n", (map)->txt[2]);
		// printf("txt[3] vaut [%s]\n", (map)->txt[3]);
		// printf("txt[4] vaut [%s]\n", (map)->txt[4]);
		// printf("pos_x vaut [%d]\n", map->pos.x);
		// printf("pos_y vaut [%d]\n", map->pos.y);
//		while (++k < x)
//			printf("%s\n", map[k].line);
	}
	size_y = 800;
	size_x = 400;
	height = 400;
	width =  800;
	pos_p_y = map[0].pos.y;
	pos_p_x = map[0].pos.x;
	dir_v_x = -1;
	dir_v_y = 0;
	plan_2d_x = 0;
	plan_2d_y = 0.66;
	time = 0;
	oldtime = 0;
	title = "Test";
	if (!(mlx_ptr = mlx_init()))
		return (-1);
	if (!(win_ptr = mlx_new_window(mlx_ptr, size_y, size_x, title)))
		return (-1);
	printf("debut init\n");
	if (!(img_ptr = mlx_new_image(mlx_ptr, width, height)))
		return (-1);
	int *kk = (int *)mlx_get_data_addr(img_ptr, &id, &id, &id);
	printf("init\n");
	bzero(kk, width * height); // initialiser tt en noir

	for (int x = 0; x < width; x++)
    {
		//calculate ray position and direction
		double cameraX = 2 * x / (double)(width) - 1; //x-coordinate in camera space
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
	
		int mapX = (int)(pos_p_x);
        int mapY = (int)(pos_p_y);
		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (pos_p_x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - pos_p_x) * deltaDistX;
		}

		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (pos_p_y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - pos_p_y) * deltaDistY;
		}

		// l'envoie du rayon
		printf("Envoie du rayon %d sur %d\n", x, width);
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}

			//Check if ray has hit a wall
			printf("X %d Y %d\n", mapX, mapY);
			if (map[mapX].line[mapY] == '1') hit = 1;

			// if(map->line[mapY].str[mapX] == '1') hit = 1;
		}
		printf("*** HIT ***\n");

		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if(side == 0) perpWallDist = (mapX - pos_p_x + (1 - stepX) / 2) / rayDirX;
		else          perpWallDist = (mapY - pos_p_y + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
        int lineHeight = (int)(height / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + height / 2;
		printf("drawStart %d\n", drawStart);
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + height / 2;
		printf("drawEnd %d\n", drawEnd);
		if(drawEnd >= height) drawEnd = height - 1;

		int color = 0xFF0000; // rouge

		//give x and y sides different brightness
		if(side == 1) {color = 0x770000;}

		// //draw the pixels of the stripe as a vertical line
		for (int y = drawStart; y < drawEnd; y++)
			kk[y * width + x] = color;
	}

	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
	// mlx_loop_hook(mlx_ptr, new_fram, &map);
	mlx_loop(mlx_ptr);
	return (0);
}