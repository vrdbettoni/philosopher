/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroth-di <vroth-di@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:53:52 by vroth-di          #+#    #+#             */
/*   Updated: 2020/06/04 18:53:53 by vroth-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int			am_i_dead(t_philo *philo)
{
	if ((show_time() > (long long)(philo->a->time_to_die + philo->last_eat)))
	{
		ft_write(philo, show_time() - philo->time, 5, philo->id);
		kill(0, SIGINT);
		return (1);
	}
	return (0);
}

int			go_sleep(t_philo *philo, int time)
{
	ft_write(philo, show_time() - philo->time, 3, philo->id);
	while (time > 0)
	{
		if (am_i_dead(philo))
			return (0);
		usleep(5000);
		time -= 5;
	}
	return (1);
}

void		take_forks(t_philo *philo)
{
	while (sem_trywait(philo->a->eat))
		am_i_dead(philo);
	ft_write(philo, show_time() - philo->time, 1, philo->id);
	while (sem_wait(philo->a->eat) == EAGAIN)
		am_i_dead(philo);
	ft_write(philo, show_time() - philo->time, 1, philo->id);
}

void		unlock_forks(t_philo *philo)
{
	sem_post(philo->a->eat);
	sem_post(philo->a->eat);
}

void		eat(t_philo *philo)
{
	philo->is_eating = 1;
	ft_write(philo, show_time() - philo->time, 2, philo->id);
	philo->count_eat++;
	philo->last_eat = show_time();
	usleep(philo->a->time_to_eat * 1000);
	philo->is_eating = 0;
}
