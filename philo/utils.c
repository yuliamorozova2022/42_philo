/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:10:27 by ymorozov          #+#    #+#             */
/*   Updated: 2023/07/18 15:23:26 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_is_space(char c)
{
	if ((c >= '\b' && c <= '\r') || c == ' ')
		return (1);
	else
		return (0);
}

static int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_atoi_new(const char *str, long *nbr)
{
	int	i;

	i = 0;
	while (ft_is_space(str[i]))
		i++;
	if ((str[i]) == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (1);
		i++;
	}
	if (ft_isdigit(str[i]) == 0)
		return (1);
	else
	{
		while (ft_isdigit(str[i]))
		{
			*nbr = *nbr * 10 + str[i] - '0';
			i++;
		}
	}
	return (0);
}

unsigned long	time_diff(struct timeval start, struct timeval end)
{
	unsigned long	s;
	unsigned long	e;

	s = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	e = (end.tv_sec * 1000) + (end.tv_usec / 1000);
	return (e - s);
}

void	ft_log(t_philo *ph, char *msg)
{
	struct timeval	time;
	t_param			*cur;

	cur = ph->prm;
	pthread_mutex_lock(&cur->p_log);
	if (cur->stop == TRUE)
	{
		pthread_mutex_unlock(&cur->p_log);
		return ;
	}
	gettimeofday(&time, NULL);
	printf("%10lu %6d %3s\n", time_diff(ph->start, time), ph->id + 1, msg);
	pthread_mutex_unlock(&cur->p_log);
}
