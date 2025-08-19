/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tutku <tutku@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:16:51 by tutku             #+#    #+#             */
/*   Updated: 2025/08/19 14:17:10 by tutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philos(t_philo philo)
{
	printf("Num of philo: %d\n", philo.data->num_of_philo);
	printf("Time to die: %d\n", philo.data->time_to_die);
	printf("Time to eat: %d\n", philo.data->time_to_eat);
	printf("Time to sleep: %d\n", philo.data->time_to_sleep);
	if (philo.data->max_eat == -1)
		printf("Time must eat: (no limit)\n");
	else
		printf("Time must eat: %d\n", philo.data->max_eat);
}
