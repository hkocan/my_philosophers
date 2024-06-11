/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatice <hatice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:14:26 by hatice            #+#    #+#             */
/*   Updated: 2024/06/12 00:50:29 by hatice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <unistd.h>

int	print_action(t_table *table, t_philo *philo, char *str)
{
	if (control_dead(table) == true)
		return (0);
	pthread_mutex_lock(&table->print);
	printf("%s%ld%s", BOLD_GREEN, get_time() - table->first_time, RESET);
	printf(" %s%d%s", BOLD_YELLOW, philo->id, RESET);
	printf(" %s\n", str);
	pthread_mutex_unlock(&table->print);
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
	wait(table, table->time_to_eat);
	mutex_last_eat(philo, 1);
	eat_count(philo, 1);
	pthread_mutex_unlock(&table->forks[philo->id - 1]);
	pthread_mutex_unlock(&table->forks[philo->id % table->num_philo]);
	return (1);
}
