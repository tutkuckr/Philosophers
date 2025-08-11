/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tutku <tutku@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:39:50 by tutku             #+#    #+#             */
/*   Updated: 2025/08/10 20:37:30 by tutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	(void)arg;
	return (NULL);
}

t_error_type	init_philos(t_data *data, t_philo *philo)
{
	int i;

	philo = malloc(sizeof(t_philo) * data->num_of_philo);
	if (!philo)
		return (ERR_MALLOC);
	i = 0;
	while (i < data->num_of_philo)
	{
		philo[i].data = data;
		philo[i].philo_id = i;
		i++;
	}
	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, routine, NULL) != 0)
			return (ERR_THREAD);
		printf("Thread %d has started\n", i); //test
		i++;
	}
	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_join(philo[i].thread, NULL);
		printf("Thread %d has finished execution\n", i); //test
		i++;
	}
	printf("Both threads end.");
	return (SUCCESS);
	}

int	main(int argc, char *argv[])
{
	// pthread_t		thread;
	t_data			data;
	t_philo			philo;
	t_error_type	status;

	if (check_error_and_init(argc, argv, &data) != SUCCESS)
		return (1);
	// print_philos(data);
	status = init_philos(&data, &philo);
	if (status != SUCCESS)
		return (error_msg(status), 1);
	return (0);
}
