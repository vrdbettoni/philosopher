/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   philo_two.h                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vroth-di <vroth-di@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/01 17:09:15 by vroth-di     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 18:48:27 by vroth-di    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <errno.h>
# include <semaphore.h>

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
	sem_t				*eat;
	sem_t				*write;
	long long			*time_eat;
}						t_all;

typedef struct			s_philo
{
	t_all				*a;
	pthread_t			th;
	int					id;
	int					count_eat;
	int					left_fork;
	int					right_fork;
	long long			time;
}						t_philo;

int						time_to_sleep(t_philo *philo, int time);
int						ft_atoi(const char *str);
int						ft_strlen(char *string);
int						go_sleep(t_philo *philo);
void					take_forks(t_philo *philo);
void					unlock_forks(t_philo *philo);
void					eat(t_philo *philo);
void					start_think(t_philo *philo);
void					*die(t_philo *philo, int id);
void					ft_exit(t_all *all, t_philo *p);
void					*philosopher(void *content);
void					*monitor(void *content);
void					ft_putnbr_base(unsigned long long nb, char *base);
int						ft_write(t_philo *philo,
						long long ms, int action, int id);
long long				show_time(void);

#endif
