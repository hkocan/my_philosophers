/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkocan <hkocan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:58:19 by hatice            #+#    #+#             */
/*   Updated: 2024/06/12 14:45:56 by hkocan           ###   ########.fr       */
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

int	waiting_time(t_table *table, time_t time)
{
	time_t	start;
	time_t last_eat;

	start = get_time();
	while (control_dead(table) == false)
	{
		last_eat = mutex_last_eat(table->philo, 0);
		if (get_time() - last_eat > table->time_to_die)
			if (check_dead(table, table->philo) == 0)
				return (2);
		if (get_time() - start >= time)
			return (0);
		else
			usleep(50);
	}
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
	int	i;
	long num;

	i = 1;
	if (!(ac == 5 || ac == 6))
		return (1);
	while(av[i])
	{
		num=ft_atoi(av[i]);
		if(num > 2147483647 || num < 0)
			return(1);
		i++;
	}
	i=1;
	while (av[i])
	{
		if(number_digit(av[i]) == 0)
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
