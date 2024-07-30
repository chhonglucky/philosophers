/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhhon <chanhhon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 19:22:59 by chanhhon          #+#    #+#             */
/*   Updated: 2024/07/30 19:27:51 by chanhhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init(t_data *data, int argc, char **argv)
{
	if (init_data(data, argc, argv))
		return (1);
	if (init_data_mutex(data))
		return (1);
	if (init_philo(data))
		return (1);
	return (0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->philo_num = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->meals_nb = ft_atoi(argv[5]);
	else
		data->meals_nb = -1;
	data->philos = NULL;
	data->finished = NULL;
	data->dead = NULL;
	data->forks = NULL;
	if (data->philo_num <= 0 || data->philo_num > 200 || data->time_to_die < 0
		|| data->time_to_eat < 0 || data->time_to_sleep < 0
		|| data->meals_nb == 0)
		return (error("parsing"));
	return (0);
}

int	init_data_mutex(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->write, NULL))
		return (1);
	data->finished = t_mutex_init(0);
	data->dead = t_mutex_init(0);
	data->forks = (t_mutex **)malloc(sizeof(t_mutex *) * data->philo_num);
	if (!data->finished || !data->dead || !data->forks)
		return (error("malloc"));
	i = 0;
	while (i < data->philo_num)
	{
		data->forks[i] = t_mutex_init(0);
		i++;
	}
	while (i--)
		if (data->forks[i] == 0)
			return (error("t_mutex_init"));
	return (0);
}

int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->philo_num);
	if (data->philos == NULL)
		return (error("malloc"));
	while (i < data->philo_num)
	{
		data->philos[i].p_id = i + 1;
		data->philos[i].eat_cnt = 0;
		data->philos[i].last_meal = t_mutex_init(0);
		if (!data->philos[i].last_meal)
			return (error("init_philo"));
		i++;
	}
	return (0);
}

t_mutex	*t_mutex_init(int data)
{
	t_mutex	*return_struct;

	return_struct = (t_mutex *)malloc(sizeof(t_mutex));
	if (return_struct == NULL)
	{
		error("malloc");
		return (0);
	}
	if (pthread_mutex_init(&return_struct->lock, NULL))
	{
		free(return_struct);
		return (0);
	}
	return_struct->data = data;
	return (return_struct);
}
