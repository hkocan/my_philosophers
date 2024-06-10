/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkocan <hkocan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:58:19 by hatice            #+#    #+#             */
/*   Updated: 2024/06/10 16:49:56 by hkocan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	wait_sleep(t_table *table, time_t time)
{
	time_t			last_eat;
	time_t	start;

	start = get_time();
	pthread_mutex_lock(&table->philo->last_eat_mutex);
	last_eat = table->philo->last_eat;
	pthread_mutex_unlock(&table->philo->last_eat_mutex);
	while (control_dead(table) == false)
	{
		if (start - last_eat >= table->time_to_die)
		{
			check_dead(table, table->philo);
			break ;
		}
		if (get_time() - start >= time)
			break ;
		else
			usleep(50);
	}
	if (control_dead(table) == true)
		return ;
}

void	error_message(char *str)
{
	printf("%s%s%s", RED, str, RESET);
}

int	check_args(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	if (!(ac == 5 || ac == 6))
		return (1);
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (9 <= str[i] && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result * sign);
}
