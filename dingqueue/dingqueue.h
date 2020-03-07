#ifndef DINGQUEUE_H_INCLUDED
#define DINGQUEUE_H_INCLUDED

struct queue
{
    struct queue * next;
    unsigned int value;
};

struct queue_head
{
    unsigned int counter;
    struct queue * first;
    struct queue * last;
};

struct queue_head queue_init()
{
    struct queue_head queue_new;
    queue_new.counter = 0;
    queue_new.first = 0;
    queue_new.last = 0;

    return queue_new;
};

unsigned char queue_push(struct queue_head * queue_head, void * value)
{
    if(((*queue_head).counter ^ 0xFFFFFFFF) != 0)
    {
        struct queue * queue_new = (struct queue*)malloc(sizeof(struct queue));
        if(queue_new == 0)
            return 1;

        (*queue_new).value = *(unsigned int*)value;
        (*queue_new).next = 0;
        if((*queue_head).first != 0)
            (*queue_head).last[0].next = queue_new;
        else
            (*queue_head).first = queue_new;
        (*queue_head).last = queue_new;
        (*queue_head).counter++;

        return 0;
    }

    return 2;
}

unsigned char queue_pop(struct queue_head * queue_head)
{
    if((*queue_head).counter > 0)
    {
        struct queue * temp = (*queue_head).first;
        (*queue_head).first = (*temp).next;
        (*queue_head).counter--;
        if((*queue_head).counter == 0)
            (*queue_head).last = 0;
        free(temp);

        return 0;
    }

    return 1;
}

void * queue_first(struct queue_head queue_head)
{
    if(queue_head.counter > 0)
        return &queue_head.first[0].value;

    return 0;
}

unsigned char queue_empty(struct queue_head queue_head)
{
    return queue_head.counter == 0;
}

#endif // DINGQUEUE_H_INCLUDED
