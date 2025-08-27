/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakir-y <tcakir-y@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:39:50 by tutku             #+#    #+#             */
/*   Updated: 2025/08/27 14:36:45 by tcakir-y         ###   ########.fr       */
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

	philo = (t_philo *)arg;
	if (!philo) //to silence compile error
		return (NULL);
	return (NULL);
}

t_error_type	init_philos(t_data *data, t_philo **philo)
{
	int	i;

	if (init_philo(data, philo) != SUCCESS)
		return (error_msg(ERR_INIT_PHILOS));
	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_create((&(*philo)[i].thread), NULL, routine, &((*philo)[i])) != 0)
			return (free(*philo), *philo = NULL, error_msg(ERR_THREAD));
		printf("thread %d is created\n", i + 1);
		i++;
	}
	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_join((*philo)[i].thread, NULL);
		i++;
	}
	printf("Both threads end.\n");
	return (SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	t_philo	*philo;

	philo = NULL;
	if (check_error(argc, argv) != SUCCESS
	|| (init_data(&data, argc, argv) != SUCCESS)
	|| (init_mutexes(&data) != SUCCESS)
	|| (init_philos(&data, &philo) != SUCCESS))
		return (free_data(&data, philo), 1);
	print_data(data); //test
	free_data(&data, philo);
	return (0);
}
