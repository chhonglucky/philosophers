/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhhon <chanhhon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 19:24:42 by chanhhon          #+#    #+#             */
/*   Updated: 2024/07/30 19:27:20 by chanhhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_data(t_data *data)
{
	int	i;

	i = 0;
	free_mutex(data->finished);
	free_mutex(data->dead);
	if (data->forks)
	{
		while (i < data->philo_num)
			free_mutex(data->forks[i++]);
		free(data->forks);
	}
	i = 0;
	if (data->philos)
	{
		while (i < data->philo_num)
			free_mutex(data->philos[i++].last_meal);
		free(data->philos);
	}
	pthread_mutex_destroy(&data->write);
	return (1);
}

void	free_mutex(t_mutex *mutex)
{
	if (!mutex)
		return ;
	pthread_mutex_destroy(&mutex->lock);
	free(mutex);
}

int	error(char *str)
{
	printf("%s error\n", str);
	return (1);
}
