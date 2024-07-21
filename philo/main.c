/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhhon <chanhhon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:48:28 by chanhhon          #+#    #+#             */
/*   Updated: 2024/07/21 13:50:17 by chanhhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (1);
	if (ft_input_checker(argv))
		return (1);
	if (ft_init(&data, argc, argv))
		return (1);
	if (data.philo_num == 1)
		return (case_one(&data));
	if (thread_init(&data))
		return (1);
	ft_exit(&data);
	return (0);
}

int	ft_input_checker(char **argv)
{
	// parsing input check
	// if fail
	// 	return 1;
	// else
	// 	return 0;

	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_init(t_data *data, int argc, char **argv)
{
	// input argv into &data
	// if fail
	// 	return 1;
	// else
	// 	return 0;
	data->philo_num = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->start_time = ft_get_time();
	if (data->philo_num <= 0 || data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0)
	{
		return (5);
	}
	if (argc == 6)
	{
		data->cnt_ate = ft_atoi(argv[5]);
		if (data->cnt_ate <= 0)
			return (6);
	}
	if (ft_init_mutex(data))
		return (1);
	return (0);
}

int	ft_init_mutex(t_data *data)
{
	// input mutex into &s_data
	// if fail
	// 	return 1;
	// else
	// 	return 0;
}

int	case_one(t_data *data)
{1
	// single-thread case
}

int	thread_init(t_data *data)
{
	// multi-thread case
}

void	ft_exit(t_data *data)
{
	// free all.
}
