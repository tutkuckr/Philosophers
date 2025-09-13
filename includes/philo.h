/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tutku <tutku@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:40:14 by tutku             #+#    #+#             */
/*   Updated: 2025/09/11 18:42:52 by tutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define MAX_INT 2147483647

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

typedef struct s_data
{
	t_philo			*philos; //test
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	int				max_eat;
	int				stopper;
	int				c_thread; //thread checker
	int				c_stop; // stop checker
	int				c_fork; //fork mutex checker
	int				c_print; //m_print checker
	long long int	start_time;
	int				is_max_eat;
	int is_dead;
	pthread_mutex_t m_stop;	   // protect stopper
	pthread_mutex_t m_is_dead; // protects death check during routine
	pthread_mutex_t	*forks;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_monitor;
	// int ready;
}	t_data;

typedef struct s_philo
{
	t_data			*data;
	pthread_t		thread;
	pthread_mutex_t	m_meal; // protect last_meal_time, meal_count
	int				id;
	int				left_fork;	// index = id
	int				right_fork;	// index = (id + 1) % N
	int				first_fork; //first fork being picked up
	int				second_fork; // second fork being picked up
	int				meal_count;
	int				is_done_eating;
	long long int	last_meal_time;
}	t_philo;

typedef enum e_error_type
{
	SUCCESS = -2,
	ERROR,
	ERR_INV_ARGC,
	ERR_INV_INPUT,
	ERR_INV_RANGE,
	ERR_PHILO_AMOUNT,
	ERR_MALLOC,
	ERR_THREAD,
	ERR_MUTEX,
	ERR_INIT_PHILOS
}	t_error_type;

//check_error.c
t_error_type	check_error(int argc, char *argv[]);

//free.c
void			free_data(t_data *data, t_philo *philo);

// init.c
t_error_type	init_philo(t_data *data, t_philo **philo);
t_error_type	start_threads(t_data *data, t_philo *philo);
t_error_type	init_data(t_data *data, int argc, char *argv[]);
t_error_type	init_mutexes(t_data *data);

// monitor.c
void			*monitor_routine(void *arg);
void			set_stopper_val(t_data *data, int val);
int				get_stopper_val(t_data *data);

// routine_multi_philo.c
void			handle_multi_philo(t_philo *philo);

// routine.c
void *routine(void *arg);

// utils.c
long long int	get_cur_time(void);
void			skip_time(int time_input);
void			m_print(t_philo *philo, char *message);
long			ft_atol(const char *nptr);
t_error_type	error_msg(t_error_type error_no);

//test.c
void			print_data(t_data data);
#endif
