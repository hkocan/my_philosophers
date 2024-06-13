/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkocan <hkocan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:38:15 by hatice            #+#    #+#             */
/*   Updated: 2024/06/13 20:12:26 by hkocan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>
#include <stdlib.h>

static int	set_philo(t_table *table)
{
	int	i;

	i = 0;
	table->philo->table = table;
	while (i < table->num_philo)
	{
		table->philo[i].id = i + 1;
		table->philo[i].eating_count = 0;
		table->philo[i].table = table;
		i++;
	}
	return (0);
}

static int	init_table(char **av, t_table *table)
{
	memset(table, 0, sizeof(t_table));
	table->num_philo = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->dead = false;
	table->run_control = false;
	if (table->num_philo < 1 || table->time_to_die < 0
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
	return (0);
}

static	int	init_mutex_add(t_table *table, int i)
{
	if (pthread_mutex_init(&table->run_simulation, NULL))
	{
		clean(table, i - 1, 1);
		return (error_message(MUTEX_ERROR), 1);
	}
	if (pthread_mutex_init(&table->print, NULL))
	{
		clean(table, i - 1, 0);
		pthread_mutex_destroy(&table->run_simulation);
		return (error_message(MUTEX_ERROR), 1);
	}
	if (pthread_mutex_init(&table->is_anyone_dead, NULL))
	{
		clean(table, i - 1, 0);
		pthread_mutex_destroy(&table->run_simulation);
		pthread_mutex_destroy(&table->print);
		return (error_message(MUTEX_ERROR), 1);
	}
	return (0);
}

static	int	init_mutex(t_table *table)
{
	int	i;

	i = -1;
	table->philo = malloc(sizeof(t_philo) * table->num_philo);
	if (!table->philo)
		return (error_message(MEM_ERROR), 1);
	while (++i < table->num_philo)
		memset(&table->philo[i], 0, sizeof(t_philo));
	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philo);
	if (!table->forks)
		return (error_message(MEM_ERROR), 1);
	while (i < table->num_philo)
	{
		if (pthread_mutex_init(&table->philo[i].eat_mutex, NULL))
			return (clean(table, i - 1, 1), error_message(MUTEX_ERROR), 1);
		if (pthread_mutex_init(&table->forks[i], NULL))
			return (clean(table, i, 1), error_message(MUTEX_ERROR), 1);
		i++;
	}
	if (init_mutex_add(table, i))
		return (1);
	return (0);
}

int	setup_simulation(t_table *table, char **av)
{
	if (init_table(av, table))
		return (1);
	if (init_mutex(table))
		return (1);
	if (set_philo(table))
		return (1);
	return (0);
}
