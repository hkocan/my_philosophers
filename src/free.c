/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatice <hatice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:00:48 by hatice            #+#    #+#             */
/*   Updated: 2024/06/09 01:11:40 by hatice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <stdlib.h>

static void	free_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->number_philo)
	{
		if (&table->forks[i])
			pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	if (&table->print)
		pthread_mutex_destroy(&table->print);
	if (&table->is_anyone_dead)
		pthread_mutex_destroy(&table->is_anyone_dead);
}

void	free_table(t_table *table)
{
	if (table->forks)
		free_forks(table);
	if (table->philo)
		free(table->philo);
	if (table)
		free(table);
}
