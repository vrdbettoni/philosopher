/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroth-di <vroth-di@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:53:52 by vroth-di          #+#    #+#             */
/*   Updated: 2020/06/09 00:24:06 by vroth-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int			go_sleep(t_philo *philo, int time)
{
	ft_write(philo, 3, philo->id);
	while (time > 0)
	{
		if ((show_time() > (long long)
			(philo->a->time_to_die + philo->last_eat)))
		{
			ft_write(philo, 5, philo->id);
			kill(0, SIGINT);
			return (0);
		}
		usleep(2000);
		time -= 2;
	}
	return (1);
}

void		*wait_forks(void *content)
{
	t_philo		*philo;
	long long	time_left;

	philo = content;
	sem_wait(philo->die);
	time_left = philo->a->time_to_die + philo->last_eat;
	sem_post(philo->die);
	while (1)
	{
		sem_wait(philo->die);
		if (philo->bwforks == 0)
		{
			sem_post(philo->die);
			return (NULL);
		}
		sem_post(philo->die);
		if (show_time() > time_left)
		{
			ft_write(philo, 5, philo->id);
			kill(0, SIGINT);
			return (NULL);
		}
	}
	return (NULL);
}

void		take_forks(t_philo *philo)
{
	sem_wait(philo->die);
	philo->bwforks = 1;
	sem_post(philo->die);
	pthread_create(&(philo)->th, NULL, wait_forks, (void*)philo);
	pthread_detach(philo->th);
	sem_wait(philo->a->eat);
	ft_write(philo, 1, philo->id);
	sem_wait(philo->a->eat);
	sem_wait(philo->die);
	philo->bwforks = 0;
	sem_post(philo->die);
	ft_write(philo, 1, philo->id);
}

void		unlock_forks(t_philo *philo)
{
	sem_post(philo->a->eat);
	sem_post(philo->a->eat);
}

void		eat(t_philo *philo)
{
	ft_write(philo, 2, philo->id);
	philo->count_eat++;
	sem_wait(philo->die);
	philo->last_eat = show_time();
	sem_post(philo->die);
	usleep(philo->a->time_to_eat * 1000);
}
