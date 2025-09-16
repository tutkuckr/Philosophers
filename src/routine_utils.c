/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tutku <tutku@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 15:08:24 by tutku             #+#    #+#             */
/*   Updated: 2025/09/15 17:51:03 by tutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// // tell all threads to exit
// // (if one dies or all eats enough)
void	set_stopper_val(t_data *data, int val)
{
	pthread_mutex_lock(&data->m_stop);
	data->c_stop = val;
	pthread_mutex_unlock(&data->m_stop);
}

int	get_stopper_val(t_data *data)
{
	int	stopper;

	pthread_mutex_lock(&data->m_stop);
	stopper = data->c_stop;
	pthread_mutex_unlock(&data->m_stop);
	return (stopper);
}

//delay for thinking odd N to prevent starvation:
void	print_and_skip_time(t_philo *philo, char *message)
{
	if (ft_strcmp(message, "is sleeping") == 0)
	{
		m_print(philo, "is sleeping");
		skip_time(philo->data, philo->data->time_to_sleep);
	}
	else if (ft_strcmp(message, "is thinking") == 0)
	{
		m_print(philo, "is thinking");
		if (philo->data->num_of_philo % 2 == 1)
			skip_time(philo->data, philo->data->time_to_eat / 2);
	}
	else if (ft_strcmp(message, "is eating") == 0)
	{
		m_print(philo, "is eating");
		skip_time(philo->data, philo->data->time_to_eat);
	}
}

int	ft_strcmp(const char *str1, const char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (str1[i] - str2[i]);
}
