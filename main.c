#include "cub.h"
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
	while (check_is_space(*str))
		str++;
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
	tab = (char**)malloc(sizeof(char*)*6);
	while (++i < 5)
		tab[i] = calloc(sizeof(char),3);
	tab[i] = "\0";
	tab[0] = "NO";
	tab[1] = "SO";
	tab[2] = "WE";
	tab[3] = "EA";
	tab[4] = "S ";
	tab[5] = "R ";
	tab[6] = "F ";
	tab[7] = "C ";
	return (tab);
}

int 	check_txt(char a, char b, char **tab)
{
	int i;

	i = -1;
	while (++i < 5)
	{
		if (tab[i][0] == a && tab[i][1] == b)
			return (i + 1);
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

char 	*fill_color_f(char *buf, int size, t_map **map)
{
	char *buf_temp;
	int i;

	i = 0;
	buf = ft_skipspace(buf);
	if (*buf == 'F')
	{
		buf_temp = (char*)calloc(sizeof(char),size);
		buf = ft_skipspace(++buf);
		while (ft_isalnum(*(buf)))
			buf_temp[i++] = (*buf++);
		(*map)-> = ft_atoi(buf_temp);
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

char 	*fill_txt(char *buf, int size, t_map **map)
{
	int i;
	int t;
	char **tab;
	int cpt;

	cpt = 5;
	buf = ft_skipspace(buf);
	tab = init_tab();
	(*map)->txt=(char**)malloc(sizeof(char*)*6);
	while ((t = check_txt(*buf, *(buf+1), tab)))
	{
		if (t == 6)
		{
			if (!(buf = check_r(buf, size, map)))
				return (0);
		}
		else if (t == 7)
		{
			if (!(buf = fill_color_f(buf, size, map)))
		}
		else if (t == 8)
		{
			fill_color_f(buf, size, map))
		}
		else
		{
			buf = buf + 2;
			(*map)->txt[t - 1] = (char *) calloc(sizeof(char), size);
			buf = ft_skipspace(buf);
			i = 0;
			while (!(check_is_space(*(buf))))
				(*map)->txt[t - 1][i++] = *buf++;
			if (--cpt)
				buf = ft_skipspace(buf);
		}
	}
	if (cpt)
		return (NULL);
	return (buf);
}






char 	*parser_premap(char *buf, int size, t_map **map)
{
	if (!(buf = check_r(buf, size, map)))
		return (0);
	if (!(buf = fill_txt(buf, size, map)))
		return (0);
	if (!(buf = fill_color(buf, size, map)))
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
	if (*buffer || !k)
		return (0);
	k = -1;
	while (++k < x)
		(*map)[k].size = ft_realloc(&(*map)[k].line, sizeof(char), (*map)[k].size, max_size);
	return (x);
}

int	flood_fill(t_map **map, int j, int i, int x)
{
	if ((*map)[j].line[i] == '1')
		return (1);
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
		while (++i < (*map)->size && (*map)[j].line[i])
		{
//			printf("(*map)[%d].line[%d] vaut [%c]\n", j, i, (*map)[j].line[i]);
			if ((*map)[j].line[i] == '0')
				if(!(flood_fill(map, j, i, x)))
				{
//					printf("erreur en (*map)[%d].line[%d] vaut [%c]\n", j, i, (*map)[j].line[i]);

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
	char *buf;
	int size;
	int fd;
	int x;
	t_map *map;

	if ((fd = open("map.txt", O_RDONLY)) == -1)
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
		printf("(*map)[%d].line[%d] vaut [%s]\n", 21, 86, map[21].line);
		if (!(check_wall(&map, x)))
			return (1);
		int k = -1;
		while (++k < x)
			printf("%s\n", map[k].line);
	}

	return (0);
}