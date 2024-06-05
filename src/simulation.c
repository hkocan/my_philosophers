/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatice <hatice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 23:20:35 by hatice            #+#    #+#             */
/*   Updated: 2024/06/05 19:10:59 by hatice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*philo_life(void *arg)
{
	t_table	*table;

	t_philo	*philo;
	table = (t_table *)arg;
	philo = table->philo;
	while (table->eating_count)
	{
		// printf("philo id: %d\n", philo->id);
	}
	return (NULL);
}

int	start_simulation(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_philo)
	{
		if (pthread_create(&table->philo[i].thread, NULL, &philo_life, table))
			return (0);
		i++;
	}
	i = 0;
	while (i < table->number_philo)
	{
		if (pthread_join(table->philo[i].thread, NULL))
			return (0);
		i++;
	}
	return (1);
}
