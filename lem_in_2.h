/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_2.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:57:06 by gtapioca          #+#    #+#             */
/*   Updated: 2020/02/28 00:18:59 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H2
# define LEM_IN_H2
# include "lem_in.h"

typedef struct s_join
{
    t_vertex    *vertex;
    struct s_join *next;
}                t_join;

#endif