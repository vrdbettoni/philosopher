/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroth-di <vroth-di@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:54:00 by vroth-di          #+#    #+#             */
/*   Updated: 2020/06/08 20:33:10 by vroth-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		init_fork_table(t_all *a)
{
	sem_unlink("sfork");
	a->eat = sem_open("sfork", O_CREAT | O_EXCL, 0644, a->nb_philo);
	sem_unlink("swrite");
	a->write = sem_open("swrite", O_CREAT | O_EXCL, 0644, 1);
	return (0);
}

int		next_init_thread(t_all a, t_philo *p, int i)
{
	pthread_join(p[i].th, NULL);
	p[i].a = &a;
	p[i].id = i + 1;
	if (i < a.nb_philo)
		philosopher(&(p[i]));
	return (0);
}

int		init_thread(t_all a)
{
	t_philo			*p;
	pid_t			*pid;
	int				i;

	pid = malloc(sizeof(pid_t) * (a.nb_philo + 1));
	if (!(p = (t_philo*)malloc(sizeof(t_philo) * (a.nb_philo + 1))))
		return (1);
	i = -1;
	(&a)->time = show_time();
	while (++i < a.nb_philo + 1)
	{
		pid[i] = fork();
		if (pid[i] == 0)
			return (next_init_thread(a, p, i));
	}
	i = -1;
	while (++i < a.nb_philo)
		waitpid(pid[i], NULL, 0);
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
	init_fork_table(&a);
	init_thread(a);
}
