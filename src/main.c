/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: hatice <hatice@student.42.fr>              +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/06/03 21:47:07 by hatice            #+#    #+#             */
/*   Updated: 2024/06/03 21:47:07 by hatice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	set_philo(t_table *table, t_philo *philo)
{
	int	i;

	i = 0;
	table->philo = malloc(sizeof(t_philo) * table->number_philo);
	philo = table->philo;
	if (!table->philo)
		return (0);
	while (i < table->number_philo)
	{
		philo[i].id = i + 1;
		philo[i].eating_count = 0;
		philo[i].last_eat = table->first_time;
		// philo[i].table = table;
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_table	*table;
	t_philo	*philo;

	table = malloc(sizeof(t_table));
	philo = malloc(sizeof(t_philo));
	if (!(ac == 5 || ac == 6))
		return (error_message("Error: Wrong number of arguments!!!\n"), 1);
	else if (!set_table(av, table, philo))
	{
		printf("num philo: %d\n", table->number_philo); // delete
		return (error_message("Error: Wrong arguments!!!\n"), 1);
	}
	else if (!set_philo(table, philo))
		return (error_message("Error: Philo initialization failed!!!\n"), 1); //
	else if (!start_simulation(table))
		return (error_message("Error: Simulation failed!!!\n"), 1); //
	return (0);
}
