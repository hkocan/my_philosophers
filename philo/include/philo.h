/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hatice <hatice@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 01:38:11 by hatice            #+#    #+#             */
/*   Updated: 2024/06/12 01:38:11 by hatice           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>

// ----- ACTIONS ----- //
# define TAKE_FORK "has taken a fork"
# define EAT "\033[1;31mis eating\033[0m"
# define SLEEP "\033[0;36mis sleeping\033[0m"
# define THINK "\033[1;34mis thinking\033[0m"
# define DIE "\033[0;31mdied\033[0m"

// ----- COLORS ----- //
# define BOLD_GREEN "\033[1;32m"
# define BOLD_YELLOW "\033[1;33m"
# define RESET "\033[0m"
# define RED "\033[0;31m"

// ----- ERROR MESSAGES ----- //
# define MEM_ERROR "Error: Memory allocation failed!!!\n"
# define ARG_ERROR "Error: Wrong arguments!!!\n"
# define MUTEX_ERROR "Error: Mutex initialization failed!!!\n"
# define TABLE_ERROR "Error: Table initialization failed!!!\n"
# define PHILO_ERROR "Error: Philo initialization failed!!!\n"
# define SIMULATION_ERROR "Error: Simulation failed!!!\n"
# define TIME_ERROR "Error: Gettimeofday failed!!!\n"

typedef struct s_philo
{
	int				id;
	int				eating_count;
	time_t			last_eat;
	pthread_t		thread;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	enought_eat;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int				num_philo;
	int				eating_count;
	int				run_count;
	bool			run_control;
	bool			dead;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			first_time;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	is_anyone_dead;
	pthread_mutex_t	run_simulation;
}	t_table;

// ----- UTILS ----- //
void	error_message(char *str);
int		check_args(int ac, char **av);
long	ft_atoi(const char *str);
int		check_dead(t_table *table, t_philo *philo);

// ----- ACTION ----- //
time_t	get_time(void);
int		waiting_time(t_table *table, time_t time);
int		eat_spaghetti(t_table *table, t_philo *philo);
int		print_action(t_table *table, t_philo *philo, char *str);

// ----- SIMULATION ----- //
int		check_dead(t_table *table, t_philo *philo);
int		start_simulation(t_table *table);

// ----- FREE ----- //
void	free_table(t_table *table, int control);
void	clean(t_table *table, int i, int control);

// ----- SETUP SIMULATION ----- //
int		setup_simulation(t_table *table, char **av);

// ----- CONTROL ----- //
bool	control_dead(t_table *table);
int		eat_count(t_philo *philo, int i);
time_t	mutex_last_eat(t_philo *philo, int i);
#endif
