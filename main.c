#include "cub.h"
#include <stdio.h>

int		check_is_space(char str)
{
	if (str == '\f' || str == '\r'
		   || str == '\t' || str == '\v' || str == ' ')
		return (1);
	return (0);
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

//int check_wall(t_map *map)
//{
//	flood fill
//	return (0);
//}

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
	return (map);
}

int		main(void)
{
	char buf[SIZE_MAP + 1];
	int size;
	int fd;
	int x;
	t_map *map;

	if ((fd = open("map.txt", O_RDONLY)) == -1)
		printf("erreur dans le fichier");
	map = init_map();
	while ((size = read(fd, buf, SIZE_MAP)) > 0)
	{
//		printf("coucouc %d--%d\n", size, SIZE_MAP);

		buf[size] = '\0';
		if (!(x = parser_map(buf, size, &map)))
			return (1);
//		printf(" x vaut : %d\n", x);
		int k = -1;
//		printf("1 : %s\n", map[16].line);
//		printf("1 : %p\n", &map[0]);
//		printf("2 : %p\n", &map[950]);
		while (++k < x)
		{
			printf("%s\n", map[k].line);
//		map[k].size = ft_realloc(&map[k].line, sizeof(char), map[k].size, max_size);
		}

	}

	return (0);
}