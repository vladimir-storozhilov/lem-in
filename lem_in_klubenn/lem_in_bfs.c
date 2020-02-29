#include "lem_in.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

bool parents_contain_way(t_lem1 *vertex)
{
    t_parents *parent;

    parent = vertex->parents;
    while (parent)
    {
        if (parent->vertex->flag == 1)
            return (true);
        parent = parent->prev;
    }
    return (false);
}

void parents_deleter(t_lem0 *st0)
{
    t_lem1 *buff_lem;
    int i;

    i = 0;
    while (i < 10)
    {
        buff_lem = (st0->lem1)[i];
        while(buff_lem)
        {
            free(buff_lem->current);
            buff_lem->current = NULL;
            buff_lem->parents = NULL;
            buff_lem = buff_lem->prev;
        }
        i++;
    }
}

void queue_deleter(t_queue *queue)
{
    t_queue *buff_queue;

    while (queue)
    {
        buff_queue = queue;
        queue = queue->next;
        free(buff_queue);
    }
}

void breadth_first_search(t_lem0 *st0)
{
    t_lem1 *current_vertex;
    t_queue *queue;
    t_links *buff_links;
    t_queue *buff_queue;
    t_queue *deleter_queue;
    t_parents *parent;
    t_way     *begin_way;
    t_way     *way2;
    t_way     *way3;
    t_way_holder *way_keeper;
    t_way_holder *buff_keeper;
    int       i;
    bool      criterion;

    criterion = true;
    i = 0;
    way_keeper = (t_way_holder *)malloc(sizeof(t_way_holder));
    way_keeper->next = 0;
    buff_keeper = way_keeper;
    while (criterion)
    {
        current_vertex = st0->start;
        queue = (t_queue *)malloc(sizeof(t_queue));
        queue->vertex = current_vertex;
        buff_queue = queue;

        parent = (t_parents *)malloc(sizeof(t_parents));
        parent->prev = NULL;
        parent->vertex = current_vertex;
        current_vertex->current = parent;
        current_vertex->parents = NULL;
        while(current_vertex != st0->end && buff_queue != 0 && current_vertex != NULL)
        {
            deleter_queue = buff_queue;
            buff_links = current_vertex->links;
            while (buff_links != 0)
            {
                if (buff_links->connection_room->flag == 0)
                {
                    if (buff_links->connection_room->parents == 0 && buff_links->connection_room != st0->start)
                    {
                        queue->next = (t_queue *)malloc(sizeof(t_queue));
                        queue->next->vertex = buff_links->connection_room;
                        parent = (t_parents *)malloc(sizeof(t_parents));
                        parent->prev = current_vertex->current;
                        parent->vertex = queue->next->vertex;
                        queue->next->vertex->current = parent;
                        queue->next->vertex->parents = current_vertex->current;
                        queue = queue->next;
                        queue->next = NULL;
                    }
                }
                buff_links = buff_links->prev;
            }
            if (buff_queue)
                buff_queue = buff_queue->next;
            if (buff_queue)
                current_vertex = buff_queue->vertex;
            free(deleter_queue);
        }
        if (current_vertex == st0->end)
        {
            parent = current_vertex->current;
            begin_way = (t_way *)malloc(sizeof(t_way));
            begin_way->vertex = parent->vertex;
            begin_way->next = 0;
            parent = parent->prev;
            while (parent)
            {
                way2 = (t_way *)malloc(sizeof(t_way));
                way2->vertex = parent->vertex;
                if (parent->vertex != st0->end && parent->vertex != st0->start)
                    way2->vertex->flag = 1;
                way2->next = begin_way;
                begin_way = way2;
                parent = parent->prev;
            }
            if (i == 0)
                way_keeper->way = way2;
            else
            {
                way_keeper->next = (t_way_holder *)malloc(sizeof(t_way_holder));
                way_keeper->next->way = way2;
                way_keeper = way_keeper->next;
                way_keeper->next = 0;
            }
        }
        if (current_vertex != st0->end)
            criterion = false;
        i = 1;
        parents_deleter(st0);
        queue_deleter(buff_queue);
    }
    while (buff_keeper)
    {
        while(buff_keeper->way)
        {
            printf("%s ",  buff_keeper->way->vertex->room_name);
            buff_keeper->way = buff_keeper->way->next;
        }
        printf("\n");
        buff_keeper = buff_keeper->next;
    }
}