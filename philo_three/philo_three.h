/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   philo_three.h                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vroth-di <vroth-di@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/01 17:09:15 by vroth-di     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 18:44:24 by vroth-di    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <semaphore.h>
# include <signal.h>

typedef struct timeval	t_time;

typedef struct			s_all
{
	int					nb_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat;
	sem_t				*eat;
	sem_t				*write;
}						t_all;

typedef struct			s_philo
{
	t_all				*a;
	pthread_t			th;
	pid_t				pid;
	int					id;
	int					is_eating;
	u_int64_t			last_eat;
	int					count_eat;
	long long			time;
}						t_philo;

int						go_sleep(t_philo *philo, int ime);
int						ft_strlen(char *string);
int						time_to_sleep(t_philo *philo, int time);
int						ft_atoi(const char *str);
int						ft_write(t_philo *philo,
						long long ms, int action, int id);
void					take_forks(t_philo *philo);
void					unlock_forks(t_philo *philo);
void					eat(t_philo *philo);
void					start_think(t_philo *philo);
void					*die(t_philo *philo, int id);
void					*philosopher(void *content);
void					*monitor(void *content);
void					ft_exit(t_all *all, t_philo *p);
void					ft_putnbr_base(unsigned long long nb, char *base);
long long				show_time(void);

#endif
