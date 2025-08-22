/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcakir-y <tcakir-y@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 01:55:40 by tutku             #+#    #+#             */
/*   Updated: 2025/08/22 17:26:17 by tcakir-y         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// check if input can be 0
// checks if input is numeric & between 1 & max_int
static t_error_type	check_input(char *argv, int argc, int curr_arg)
{
	int		j;
	long	val;

	j = 0;
	while (argv[j])
	{
		if (!(argv[j] >= '0' && argv[j] <= '9'))
			return (error_msg(ERR_INV_INPUT));
		j++;
	}
	val = ft_atol(argv);
	if (argc == 6 && curr_arg == 5)
	{
		if (val < 0 || val > MAX_INT)
			return (error_msg(ERR_INV_RANGE));
	}
	else
	{
		if (val < 1 || val > MAX_INT)
			return (error_msg(ERR_INV_RANGE));
	}
	return (SUCCESS);
}

t_error_type	check_error(int argc, char *argv[])
{
	t_error_type	status;
	int				i;

	if (!(argc == 5 || argc == 6))
		return (error_msg(ERR_INV_ARGC));
	i = 1;
	while (i < argc)
	{
		status = check_input(argv[i], argc, i);
		if (status != SUCCESS)
			return (error_msg(status));
		i++;
	}
	return (SUCCESS);
}
