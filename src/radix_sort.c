/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumajeed <mumajeed@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:16:01 by mumajeed          #+#    #+#             */
/*   Updated: 2025/01/30 03:22:49 by mumajeed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"
#include <stdio.h>


// Función para ordenar listas de tamaño 2
static void sort_two(t_list **stack_a)
{
    if (*(int *)(*stack_a)->content > *(int *)(*stack_a)->next->content)
    {
        // Intercambiar los dos elementos
        t_list *tmp = *stack_a;
        *stack_a = (*stack_a)->next;
        tmp->next = (*stack_a)->next;
        (*stack_a)->next = tmp;
        printf("sa\n");
    }
}

// Función para ordenar listas de tamaño 3
static int get_max_num(t_list *stack)
{
    int max = INT_MIN;

    while (stack)
    {
        if (*(int *)(stack->content) > max)
            max = *(int *)(stack->content);
        stack = stack->next;
    }
    return max;
}

static int get_max_bits(int max_num)
{
    int bits = 0;

    while ((max_num >> bits) != 0)
        bits++;
    return bits;
}

static void rotate_a(t_list **stack_a)
{
    if (*stack_a && (*stack_a)->next)
    {
        t_list *tmp = *stack_a;
        *stack_a = (*stack_a)->next;
        tmp->next = NULL;
        ft_lstadd_back(stack_a, tmp);
        printf("ra\n");
    }
}

static void reverse_rotate_a(t_list **stack_a)
{
    if (*stack_a && (*stack_a)->next)
    {
        t_list *tmp = *stack_a;
        t_list *last = ft_lstlast(*stack_a);

        while (tmp->next != last)
            tmp = tmp->next;

        tmp->next = NULL;
        last->next = *stack_a;
        *stack_a = last;
        printf("rra\n");
    }
}

static void push_b(t_list **stack_a, t_list **stack_b)
{
    if (*stack_a)
    {
        t_list *tmp = *stack_a;
        *stack_a = (*stack_a)->next;
        tmp->next = *stack_b;
        *stack_b = tmp;
        printf("pb\n");
    }
}

static void push_a(t_list **stack_a, t_list **stack_b)
{
    if (*stack_b)
    {
        t_list *tmp = *stack_b;
        *stack_b = (*stack_b)->next;
        tmp->next = *stack_a;
        *stack_a = tmp;
        printf("pa\n");
    }
}

static void sort_three(t_list **stack_a)
{
    int a = *(int *)(*stack_a)->content;
    int b = *(int *)(*stack_a)->next->content;
    int c = *(int *)(*stack_a)->next->next->content;

    if (a > b && b > c)
    {
        printf("sa\n");  // Intercambiar a y b
        printf("rra\n"); // Rotar inversamente a
    }
    else if (a > c && c > b)
    {
        printf("ra\n");  // Rotar a
    }
    else if (b > a && a > c)
    {
        printf("rra\n"); // Rotar inversamente a
    }
    else if (b > c && c > a)
    {
        printf("sa\n");  // Intercambiar a y b
    }
    else if (c > a && a > b)
    {
        printf("sa\n");  // Intercambiar a y b
        printf("ra\n");  // Rotar a
    }
}

static void sort_five(t_list **stack_a)
{
    t_list *stack_b = NULL;
    int smallest, second_smallest;
    int size = ft_lstsize(*stack_a);
    int i = 0;

    // Verifica si la pila ya está ordenada
    if (is_sorted(*stack_a))
        return;

    // Encuentra el número más pequeño y el segundo más pequeño
    smallest = smallest_number(*stack_a);
    second_smallest = second_smallest_number(*stack_a, smallest);

    // Mover el número más pequeño a la pila B
    while (*(int *)(*stack_a)->content != smallest)
    {
        if (i++ < size / 2)
            rotate_a(stack_a);  // Rotar a
        else
            reverse_rotate_a(stack_a);  // Rotar inversamente a
    }
    push_b(stack_a, &stack_b);  // Mover el más pequeño a B

    // Mover el segundo número más pequeño a la pila B
    i = 0;  // Reiniciar el índice
    while (*(int *)(*stack_a)->content != second_smallest)
    {
        if (i++ < size / 2)
            rotate_a(stack_a);  // Rotar a
        else
            reverse_rotate_a(stack_a);  // Rotar inversamente a
    }
    push_b(stack_a, &stack_b);  // Mover el segundo más pequeño a B

    // Ordenar los tres elementos restantes en la pila A
    sort_three(stack_a);

    // Restaurar los dos elementos de la pila B a la pila A
    push_a(stack_a, &stack_b);
    push_a(stack_a, &stack_b);
}

static void radix_sort(t_list **stack_a)
{
    t_list *stack_b = NULL;
    int max_num = get_max_num(*stack_a);
    int max_bits = get_max_bits(max_num);
    int i = 0;

    while (i < max_bits)
    {
        int j = 0;
        while (j < ft_lstsize(*stack_a))
        {
            if (((*(int *)(*stack_a)->content >> i) & 1) == 1)
                rotate_a(stack_a);
            else
                push_b(stack_a, &stack_b);
            j++;
        }

        while (stack_b)
            push_a(stack_a, &stack_b);

        i++;
    }
}

void sort_stack(t_list **stack_a)
{
    if (is_sorted(*stack_a))
        return;

    int size = ft_lstsize(*stack_a);

    if (size == 2)
    {
        sort_two(stack_a);
    }
    else if (size == 3)
    {
        sort_three(stack_a);
    }
    else if (size == 5)
    {
        sort_five(stack_a);
    }
    else
    {
        radix_sort(stack_a);
    }
}
