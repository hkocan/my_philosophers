/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkocan <hkocan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:58:19 by hatice            #+#    #+#             */
/*   Updated: 2024/06/13 21:57:28 by hkocan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	check_dead(t_table *table, t_philo *philo)
{
	time_t	last_eat;

	if (control_dead(table) == true)
		return (0);
	if (table->eating_count != -1 && eat_count(philo, 0) == table->eating_count)
		return (0);
	pthread_mutex_lock(&table->is_anyone_dead);
	last_eat = mutex_last_eat(philo, 0);
	if (get_time() - last_eat > table->time_to_die && table->dead == false)
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

void	error_message(char *str)
{
	printf("%s%s%s", RED, str, RESET);
}

static int	number_digit(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	i = 0;
	if ((str[0] == '-' || str[0] == '+') && !str[1])
		return (0);
	if (str[0] == '-' || str[0] == '+')
		str++;
	while (*str == '0')
		str++;
	while (str[i])
		i++;
	if (i > 11)
		return (0);
	return (1);
}

int	check_args(int ac, char **av)
{
	int		i;
	long	num;

	i = 1;
	if (!(ac == 5 || ac == 6))
		return (1);
	while (av[i])
	{
		num = ft_atoi(av[i]);
		if (num > 2147483647 || num <= 0)
			return (1);
		i++;
	}
	i = 1;
	while (av[i])
	{
		if (number_digit(av[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

long	ft_atoi(const char *str)
{
	int		sign;
	long	result;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == 32 || (9 <= str[i] && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign *= -1;
	}
	while (str[i])
		result = result * 10 + (str[i++] - '0');
	return ((sign * result));
}
