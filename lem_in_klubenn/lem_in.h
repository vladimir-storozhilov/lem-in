#ifndef LEM_IN_LEM_IN_H
#define LEM_IN_LEM_IN_H

# define START 1
# define END 2

# include "../libft/libft.h"
#include <fcntl.h>
#include <errno.h>

struct s_lem1;

typedef struct		s_links
{
	int				weight;
	int				flag;
	struct s_links	*next;
	struct s_links	*prev;
	struct s_lem1	*connection_room;
}					t_links;

// gtapioca's structure
typedef struct		s_parents
{
	// struct s_parents *next;
	struct s_parents *prev;
	struct s_lem1	*vertex;
}					t_parents;

typedef struct		s_lem1
{
	int				flag;
	char			*room_name;
	int 			position[2];
	int 			room_type;
	struct s_lem1	*next;
	struct s_lem1	*prev;
	struct s_links	*links;
	t_parents		*parents;
	t_parents		*current;
}					t_lem1;

typedef struct	s_lem0
{
	int 		ants;
	int 		tmp_info;
	t_lem1 		*start;
	t_lem1 		*end;
	t_lem1		*lem1[10];
	t_list		*head_print;
	t_list		*print;
}				t_lem0;

// gtapioca's structures

typedef struct s_queue
{
	t_lem1	*vertex;
	struct s_queue	*next;
}				t_queue;

typedef struct s_way
{
	t_lem1	*vertex;
	struct s_way *next;
}				t_way;

typedef struct s_way_holder
{
	t_way				*way;
	struct s_way_holder *next;
}				t_way_holder;

// end of gtapioca's structures

int		atoi_lem(char *str, t_lem0 *st0);
char	**split(char *line, char c);
void	error_management(t_lem0 *st, char *str);
int		get_next_line(int fd, char **line);

// gtapioca's functions
void	breadth_first_search(t_lem0 *st0);
// end of gtapioca's functions

#endif
