/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+  	      +:+     */
/*   By: hatice <hatice@student.42.fr>              +#+  +:+	   +#+        */
/*                                                +#+#+#+#+#+	+#+           */
/*   Created: 2024/06/03 21:46:15 by hatice            #+#    #+#             */
/*   Updated: 2024/06/03 21:46:15 by hatice           ###   ########.fr       */
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

/*# define YELLOW "\033[0;33m"
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define BOLD_RED "\033[1;31m"
# define BOLD_BLUE "\033[1;34m"
# define BOLD_MAGENTA "\033[1;35m"
# define BOLD_CYAN "\033[1;36m"*/

// ----- ERROR MESSAGES ----- //
# define MEM_ERROR "Error: Memory allocation failed!!!\n"
# define ARG_ERROR "Error: Wrong arguments!!!\n"
# define MUTEX_ERROR "Error: Mutex initialization failed!!!\n"
# define TABLE_ERROR "Error: Table initialization failed!!!\n"
# define PHILO_ERROR "Error: Philo initialization failed!!!\n"
# define SIMULATION_ERROR "Error: Simulation failed!!!\n"

typedef struct s_philo
{
	int				id;
	int				eating_count;
	time_t			last_eat;
	pthread_t		thread;
	pthread_mutex_t last_eat_mutex;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int				num_philo;
	int				eating_count;
	bool			dead;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			first_time;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	is_anyone_dead;
}	t_table;

// ----- UTILS ----- //
time_t	get_time(void);
void	wait_sleep(t_table *table, time_t time);
void	error_message(char *str);
int		check_args(int ac, char **av);
int		ft_atoi(const char *str);

// ----- ACTION ----- //
int		eat_spaghetti(t_table *table, t_philo *philo);
int		print_action(t_table *table, t_philo *philo, char *str);

// ----- SIMULATION ----- //
int		check_dead(t_table *table, t_philo *philo);
int		start_simulation(t_table *table);
void	*philo_life(void *arg);

// ----- FREE ----- //
void	free_table(t_table *table);

// ----- SETUP SIMULATION ----- //
int		setup_simulation(t_table *table, char **av);

// ----- CONTROL ----- //
bool		control_dead(t_table *table);
#endif
