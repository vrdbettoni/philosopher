/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroth-di <vroth-di@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:54:17 by vroth-di          #+#    #+#             */
/*   Updated: 2020/06/08 21:01:11 by vroth-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void		ft_exit(t_all *all, t_philo *p)
{
	sem_close(all->eat);
	sem_close(all->write);
	free(p);
	kill(0, SIGINT);
}

void		*philosopher(void *content)
{
	t_philo	*philo;

	philo = content;
	philo->id_die = ft_itoa(philo->id);
	sem_unlink(philo->id_die);
	philo->die = sem_open(philo->id_die, O_CREAT | O_EXCL, 0644, 1);
	free(philo->id_die);
	philo->count_eat = 0;
	philo->last_eat = show_time();
	while (1)
	{
		take_forks(philo);
		eat(philo);
		unlock_forks(philo);
		if (philo->a->must_eat != -1 && philo->count_eat >= philo->a->must_eat)
			return (NULL);
		go_sleep(philo, philo->a->time_to_sleep);
		ft_write(philo, 4, philo->id);
	}
	return (NULL);
}
