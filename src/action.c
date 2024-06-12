/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkocan <hkocan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:14:26 by hatice            #+#    #+#             */
/*   Updated: 2024/06/12 13:02:13 by hkocan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

int	print_action(t_table *table, t_philo *philo, char *str)
{
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
		if(print_action(table, philo, TAKE_FORK) == 0)
			return (0);
		pthread_mutex_lock(&table->forks[philo->id % table->num_philo]);
		if(print_action(table, philo, TAKE_FORK) == 0)
			return (0);
	}
	else
	{
		pthread_mutex_lock(&table->forks[philo->id % table->num_philo]);
		if (print_action(table, philo, TAKE_FORK) == 0)
			return (0);
		pthread_mutex_lock(&table->forks[philo->id - 1]);
		if (print_action(table, philo, TAKE_FORK) == 0)
			return (0);
	}
	if (print_action(table, philo, EAT) == 0)
		return (0);
	if (waiting_time(table, table->time_to_eat) != 0)
		return (0);
	mutex_last_eat(philo, 1);
	eat_count(philo, 1);
	pthread_mutex_unlock(&table->forks[philo->id - 1]);
	pthread_mutex_unlock(&table->forks[philo->id % table->num_philo]);
	return (1);
}
