/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatice <hatice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:14:26 by hatice            #+#    #+#             */
/*   Updated: 2024/06/07 01:24:28 by hatice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <unistd.h>

int	print_action(t_table *table, t_philo *philo, char *str)
{

	pthread_mutex_lock(&table->print);
	printf("%ld %d %s\n", get_time() - table->first_time, philo->id, str);
	pthread_mutex_unlock(&table->print);
	return (1);
}

int	eat_spaghetti(t_table *table, t_philo *philo)
{
	if(table->dead == true)
		return (0);
	pthread_mutex_lock(&table->forks[philo->id - 1]);
	print_action(table, philo, "has taken a fork");
	if (table->number_philo == 1)
		return (0);
	pthread_mutex_lock(&table->forks[(philo->id) % table->number_philo]);
	print_action(table, philo, "has taken a fork");
	philo->last_eat = get_time();
	print_action(table, philo, "is eating");
	philo->eating_count++;
	usleep(table->time_to_eat);
	pthread_mutex_unlock(&table->forks[philo->id - 1]);
	pthread_mutex_unlock(&table->forks[(philo->id) % table->number_philo]);
	return (1);
}
