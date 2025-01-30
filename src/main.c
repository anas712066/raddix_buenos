/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumajeed <mumajeed@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:17:44 by mumajeed          #+#    #+#             */
/*   Updated: 2025/01/30 03:28:16 by mumajeed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

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