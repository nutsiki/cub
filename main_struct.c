#include "main_struct.h"
#include <stdio.h>
#include "minilibx/mlx.h"
#include <string.h>
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
//			printf("add [%p]\n", (*map)->txt[t - 1]);
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
		return (0);
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
		if ((*map)->line[x].index == (*map)->line[x].size)
			(*map)->line[x].size = ft_realloc(&(*map)->line[x].str, sizeof(char), (*map)->line[x].size, (*map)->line[x].size + 20);
		k -= is_cardinal(*buffer);
		(*map)->line[x].str[(*map)->line[x].index++] = *buffer;
		if (*buffer++ == '\n')
		{
			(*map)->line[x].str[(*map)->line[x].index - 1] = 0;
			if (max_size < (*map)->line[x].index)
				max_size = (*map)->line[x].index;
			if (++x == size_map)
				size_map = ft_realloc((char **) &(*map)->line, sizeof(t_line), size_map, size_map + 20);
		}
	}
	if (*buffer || k != 1)
		return (0);
	k = -1;
	while (++k < x)
		(*map)->line[k].size = ft_realloc(&(*map)->line[k].str, sizeof(char), (*map)->line[k].size, max_size);
	return (x);
}

int	flood_fill(t_map **map, int j, int i, int x)
{
	if ((i - 1 >= 0) && ((check_is_space((*map)->line[j].str[i - 1]))))
		return (0);
	if ((i + 1 < (*map)->line[j].index) && ((check_is_space((*map)->line[j].str[i + 1]))))
		return (0);
	if ((j - 1 >= 0) && ((check_is_space((*map)->line[j - 1].str[i]))))
		return (0);
	if ((j + 1 < x) && ((check_is_space((*map)->line[j + 1].str[i]))))
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
//		printf("(*map)[%d].line vaut [%s]\n", j, (*map)->line[j].str);
//		printf("(*map)[%d].line vaut [%p]\n", j, (*map)->line[j].str);

		while (++i < (*map)->line[j].index && (*map)->line[j].str[i])
		{

			if (is_cardinal((*map)->line[j].str[i]))
			{
				printf("position en (*map)[%d].line[%d] vaut [%c]\n", j, i, (*map)->line[j].str[i]);

				(*map)->pos.x = j;
				(*map)->pos.y = i;
			}
//			printf("(*map)[%d].line[%d] vaut [%s]\n", j, i, (*map)[j].line);
			if ((*map)->line[j].str[i] == '0')
				if(!(flood_fill(map, j, i, x)))
				{
					printf("erreur en (*map)[%d].line[%d] vaut [%c]\n", j, i, (*map)->line[j].str[i]);

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
	if (!(map->line = calloc(size_map, sizeof(t_line))))
		return (NULL);
	map->line->size = 0;
	map->line->index = 0;
	map->line->str = calloc(size_map, sizeof(char*));
	map->reso_x = 0;
	map->reso_y = 0;
	map->dirX = -1;
	map->dirY = 0;
	map->planeX = 0;
	map->planeY = 0.66;
	return (map);
}

int new_frame(void *param)
{
	t_map *map;

	map = (t_map*)param;
	bzero(map->data, map->reso_x * map->reso_y); // initialiser tt en noir
	for (int x = 0; x < map->reso_x; x++)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)(map->reso_x) - 1; //x-coordinate in camera space
		double rayDirX = map->dirX + map->planeX * cameraX;
		double rayDirY = map->dirY + map->planeY * cameraX;

		int mapX = (int)(map->pos.x);
		int mapY = (int)(map->pos.y);
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
			sideDistX = (map->pos.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - map->pos.x) * deltaDistX;
		}

		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (map->pos.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - map->pos.y) * deltaDistY;
		}

		// l'envoie du rayon
		printf("Envoie du rayon %d sur %d\n", x, (int)map->reso_x);
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
			if (map->line[mapX].str[mapY] == '1') hit = 1;
		}
		printf("*** HIT ***\n");

		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if(side == 0) perpWallDist = (mapX - map->pos.x + (1 - stepX) / 2) / rayDirX;
		else          perpWallDist = (mapY - map->pos.y + (1 - stepY) / 2) / rayDirY;

		//Calculate map->reso_y of line to draw on screen
		int lineheight = (int)(map->reso_y / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineheight / 2 + map->reso_y / 2;
		printf("drawStart %d\n", drawStart);
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineheight / 2 + map->reso_y / 2;
		printf("drawEnd %d\n", drawEnd);
		if(drawEnd >= map->reso_y) drawEnd = map->reso_y - 1;

		int color = 0xFF0000; // rouge

		//give x and y sides different brightness
		if(side == 1) {color = 0x770000;}

		// //draw the pixels of the stripe as a vertical line
		for (int y = 0; y < drawStart; y++)
			map->data[y * (int)map->reso_x + x] = 0X00FFFF;
		for (int y = drawStart; y < drawEnd; y++)
			map->data[y * (int)map->reso_x + x] = color;
		for (int y = drawEnd; y < map->reso_y; y++)
			map->data[y * (int)map->reso_x + x] = 0X00FF00;
	}
	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->img_ptr, 0, 0);
}

int		main(void)
{
	char *buf;
	int size;
	int fd;
	int x;
	t_map *map;

	if ((fd = open("map.cub", O_RDONLY)) == -1)
		printf("erreur dans le fichier");
	map = init_map();
	buf = calloc(sizeof(char), SIZE_MAP);
	while ((size = read(fd, buf, SIZE_MAP)) > 0)
	{
		buf[size] = '\0';
		if (!(buf = parser_premap(buf, size, &map)))
			return (1);
		if (!(x = parser_map(buf, size, &(map))))
			return (1);
		if (!(check_wall(&map, x)))
			return (1);
	}
	if (!(map->mlx_ptr = mlx_init()) ||
		!(map->win_ptr = mlx_new_window(map->mlx_ptr, map->reso_x, map->reso_y, "Test")) ||
		!(map->img_ptr = mlx_new_image(map->mlx_ptr, map->reso_x, map->reso_y)) ||
		!(map->data = (int *)mlx_get_data_addr(map->img_ptr, &map->id, &map->id, &map->id)))
		return (-1);

	mlx_loop_hook(map->mlx_ptr, new_frame, map);
	mlx_key_hook(map->win_ptr, ,map);// faire une fonction qui deplqce le perso
	mlx_loop(map->mlx_ptr);
	return (0);
}