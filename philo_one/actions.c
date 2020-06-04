/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroth-di <vroth-di@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:53:00 by vroth-di          #+#    #+#             */
/*   Updated: 2020/06/04 18:53:03 by vroth-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		take_forks(t_philo *philo)
{
	if (philo->a->someone_died == 1)
		return ;
	pthread_mutex_lock(&(philo->a->eat[philo->left_fork - 1]));
	ft_write(philo, show_time() - philo->time, 1, philo->id);
	pthread_mutex_lock(&(philo->a->eat[philo->right_fork - 1]));
	ft_write(philo, show_time() - philo->time, 1, philo->id);
}

void		unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->a->eat[philo->left_fork - 1]));
	pthread_mutex_unlock(&(philo->a->eat[philo->right_fork - 1]));
}

void		eat(t_philo *philo)
{
	if (philo->a->someone_died == 1)
		return ;
	philo->a->is_eating[philo->id - 1] = 1;
	ft_write(philo, show_time() - philo->time, 2, philo->id);
	philo->a->time_eat[philo->id - 1] = show_time();
	usleep(philo->a->time_to_eat * 1000);
	philo->count_eat++;
	philo->a->is_eating[philo->id - 1] = 0;
}

int			go_sleep(t_philo *philo)
{
	if (philo->a->someone_died == 1)
		return (0);
	ft_write(philo, show_time() - philo->time, 3, philo->id);
	usleep(philo->a->time_to_sleep * 1000);
	return (1);
}

void		start_think(t_philo *philo)
{
	if (philo->a->someone_died == 1)
		return ;
	ft_write(philo, show_time() - philo->time, 4, philo->id);
}
