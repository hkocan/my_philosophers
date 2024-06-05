/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+
				+:+			+:+     */
/*   By: hatice <hatice@student.42.fr>              +#+  +:+		+#+        */
/*                                                +#+#+#+#+#+	+#+           */
/*   Created: 2024/06/03 21:46:15 by hatice            #+#    #+#             */
/*   Updated: 2024/06/03 21:46:15 by hatice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

// ----- COLORS ----- //
# define RED "\033[0;31m"
# define YELLOW "\033[0;33m"
# define END "\033[0m"

typedef struct s_philo
{
	int				id;//
	int				eating_count;//
	time_t			last_eat;//
	pthread_t		thread;
	//struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int				number_philo;//
	int				eating_count;//
	time_t			time_to_die;//
	time_t			time_to_eat;//
	time_t			time_to_sleep;//
	time_t			first_time;//
	t_philo			*philo;//
	bool			dead;//
	pthread_mutex_t	*forks;//
	pthread_mutex_t	print;//
	pthread_mutex_t	is_anyone_dead;//
}	t_table;

void	error_message(char *str);
int		ft_atoi(const char *str);
time_t	get_time(void);
int		check_args(char **av);
int		start_simulation(t_table *table);
int		set_table(char **av, t_table *table, t_philo *philo);
#endif
