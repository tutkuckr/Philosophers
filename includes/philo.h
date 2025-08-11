/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tutku <tutku@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:40:14 by tutku             #+#    #+#             */
/*   Updated: 2025/08/10 21:55:18 by tutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H

# define MAX_INT 2147483647

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct	s_data
{
	int	num_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	max_eat;
}	t_data;

typedef struct s_philo
{
	t_data 		*data;
	pthread_t	thread;
	int			philo_id;
	int left_fork;
	int right_fork;

} t_philo;

typedef enum e_error_type
{
	SUCCESS,
	ERROR,
	ERR_INV_ARGC,
	ERR_INV_INPUT,
	ERR_INV_RANGE,
	ERR_PHILO_AMOUNT,
	ERR_MALLOC,
	ERR_THREAD
} t_error_type;

//init.c
t_error_type	check_error_and_init(int argc, char *argv[], t_data *data);

// utils.c
long			ft_atol(const char *nptr);
void			error_msg(t_error_type error_no);

//test.c
void			print_philos(t_data data);
#endif
