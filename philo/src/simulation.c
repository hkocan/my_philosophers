/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkocan <hkocan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 23:20:35 by hatice            #+#    #+#             */
/*   Updated: 2024/06/13 22:27:31 by hkocan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	one_philo(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&table->forks[philo->id - 1]);
	if (print_action(table, philo, TAKE_FORK) == 0)
		return ;
	pthread_mutex_unlock(&table->forks[philo->id - 1]);
	if (print_action(table, philo, DIE) == 0)
		return ;
}

static	void	*numerous_philo(t_table *table, t_philo *philo)
{
	int	right_fork;
	int	left_fork;

	right_fork = philo->id - 1;
	left_fork = philo->id % table->num_philo;
	if (philo->id % 2 == 0)
		waiting_time(table, table->time_to_eat / 2);
	while (check_dead(table, philo))
	{
		if (eat_spaghetti(table, philo) == 0)
			return (pthread_mutex_unlock(&table->forks[right_fork]),
				pthread_mutex_unlock(&table->forks[left_fork]), NULL);
		if (print_action(table, philo, SLEEP) == 0)
			return (NULL);
		if (waiting_time(table, table->time_to_sleep) == 2)
			return (NULL);
		if (print_action(table, philo, THINK) == 0)
			return (NULL);
	}
	return (NULL);
}

static	void	*philo_life(void *arg)
{
	t_table	*table;
	t_philo	*philo;

	philo = (t_philo *)arg;
	table = philo->table;
	pthread_mutex_lock(&table->run_simulation);
	while (table->run_control == false)
	{
		pthread_mutex_unlock(&table->run_simulation);
		return (NULL);
	}
	pthread_mutex_unlock(&table->run_simulation);
	mutex_last_eat(philo, 1);
	if (table->num_philo == 1)
	{
		one_philo(table, philo);
		return (NULL);
	}
	if (numerous_philo(table, philo) == NULL)
		return (NULL);
	return (NULL);
}

int	start_simulation(t_table *table)
{
	int		i;
	t_philo	*philo;

	philo = table->philo;
	i = 0;
	pthread_mutex_lock(&table->run_simulation);
	while (i < table->num_philo)
	{
		table->run_control = false;
		if (pthread_create(&philo[i].thread, NULL, &philo_life, &philo[i]))
			return (pthread_mutex_unlock(&table->run_simulation), 1);
		table->run_count ++;
		i++;
	}
	table->first_time = get_time();
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
