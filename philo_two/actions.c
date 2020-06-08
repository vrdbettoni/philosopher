/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroth-di <vroth-di@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 14:44:51 by vroth-di          #+#    #+#             */
/*   Updated: 2020/06/08 17:23:46 by vroth-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void		take_forks(t_philo *philo)
{
	sem_wait(philo->a->sdie);
	if (philo->a->someone_died == 1)
	{
		philo->stop = 1;
		sem_post(philo->a->sdie);
		return ;
	}
	sem_post(philo->a->sdie);
	sem_wait(philo->a->eat);
	ft_write(philo, 1, philo->id);
	sem_wait(philo->a->eat);
	ft_write(philo, 1, philo->id);
}

void		unlock_forks(t_philo *philo)
{
	sem_post(philo->a->eat);
	sem_post(philo->a->eat);
}

void		eat(t_philo *philo)
{
	sem_wait(philo->a->sdie);
	if (philo->a->someone_died == 1)
	{
		philo->stop = 1;
		sem_post(philo->a->sdie);
		return ;
	}
	sem_post(philo->a->sdie);
	sem_wait(philo->a->who_is_eating);
	philo->a->is_eating[philo->id - 1] = 1;
	philo->a->time_eat[philo->id - 1] = show_time();
	sem_post(philo->a->who_is_eating);
	ft_write(philo, 2, philo->id);
	usleep(philo->a->time_to_eat * 1000);
	philo->count_eat++;
	sem_wait(philo->a->who_is_eating);
	philo->a->is_eating[philo->id - 1] = 0;
	sem_post(philo->a->who_is_eating);
}

int			go_sleep(t_philo *philo)
{
	sem_wait(philo->a->sdie);
	if (philo->a->someone_died == 1)
	{
		philo->stop = 1;
		sem_post(philo->a->sdie);
		return (0);
	}
	sem_post(philo->a->sdie);
	ft_write(philo, 3, philo->id);
	usleep(philo->a->time_to_sleep * 1000);
	return (1);
}

void		start_think(t_philo *philo)
{
	sem_wait(philo->a->sdie);
	if (philo->a->someone_died == 1)
	{
		philo->stop = 1;
		sem_post(philo->a->sdie);
		return ;
	}
	sem_post(philo->a->sdie);
	ft_write(philo, 4, philo->id);
}
