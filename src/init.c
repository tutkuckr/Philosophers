/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tutku <tutku@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:18:20 by tutku             #+#    #+#             */
/*   Updated: 2025/08/10 16:24:33 by tutku            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// check if input can be 0
// checks if input is numeric & between 1 & max_int
static t_error_type check_input(char *argv, int argc, int curr_arg)
{
	int j;
	long val;

	j = 0;
	while (argv[j])
	{
		if (!(argv[j] >= '0' && argv[j] <= '9'))
			return (ERR_INV_INPUT);
		j++;
	}
	val = ft_atol(argv);
	if (argc == 6 && curr_arg == 5)
	{
		if (val < 0 || val > MAX_INT)
			return (ERR_INV_RANGE);
	}
	else
	{
		if (val < 1 || val > MAX_INT)
			return (ERR_INV_RANGE);
	}
	return (SUCCESS);
}

static t_error_type	check_error(int argc, char *argv[])
{
	t_error_type	status;
	int				i;

	if (!(argc == 5 || argc == 6))
		return (ERR_INV_ARGC);
	i = 1;
	while (i < argc)
	{
		status = check_input(argv[i], argc, i);
		if (status != SUCCESS)
			return (status);
		i++;
	}
	return (SUCCESS);
}

static t_error_type	init_data(t_data *data, int argc, char *argv[])
{
	data->num_of_philo = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (data->num_of_philo > 200)
		return (ERR_PHILO_AMOUNT);
	if (argc == 6)
		data->max_eat = ft_atol(argv[5]);
	else
		data->max_eat = -1;
	return (SUCCESS);
}

t_error_type	check_error_and_init(int argc, char *argv[], t_data *data)
{
	t_error_type	status;

	status = check_error(argc, argv);
	if (status != SUCCESS)
		return (error_msg(status), status);
	status = init_data(data, argc, argv);
	if (status != SUCCESS)
		return (error_msg(status), status);
	return (SUCCESS);
}

