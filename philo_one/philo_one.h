/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroth-di <vroth-di@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:53:26 by vroth-di          #+#    #+#             */
/*   Updated: 2020/06/05 19:26:02 by vroth-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <errno.h>

typedef struct timeval	t_time;

typedef struct			s_all
{
	int					nb_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat;
	int					someone_died;
	int					*is_eating;
	long long			time;
	long long			*time_eat;
	pthread_mutex_t		*eat;
	pthread_mutex_t		write;
}						t_all;

typedef struct			s_philo
{
	t_all				*a;
	pthread_t			th;
	int					id;
	int					count_eat;
	int					left_fork;
	int					right_fork;
}						t_philo;

int						go_sleep(t_philo *philo);
int						time_to_sleep(t_philo *philo, int time);
int						ft_strlen(char *string);
int						ft_write(t_philo *philo, int action, int id);
int						ft_atoi(const char *str);
void					take_forks(t_philo *philo);
void					unlock_forks(t_philo *philo);
void					eat(t_philo *philo);
void					start_think(t_philo *philo);
void					*die(t_philo *philo, int id);
void					*philosopher(void *content);
void					*monitor(void *content);
void					ft_putnbr_base(unsigned long long nb, char *base);
void					ft_exit(t_all *all, t_philo *p);
long long				show_time(void);

#endif
