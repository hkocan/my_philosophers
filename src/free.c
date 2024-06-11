/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatice <hatice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:00:48 by hatice            #+#    #+#             */
/*   Updated: 2024/06/11 11:03:48 by hatice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdlib.h>

static void	destroy_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philo[i].eat_mutex);
		i++;
	}
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->is_anyone_dead);
}

void	free_table(t_table *table)
{
	if (table)
	{
		destroy_mutex(table);
		if (table->forks)
		{
			free(table->forks);
			table->forks = NULL;
		}
		if (table->philo)
		{
			free(table->philo);
			table->philo = NULL;
		}
		free(table);
		table = NULL;
	}
}
