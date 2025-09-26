/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakir-y <tcakir-y@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:40:14 by tutku             #+#    #+#             */
/*   Updated: 2025/09/26 17:47:21 by tcakir-y         ###   ########.fr       */
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

typedef struct s_m_control
{
	int	print;
	int	monitor;
	int	stop;
	int	ready;
	int	fork;
	//int	thread;
	int	meal;
	int	mutexes;
}	t_m_control;

typedef struct s_data
{
	t_philo			*philos;
	pthread_t		t_monitor;
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	int				max_eat;
	int				c_thread; //thread checker
	int				c_stop; //stop checker
	int				c_monitor;
	int				ready; //checks if all threads are created to continue
	long long		start_time;
	int				is_max_eat;
	pthread_mutex_t	m_stop;
	pthread_mutex_t	*forks;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_monitor;
	pthread_mutex_t	m_ready;
	t_m_control		control;
}	t_data;

typedef struct s_philo
{
	t_data			*data;
	pthread_t		thread;
	pthread_mutex_t	m_meal; // protect last_meal_time, meal_count
	int				id;
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
void			destroy_mutexes(t_data *data);
void			free_data(t_data *data, t_philo *philo);

// init.c
t_error_type	init_philo(t_data *data, t_philo **philo);
t_error_type	init_data(t_data *data, int argc, char *argv[]);
t_error_type	init_mutexes(t_data *data);

// monitor.c
void			*monitor_routine(void *arg);

// routine.c
t_error_type	start_threads(t_data *data, t_philo *philo);

//utils_print.c
void			m_print(t_philo *philo, char *message);
void			skip_time(t_data *data, int time_input);
void			print_and_skip_time(t_philo *philo, char *message);

// utils.c
long long int	get_cur_time(void);
int				ft_strcmp(const char *str1, const char *str2);
long			ft_atol(const char *nptr);
t_error_type	error_msg(t_error_type error_no);

//utils_routine.c
void			set_stopper_val(t_data *data, int val);
int				get_stopper_val(t_data *data);
void			set_ready_val(t_data *data, int val);
int				get_ready_val(t_data *data);

// test.c
void			print_data(t_data data);
#endif
