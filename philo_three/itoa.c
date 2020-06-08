/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroth-di <vroth-di@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 20:11:36 by vroth-di          #+#    #+#             */
/*   Updated: 2020/06/09 01:23:12 by vroth-di         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static char		*ft_small(const char *s)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i])
		i++;
	str = NULL;
	if (!(str = (char*)malloc(sizeof(*str) * (i + 1))))
		return (NULL);
	str[i] = '\0';
	while (i--)
		str[i] = s[i];
	return (str);
}

static char		*ft_res(char *res, int lenght, int n, int signe)
{
	res[lenght] = '\0';
	while (lenght--)
	{
		res[lenght] = n % 10 + 48;
		n = n / 10;
	}
	if (signe != 0)
		res[0] = '-';
	return (res);
}

char			*ft_itoa(int n)
{
	int		nb;
	int		lenght;
	int		signe;
	char	*res;

	nb = n;
	signe = 1;
	lenght = 1;
	if (n == -2147483648)
		return (ft_small("-2147483648"));
	if (nb < 0)
		n = n * -1;
	else
		signe = 0;
	lenght = lenght + signe;
	while (nb /= 10)
		lenght++;
	if (!(res = (char*)malloc(sizeof(char) * (lenght + 1))))
		return (NULL);
	return (ft_res(res, lenght, n, signe));
}
