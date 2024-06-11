/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:++:+			+:+   */
/*   By: hatice <hatice@student.42.fr>              +#+  +:+	   +#+        */
/*                                                +#+#+#+#+#+	+#+           */
/*   Created: 2024/06/03 21:47:07 by hatice            #+#    #+#             */
/*   Updated: 2024/06/03 21:47:07 by hatice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

int	main(int ac, char **av)
{
	t_table	*table;

	if (check_args(ac, av))
		return (error_message(ARG_ERROR), 1);
	table = malloc(sizeof(t_table));
	if (!table)
		return (error_message(MEM_ERROR), 1);
	if (setup_simulation(table, av))
		return (free_table(table), 1);
	if (start_simulation(table))
		return (free_table(table), error_message(SIMULATION_ERROR), 1);
	free_table(table);
	return (0);
}
