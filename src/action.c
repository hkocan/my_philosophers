/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkocan <hkocan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:14:26 by hatice            #+#    #+#             */
/*   Updated: 2024/06/10 16:35:50 by hkocan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

int	print_action(t_table *table, t_philo *philo, char *str)
{
	check_dead(table, philo);
	pthread_mutex_lock(&table->is_anyone_dead);
	if (table->dead == true)
		return (pthread_mutex_unlock(&table->is_anyone_dead), 0);
	pthread_mutex_lock(&table->print);
	printf("%s%ld%s", BOLD_GREEN, get_time() - table->first_time, RESET);
	printf(" %s%d%s", BOLD_YELLOW, philo->id, RESET);
	printf(" %s\n", str);
	pthread_mutex_unlock(&table->print);
	pthread_mutex_unlock(&table->is_anyone_dead);
	return (1);
}

int	eat_spaghetti(t_table *table, t_philo *philo)
{
	if (control_dead(table) == true)
		return (0);
	if (philo->id - 1 < (philo->id % table->num_philo))
	{
		pthread_mutex_lock(&table->forks[philo->id - 1]);
		print_action(table, philo, TAKE_FORK);
		pthread_mutex_lock(&table->forks[philo->id % table->num_philo]);
		print_action(table, philo, TAKE_FORK);
	}
	else
	{
		pthread_mutex_lock(&table->forks[philo->id % table->num_philo]);
		print_action(table, philo, TAKE_FORK);
		pthread_mutex_lock(&table->forks[philo->id - 1]);
		print_action(table, philo, TAKE_FORK);
	}
	print_action(table, philo, EAT);
	wait_sleep(table, table->time_to_eat);
	pthread_mutex_lock(&philo->last_eat_mutex);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->last_eat_mutex);
	philo->eating_count++;
	pthread_mutex_unlock(&table->forks[philo->id - 1]);
	pthread_mutex_unlock(&table->forks[philo->id % table->num_philo]);
	return (1);
}
