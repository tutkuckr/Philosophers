/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tutku <tutku@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 23:02:10 by tutku             #+#    #+#             */
/*   Updated: 2025/09/15 17:22:24 by tutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// TODO check leak on exit
long long int	get_cur_time(void)
{
	struct timeval	tv;
	long long int	current_time;

	if (gettimeofday(&tv, NULL) == -1)
	{
		write(2, "gettimeofday error\n", 20);
		exit(1);
	}
	current_time = (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000LL);
	return (current_time);
}

void	skip_time(t_data *data, int time_input)
{
	long long	wait_time;

	wait_time = get_cur_time();
	while (get_cur_time() - wait_time < time_input)
	{
		if (get_stopper_val(data))
			break ;
		usleep(500);
	}
}

void	m_print(t_philo *philo, char *message)
{
	long long	time_passed;

	pthread_mutex_lock(&philo->data->m_print);
	if (philo->data->c_stop == 1)
	{
		pthread_mutex_unlock(&philo->data->m_print);
		return ;
	}
	time_passed = get_cur_time() - philo->data->start_time;
	printf("%lld %d %s\n", time_passed, (philo->id + 1), message);
	if (ft_strcmp(message, "died") == 0)
		set_stopper_val(philo->data, 1);
	pthread_mutex_unlock(&philo->data->m_print);
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
	size_t		i;
	int			len;

	i = 0;
	len = 0;
	while (e_msg[error_no][len] != '\0')
		len++;
	while (e_msg[error_no][i] != '\0')
	{
		write(2, &e_msg[error_no][i], 1);
		i++;
	}
	return (error_no);
}
