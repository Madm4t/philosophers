/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgering <mgering@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:14:49 by mgering           #+#    #+#             */
/*   Updated: 2024/08/27 14:56:53 by mgering          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <limits.h> //INT_MAX
# include <stdbool.h>	//fot bool type
# include <string.h>	//memset
# include <stdio.h>	//printf
# include <stdlib.h> //maloc, free
# include <unistd.h> //write, usleep
# include <sys/time.h> //gettimeofday
# include <errno.h> //err return values for pthread
# include <pthread.h> /* pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock
						*/
# define RED "\033[31m"	//Define ANSI escape sequences for colors and styles
# define GR "\033[32m"
# define YEL "\033[33m"
# define BL "\033[34m"
# define MAG "\033[35m"
# define CY "\033[36m"
# define WHITE "\033[37m"
# define RST "\033[0m"

typedef struct s_data	t_data;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}					t_fork;

typedef struct s_philo
{
	int			id;
	int			meals_eaten;
	long		meal_time;
	long		philo_time;
	bool		is_dead;
	bool		full;
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_t	thread;
	t_data		*data;
}				t_philo;

typedef struct s_data
{
	int				num_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			dinner_time_start;
	long			current_time;
	int				num_of_meals;
	t_fork			*forks;
	t_philo			*philos;
	pthread_mutex_t	print_lock;
	bool			dinner_start;
}					t_data;

typedef enum e_operation
{
	CREATE,
	DETACH,
	JOIN,
	INIT,
	DESTROY,
	LOCK,
	UNLOCK,
}	t_operation;

typedef enum e_print
{
	L_FORK,
	R_FORK,
	EAT,
	SLEEP,
	THINK,
	DEAD,
}			t_print;

//--------------philo.c---------------------
int		main(int argc, char **argv);
void	*philo_routine(void *arg);
void	*start_dinner(t_data *data);

//--------------time_utils.c----------------
long	accurate_sleep(long usec);
long	current_time_us(void);

//--------------check.c---------------------
int		input_check(char **argv);
long	ft_atol(const char *str);

//--------------init.c----------------------
int		init_data(char **argv, t_data *data);

//--------------thread_utils.c--------------
int		error_msg(int ret, const char *err_msg);
int		mutex_handler(pthread_mutex_t *mutex, t_operation operation);
int		thread_handler(t_philo *philp, t_operation operation);

//--------------message.c-------------------
int		philo_print(t_philo *philo, t_print msg);

//--------------philo_state.c---------------
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
void	philo_died(t_philo *philo);

#endif