/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakir-y <tcakir-y@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 23:02:10 by tutku             #+#    #+#             */
/*   Updated: 2025/08/27 14:20:42 by tcakir-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

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
t_error_type	error_msg(t_error_type error_no)
{
	const char	*e_msg[] = {
		"Invalid argc (expected 5 or 6)!\n",
		"Invalid argv: must be numeric\n",
		"Invalid range of input\n",
		"Invalid philo amount\n",
		"Malloc error\n",
		"Failed to create thread\n",
		"Error on mutex\n",
		"Error initalizing philosophers\n"
	};

	ft_putstr_fd((char *)e_msg[error_no], 2);
	//if (error_no == ERR_INV_ARGC)
	//	ft_putstr_fd("Invalid argc (expected 5 or 6)!\n", 2);
	//else if (error_no == ERR_INV_INPUT)
	//	ft_putstr_fd("Invalid argv: must be numeric\n", 2);
	//else if (error_no == ERR_INV_RANGE)
	//	ft_putstr_fd("Invalid range of input\n", 2);
	//else if (error_no == ERR_PHILO_AMOUNT)
	//	ft_putstr_fd("Invalid philo amount\n");
	//else if (error_no == ERR_MALLOC)
	//	ft_putstr_fd("Malloc error\n");
	//else if (error_no == ERR_THREAD)
	//	ft_putstr_fd("Failed to create thread\n");
	//else if (error_no == ERR_MUTEX)
	//	ft_putstr_fd("Error on mutex\n");
	return (error_no);
}
