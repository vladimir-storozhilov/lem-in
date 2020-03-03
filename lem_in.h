#ifndef LEM_IN_LEM_IN_H
#define LEM_IN_LEM_IN_H

# define START 1
# define END 2

# include "../../libft/libft.h"
#include <fcntl.h>
#include <errno.h>

struct s_lem1;

typedef struct		s_links
{
	int				weight;
	int				flag;
	int 			ant_number;
	struct s_links	*next;
	struct s_links	*prev;
	struct s_lem1	*connection_room;
}					t_links;

// each struct contains one path, path length and link to the first room from the start which defines the beginning of the path
// next and prev are links to other paths within the same solution
typedef struct			s_sol_links
{
	int 				length;
	int					ants_to_pass;
	t_links				*links;
	struct s_sol_links	*prev;
	struct s_sol_links	*next;
}						t_sol_links;

// main structure with links to several solutions. Each solution can contain several paths
// moves is calculated as number of moves, needed for this solution to put through all ants
typedef struct		s_solution
{
	int					moves;
	t_sol_links			*sol_links;
	struct s_solution	*prev;
	struct s_solution	*next;
}					t_solution;

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
	t_solution	*solution;
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
void	calc_length(t_lem0 *lem0);

// gtapioca's functions
void	breadth_first_search(t_lem0 *st0);
void	breadth_first_search_2(t_lem0 *st0);
void	shortest_ways_free(t_lem0 *st0);
// end of gtapioca's functions

#endif
