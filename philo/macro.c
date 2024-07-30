/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhhon <chanhhon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 19:25:13 by chanhhon          #+#    #+#             */
/*   Updated: 2024/07/30 19:35:28 by chanhhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	messages(char *str, t_philo *philo)
{
	int	time;

	time = get_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->write);
	if (read_mutex(philo->data->dead) == 0)
		printf("%d %d %s\n", time, philo->p_id, str);
	pthread_mutex_unlock(&philo->data->write);
}

int	read_mutex(t_mutex *check_mutex)
{
	int	return_data;

	pthread_mutex_lock(&check_mutex->lock);
	return_data = check_mutex->data;
	pthread_mutex_unlock(&check_mutex->lock);
	return (return_data);
}

void	write_mutex(t_mutex *check_mutex)
{
	pthread_mutex_lock(&check_mutex->lock);
	check_mutex->data++;
	pthread_mutex_unlock(&check_mutex->lock);
}
