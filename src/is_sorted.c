/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_sorted.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumajeed <mumajeed@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 00:32:50 by mumajeed          #+#    #+#             */
/*   Updated: 2025/01/30 00:32:50 by mumajeed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int is_sorted(t_list *stack)
{
    while (stack && stack->next)
    {
        if (*(int *)(stack->content) > *(int *)(stack->next->content))
            return 0; // No está ordenado
        stack = stack->next;
    }
    return 1; // Está ordenado
}
