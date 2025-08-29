/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tutku <tutku@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:18:20 by tutku             #+#    #+#             */
/*   Updated: 2025/08/29 20:24:59 by tutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_error_type	start_threads(t_data *data, t_philo *philo)
{
	int	i;
	int j;

	data->t_started = 0;
	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_create((&philo[i].thread), NULL, routine, (&philo[i])) != 0)
		{
			j = -1;
			while (++j < data->t_started)
				pthread_join(philo[i].thread, NULL);
			data->t_started = 0;
			return (error_msg(ERR_THREAD));
		}
		printf("thread %d is created\n", i + 1); // test
		i++;
		data->t_started++;
	}
	return (SUCCESS);
}

t_error_type	init_philo(t_data *data, t_philo **philo)
{
	int	i;

	*philo = malloc(sizeof(t_philo) * data->num_of_philo);
	if (!*philo)
		return (error_msg(ERR_MALLOC));
	i = 0;
	while (i < data->num_of_philo)
	{
		(*philo)[i].data = data;
		(*philo)[i].id = i;
		(*philo)[i].left_fork = i;
		(*philo)[i].right_fork = (i + 1) % data->num_of_philo;
		i++;
	}
	return (SUCCESS);
}

t_error_type	init_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->controller, NULL) != 0)
		return (error_msg(ERR_MUTEX));
	data->c_inited = 1;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
	if (!data->forks)
		return (error_msg(ERR_MALLOC));
	data->f_started = 0;
	while (data->f_started < data->num_of_philo)
	{
		if (pthread_mutex_init(&data->forks[data->f_started], NULL) != 0)
			return (error_msg(ERR_MUTEX));
		data->f_started++;
	}
	return (SUCCESS);
}

t_error_type	init_data(t_data *data, int argc, char *argv[])
{
	memset(data, 0, sizeof(*data));
	data->num_of_philo = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	data->start_time = get_cur_time();
	if (data->num_of_philo <= 0 || data->num_of_philo > 200)
		return (error_msg(ERR_PHILO_AMOUNT));
	if (argc == 6)
		data->max_eat = ft_atol(argv[5]);
	else
		data->max_eat = -1;
	return (SUCCESS);
}
