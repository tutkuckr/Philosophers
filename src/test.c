/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tutku <tutku@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:16:51 by tutku             #+#    #+#             */
/*   Updated: 2025/09/15 17:21:01 by tutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_data(t_data data)
{
	printf("Num of philo: %d\n", data.num_of_philo);
	printf("Time to die: %d\n", data.time_to_die);
	printf("Time to eat: %d\n", data.time_to_eat);
	printf("Time to sleep: %d\n", data.time_to_sleep);
	if (data.max_eat == -1)
		printf("Time must eat: (no limit)\n");
	else
		printf("Time must eat: %d\n", data.max_eat);
}
