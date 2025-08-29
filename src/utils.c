/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tutku <tutku@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 23:02:10 by tutku             #+#    #+#             */
/*   Updated: 2025/08/29 15:27:14 by tutku            ###   ########.fr       */
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
	return (error_no);
}
