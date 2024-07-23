/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhhon <chanhhon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:48:28 by chanhhon          #+#    #+#             */
/*   Updated: 2024/07/23 22:51:57 by chanhhon         ###   ########.fr       */
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
				return (error("input error", NULL));
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
		data->max_meals = ft_atoi(argv[5]);
		if (data->max_meals <= 0)
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
	if (pthread_mutex_init(&data->write, NULL))
		return (error("pthread_mutex_init", data));
	if (pthread_mutex_init(&data->lock, NULL))
		return (error("pthread_mutex_init", data));
	return (0);
}

int	case_one(t_data *data)
{
	// single-thread case
}

int	thread_init(t_data *data)
{
	// multi-thread case
	int			i;
	pthread_t	t0;

	i = -1;
	data->start_time = get_time();
	if (data->max_meals > 0)
	{
		if (pthread_create(&t0, NULL, &monitor, &data->philos[0]))
			return (error("pthread_create error", data));
	}
	while (++i < data->philo_num)
	{
		if (pthread_create(&data->tid[i], NULL, &routine, &data->philos[i]))
			return (error("pthread_create error", data));
		usleep(1);
	}
	i = -1;
	while (++i < data->philo_num)
	{
		if (pthread_join(data->tid[i], NULL))
			return (error("pthread_join error", data));
	}
	return (0);
}

void	*monitor(void *data)
{
	// check if philo->meal_cnt is over data->max_meals
}

void	*routine(void *philo)
{
	// philo	eat->sleep->think
}

void	ft_exit(t_data *data)
{
	// free all.
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].lock);
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->lock);
	clear_data(data);
}

void	clear_data(t_data *data)
{
	if (data->tid)
		free(data->tid);
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
}

int	error(char *str, t_data *data)
{
	printf("%s\n", str);
	if (data)
		ft_exit(data);
	return (1);
}

int	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (error("gettimeofday error\n", NULL));
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	messages(char *str, t_philo *philo)
{
	int	time;

	pthread_mutex_lock(&philo->data->write);
	time = get_time() - philo->data->start_time;
	if (ft_strcmp(DIED, str) == 0 && philo->data->dead == 0)
	{
		printf("%d %d %s\n", time, philo->p_id, str);
		philo->data->dead = 1;
	}
	if (!philo->data->dead)
		printf("%d %d %s\n", time, philo->p_id, str);
	pthread_mutex_unlock(&philo->data->write);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	messages(TAKE_FORKS, philo);
	pthread_mutex_lock(philo->l_fork);
	messages(TAKE_FORKS, philo);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	messages(SLEEPING, philo);
	usleep(philo->data->time_to_sleep);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->time_left = get_time() + philo->data->time_to_die;
	messages(EATING, philo);
	philo->num_meals++;
	usleep(philo->data->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->lock);
	drop_forks(philo);
}
