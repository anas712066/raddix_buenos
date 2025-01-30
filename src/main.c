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
    t_list *stack_a;

    if (argc < 2)
        return (0);

    // Parsear los argumentos y llenar la pila A
    stack_a = parse_arguments(argc, argv);
    if (!stack_a)
    {
        ft_putstr_fd("Error\n", 2);
        return (1);
    }

    // Ordenar solo si no está ordenado
    if (!is_sorted(stack_a))
        sort_stack(&stack_a);

    // Liberar memoria al final
    ft_lstclear(&stack_a, free);

    return (0);
}