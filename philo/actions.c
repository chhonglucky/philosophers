/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhhon <chanhhon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 19:22:01 by chanhhon          #+#    #+#             */
/*   Updated: 2024/07/30 19:27:11 by chanhhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_l_forks(t_philo *philo)
{
	while (read_mutex(philo->data->dead) == 0)
	{
		pthread_mutex_lock(&philo->l_fork->lock);
		if (philo->l_fork->data == 0)
		{
			philo->l_fork->data = philo->p_id;
			messages(TAKE_FORKS, philo);
			pthread_mutex_unlock(&philo->l_fork->lock);
			break ;
		}
		pthread_mutex_unlock(&philo->l_fork->lock);
	}
	while (read_mutex(philo->data->dead) == 0)
	{
		pthread_mutex_lock(&philo->r_fork->lock);
		if (philo->r_fork->data == 0)
		{
			philo->r_fork->data = philo->p_id;
			messages(TAKE_FORKS, philo);
			pthread_mutex_unlock(&philo->r_fork->lock);
			break ;
		}
		pthread_mutex_unlock(&philo->r_fork->lock);
	}
}

void	ph_r_forks(t_philo *philo)
{
	while (read_mutex(philo->data->dead) == 0)
	{
		pthread_mutex_lock(&philo->r_fork->lock);
		if (philo->r_fork->data == 0)
		{
			philo->r_fork->data = philo->p_id;
			messages(TAKE_FORKS, philo);
			pthread_mutex_unlock(&philo->r_fork->lock);
			break ;
		}
		pthread_mutex_unlock(&philo->r_fork->lock);
	}
	while (read_mutex(philo->data->dead) == 0)
	{
		pthread_mutex_lock(&philo->l_fork->lock);
		if (philo->l_fork->data == 0)
		{
			philo->l_fork->data = philo->p_id;
			messages(TAKE_FORKS, philo);
			pthread_mutex_unlock(&philo->l_fork->lock);
			break ;
		}
		pthread_mutex_unlock(&philo->l_fork->lock);
	}
}

void	ph_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal->lock);
	philo->last_meal->data = get_time();
	pthread_mutex_unlock(&philo->last_meal->lock);
	messages(EATING, philo);
	philo->eat_cnt++;
	if (philo->eat_cnt == philo->data->meals_nb)
		write_mutex(philo->data->finished);
	ft_usleep(philo->data->time_to_eat);
}

void	ph_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->l_fork->lock);
	philo->l_fork->data = 0;
	pthread_mutex_unlock(&philo->l_fork->lock);
	pthread_mutex_lock(&philo->r_fork->lock);
	philo->r_fork->data = 0;
	pthread_mutex_unlock(&philo->r_fork->lock);
	messages(SLEEPING, philo);
	ft_usleep(philo->data->time_to_sleep);
}

void	ph_think(t_philo *philo)
{
	messages(THINKING, philo);
}
