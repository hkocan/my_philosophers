/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatice <hatice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:38:15 by hatice            #+#    #+#             */
/*   Updated: 2024/06/09 01:14:09 by hatice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <stdlib.h>

static int	set_philo(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	table->philo = malloc(sizeof(t_philo) * table->number_philo);
	if (!table->philo)
		return (error_message(MEM_ERROR), 1);
	philo = table->philo;
	while (i < table->number_philo)
	{
		philo[i].id = i + 1;
		philo[i].eating_count = 0;
		philo[i].last_eat = table->first_time;
		philo[i].table = table;
		i++;
	}
	return (0);
}

static int	init_table(char **av, t_table *table)
{
	table->first_time = get_time();
	table->number_philo = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->dead = false;
	if (table->number_philo < 1 || table->time_to_die < 0
		|| table->time_to_eat < 0 || table->time_to_sleep < 0)
		return (1);
	if (av[5])
	{
		table->eating_count = ft_atoi(av[5]);
		if (table->eating_count < 1)
			return (1);
	}
	else
		table->eating_count = -1;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->number_philo);
	if (!table->forks)
		return (error_message(MEM_ERROR), 1);
	return (0);
}

static int	init_mutex(t_table *table)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&table->print, NULL))
		return (error_message(MUTEX_ERROR), 1);
	if (pthread_mutex_init(&table->is_anyone_dead, NULL))
		return (error_message(MUTEX_ERROR), 1);
	while (i < table->number_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			return (error_message(MUTEX_ERROR), 1);
		i++;
	}
	return (0);
}

static int	set_table(char **av, t_table *table)
{
	if (init_table(av, table))
		return (1);
	if (init_mutex(table))
		return (1);
	return (0);
}

int	setup_simulation(t_table *table, char **av)
{
	if (set_table(av, table))
		return (error_message(TABLE_ERROR), 1);
	else if (set_philo(table))
		return (error_message(PHILO_ERROR), 1);
	return (0);
}
