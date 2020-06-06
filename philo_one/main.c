/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroth-di <vroth-di@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 17:46:05 by vroth-di          #+#    #+#             */
/*   Updated: 2020/06/06 14:14:59 by vroth-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		init_fork_table(t_all *a)
{
	int	i;

	i = -1;
	if (!(a->eat = malloc(a->nb_philo * sizeof(pthread_mutex_t)))
			|| !(a->who_is_eating = malloc(a->nb_philo * sizeof(pthread_mutex_t))))
		return (1);
	if (!(a->is_eating = malloc(sizeof(long long) * a->nb_philo))
			|| !(a->time_eat = malloc(sizeof(long long) * a->nb_philo)))
		return (1);
	i = -1;
	while (++i < a->nb_philo)
		a->is_eating[i] = 0;
	i = -1;
	while (++i < a->nb_philo)
	{
		pthread_mutex_init(&(a->eat[i]), NULL);
		pthread_mutex_init(&(a->who_is_eating[i]), NULL);
	}
	pthread_mutex_init(&(a->write), NULL);
	return (0);
}

int		init_thread(t_all a)
{
	t_philo			*p;
	int				i;

	if (!(p = (t_philo*)malloc(sizeof(t_philo) * (a.nb_philo + 1))))
		return (1);
	i = -1;
	while (++i < a.nb_philo)
	{
		p[i].a = &a;
		p[i].id = i + 1;
		pthread_create(&(p[i].th), NULL, philosopher, &(p[i]));
		usleep(50);
	}
	p[i].a = &a;
	p[i].id = i + 1;
	pthread_create(&(p[i].th), NULL, monitor, &(p[i]));
	i = -1;
	while (++i < a.nb_philo + 1)
		pthread_join(p[i].th, NULL);
	ft_exit(&a, p);
	return (0);
}

int		main(int ac, char **av)
{
	t_all			a;

	if (ac < 5 || ac > 6)
		return (write(1, "Error: arguments.\n", 17));
	a.nb_philo = ft_atoi(av[1]);
	a.time_to_die = ft_atoi(av[2]);
	a.time_to_eat = ft_atoi(av[3]);
	a.time_to_sleep = ft_atoi(av[4]);
	a.must_eat = ac == 6 ? ft_atoi(av[5]) : -1;
	a.someone_died = 0;
	init_fork_table(&a);
	init_thread(a);
}
