/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatice <hatice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:38:15 by hatice            #+#    #+#             */
/*   Updated: 2024/06/06 23:52:06 by hatice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_args(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	init_table(char **av, t_table *table, t_philo *philo)
{
	(table)->first_time = get_time();
	table->philo = philo;
	table->number_philo = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->dead = false;
	if (table->number_philo < 1 || table->time_to_die < 0
		|| table->time_to_eat < 0 || table->time_to_sleep < 0)
		return (0);
	if (av[5])
	{
		table->eating_count = ft_atoi(av[5]);
		if (table->eating_count < 1)
			return (0);
	}
	else
		table->eating_count = -1;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->number_philo);
	if (!table->forks)
		return (0);
	return (1);
}

int	init_mutex(t_table *table)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&table->print, NULL))
		return (0);
	if (pthread_mutex_init(&table->is_anyone_dead, NULL))
		return (0);
	while (i < table->number_philo)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			return (0);
		i++;
	}
	return (1);
}

int	set_table(char **av, t_table *table, t_philo *philo)
{
	if (check_args(av))
		return (0);
	init_table(av, table, philo);
	if (!init_mutex(table))
		return (0);
	return (1);
}
//table and table->forks malloc
