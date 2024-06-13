/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkocan <hkocan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:13:49 by hkocan            #+#    #+#             */
/*   Updated: 2024/06/13 20:09:58 by hkocan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	control_dead(t_table *table)
{
	bool	dead;

	pthread_mutex_lock(&table->is_anyone_dead);
	dead = table->dead;
	pthread_mutex_unlock(&table->is_anyone_dead);
	return (dead);
}

time_t	mutex_last_eat(t_philo *philo, int i)
{
	time_t	last_eat;

	if (i == 0)
	{
		pthread_mutex_lock(&philo->eat_mutex);
		last_eat = philo->last_eat;
		return (pthread_mutex_unlock(&philo->eat_mutex), last_eat);
	}
	else
	{
		pthread_mutex_lock(&philo->eat_mutex);
		philo->last_eat = get_time();
		last_eat = philo->last_eat;
		return (pthread_mutex_unlock(&philo->eat_mutex), last_eat);
	}
}

int	eat_count(t_philo *philo, int i)
{
	int	count;

	if (i == 0)
	{
		pthread_mutex_lock(&philo->enought_eat);
		count = philo->eating_count;
		pthread_mutex_unlock(&philo->enought_eat);
		return (count);
	}
	else
	{
		pthread_mutex_lock(&philo->enought_eat);
		philo->eating_count++;
		count = philo->eating_count;
		return (pthread_mutex_unlock(&philo->enought_eat), count);
	}
}
