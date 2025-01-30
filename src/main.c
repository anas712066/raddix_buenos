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

int main(int argc, char **argv)
{
    t_list *stack_a = NULL;

    if (argc > 1)
    {
        stack_a = parse_arguments(argc, argv); // Crear y validar el stack
    }
    else
    {
        return 0;
    }

    sort_stack(&stack_a); // Ordenar el stack

    // Liberar la memoria de la lista
    ft_lstclear(&stack_a, free);
    return 0;
}
