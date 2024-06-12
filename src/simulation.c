/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkocan <hkocan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 23:20:35 by hatice            #+#    #+#             */
/*   Updated: 2024/06/12 16:35:05 by hkocan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdio.h> //
#include <unistd.h>

int	check_dead(t_table *table, t_philo *philo)
{
	time_t	last_eat;
	if (control_dead(table) == true)
		return (0);
	if (table->eating_count != -1 && eat_count(philo, 0) == table->eating_count)
		return (0);
	pthread_mutex_lock(&table->is_anyone_dead);
	last_eat=mutex_last_eat(philo, 0);
	if (get_time() - last_eat > table->time_to_die
		&& table->dead == false)
	{
		pthread_mutex_lock(&table->print);
		table->dead = true;
		printf("\033[0;31m%ld %d %s\n", get_time() - table->first_time,
			philo->id, DIE);
		pthread_mutex_unlock(&table->print);
		pthread_mutex_unlock(&table->is_anyone_dead);
		return (0);
	}
	pthread_mutex_unlock(&table->is_anyone_dead);
	return (1);
}

static void	one_philo(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&table->forks[philo->id - 1]);
	if(print_action(table, philo, TAKE_FORK) == 0)
		return ;
	pthread_mutex_unlock(&table->forks[philo->id - 1]);
	if(print_action(table, philo, DIE) == 0)
		return ;
}

bool run_similation(t_table *table)
{
	int count;
	count = 0;
	bool check;
	while (1)
	{
		printf("count: %d\n", count);
		pthread_mutex_lock(&table->run_simulation);
		if(table->run_control == table->num_philo)
		{
			pthread_mutex_unlock(&table->run_simulation);
			table->run_control = true;
			check = table->run_control;
			return (check);
		}
		count += 1;
		check = table->run_control;
		pthread_mutex_unlock(&table->run_simulation);
	}
	return (check);
}

void	*philo_life(void *arg)
{
	t_table	*table;
	t_philo	*philo;
	int		count;

	count = 0;
	philo = (t_philo *)arg;
	table = philo->table;


	if(run_similation(table) == false)//
		return (NULL);
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
		{
			pthread_mutex_unlock(&table->forks[philo->id - 1]);
			pthread_mutex_unlock(&table->forks[philo->id % table->num_philo]);
			return (NULL);
		}
		if (print_action(table, philo, SLEEP) == 0)
			return (NULL);
		if (waiting_time(table, table->time_to_sleep) == 2)
			return (NULL);
		if (print_action(table, philo, THINK) == 0)
			return (NULL);
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
}
