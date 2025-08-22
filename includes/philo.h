/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakir-y <tcakir-y@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:40:14 by tutku             #+#    #+#             */
/*   Updated: 2025/08/22 17:21:10 by tcakir-y         ###   ########.fr       */
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

typedef struct s_data
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat;
	pthread_mutex_t	*forks;
}	t_data;

typedef struct s_philo
{
	t_data			*data;
	pthread_t		thread;
	pthread_mutex_t	start;
	int				id;
	int				left_fork; // index = id
	int				right_fork; // index = (id + 1) % N
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

// init.c
t_error_type	init_philo(t_data *data, t_philo **philo);
t_error_type	init_data(t_data *data, int argc, char *argv[]);

// utils.c
void			ft_putstr_fd(char *s, int fd);
long			ft_atol(const char *nptr);
t_error_type	error_msg(t_error_type error_no);

//test.c
void			print_philos(t_philo philo);
#endif
