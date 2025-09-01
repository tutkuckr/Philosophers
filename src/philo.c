/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tutku <tutku@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:39:50 by tutku             #+#    #+#             */
/*   Updated: 2025/09/01 14:01:31 by tutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_error_type	init_all(int argc, char *argv[], t_data *data, t_philo **philo)
{
	t_error_type status;

	status = init_data(data, argc, argv);
	if (status != SUCCESS)
		return (status);
	status = init_mutexes(data);
	if (status != SUCCESS)
		return (status);
	status = init_philo(data, philo);
	if (status != SUCCESS)
		return (status);
	status = start_threads(data, *philo);
	if (status != SUCCESS)
		return (status);
	return (SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_data	data;
	t_philo	*philo;

	philo = NULL;
	if (check_error(argc, argv) != SUCCESS)
		return (1);
	if (init_all(argc, argv, &data, &philo) != SUCCESS)
		return (free_data(&data, philo), 1);
	// print_data(data); //test
	free_data(&data, philo);
	return (0);
}
