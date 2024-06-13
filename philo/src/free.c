/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkocan <hkocan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:00:48 by hatice            #+#    #+#             */
/*   Updated: 2024/06/13 20:11:26 by hkocan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

void	clean(t_table *table, int i, int control)
{
	if (control && i >= 0)
	{
		pthread_mutex_destroy(&table->philo[i].eat_mutex);
		control = 0;
		i--;
	}
	while (i >= 0)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philo[i].eat_mutex);
		i--;
	}
}

static	void	mutex_destroy(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philo[i].eat_mutex);
		i++;
	}
	pthread_mutex_destroy(&table->run_simulation);
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->is_anyone_dead);
}

void	free_table(t_table *table, int control)
{
	if (table)
	{
		if (control)
			mutex_destroy(table);
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
