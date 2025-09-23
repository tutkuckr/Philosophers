/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakir-y <tcakir-y@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:03:31 by tcakir-y          #+#    #+#             */
/*   Updated: 2025/09/23 20:22:53 by tcakir-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	m_print(t_philo *philo, char *message)
{
	long long	time_passed;

	pthread_mutex_lock(&philo->data->m_print);
	if (get_stopper_val(philo->data) == 1 && ft_strcmp(message, "died") != 0)
	{
		pthread_mutex_unlock(&philo->data->m_print);
		return ;
	}
	time_passed = get_cur_time() - philo->data->start_time;
	if (ft_strcmp(message, "died") == 0)
	{
		if (get_stopper_val(philo->data) == 0)
			set_stopper_val(philo->data, 1);
		printf("%lld %d %s\n", time_passed, (philo->id + 1), message);
	}
	else
	{
		printf("%lld %d %s\n", time_passed, (philo->id + 1), message);
	}
	pthread_mutex_unlock(&philo->data->m_print);
}

void	skip_time(t_data *data, int time_input)
{
	long long	wait_time;

	wait_time = get_cur_time() + time_input; //changed here
	while (get_stopper_val(data) != 1 && get_cur_time() < wait_time)
		usleep(100);
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