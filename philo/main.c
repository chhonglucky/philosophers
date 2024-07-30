/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhhon <chanhhon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:15:42 by chanhhon          #+#    #+#             */
/*   Updated: 2024/07/30 19:34:41 by chanhhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (1);
	if (input_checker(argv))
		return (1);
	if (init(&data, argc, argv))
		return (free_data(&data));
	init_thread(&data);
	free_data(&data);
	return (0);
}

void	init_thread(t_data *data)
{
	int	i;

	i = -1;
	data->start_time = get_time();
	while (++i < data->philo_num)
	{
		data->philos[i].data = data;
		data->philos[i].last_meal->data = data->start_time;
		data->philos[i].l_fork = data->forks[i];
		data->philos[i].r_fork = data->forks[(i + 1) % data->philo_num];
		if (pthread_create(&data->philos[i].t_id, NULL,
				&routine, &data->philos[i]))
			error("pthread_create");
	}
	monitor(data);
	i = -1;
	while (++i < data->philo_num)
		pthread_join(data->philos[i].t_id, NULL);
}

void	*routine(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	if (philo->p_id % 2)
		usleep(100);
	while (read_mutex(philo->data->dead) == 0)
	{
		if (philo->p_id % 2)
			ph_l_forks(philo);
		else
			ph_r_forks(philo);
		ph_eat(philo);
		ph_sleep(philo);
		ph_think(philo);
	}
	return ((void *)0);
}

void	monitor(t_data *data)
{
	int	index;

	index = 0;
	while (1)
	{
		if (get_time() - read_mutex(data->philos[index].last_meal)
			> data->time_to_die)
		{
			messages(DIED, &data->philos[index]);
			write_mutex(data->dead);
			break ;
		}
		if (data->meals_nb)
		{
			if (read_mutex(data->finished) == data->philo_num)
			{
				write_mutex(data->dead);
				break ;
			}
		}
		index++;
		if (index == data->philo_num)
			index = 0;
	}
}
