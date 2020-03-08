#ifndef DINGLIST_H_INCLUDED
#define DINGLIST_H_INCLUDED

struct list
{
    struct list * next;
    unsigned int value;
};

struct list_head
{
    struct list * first;
    unsigned int counter;
};

struct list_head list_init()
{
    struct list_head list_new;
    list_new.first = 0;
    list_new.counter = 0;

    return list_new;
};

unsigned char list_insert(struct list_head * list_head, void * value, unsigned int index)
{
    if(((*list_head).counter ^ 0xFFFFFFFF) != 0)
    {
        if(index > (*list_head).counter)
            return 3;

        struct list * list_new = (struct list*)malloc(sizeof(struct list));
        if(list_new == 0)
            return 1;

        (*list_new).value = *(unsigned int*)value;

        if(index > 0)
        {
            struct list * iterator = (*list_head).first;
            for(unsigned int i = 1; i<index; i++)
            (*list_new).next = (*iterator).next;
            (*iterator).next  = list_new;
        }
        else
        {
            (*list_new).next = (*list_head).first;
            (*list_head).first = list_new;
        }

        (*list_head).counter++;

        return 0;
    }

    return 2;
}

unsigned char list_delete(struct list_head * list_head, unsigned int index)
{
    if((*list_head).counter > index)
    {
        struct list * iterator = (*list_head).first;

        if(index == 0)
        {
            (*list_head).first = (*iterator).next;
            free(iterator);
        }
        else
        {
            for(unsigned int i = 1; i < index; i++)
                iterator = (*iterator).next;

            struct list * temp = (*iterator).next;
            (*iterator).next = (*temp).next;
            free(temp);
        }

        (*list_head).counter--;

        return 0;
    }

    return 1;
}

void * list_element(struct list_head list_head, unsigned int index)
{
    if(list_head.counter <= index)
        return 0;

    struct list * iterator = list_head.first;
    for(unsigned int i = 0; i < index; i++)
                iterator = (*iterator).next;

    return &(*iterator).value;
}

unsigned int list_count(struct list_head list_head)
{
    return list_head.counter;
}

#endif // DINGLIST_H_INCLUDED
