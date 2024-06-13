/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkocan <hkocan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:14:26 by hatice            #+#    #+#             */
/*   Updated: 2024/06/13 21:17:33 by hkocan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

time_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (error_message(TIME_ERROR), 0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	waiting_time(t_table *table, time_t time)
{
	time_t	start;
	time_t	last_eat;

	start = get_time();
	while (control_dead(table) == false)
	{
		last_eat = mutex_last_eat(table->philo, 0);
		if (get_time() - last_eat >= table->time_to_die)
			if (check_dead(table, table->philo) == 0)
				return (2);
		if (get_time() - start >= time)
			return (0);
		else
			usleep(50);
	}
	return (1);
}

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

static	int	get_fork(t_table *table, t_philo *philo)
{
	if (philo->id - 1 < (philo->id % table->num_philo))
	{
		pthread_mutex_lock(&table->forks[philo->id - 1]);
		if (print_action(table, philo, TAKE_FORK) == 0)
			return (0);
		pthread_mutex_lock(&table->forks[philo->id % table->num_philo]);
		if (print_action(table, philo, TAKE_FORK) == 0)
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
	return (1);
}

int	eat_spaghetti(t_table *table, t_philo *philo)
{
	if (control_dead(table) == true)
		return (0);
	if (get_fork(table, philo) == 0)
		return (0);
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
