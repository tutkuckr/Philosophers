/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tutku <tutku@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:39:50 by tutku             #+#    #+#             */
/*   Updated: 2025/08/26 00:05:24 by tutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Even ID: take right then left
Odd ID: take left then right
*/
void	*routine(void *arg)
{
	t_philo			*philo;
	

	//if (pthread_mutex_init(&philo->start, NULL) != 0)
	//{
	//	return (error_msg(ERR_MUTEX)); //has to return void *
	//}

	philo = (t_philo *)arg;
	if (!philo) //to silence compile error
		return (NULL);
	return (NULL);
}

t_error_type	init_philos(t_data *data, t_philo *philo)
{
	int	i;

	if (init_philo(data, &philo) != SUCCESS)
		return (error_msg(ERR_INIT_PHILOS));
	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]) != 0)
			return (free(philo), error_msg(ERR_THREAD));
		printf("Thread %d has started\n", i);
		i++;
	}
	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_join(philo[i].thread, NULL);
		printf("Thread %d has finished execution\n", i);
		i++;
	}
	printf("Both threads end.\n");
	return (SUCCESS);
}

t_error_type	init_mutexes(t_data *data)
{
	int i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
	if (!data->forks)
		return (error_msg(ERR_MALLOC));
	while (i < data->num_of_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			destroy_mutex(data, (i - 1));
			return (error_msg(ERR_MUTEX));
		}
		i++;
	}
	return (SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_data			data;
	t_philo			philo;

	memset(&philo, 0, sizeof(philo));
	if (check_error(argc, argv) != SUCCESS
	|| init_data(&data, argc, argv) != SUCCESS
	|| init_mutexes(&data) != SUCCESS
	|| init_philos(&data, &philo) != SUCCESS)
		return (1);
	print_data(data);
	return (0);
}
