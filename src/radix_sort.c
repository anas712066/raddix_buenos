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
        swap_a(stack_a);  // Intercambiar a y b
        reverse_rotate_a(stack_a); // Rotar inversamente a
    }
    else if (a > c && c > b)
    {
        rotate_a(stack_a);  // Rotar a
    }
    else if (b > a && a > c)
    {
        reverse_rotate_a(stack_a); // Rotar inversamente a
    }
    else if (b > c && c > a)
    {
        swap_a(stack_a);  // Intercambiar a y b
    }
    else if (c > a && a > b)
    {
        swap_a(stack_a);  // Intercambiar a y b
        rotate_a(stack_a);  // Rotar a
    }
}

void sort_five(t_list **stack_a)
{
    t_list *stack_b = NULL;
    int smallest, second_smallest;
    
    smallest = smallest_number(*stack_a);
    second_smallest = second_smallest_number(*stack_a, smallest);

    // Mover el número más pequeño a B
    while (*(int *)(*stack_a)->content != smallest)
        rotate_a(stack_a); // 1 movimiento por cada rotación
    push_b(stack_a, &stack_b); // pb (1 movimiento)

    // Mover el segundo número más pequeño a B
    while (*(int *)(*stack_a)->content != second_smallest)
        rotate_a(stack_a); // 1 movimiento por cada rotación
    push_b(stack_a, &stack_b); // pb (1 movimiento)

    // Ordenar los tres números restantes
    sort_three(stack_a);

    // Regresar los números de B a A
    push_a(stack_a, &stack_b); // pa (1 movimiento)
    push_a(stack_a, &stack_b); // pa (1 movimiento)
}

void radix_sort(t_list **stack_a)
{
    t_list *stack_b = NULL;
    int max_num = get_max_num(*stack_a);
    int max_bits = get_max_bits(max_num);
    int i, j, size;

    size = ft_lstsize(*stack_a);
    for (i = 0; i < max_bits; i++)
    {
        j = 0;
        while (j < size)
        {
            if (((*(int *)(*stack_a)->content >> i) & 1) == 1)
                rotate_a(stack_a);
            else
                push_b(stack_a, &stack_b);
            j++;
        }
        while (stack_b)
            push_a(stack_a, &stack_b);
    }
}

void sort_stack(t_list **stack_a)
{
    int size = ft_lstsize(*stack_a);

    if (is_sorted(*stack_a))
        return;

    if (size == 2)
        sort_two(stack_a);
    else if (size == 3)
        sort_three(stack_a);
    else if (size == 5)
        sort_five(stack_a);
    else
        radix_sort(stack_a);
}