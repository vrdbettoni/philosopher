/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroth-di <vroth-di@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:53:00 by vroth-di          #+#    #+#             */
/*   Updated: 2020/06/08 19:01:37 by vroth-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		take_forks(t_philo *philo)
{
	pthread_mutex_lock(&(philo->a->one_die));
	if (philo->a->someone_died == 1)
	{
		pthread_mutex_unlock(&(philo->a->one_die));
		philo->stop = 1;
		return ;
	}
	pthread_mutex_unlock(&(philo->a->one_die));
	pthread_mutex_lock(&(philo->a->eat[philo->left_fork]));
	ft_write(philo, 1, philo->id);
	pthread_mutex_lock(&(philo->a->eat[philo->right_fork]));
	ft_write(philo, 1, philo->id);
}

void		unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->a->eat[philo->left_fork]));
	pthread_mutex_unlock(&(philo->a->eat[philo->right_fork]));
}

void		eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->a->one_die));
	if (philo->a->someone_died == 1)
	{
		pthread_mutex_unlock(&(philo->a->one_die));
		philo->stop = 1;
		return ;
	}
	pthread_mutex_unlock(&(philo->a->one_die));
	pthread_mutex_lock(&(philo->a->who_is_eating[philo->id - 1]));
	philo->a->is_eating[philo->id - 1] = 1;
	pthread_mutex_unlock(&(philo->a->who_is_eating[philo->id - 1]));
	ft_write(philo, 2, philo->id);
	philo->a->time_eat[philo->id - 1] = show_time();
	usleep(philo->a->time_to_eat * 1000);
	philo->count_eat++;
	pthread_mutex_lock(&(philo->a->who_is_eating[philo->id - 1]));
	philo->a->is_eating[philo->id - 1] = 0;
	pthread_mutex_unlock(&(philo->a->who_is_eating[philo->id - 1]));
}

int			go_sleep(t_philo *philo)
{
	pthread_mutex_lock(&(philo->a->one_die));
	if (philo->a->someone_died == 1)
	{
		pthread_mutex_unlock(&(philo->a->one_die));
		philo->stop = 1;
		return (1);
	}
	pthread_mutex_unlock(&(philo->a->one_die));
	ft_write(philo, 3, philo->id);
	usleep(philo->a->time_to_sleep * 1000);
	return (1);
}

void		start_think(t_philo *philo)
{
	pthread_mutex_lock(&(philo->a->one_die));
	if (philo->a->someone_died == 1)
	{
		pthread_mutex_unlock(&(philo->a->one_die));
		philo->stop = 1;
		return ;
	}
	pthread_mutex_unlock(&(philo->a->one_die));
	ft_write(philo, 4, philo->id);
}
