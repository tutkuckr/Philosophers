/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tutku <tutku@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 23:02:10 by tutku             #+#    #+#             */
/*   Updated: 2025/08/10 20:37:00 by tutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *nptr)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = (result * 10) + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}

// later define messages with const str, and use one printf
void	error_msg(t_error_type error_no)
{
	if (error_no == ERR_INV_ARGC)
		printf("Invalid argc (expected 5 or 6)!\n"); //change into putstr -> pass with fd=2
	else if (error_no == ERR_INV_INPUT)
		printf("Invalid argv: must be numeric\n");
	else if (error_no == ERR_INV_RANGE)
		printf("Invalid range of input\n");
	else if (error_no == ERR_PHILO_AMOUNT)
		printf("Invalid philo amount\n");
	else if (error_no == ERR_MALLOC)
		printf("Malloc error\n");
	else if (error_no == ERR_THREAD)
		printf("Failed to create thread\n");
}
