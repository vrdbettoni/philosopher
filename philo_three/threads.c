/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   threads.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vroth-di <vroth-di@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/05 04:50:31 by vroth-di     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 18:45:14 by vroth-di    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "philo_three.h"

void		ft_exit(t_all *all, t_philo *p)
{
	sem_close(all->eat);
	sem_close(all->write);
	free(p);
	kill(0, SIGINT);
}

void		*die(t_philo *philo, int id)
{
	ft_write(philo, show_time() - philo->time, 5, id);
	return (NULL);
}

void		*philosopher(void *content)
{
	t_philo	*philo;

	philo = content;
	philo->time = show_time();
	philo->count_eat = 0;
	philo->is_eating = 0;
	philo->last_eat = show_time();
	while (1)
	{
		take_forks(philo);
		eat(philo);
		unlock_forks(philo);
		if (philo->a->must_eat != -1 && philo->count_eat >= philo->a->must_eat)
		{
			philo->is_eating = 1;
			return (NULL);
		}
		go_sleep(philo, philo->a->time_to_sleep);
		ft_write(philo, show_time() - philo->time, 4, philo->id);
	}
	return (NULL);
}
