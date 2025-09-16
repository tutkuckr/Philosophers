/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tutku <tutku@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 15:39:50 by tutku             #+#    #+#             */
/*   Updated: 2025/09/15 17:22:10 by tutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data	data;
	t_philo	*philo;

	philo = NULL;
	if (check_error(argc, argv) != SUCCESS)
		return (1);
	if (init_data(&data, argc, argv) != SUCCESS)
		return (1);
	if (init_philo(&data, &philo) != SUCCESS)
		return (free_data(&data, philo), 1);
	if (data.max_eat == 0)
		return (free_data(&data, philo), 1);
	if (start_threads(&data, philo) != SUCCESS)
		return (free_data(&data, philo), 1);
	free_data(&data, philo);
	return (0);
}
