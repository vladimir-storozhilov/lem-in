/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:57:06 by gtapioca          #+#    #+#             */
/*   Updated: 2020/02/28 00:32:46 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include <stdbool.h>
# include "lem_in_2.h"

typedef struct s_vertex
{
    bool marked;
    char *name;
    int x;
    int y;
    int pointer_amount;   
    // t_join *list_link;
}              t_vertex;

typedef struct s_help
{
    t_vertex    *vertex;
    struct s_help *next;
}              t_help;

typedef struct s_join
{
    t_vertex    *vertex;
    struct s_join *next;
}               t_join;

typedef  struct s_list_help
{
    t_vertex *current;
   struct s_list_help *next;
}               t_list_help;

#endif