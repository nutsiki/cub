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

int 	check_no(char *buf, int size, t_map **map)
{
	int i;
	int t;
	char **tab;
	int l;

	i = 0;
	l = 0;
	buf = ft_skipspace(buf);
	tab = init_tab();
	(*map)->txt=(char**)malloc(sizeof(char)*6);
//	while (tab++)
//	{
//		*tab = malloc(sizeof(char)*3);
//		*tab[2] = '\0';
//	}
//	tab = {"NO", "SO", "WE", "EA", "S "};
	while ((t = check_txt(*buf, *(buf+1), tab)))
	{
		if (l == t)
			return (0);
		l = t;
		printf("t vaut %d\n", t);
		buf = buf + 2;
		(*map)->txt[t - 1] = (char*)calloc(sizeof(char),size);
		buf = ft_skipspace(buf);
		printf("cou [%c] \n", *buf);
		printf("0 add vaut [%p] \n", (*map)->txt[t - 1]);
		i = 0;
		while (!(check_is_space(*(buf))))
		{
			printf("buf vaut %c\n", *buf);
			(*map)->txt[t - 1][i++] = *buf++;
			printf("txt vaut %c\n", (*map)->txt[t - 1][i - 1]);
		}
		buf = ft_skipspace(buf);

		printf("string vaut [%s] \n", (*map)->txt[t - 1]);
		printf("0 add vaut [%p] \n", (*map)->txt[t - 1]);
	}
	return (1);
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
		printf("1 buf vaut %c\n", *buf);
		while (ft_isalnum(*(buf)))
		{
			printf("2 buf_temp vaut %c\n", *buf_temp);
			printf("3 buf vaut %c\n", *buf);
			buf_temp[i++] = (*buf++);
			printf("2a buf_temp vaut %c\n", *buf_temp);
			printf("3a buf vaut %c\n", *buf);
		}
		printf("4 buf vaut %s\n", buf_temp);
		(*map)->reso_x = ft_atoi(buf_temp);
		printf("5 buf vaut %c\n", *buf);
		i = 0;
		buf = ft_skipspace(buf);
		printf("6 buf vaut %c\n", *buf);

		while (ft_isalnum(*buf))
			buf_temp[i++] = *buf++;
		(*map)->reso_y = ft_atoi(buf_temp);
	}
	else
		return (0);
	free((void*)buf_temp);
	return (buf);
}

int 	parser_premap(char *buf, int size, t_map **map)
{
	buf = check_r(buf, size, map);
	printf("yo [%c]\n", *buf);
	check_no(buf, size, map);
	return (1);
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
	printf("nivo\n");
	while (check_map(*buffer) && k)
	{
//		printf("couco[%d]\n", x);
//		printf("ind : [%d]\n", (*map)[x].index);
//		printf("siz : [%d]\n", (*map)[x].size);
		if ((*map)[x].index == (*map)[x].size)
			(*map)[x].size = ft_realloc(&(*map)[x].line, sizeof(char), (*map)[x].size, (*map)[x].size + 20);
		k -= is_cardinal(*buffer);

		(*map)[x].line[(*map)[x].index++] = *buffer;
//		printf("haha\n");

		if (*buffer++ == '\n')
		{
			(*map)[x].line[(*map)[x].index - 1] = 0;
			if (max_size < (*map)[x].index)
				max_size = (*map)[x].index;
//			printf("hihi\n");
			if (++x == size_map)
				size_map = ft_realloc((char **) &(*map), sizeof(t_map), size_map, size_map + 20);
//			printf("hoho\n");

		}
	}
	if (*buffer || !k)
		return (0);
	k = -1;
	while (++k < x)
	{
//		printf("%s\n", map[k]->line);
//		printf("%p\n", (*map)[k].line);
//		printf("1 : %p\n", &map[k]);

		(*map)[k].size = ft_realloc(&(*map)[k].line, sizeof(char), (*map)[k].size, max_size);
	}
	return (x);
}

int	flood_fill(t_map **map, int j, int i, int x)
{
	printf("0a coucou map[%d]->line[%d] vaut %c\n", j, i, (*map)[j].line[i]);
	if ((*map)[j].line[i] == 'X')
		return (1);
	(*map)[j].line[i] = 'X';
	printf("1a coucou map[%d]->line[%d] vaut %c\n", j, i, (*map)[j].line[i]);
	if ((i - 1 >= 0) && (!(check_is_space((*map)[j].line[i - 1]))) && (*map)[j].line[i - 1] != '1')
		flood_fill(map, j, i - 1, x);
	printf("2a coucou map[%d]->line[%d] vaut %c\n", j, i, (*map)[j].line[i]);
	if ((i + 1 < (*map)[j].index) && (!(check_is_space((*map)[j].line[i + 1]))) && (*map)[j].line[i + 1] != '1')
		flood_fill(map, j, i + 1, x);
	printf("3a coucou map[%d]->line[%d] vaut %c\n", j, i, (*map)[j].line[i]);
	if ((j - 1 >= 0) && (!(check_is_space((*map)[j - 1].line[i]))) && (*map)[j - 1].line[i] != '1')
		flood_fill(map, j - 1, i, x);
	printf("4a coucou map[%d]->line[%d] vaut %c\n", j, i, (*map)[j].line[i]);
	if ((j + 1 < x) && (!(check_is_space((*map)[j + 1].line[i]))) && ((*map)[j + 1].line[i]) != '1')
		flood_fill(map, j + 1, i, x);
	printf("PAS CORRECT map[%d]->line[%d] vaut %c\n", j, i, (*map)[j].line[i]);
	return (0);
}

int check_wall(t_map **map, int x)
{
	int i;
	int j;

	j = -1;
	while (++j < x)
	{
		i = -1;
		printf("1 map[%d]->line[%d] : %c\n", j, i + 1, (*map)[j].line[i + 1]);
		while (++i < (*map)->size && (*map)[j].line[i])
		{
			printf("2 map[%d]->line[%d] : %c\n", j, i, (*map)[j].line[i]);
			if ((*map)[j].line[i] == '0')
			{
				if(!(flood_fill(map, j, i, x)))
					return (0);
			}
			printf("3 map[%d]->line[%d] : %c\n", j, i, (*map)[j].line[i]);
		}
		printf("4 map[%d]->line[%d]\n", j, i);

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
	char buf[SIZE_MAP + 1];
	int size;
	int fd;
	int x;
	t_map *map;

	if ((fd = open("map1.txt", O_RDONLY)) == -1)
		printf("erreur dans le fichier");
	map = init_map();
	while ((size = read(fd, buf, SIZE_MAP)) > 0)
	{
//		printf("coucouc %d--%d\n", size, SIZE_MAP);

		buf[size] = '\0';

		parser_premap(buf, size, &map);
		printf("coucou\n");
		printf("%d--%d\n", map->reso_x, map->reso_y);
		printf("txt 0 %s\n", map->txt[0]);
		printf("txt 1 %s\n", map->txt[1]);
		printf("txt 2 %s\n", map->txt[2]);
		printf("txt 3 %s\n", map->txt[3]);
		printf("txt 4 %s\n", map->txt[4]);
		if (!(x = parser_map(buf, size, &map)))
			return (1);
		printf("samiiiiiiii0 : %p\n", map[1].line);
		printf("samiiiiiiii0 : %p\n", &map);
		printf("samiiiiiiii0 : %p\n", map);
		if (!(check_wall(&map, x)))
			return (-1);
		printf(" x vaut : %d\n", x);
		int k = -1;
		printf("1 : %p\n", map[1].line);
		printf("1 : %p\n", &map);
		printf("1 : %p\n", map);
//		printf("1 : %s\n", map[1].line);
//		printf("2 : %p\n", &map[950]);
		while (++k <= x)
		{
			printf("%s\n", map[k].line);
//		map[k].size = ft_realloc(&map[k].line, sizeof(char), map[k].size, max_size);
		}

	}

	return (0);
}