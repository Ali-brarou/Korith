#ifndef _KORITH_LIST_H_
#define _KORITH_LIST_H_

#include <korith/types.h> 

static inline void list_head_init(struct list_head *list)
{ 
    list->next = list; 
    list->prev = list; 
}

/* helper function */ 
static inline void __list_add(struct list_head *new, 
                              struct list_head *prev, 
                              struct list_head *next)
{
    new->next = next;  
    new->prev = prev; 
    prev->next = new; 
    next->prev = new; 
}

static inline void list_add(struct list_head *new, struct list_head *head)
{
    __list_add(new, head, head->next); 
}

static inline void list_add_tail(struct list_head *new, struct list_head *head)
{
    __list_add(new, head->prev, head); 
}

#define list_entry(ptr, type, member) \
    ((type*)((char*)ptr - offsetof(type, member)))

/* not safe for deletion */ 
#define list_for_each(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)

#endif
