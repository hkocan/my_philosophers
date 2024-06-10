/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkocan <hkocan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 23:20:35 by hatice            #+#    #+#             */
/*   Updated: 2024/06/10 16:35:12 by hkocan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

int	check_dead(t_table *table, t_philo *philo)
{

	if (control_dead(table)==true)
		return (0);
	if (table->eating_count != -1 && philo->eating_count >= table->eating_count)
		return (0);
	if (get_time() - philo->last_eat > table->time_to_die)
	{
		pthread_mutex_lock(&table->is_anyone_dead);
		table->dead = true;
		printf("\033[0;31m%ld %d %s\n", get_time() - table->first_time,
			philo->id, DIE);
		pthread_mutex_unlock(&table->is_anyone_dead);
		return (0);
	}
	return (1);
}

void	*philo_life(void *arg)
{
	t_table	*table;
	t_philo	*philo;

	philo = (t_philo *)arg;
	table = philo->table;
	if (philo->id % 2 == 0)
		wait_sleep(table, table->time_to_eat / 2);
	while (check_dead(table, philo))
	{
		if (control_dead(table) == true)
			break ;
		if (table->num_philo == 1)
		{
			pthread_mutex_lock(&table->forks[philo->id - 1]);
			print_action(table, philo, TAKE_FORK);
			pthread_mutex_unlock(&table->forks[philo->id - 1]);
			print_action(table, philo, DIE);
			break ;
		}
		eat_spaghetti(table, philo);
		print_action(table, philo, SLEEP);
		wait_sleep(table, table->time_to_sleep);
		print_action(table, philo, THINK);
	}
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
		if (pthread_create(&philo[i].thread, NULL, &philo_life, &philo[i]))
			return (1);
		i++;
	}
	i = 0;
	while (i < table->num_philo)
	{
		if (pthread_join(philo[i].thread, NULL))
			return (1);
		i++;
	}
	return (0);
	free_table(table);
}
