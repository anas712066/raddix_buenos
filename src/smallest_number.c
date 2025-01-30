
#include "../includes/push_swap.h"

int smallest_number(t_list *stack)
{
    int smallest;
    
    if (stack == NULL)
        return (0); // Devuelve 0 si la lista está vacía
    
    smallest = *(int *)(stack->content);
    stack = stack->next;
    
    while (stack)
    {
        if (*(int *)(stack->content) < smallest)
            smallest = *(int *)(stack->content);
        stack = stack->next;
    }
    
    return smallest;
}

int second_smallest_number(t_list *stack, int smallest)
{
    int second_smallest = INT_MAX;

    while (stack)
    {
        int num = *(int *)(stack->content);
        if (num != smallest && num < second_smallest)
            second_smallest = num;
        stack = stack->next;
    }
    return second_smallest;
}