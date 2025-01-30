/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mumajeed <mumajeed@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:15:11 by mumajeed          #+#    #+#             */
/*   Updated: 2025/01/30 03:28:07 by mumajeed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void print_error_and_exit(void)
{
    write(2, "Error\n", 6);
    exit(EXIT_FAILURE);
}

// Función para validar si una cadena es un número válido
int is_valid_number(char *str)
{
    int i = 0;
    long num;

    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return 0;
        i++;
    }
    num = ft_atoi(str);
    if (num < INT_MIN || num > INT_MAX)
        return 0;
    return 1;
}

// Función para verificar duplicados en la lista
int has_duplicates(t_list *head, int num)
{
    while (head)
    {
        if (*(int *)(head->content) == num)
            return 1;
        head = head->next;
    }
    return 0;
}

// Función para dividir una cadena en múltiples argumentos
char **split_arguments(char *str)
{
    char **args = ft_split(str, ' ');
    if (!args)
        print_error_and_exit();
    return args;
}

// Función para liberar la memoria de una matriz de cadenas
void free_arguments(char **args)
{
    int i = 0;
    while (args[i])
    {
        free(args[i]);
        i++;
    }
    free(args);
}

// Función para analizar y validar los argumentos
t_list *parse_arguments(int argc, char **argv)
{
    t_list *stack_a = NULL;
    int i = 1;

    while (i < argc)
    {
        int num = ft_atoi(argv[i]);
        t_list *new_node = ft_lstnew(&num);
        if (!new_node)
        {
            ft_lstclear(&stack_a, free);
            return (NULL);
        }
        ft_lstadd_back(&stack_a, new_node);
        i++;
    }
    return (stack_a);
}
