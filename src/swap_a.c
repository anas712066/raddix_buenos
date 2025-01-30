/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumajeed <mumajeed@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:23:27 by mumajeed          #+#    #+#             */
/*   Updated: 2025/01/30 13:23:44 by mumajeed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void swap_a(t_list **stack_a)
{
    if (*stack_a && (*stack_a)->next)
    {
        t_list *first = *stack_a;
        t_list *second = (*stack_a)->next;

        first->next = second->next;
        second->next = first;
        *stack_a = second;
        printf("sa\n");
    }
}
