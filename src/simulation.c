/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatice <hatice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 23:20:35 by hatice            #+#    #+#             */
/*   Updated: 2024/06/13 09:12:02 by hatice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdio.h> //
#include <unistd.h>

static void	one_philo(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&table->forks[philo->id - 1]);
	if (print_action(table, philo, TAKE_FORK) == 0)
		return ;
	pthread_mutex_unlock(&table->forks[philo->id - 1]);
	if (print_action(table, philo, DIE) == 0)
		return ;
}

bool	run_simulation(t_table *table)
{
	table->run_count++;
	printf("run_control: %d\n", table->run_count);
	if (table->run_count != table->num_philo)
	{
		pthread_mutex_unlock(&table->run_simulation);
		return (false);
	}
	else
		return (true);
}

void	*philo_life(void *arg)
{
	t_table	*table;
	t_philo	*philo;

	philo = (t_philo *)arg;
	table = philo->table;
	run_simulation(table);
	while (table->run_control == false)
		usleep(50);
	pthread_mutex_lock(&table->run_simulation);
	if (table->num_philo == 1)
	{
		one_philo(table, philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		waiting_time(table, table->time_to_eat / 2);
	while (check_dead(table, philo))
	{
		if (eat_spaghetti(table, philo) == 0)
			return (pthread_mutex_unlock(&table->forks[philo->id - 1]),
				pthread_mutex_unlock(&table->forks[philo->id
					% table->num_philo]), NULL);
		if (print_action(table, philo, SLEEP) == 0)
			return (NULL);
		if (waiting_time(table, table->time_to_sleep) == 2)
			return (NULL);
		if (print_action(table, philo, THINK) == 0)
			return (NULL);
	}
	pthread_mutex_unlock(&table->run_simulation);
	return (NULL);
}

int	start_simulation(t_table *table)
{
	int		i;
	t_philo	*philo;

	philo = table->philo;
	i = 0;
	while (i < table->num_philo)
	{
		pthread_mutex_lock(&table->run_simulation);
		table->run_control = false;
		if (pthread_create(&philo[i].thread, NULL, &philo_life, &philo[i]))
		{
			return (pthread_mutex_unlock(&table->run_simulation), 1);
		}
		i++;
	}
	table->run_control = true;
	pthread_mutex_unlock(&table->run_simulation);
	i = 0;
	while (i < table->num_philo)
	{
		if (pthread_join(philo[i++].thread, NULL))
			return (1);
	}
	return (0);
}
