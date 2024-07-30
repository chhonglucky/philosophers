/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhhon <chanhhon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:15:57 by chanhhon          #+#    #+#             */
/*   Updated: 2024/07/30 19:35:47 by chanhhon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define TAKE_FORKS "has taken a fork"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define EATING "is eating"
# define DIED "died"

typedef struct s_mutex
{
	int				data;
	pthread_mutex_t	lock;
}				t_mutex;

struct	s_philo;

typedef struct s_data
{
	struct s_philo	*philos;
	pthread_mutex_t	write;
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_nb;
	int				start_time;
	t_mutex			*finished;
	t_mutex			*dead;
	t_mutex			**forks;
}				t_data;

typedef struct s_philo
{
	int				p_id;
	int				eat_cnt;
	t_mutex			*r_fork;
	t_mutex			*l_fork;
	t_mutex			*last_meal;
	t_data			*data;
	pthread_t		t_id;
}					t_philo;

/* actions */

void	ph_l_forks(t_philo *philo);
void	ph_r_forks(t_philo *philo);
void	ph_eat(t_philo *philo);
void	ph_sleep(t_philo *philo);
void	ph_think(t_philo *philo);

/* free */

int		free_data(t_data *data);
void	free_mutex(t_mutex *mutex);
int		error(char *str);

/* init */

int		init(t_data *data, int argc, char **argv);
int		init_data(t_data *data, int argc, char **argv);
int		init_data_mutex(t_data *data);
int		init_philo(t_data *data);
t_mutex	*t_mutex_init(int data);

/* macro */

void	messages(char *str, t_philo *philo);
int		read_mutex(t_mutex *check_mutex);
void	write_mutex(t_mutex *check_mutex);

/* main */

void	init_thread(t_data *data);
void	*routine(void *philo_pointer);
void	monitor(t_data *data);

/* utils */

int		get_time(void);
int		ft_atoi(const char *str);
int		input_checker(char **argv);
int		ft_usleep(int time);
int		ft_strcmp(char *s1, char *s2);

#endif
