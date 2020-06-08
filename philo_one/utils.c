/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroth-di <vroth-di@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 18:53:45 by vroth-di          #+#    #+#             */
/*   Updated: 2020/06/08 17:47:55 by vroth-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int			ft_strlen(char *string)
{
	int				i;

	i = 0;
	while (string[i])
		i++;
	return (i);
}

int			ft_atoi(const char *str)
{
	int				i;
	int				nb;
	int				sign;

	sign = 1;
	i = 0;
	nb = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		nb = nb * 10 + (int)str[i++] - '0';
	return (nb * sign);
}

void		ft_putnbr_base(unsigned long long nb, char *base)
{
	unsigned int	taille_base;

	taille_base = ft_strlen(base);
	if (nb >= taille_base)
		ft_putnbr_base(nb / taille_base, base);
	write(1, &base[nb % taille_base], 1);
}

int			ft_write(t_philo *philo, int action, int id)
{
	long long	ms;

	pthread_mutex_lock(&(philo->a->one_die));
	if (philo->a->someone_died == 1)
	{
		pthread_mutex_unlock(&(philo->a->one_die));
		return (0);
	}
	action == 5 ? philo->a->someone_died = 1 : 0;
	pthread_mutex_unlock(&(philo->a->one_die));
	pthread_mutex_lock(&(philo->a->write));
	ms = show_time() - philo->a->time;
	ft_putnbr_base((unsigned long long)ms, "0123456789");
	write(1, " ", 1);
	ft_putnbr_base((unsigned long long)id, "0123456789");
	action == 1 ? write(1, " has taken a fork\n", 18) : 0;
	action == 2 ? write(1, " is eating\n", 11) : 0;
	action == 3 ? write(1, " is sleeping\n", 13) : 0;
	action == 4 ? write(1, " is thinking\n", 13) : 0;
	action == 5 ? write(1, " died\n", 6) : 0;
	action == 6 ? write(1, " finish\n", 9) : 0;
	pthread_mutex_unlock(&(philo->a->write));
	return (action == 5 ? 0 : 1);
}

long long	show_time(void)
{
	t_time			time;
	long long		s;
	long long		us;

	gettimeofday(&time, NULL);
	s = time.tv_sec;
	us = time.tv_usec;
	return (s * 1000 + us / 1000);
}
