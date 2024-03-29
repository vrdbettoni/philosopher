/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroth-di <vroth-di@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:54:54 by vroth-di          #+#    #+#             */
/*   Updated: 2020/06/08 19:24:38 by vroth-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void		ft_exit(t_all *all, t_philo *p)
{
	sem_close(all->eat);
	sem_close(all->write);
	sem_close(all->who_is_eating);
	free(all->is_eating);
	free(all->time_eat);
	free(p);
}

void		*die(t_philo *philo, int id)
{
	sem_post(philo->a->who_is_eating);
	ft_write(philo, 5, id);
	return (NULL);
}

void		*philosopher(void *content)
{
	t_philo		*philo;

	philo = content;
	sem_wait(philo->a->who_is_eating);
	philo->id == 1 ? philo->a->time = show_time() : 0;
	philo->a->time_eat[philo->id - 1] = show_time();
	sem_post(philo->a->who_is_eating);
	while (philo->stop == 0)
	{
		take_forks(philo);
		eat(philo);
		unlock_forks(philo);
		if (philo->a->must_eat != -1 && philo->count_eat >= philo->a->must_eat)
		{
			sem_wait(philo->a->who_is_eating);
			philo->a->is_eating[philo->id - 1] = 1;
			sem_post(philo->a->who_is_eating);
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
			sem_wait(philo->a->who_is_eating);
			if (!philo->a->is_eating[i]
				&& show_time() >= philo->a->time_eat[i] + philo->a->time_to_die)
				return (die(philo, i + 1));
			philo->a->is_eating[i] ? count++ : 0;
			sem_post(philo->a->who_is_eating);
		}
		if (count == philo->a->nb_philo)
			return (NULL);
		count = 0;
		i = -1;
	}
}
