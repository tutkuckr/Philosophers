/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tutku <tutku@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:39:50 by tutku             #+#    #+#             */
/*   Updated: 2025/08/11 18:18:41 by tutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	
	return (NULL);
}

t_error_type	init_philos(t_data *data, t_philo *philo)
{
	int				i;

	if (init_philo(data, &philo) != SUCCESS)
		return (ERR_INIT_PHILOS);
	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]) != 0)
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
	// pthread_mutex_destroy(&lock);
	printf("Both threads end.");
	return (SUCCESS);
	}

int	main(int argc, char *argv[])
{
	t_data			data;
	t_philo			philo;
	t_error_type	status;

	if (check_error_and_init(argc, argv, &data) != SUCCESS)
		return (1);
	status = init_philos(&data, &philo);
	if (status != SUCCESS)
		return (error_msg(status), 1);
	print_philos(philo);
	return (0);
}
