#include "lem_in.h"
#include <stdlib.h>
#include <stdio.h>

void breadth_first_search(t_lem0 *st0)
{
    t_lem1 *current_vertex;
    t_queue *queue;
    t_links *buff_links;
    t_queue *buff_queue;
    t_queue *deleter_queue;
    
    current_vertex = st0->start;
    current_vertex->flag = 1;
    queue = (t_queue *)malloc(sizeof(t_queue));
    queue->vertex = current_vertex;
    buff_queue = queue;
    while(current_vertex != st0->end && current_vertex != NULL)
    {
        deleter_queue = buff_queue;
        buff_links = current_vertex->links;
        while (buff_links != 0)
        {
            if (buff_links->connection_room->flag == 0)
            {
                queue->next = (t_queue *)malloc(sizeof(t_queue));
                queue->next->vertex = buff_links->connection_room;
                queue = queue->next;
                buff_links->connection_room->flag = 1;
            }
            buff_links = buff_links->prev;
        }
        buff_queue = buff_queue->next;
        current_vertex = buff_queue->vertex;
        free(deleter_queue);
    }
    printf("%s\n", current_vertex->room_name);
}