/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroth-di <vroth-di@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:53:52 by vroth-di          #+#    #+#             */
/*   Updated: 2020/06/06 16:12:06 by vroth-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int			go_sleep(t_philo *philo, int time)
{
	ft_write(philo, 3, philo->id);
	while (time > 0)
	{
		if ((show_time() > (long long)(philo->a->time_to_die + philo->last_eat)))
		{
			ft_write(philo, 5, philo->id);
			kill(0, SIGINT);
			return (0);
		}
		usleep(5000);
		time -= 5;
	}
	return (1);
}

void		*wait_forks(void *content)
{
	t_philo		*philo;
	long long	time_left;

	philo = content;
	time_left = philo->a->time_to_die + philo->last_eat;
	while (1)
	{
		if (philo->bwforks == 0)
			return (NULL);
		if (show_time() > time_left)
		{
			ft_write(philo, 5, philo->id);
			kill(0, SIGINT);
			return (NULL);
		}
	}
	return(NULL);
}

void		take_forks(t_philo *philo)
{
	philo->bwforks = 1;
	pthread_create(&(philo)->th, NULL, wait_forks, (void*)philo);
	pthread_detach(philo->th);
	sem_wait(philo->a->eat);
	ft_write(philo, 1, philo->id);
	sem_wait(philo->a->eat);
	philo->bwforks = 0;
	ft_write(philo, 1, philo->id);
}

void		unlock_forks(t_philo *philo)
{
	sem_post(philo->a->eat);
	sem_post(philo->a->eat);
}

void		eat(t_philo *philo)
{
	philo->is_eating = 1;
	ft_write(philo, 2, philo->id);
	philo->count_eat++;
	philo->last_eat = show_time();
	usleep(philo->a->time_to_eat * 1000);
	philo->is_eating = 0;
}
