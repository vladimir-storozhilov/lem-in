#include "lem_in.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// void shortest_ways_free(t_lem0 *st0)
// {
//     t_links *buff_links;

//     buff_links = st0->solution->sol_links->links;
//     while (buff_links)
//     {
//         buff_links->connection_room->flag = 0;
//         buff_links = buff_links->next;
//     }
// }

void negative_weigth_finder(t_parents *begin_way, t_parents *way2)
{
    t_links *buff_links;
    t_links *buff_links_2;

    buff_links = begin_way->vertex->links;
    while (buff_links->connection_room != way2->vertex)
        buff_links = buff_links->prev;
    if (buff_links->weight == -1)
    {
        buff_links_2 = way2->vertex->links;
        while (buff_links_2->connection_room != begin_way->vertex)
            buff_links_2 = buff_links_2->prev;
        buff_links_2->weight = -1;
    }
}

// void current_vertex_and_queue_initializer(t_lem1 **current_vertex,
//     t_queue **queue, t_queue **buff_queue, t_lem0 *st0)
// {
//     (*current_vertex) = st0->start;
//     (*queue) = (t_queue *)malloc(sizeof(t_queue));
//     (*queue)->vertex = (*current_vertex);
//     (*buff_queue) = (*queue);
//     (*queue)->next = NULL;
//     (*current_vertex)->current = (t_parents *)malloc(sizeof(t_parents));
//     (*current_vertex)->current->prev = NULL;
//     (*current_vertex)->current->vertex = (*current_vertex);
//     (*current_vertex)->parents = NULL;
// }

bool parents_contain_way(t_queue *buff_queue)
{
    t_parents *parent;

    parent = 0;
    while (buff_queue)
    {
        parent = buff_queue->vertex->parents;
        while (parent)
        {
            if (parent->vertex->flag == 1)
                return (true);
            parent = parent->prev;
        }
        buff_queue = buff_queue->next;
    }
    return (false);
}

// void parents_deleter(t_lem0 *st0)
// {
//     t_lem1 *buff_lem;
//     int i;

//     i = 0;
//     while (i < 10)
//     {
//         buff_lem = (st0->lem1)[i];
//         while(buff_lem)
//         {
//             free(buff_lem->current);
//             buff_lem->current = NULL;
//             buff_lem->parents = NULL;
//             buff_lem = buff_lem->prev;
//         }
//         i++;
//     }
// }

// void queue_deleter(t_queue *queue)
// {
//     t_queue *buff_queue;

//     while (queue)
//     {
//         buff_queue = queue;
//         queue = queue->next;
//         free(buff_queue);
//     }
// }

void    ways_destroyer(t_lem1 *current_vertex)
{
    t_parents *parent;

    parent = current_vertex->current;
    while (parent->prev)
    {
        negative_weigth_finder(parent, parent->prev);
        parent = parent->prev;
    }
}

// void queue_creator(t_lem1 **current_vertex, t_queue **queue, t_links **buff_links)
// {
//     t_links *helper_links;
//     (*queue)->next = (t_queue *)malloc(sizeof(t_queue));
//     (*queue)->next->vertex = (*buff_links)->connection_room;
//     (*queue)->next->vertex->current = (t_parents *)malloc(sizeof(t_parents));
//     (*queue)->next->vertex->current->prev = (*current_vertex)->current;
//     (*queue)->next->vertex->current->vertex = (*queue)->next->vertex;
//     (*queue)->next->vertex->parents = (*current_vertex)->current;
//     (*queue) = (*queue)->next;
//     (*queue)->next = NULL;
// }

bool destroyed_links_finder(t_links *direct_link, t_lem1 *current_vertex)
{
    t_links *buff_link;

    if (direct_link->weight == -1)
    {
        buff_link = direct_link->connection_room->links;
        while (buff_link)
        {
            if (buff_link->connection_room == current_vertex)
            {
                if (buff_link->weight == -1)
                    return (true);
            }
            buff_link = buff_link->prev;
        }
    }
    return (false);
}

bool breadth_first_search_cycle_finder_2(t_queue **queue,
    t_queue **buff_queue, t_lem1 **current_vertex, t_lem0 *st0)
{
    t_queue *deleter_queue;
    t_links *buff_links;

    while((*current_vertex != st0->end &&
        *buff_queue != 0 && *current_vertex != NULL))
    {
        deleter_queue = *buff_queue;
        buff_links = (*current_vertex)->links;
        while (buff_links != 0)
        {
            if (!(destroyed_links_finder(buff_links, *current_vertex)) && buff_links->connection_room->flag != 1)
            {
                if (buff_links->connection_room->parents == 0 &&
                    buff_links->connection_room != st0->start)
                {
                    queue_creator(current_vertex, queue, &buff_links);
                }
            }
            buff_links = buff_links->prev;
        }
        if (*buff_queue)
            *buff_queue = (*buff_queue)->next;
        if (*buff_queue)
            (*current_vertex) = (*buff_queue)->vertex;
        free(deleter_queue);
    }
    if (*current_vertex == st0->end)
        return true;
    return false;
}

bool breadth_first_search_cycle_finder_1(t_queue **queue,
    t_queue **buff_queue, t_lem1 **current_vertex, t_lem0 *st0)
{
    t_queue *deleter_queue;
    t_links *buff_links;

    while((*current_vertex != st0->end &&
        *buff_queue != 0 && *current_vertex != NULL))
    {
        deleter_queue = *buff_queue;
        buff_links = (*current_vertex)->links;
        while (buff_links != 0)
        {
            if (buff_links->weight != -1)
            {
                if (buff_links->connection_room->parents == 0 &&
                    buff_links->connection_room != st0->start)
                {
                    queue_creator(current_vertex, queue, &buff_links);
                }
            }
            buff_links = buff_links->prev;
        }
        if (*buff_queue)
            *buff_queue = (*buff_queue)->next;
        if (*buff_queue)
            (*current_vertex) = (*buff_queue)->vertex;
        free(deleter_queue);
    }
    if (*current_vertex == st0->end)
        return true;
    return false;
}

void weight_zeroing(t_lem0 *st0)
{
    int i;
    t_lem1 *buff;
    t_links *buff_link;

    i = 0;
    while(i < 10)
    {
        buff = st0->lem1[i];
        while (buff)
        {
            buff_link = buff->links;
            while (buff_link->prev)
            {
                if (buff_link->weight == -1)
                    buff_link->weight = 0;
                buff_link = buff_link->prev;
            }
            buff = buff->prev;
        }
        i++;
    }
}

void delete_flags(t_lem0 *st0)
{
    int i;
    t_lem1 *buff;

    i = 0;
    while(i < 10)
    {
        buff = st0->lem1[i];
        while (buff)
        {
            if (buff->flag == 1)
                buff->flag = 0;
            buff = buff->prev;
        }
        i++;
    }
}

void ways_weight_modifier(t_lem0 *st0)
{
    t_links *buff_link;
    t_links *buff_link_2;
    t_sol_links *buff_sol;

    buff_sol = st0->solution->sol_links;
    while (buff_sol)
    {
        buff_link = buff_sol->links;
        while (buff_link && buff_link->connection_room != st0->end)
        {
            buff_link_2 = buff_link->connection_room->links;
            while (buff_link_2)
            {
                if (buff_link_2->connection_room == buff_link->next->connection_room)
                    buff_link_2->weight = -1;
                buff_link_2 = buff_link_2->prev;
            }
            buff_link = buff_link->next;
        }
        buff_sol = buff_sol->next;
    }
}

void    ways_creator_2(t_lem1 *current_vertex, t_lem0 *st0,
        int *i, t_queue *buff_queue, t_sol_links **way_keeper)
{
    t_parents   *parent;
    t_links     *begin_way;
    t_links     *way2;
    t_links     *buff_links;
    int         length;

    length = 0;
    parent = current_vertex->current;
    begin_way = (t_links *)malloc(sizeof(t_links));
    begin_way->connection_room = parent->vertex;
    begin_way->next = 0;
    begin_way->prev = 0;
    parent = parent->prev;
    while (parent)
    {
        way2 = (t_links *)malloc(sizeof(t_links));
        way2->connection_room = parent->vertex;
        // buff_links = way2->connection_room->links;
        // while(buff_links->connection_room != begin_way->connection_room)
        //     buff_links = buff_links->prev;
        // buff_links->weight = -1;
        if (parent->vertex != st0->end
            && parent->vertex != st0->start)
            way2->connection_room->flag = 1;
        way2->next = begin_way;
        begin_way->prev = way2;
        begin_way = way2;
        way2->prev = 0;
        parent = parent->prev;
        length += 1;
    }
    if (*i == 0)
    {
        (*way_keeper)->links = way2;
        (*way_keeper)->next = 0;
        (*way_keeper)->prev = 0;
        (*way_keeper)->length = length;
    }
    else
    {
        (*way_keeper)->next = (t_sol_links *)malloc(sizeof(t_sol_links));
        (*way_keeper)->next->links = way2;
        (*way_keeper)->next->prev = (*way_keeper);
        (*way_keeper) = (*way_keeper)->next;
        (*way_keeper)->length = length;
        (*way_keeper)->next = 0;
    }
}

void breadth_first_search_2(t_lem0 *st0)
{
    t_lem1 *current_vertex;
    t_queue *queue;
    t_queue *buff_queue;
    t_solution  *solution;
    t_sol_links  *way_keeper;
    t_sol_links  *buff_keeper;
    int       i;
    bool      criterion;

    delete_flags(st0);
    weight_zeroing(st0);
    ways_weight_modifier(st0);
    criterion = true;
    i = 0;
    while (true)
    {
        current_vertex_and_queue_initializer(&current_vertex, &queue, &buff_queue, st0);
        if (!breadth_first_search_cycle_finder_1(&queue, &buff_queue, &current_vertex, st0))
        {
            parents_deleter(st0);
            queue_deleter(buff_queue);
            // criterion = false;
            break;
        }
        // if (current_vertex == st0->end)
        ways_destroyer(current_vertex);
        parents_deleter(st0);
        queue_deleter(buff_queue);
    }
    while (criterion)
    {
        current_vertex_and_queue_initializer(&current_vertex, &queue, &buff_queue, st0);
        if (!breadth_first_search_cycle_finder_2(&queue, &buff_queue, &current_vertex, st0))
            break;
        if (current_vertex == st0->end)
            ways_creator_2(current_vertex, st0, &i, buff_queue, &way_keeper);
        if (current_vertex != st0->end)
            criterion = false;
        i = 1;
        parents_deleter(st0);
        queue_deleter(buff_queue);
    }
    // way_keeper = (t_sol_links *)malloc(sizeof(t_sol_links));
    // way_keeper->next = 0;
    buff_keeper = way_keeper;
    st0->solution->prev = (t_solution *)malloc(sizeof(t_solution));
    st0->solution->prev->prev = 0;
    st0->solution->prev->next = st0->solution;
    st0->solution->sol_links = buff_keeper;
    st0->solution = st0->solution->prev;
    while (buff_keeper)
    {
        while(buff_keeper->links)
        {
            printf("%s ",  buff_keeper->links->connection_room->room_name);
            buff_keeper->links = buff_keeper->links->next;
        }
        printf("\n");
        buff_keeper = buff_keeper->prev;
    }
    printf("\n");
}

void bfs_expand(t_lem0 *st0)
{
    t_solution *buff_solution;

    buff_solution = st0->solution;
    while(buff_solution)
    {
        breadth_first_search_2(st0);
        buff_solution = buff_solution->prev;
    }
}