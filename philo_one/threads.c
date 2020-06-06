/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroth-di <vroth-di@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:53:39 by vroth-di          #+#    #+#             */
/*   Updated: 2020/06/06 16:56:52 by vroth-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		ft_exit(t_all *all, t_philo *p)
{
	pthread_mutex_destroy(all->eat);
	pthread_mutex_destroy(&(all->write));
	pthread_mutex_destroy((all->who_is_eating));
	free(all->eat);
	free(all->is_eating);
	free(all->who_is_eating);
	free(all->time_eat);
	free(p);
}

void		*die(t_philo *philo, int id)
{
	ft_write(philo, 5, id);
	return (NULL);
}

void		*philosopher(void *content)
{
	t_philo		*philo;

	philo = content;
	pthread_mutex_lock(&(philo->a->who_is_eating[philo->id - 1]));;
	philo->id == 1 ? philo->a->time = show_time() : 0;
	philo->count_eat = 0;
	philo->left_fork = philo->id;
	philo->right_fork = philo->id + 1 > philo->a->nb_philo ?
		1 : philo->id + 1;
	philo->a->time_eat[philo->id - 1] = show_time();
	pthread_mutex_unlock(&(philo->a->who_is_eating[philo->id - 1]));
	while (philo->a->someone_died == 0)
	{
		take_forks(philo);
		eat(philo);
		unlock_forks(philo);
		if (philo->a->must_eat != -1 && philo->count_eat >= philo->a->must_eat)
		{
			philo->a->is_eating[philo->id - 1] = 1;
			return (NULL);
		}
		go_sleep(philo);
		start_think(philo);
	}
	return (NULL);
}

void		*monitor(void *content)
{
	int			i;
	int			count;
	t_philo		*philo;

	i = -1;
	philo = content;
	count = philo->a->nb_philo;
	usleep(2000);
	while (1)
	{
		while (++i < philo->a->nb_philo)
		{
			pthread_mutex_lock(&(philo->a->who_is_eating[i]));
			if (!philo->a->is_eating[i]
				&& show_time() >= philo->a->time_eat[i] + philo->a->time_to_die)
				return (die(philo, i + 1));
			philo->a->is_eating[i] ? count++ : 0;
			pthread_mutex_unlock(&(philo->a->who_is_eating[i]));

		}
		if (count == philo->a->nb_philo)
			return (NULL);
		count = 0;
		i = -1;
	}
}
