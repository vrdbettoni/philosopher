/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroth-di <vroth-di@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:54:36 by vroth-di          #+#    #+#             */
/*   Updated: 2020/06/09 01:18:59 by vroth-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		init_fork_table(t_all *a)
{
	int				i;

	i = -1;
	if (!(a->is_eating = malloc(sizeof(long long) * a->nb_philo))
			|| !(a->time_eat = malloc(sizeof(long long) * a->nb_philo)))
		return (1);
	i = -1;
	while (++i < a->nb_philo)
		a->is_eating[i] = 0;
	if (sem_unlink("sdie") == -1 || sem_unlink("is_eating") == -1
		|| sem_unlink("sfork") == -1 || sem_unlink("swrite") == -1)
		return (1);
	a->sdie = sem_open("sdie", O_CREAT | O_EXCL, 0644, 1);
	a->who_is_eating = sem_open("is_eating", O_CREAT | O_EXCL, 0644, 1);
	a->eat = sem_open("sfork", O_CREAT | O_EXCL, 0644, a->nb_philo);
	a->write = sem_open("swrite", O_CREAT | O_EXCL, 0644, 1);
	if ( a->sdie == SEM_FAILED || a->who_is_eating == SEM_FAILED
		|| a->eat == SEM_FAILED || a->write == SEM_FAILED)
		return (1);
	return (0);
}

int		init_thread(t_all a)
{
	t_philo			*p;
	int				i;

return (1);
	if (!(p = (t_philo*)malloc(sizeof(t_philo) * (a.nb_philo + 1))))
		return (1);
	i = -1;
	while (++i < a.nb_philo)
	{
		p[i].a = &a;
		p[i].id = i + 1;
		p[i].stop = 0;
		p[i].count_eat = 0;
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
	if (init_fork_table(&a) == 1 || init_thread(a) == 1)
		return (1);
	return (0);
}
