/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtapioca <gtapioca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:57:06 by gtapioca          #+#    #+#             */
/*   Updated: 2020/02/28 00:15:56 by gtapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line/get_next_line.h"
#include "get_next_line/libft/libft.h"
#include "lem_in.h"
#include "lem_in_2.h"
#include <stdlib.h>
#include <stdio.h>

void add_link(t_list_help *buff_list, t_list_help *begin_list)
{
    t_join *buff;
    if (buff_list->current->list_link == 0)
    {
        buff = (t_join *)malloc(sizeof(t_join));
        // buff_list->current->list_link = (t_join *)malloc(sizeof(t_join));
        buff->vertex = begin_list->current;
        buff_list->current->list_link = buff;
    }
    else
    {
        buff = buff_list->current->list_link;
        while (buff->next)
            buff = buff->next;
        buff->next = (t_join *)malloc(sizeof(t_join));
        buff->next->vertex = begin_list->current;
        buff->next->next = 0;
    }
    if (begin_list->current->list_link == 0)
    {
        buff = (t_join *)malloc(sizeof(t_join));
        // buff_list->current->list_link = (t_join *)malloc(sizeof(t_join));
        buff->vertex = buff_list->current;
        begin_list->current->list_link = buff;
        // begin_list->current->list_link = (t_join *)malloc(sizeof(t_join));
        // begin_list->current->list_link->vertex = buff_list->current;
    }
    else
    {
        buff = begin_list->current->list_link;
        while (buff->next)
            buff = buff->next;
        buff->next = (t_join *)malloc(sizeof(t_join));
        buff->next->vertex = begin_list->current;
        buff->next->next = 0;
    }
}

char *substring_finder(char *str, bool half)
{
    char *substr;
    int i;

    i = 0;
    if (half == true)
    {
        while(str[i] != '-')
            i++;
        substr = (char *)malloc(sizeof(char) * (i + 1));
        i = 0;
        while (str[i] != '-')
        {
            substr[i] = str[i];
            i++;
        }
        substr[i] = 0;
    }
    else
    {
        while(*str != '-')
            str++;
        str++;
        while(str[i] != '\0')
            i++;
        substr = (char *)malloc(sizeof(char) * (i + 1));
        i = 0;
        while (str[i] != '\0')
        {
            substr[i] = str[i];
            i++;
        }
        substr[i] = 0;
    }
    return (substr);
}

void parse_vertex(char *str, t_list_help  *j)
{
    int count;
    char *str1;
    
    count = 0;
    while (str[count] != '\0' && str[count] != ' ')
        count++;
    j->current->name = (char *)malloc(sizeof(char) * count);
    while (*str != '\0' && *str != ' ')
    {
        *(j->current->name) = *str;
        str++;
        (j->current->name)++;
    }
    *(j->current->name) = 0;
    (j->current->name)--;
    while (*(j->current->name) != 0)
        (j->current->name)--;
    (j->current->name)++;
    count = 0;
    while (*str != '\0')
    {
        if (*str <= '9' && *str >= '0' && count == 0)
        {
            j->current->x = ft_atoi(str);
            str = str + ft_strlen(ft_itoa(j->current->x));
            count++;
        }
        if (*str <= '9' && *str >= '0' && count == 1)
        {
            j->current->y = ft_atoi(str);
            str = str + ft_strlen(ft_itoa(j->current->y));
        }
        if (*str != 0)
            str++;
    }
    j->current->list_link = NULL;
}

int main()
{
    int ants_amount;
    char **line;
    *line = NULL;
    t_vertex *list_rooms;
    t_list_help *list_rooms_order;
    t_list_help *begin_list;
    t_list_help *begin_list2;
    t_list_help *buff_list;

    get_next_line(0, line);
    ants_amount = ft_atoi(*line);
    int i;
    i = 0;
    while (get_next_line(0, line) && *line && !(ft_strchr(*line, '-')))
    {
        if (i == 0)
        {
            list_rooms_order = (t_list_help *)malloc(sizeof(t_list_help));
            begin_list =  list_rooms_order;
            list_rooms_order->current = (t_vertex *)malloc(sizeof(t_vertex));
            parse_vertex(*line, list_rooms_order);
            i++;
        }
        else
        {
            list_rooms_order->next = (t_list_help *)malloc(sizeof(t_list_help));
            list_rooms_order = list_rooms_order->next;
            list_rooms_order->current = (t_vertex *)malloc(sizeof(t_vertex));
            parse_vertex(*line, list_rooms_order);
            i++;
        }       
    }
    list_rooms_order->next = NULL;
    begin_list2 = begin_list;
    printf("\n");
    while (begin_list)
    {
        printf("%s %d %d\n", begin_list->current->name, begin_list->current->x, begin_list->current->y);
        begin_list = begin_list->next;
    }
    begin_list = begin_list2;
    while (get_next_line(0, line))
    {
        while (begin_list && ft_strcmp(substring_finder(*line, true), begin_list->current->name) != 0)
            begin_list = begin_list->next;
        if (begin_list != NULL && ft_strcmp(substring_finder(*line, true), begin_list->current->name) != 0)
        {
            buff_list = begin_list;
            begin_list = begin_list2;
            while (begin_list && ft_strcmp(substring_finder(*line, false), begin_list->current->name) != 0)
                begin_list = begin_list->next;
            add_link(buff_list, begin_list);
            // (buff_list->current->next)[buff_list->current->pointer_amount] = begin_list->current;
            // buff_list->current->pointer_amount += 1;
            // (begin_list->current->next)[begin_list->current->pointer_amount] = buff_list->current;
            // begin_list->current->pointer_amount += 1;
        }
        begin_list = begin_list2;
    }
    // printf("%s %s", begin_list->current->list_link->vertex->name, begin_list->current->list_link->next->vertex->name);
}