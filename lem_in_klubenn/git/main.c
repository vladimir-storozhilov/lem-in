#include "lem_in.h"

void	error_management(t_lem0 *st, char *str)
{
	t_lem1	*tmp;

	ft_putstr_fd(str, 2);
	while (st->lem1)
	{
		tmp = st->lem1;
		st->lem1 = st->lem1->prev;
		free(tmp->room_name);
		free(tmp);
	}
	// room name, links
	free(st);
	exit(0);
}

void	free_arr(char **arr, int i)
{
	while (i >= 0)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
}

t_lem1	*new_lem1(char *name, t_lem1 *prev, t_lem1 *next)
{
	t_lem1 *lem1;

	lem1 = ft_memalloc(sizeof(t_lem1));
	if (!lem1)
		return (NULL);
	lem1->room_name = name;
	lem1->prev = prev;
	lem1->next = next;
	return (lem1);
}

void	instructions(t_lem0 *st0, char *line, int launch)
{
	if (!ft_strcmp(line, "start"))
	{
		if (st0->tmp_info)
			error_management(st0, "ERROR: multiple instructions for one room");
		else if (!launch)
			error_management(st0, "ERROR: room specification before defining number of ants");
		st0->tmp_info = START;
	}
	else if (!ft_strcmp(line, "end"))
	{
		if (st0->tmp_info)
			error_management(st0, "ERROR: multiple instructions for one room");
		else if (!launch)
			error_management(st0, "ERROR: room specification before defining number of ants");
		st0->tmp_info = END;
	}
	else
		return ;
	if ((st0->start && st0->tmp_info == START) || (st0->end && st0->tmp_info == END))
		error_management(st0, "ERROR: multiple start or end rooms");
}

int		check_ants(t_lem0 *st0, char *line, int i)
{
	int j;

	j = 0;
	if (!line || !*line)
		error_management(st0, "ERROR: no or empty line\n");
	if (*line == '#' && *(line + 1) == '#')
	{
		instructions(st0, line + 2, 0);
		return (0);
	}
	st0->ants = atoi_lem(line, st0);
	if (j < 0 || st0->ants < 0)
		error_management(st0, "ERROR: wrong number of ants\n");
	ft_putstr(line);
	ft_putchar('\n');
	return (1);
}

int 	check_coord(char *a, char *b)
{
	if (!*a || !*b)
		return (-1);
	if (*a == '+' || *a == '-')
		a++;
	if (*b == '+' || *b == '-')
		b++;
	while (*a)
	{
		if (*a < '0' || *a > '9')
			return (-1);
		a++;
	}
	while (*b)
	{
		if (*b < '0' || *b > '9')
			return (-1);
		b++;
	}
	return (0);
}

int		hash_func(char *str)
{
	int i;

	i = 0;
	while(*str)
	{
		i += *str;
		i %= 10;
		str++;
	}
	return (i);
}

int 	check_rooms2(t_lem0 *st0, char *line, int i)
{
	char	**arr;
	int		j;
	int 	k;

	j = 0;
	k = 0;
	if (!(arr = split(line, ' ')))
		error_management(st0, "ERROR: wrong file contents or memory wasn't allocated");
	while (arr[i])
		i++;
	if (i != 3)
	{
		free_arr(arr, i);
		return (1);
	}
	if (!*arr[0] || check_coord(arr[1], arr[2]))
	{
		free_arr(arr, i);
		error_management(st0, "ERROR: wrong room name or coordinates\n");
	}
	i = hash_func(arr[0]);
	if (!(st0->lem1[i]))
		st0->lem1[i] = new_lem1(arr[0], NULL, NULL);
	else
	{
		st0->lem1[i]->next = new_lem1(arr[0], st0->lem1[i], NULL);
		st0->lem1[i] = st0->lem1[i]->next;
	}
	if (st0->tmp_info == START)
		st0->start = st0->lem1[i];
	else if (st0->tmp_info == END)
		st0->end = st0->lem1[i];
	st0->lem1[i]->room_type = st0->tmp_info;
	st0->tmp_info = 0;
	st0->lem1[i]->position[0] = atoi_lem(arr[1], st0);
	st0->lem1[i]->position[1] = atoi_lem(arr[2], st0);
	free(arr[1]);
	free(arr[2]);
	if (j < 0 || k < 0)
		error_management(st0, "ERROR: wrong coordinates\n");
	return (0);
}

int 	check_rooms1(t_lem0 *st0, char *line)
{
	if (!line || !*line || *line == 'L')
		error_management(st0, "ERROR\n");
	if (*line == '#' && *(line + 1) == '#')
		instructions(st0, line + 2, 1);
	else if (*line == '#')
		return (0);
	else
		return (check_rooms2(st0, line, 0));
	return (0);
}


void	check_links(t_lem0 *st0, char *line, int i)
{
	char **arr;

	if (!*line || *line == 'L')
		error_management(st0, "ERROR\n");
	if (*line == '#')
		return ;
	else
	{
		arr = split(line, '-');
		while (arr[i])
			i++;
		if (i != 2)
		{
			free_arr(arr, i);
			error_management(st0, "ERROR: wrong link\n");
		}
		
	}

}

void	parsing(char *av, int i, int j)
{
	int		fd;
	int		gnl;
	char	*line;
	t_lem0	*st0;

	if (!(st0 = ft_memalloc(sizeof(t_lem0))))
		error_management(st0, "ERROR: memory wasn't allocated\n");
	if (!(fd = open(av, O_RDONLY)))
		error_management(st0, "ERROR: can't open the file\n");
	while ((gnl = get_next_line(fd, &line)))
	{
		if (gnl == -1)
			error_management(st0, "ERROR: can't read from the file\n");
		if (i == 0)
			i = check_ants(st0, line, 0);
		else if (j == 0)
			j = check_rooms1(st0, line);
		if (j)
			check_links(st0, line, 0);
		free(line);
	}
//	processing(st0);
}

int	main(int ac, char **av)
{
	errno = 0;
	if (ac < 2)
		ft_putstr_fd("ERROR\n", 2);
	parsing(av[1], 0, 0);
	return 0;
}
