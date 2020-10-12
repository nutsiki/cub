#include "main_struct.h"
#include <stdio.h>

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

int 	parser_map(char *buffer, int size, t_line **line)
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
		if (line[x]->index == line[x]->size)
			line[x]->size = ft_realloc(&(*line)[x].str, sizeof(char), line[x]->size, line[x]->size + 20);
		k -= is_cardinal(*buffer);

		(*line)[x].str[line[x]->index++] = *buffer;
		if (*buffer++ == '\n')
		{
			(*line)[x].str[(*line)[x].index - 1] = 0;
			if (max_size < ((*line)[x].index))
				max_size = (*line)[x].index;
			if (++x == size_map)
				size_map = ft_realloc((char **) &((*line)), sizeof(t_line), size_map, size_map + 20);
		}

		printf("yo [%s]\n", (*line)[50].str);
	}
	if (*buffer || k != 1)
		return (0);
	k = -1;
	while (++k < x)
		line[k]->size = ft_realloc(&(*line)[k].str, sizeof(char), (*line)[k].size, max_size);
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
	return (map);
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
		printf("color->r vaut [%d]\n", map->color_f.r);
		printf("color->g vaut [%d]\n", (map)->color_f.g);
		printf("color->b vaut [%d]\n", (map)->color_f.b);
		printf("color->r vaut [%d]\n", (map)->color_c.r);
		printf("color->g vaut [%d]\n", (map)->color_c.g);
		printf("color->b vaut [%d]\n", (map)->color_c.b);
		if (!(x = parser_map(buf, size, &(map)->line)))
			return (1);
		printf("line[%d] vaut [%s]\n", 90, map->line[90].str);

		if (!(check_wall(&map, x)))
		{
//			printf("(*map)[%d].line[%d] vaut [%s]\n", 1, 76, map[1].line);
			return (1);
		}

		 int k = -1;
//		 printf("color->r vaut [%d]\n", map->color_f.r);
//		 printf("color->g vaut [%d]\n", (map)->color_f.g);
//		 printf("color->b vaut [%d]\n", (map)->color_f.b);
//		 printf("color->r vaut [%d]\n", (map)->color_c.r);
//		 printf("color->g vaut [%d]\n", (map)->color_c.g);
//		 printf("color->b vaut [%d]\n", (map)->color_c.b);
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
	return (0);
}