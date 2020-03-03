/*

 struct solution

 z ants

sol1:	way1 - n moves;
 		way2 - n + x moves;

sol2:	way1 - a moves;
 		way2 - a + b moves;
 		way3 - a + c moves;


		 решение	 пути			  ребро к комнате
 lem0 -- solution -- sol_links ------ links
		 |_moves	 |_length		  |_ant number
					 |_ants_to_pass	  |_connection_room
 */

#include "lem_in.h"

void	calc_ants_pass(t_solution *solution, t_sol_links *sol_link, int ant, int ants)
{
	t_sol_links *tmp;

	tmp = solution->sol_links;
	while (tmp && tmp != sol_link->next && ant < ants)
	{
		tmp->ants_to_pass += 1;
		ant++;
		tmp = tmp->next;
	}
}

void	print_moves(t_solution *solution)
{
	t_sol_links *path;
	t_links		*room;
	int			first_print;

	first_print = 1;
	path = solution->sol_links;
	while (path)
	{
		room = path->links;
		while (room->next)
			room = room->next;
		while (room->prev)
		{
			if (room->ant_number && first_print-- > 0)
				printf("L%d-%s", room->ant_number, room->connection_room->room_name);
			else
				printf(" L%d-%s", room->ant_number, room->connection_room->room_name);
			room = room->prev;
		}
		path = path->next;
	}
	ft_putchar('\n');
}

void	move_ants2(t_sol_links *sol_link, int antnum)
{
	t_links		*link;

	link = sol_link->links;
	while (link->next && link->ant_number)
		link = link->next;
	while (link->prev)
	{
		link->ant_number = link->prev->ant_number;
		link = link->prev;
	}
	link->ant_number = antnum;
}

// i think it's equivalent to the next function below, but in case i'm wrong this is the long version
void	move_ants_tmp(t_solution *solution, t_lem0 *lem0)
{
	int			antnum;
	t_sol_links *sol_link;

	antnum = 0;
	while ((solution->moves)-- > 0)
	{
		sol_link = solution->sol_links;
		if (antnum < lem0->ants)
		{
		while (sol_link && antnum++ < lem0->ants)
		{
			move_ants2(sol_link, antnum);
			sol_link = sol_link->next;
		}
		if (sol_link && antnum >= lem0->ants)
			while (sol_link)
			{
				move_ants2(sol_link, 0);
				sol_link = sol_link->next;
			}
		}
		else
		{
			while (sol_link)
			{
				move_ants2(sol_link, 0);
				sol_link = sol_link->next;
			}
		}
		print_moves(solution);
	}
}

void	move_ants(t_solution *solution, t_lem0 *lem0)
{
	int			antnum;
	t_sol_links *sol_link;

	antnum = 0;
	while ((solution->moves)-- > 0)
	{
		sol_link = solution->sol_links;
		while (sol_link && antnum++ < lem0->ants)
		{
			move_ants2(sol_link, antnum);
			sol_link = sol_link->next;
		}
		if (sol_link && antnum >= lem0->ants)
			while (sol_link)
			{
				move_ants2(sol_link, 0);
				sol_link = sol_link->next;
			}
		print_moves(solution);
	}
}

void	calc_moves(t_lem0 *lem0)
{
	int ant;
	int counter;
	int moves;
	t_sol_links *sol_link;
	t_solution	*sol;

	sol = lem0->solution;

	while (sol)
	{
		ant = 0;
		counter = 1;
		moves = 0;
		sol_link = sol->sol_links;
		while (ant <= lem0->ants && sol_link)
		{
			if (sol_link->next && sol_link->length + ant + 1 <= sol_link->next->length) // solution paths must be sorted according to number of moves
			{
				calc_ants_pass(sol, sol_link, ant, lem0->ants);
				ant += counter;
			}
			else if (sol_link->next)
			{
				counter++;
				sol_link = sol_link->next;
			}
			else
			{
				calc_ants_pass(sol, sol_link, ant, lem0->ants);
				ant += counter;
			}
			moves++;
		}
		sol->moves = moves + sol->sol_links->length;
		sol = sol->next;
	}
}

t_solution	*best_solution(t_lem0 *lem0)
{
	t_solution	*sol;
	t_solution *tmp;
	int 		moves;

	tmp = lem0->solution;
	moves = tmp->moves;
	sol = tmp;
	while (tmp)
	{
		if (moves < tmp->moves)
		{
			moves = tmp->moves;
			sol = tmp;
		}
		tmp = tmp->next;
	}
	return (sol);
}

void	calc_length(t_lem0 *lem0)
{
	int i;
	t_solution	*sol;
	t_links		*link;
	t_sol_links	*sol_link;

	sol = lem0->solution;
	while (sol)
	{
		sol_link = sol->sol_links;
		while (sol_link)
		{
			i = 0;
			link = sol_link->links;
			while (link)
			{
				i++;
				link = link->next;
			}
			sol_link->length = i;
			sol_link = sol_link->next;
		}
		sol = sol->next;
	}
	calc_moves(lem0);
	move_ants(best_solution(lem0), lem0);

}