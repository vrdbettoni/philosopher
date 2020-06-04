/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   threads.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vroth-di <vroth-di@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/05 04:50:31 by vroth-di     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 18:51:55 by vroth-di    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "philo_two.h"

void		ft_exit(t_all *all, t_philo *p)
{
	sem_close(all->eat);
	sem_close(all->write);
	free(all->is_eating);
	free(all->time_eat);
	free(p);
}

void		*die(t_philo *philo, int id)
{
	ft_write(philo, show_time() - philo->time, 5, id);
	return (NULL);
}

void		*philosopher(void *content)
{
	t_philo		*philo;

	philo = content;
	philo->a->is_eating[philo->id - 1] = 1;
	philo->time = show_time();
	philo->count_eat = 0;
	philo->a->time_eat[philo->id - 1] = show_time();
	philo->a->is_eating[philo->id - 1] = 0;
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
	philo->time = show_time() - 2;
	usleep(2000);
	while (1)
	{
		while (++i < philo->a->nb_philo)
		{
			if (!philo->a->is_eating[i]
				&& show_time() >= philo->a->time_eat[i] + philo->a->time_to_die)
				return (die(philo, i + 1));
			philo->a->is_eating[i] ? count++ : 0;
		}
		if (count == philo->a->nb_philo)
			return (NULL);
		count = 0;
		i = -1;
	}
}
