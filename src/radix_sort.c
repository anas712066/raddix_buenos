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

void rotate_a(t_list **stack_a)
{
    if (*stack_a && (*stack_a)->next)
    {
        t_list *tmp = *stack_a;
        *stack_a = (*stack_a)->next;
        tmp->next = NULL;
        ft_lstadd_back(stack_a, tmp);
        ft_putstr_fd("ra\n", 1);
    }
}

void reverse_rotate_a(t_list **stack_a)
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
        ft_putstr_fd("rra\n", 1);
    }
}

void push_b(t_list **stack_a, t_list **stack_b)
{
    if (*stack_a)
    {
        t_list *tmp = *stack_a;
        *stack_a = (*stack_a)->next;
        tmp->next = *stack_b;
        *stack_b = tmp;
        ft_putstr_fd("pb\n", 1);
    }
}

void push_a(t_list **stack_a, t_list **stack_b)
{
    if (*stack_b)
    {
        t_list *tmp = *stack_b;
        *stack_b = (*stack_b)->next;
        tmp->next = *stack_a;
        *stack_a = tmp;
        ft_putstr_fd("pa\n", 1);
    }
}

static void sort_two(t_list **stack_a)
{
    if (*(int *)(*stack_a)->content > *(int *)(*stack_a)->next->content)
    {
        swap_a(stack_a);
    }
}

static void sort_three(t_list **stack_a)
{
    int a = *(int *)(*stack_a)->content;
    int b = *(int *)(*stack_a)->next->content;
    int c = *(int *)(*stack_a)->next->next->content;

    if (a > b && b > c)
    {
        swap_a(stack_a);
        reverse_rotate_a(stack_a);
    }
    else if (a > c && c > b)
    {
        rotate_a(stack_a);
    }
    else if (b > a && a > c)
    {
        reverse_rotate_a(stack_a);
    }
    else if (b > c && c > a)
    {
        swap_a(stack_a);
    }
    else if (c > a && a > b)
    {
        swap_a(stack_a);
        rotate_a(stack_a);
    }
}

void sort_five(t_list **stack_a)
{
    t_list *stack_b = NULL;
    int smallest = smallest_number(*stack_a);
    int second_smallest = second_smallest_number(*stack_a, smallest);

    while (ft_lstsize(*stack_a) > 3)
    {
        if (*(int *)(*stack_a)->content == smallest || *(int *)(*stack_a)->content == second_smallest)
        {
            push_b(stack_a, &stack_b);
        }
        else
        {
            rotate_a(stack_a);
        }
    }
    sort_three(stack_a);
    push_a(stack_a, &stack_b);
    if (*(int *)(stack_b->content) == smallest)
    {
        push_a(stack_a, &stack_b);
    }
    else
    {
        push_a(stack_a, &stack_b);
        rotate_a(stack_a);
    }
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
        int size = ft_lstsize(*stack_a);
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
        i++;
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