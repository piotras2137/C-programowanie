#ifndef DINGSTACK_H_INCLUDED
#define DINGSTACK_H_INCLUDED

struct stack_head
{
    unsigned int counter;
    struct stack * current;
};

struct stack
{
    unsigned int value;
    struct stack * next;
};

struct stack_head stack_init()
{
    struct stack_head new_stack_head;
    new_stack_head.counter = 0;
    new_stack_head.current = 0;
    return new_stack_head;
};

unsigned char stack_push(struct stack_head * stack_head, void * value)
{
    if(((*stack_head).counter ^ 0xFFFFFFFF) != 0)
    {
        struct stack * new_stack = (struct stack*)malloc(sizeof(struct stack));
        if(new_stack == 0)
            return 1;

        (*new_stack).next = (*stack_head).current;
        (*new_stack).value = *((unsigned int*)value);
        (*stack_head).current = new_stack;
        (*stack_head).counter++;

        return 0;
    }

    return 2;
}

unsigned char stack_pop(struct stack_head * stack_head)
{
    if((*stack_head).counter > 0)
    {
        struct stack * temp = (*stack_head).current;
        (*stack_head).current = (*temp).next;
        (*stack_head).counter--;
        free(temp);

        return 0;
    }
    return 1;
}

void * stack_top(struct stack_head stack_head)
{
    if(stack_head.current != 0)
        return &stack_head.current[0].value;

    return 0;
}

unsigned char stack_empty(struct stack_head stack_head)
{
    return stack_head.counter == 0;
}

#endif // DINGSTACK_H_INCLUDED
