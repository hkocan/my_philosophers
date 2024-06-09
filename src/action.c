/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatice <hatice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:14:26 by hatice            #+#    #+#             */
/*   Updated: 2024/06/09 01:13:23 by hatice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <unistd.h>
#include <stdio.h>

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
	if (table->dead == true)
		return (0);
	pthread_mutex_lock(&table->forks[philo->id - 1]);
	print_action(table, philo, TAKE_FORK);
	if (table->number_philo == 1)
	{
		pthread_mutex_unlock(&table->forks[philo->id - 1]);
		print_action(table, philo, EAT);//
		return (1);//
	}
	pthread_mutex_lock(&table->forks[(philo->id) % table->number_philo]);
	print_action(table, philo, TAKE_FORK);
	print_action(table, philo, EAT);
	wait_sleep(table, table->time_to_eat);
	pthread_mutex_unlock(&table->forks[philo->id - 1]);
	pthread_mutex_unlock(&table->forks[(philo->id) % table->number_philo]);
	philo->eating_count++;
	philo->last_eat = get_time();
	return (1);
}
