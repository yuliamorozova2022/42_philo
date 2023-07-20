/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 18:05:20 by ymorozov          #+#    #+#             */
/*   Updated: 2023/07/19 16:13:16 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	alive(t_param *st, int id)
{
	struct timeval	time;

	if (st->stop == TRUE)
		return (FALSE);
	gettimeofday(&time, NULL);
	if (time_diff(st->phs[id]->last_meal, time) >= (unsigned long) st->t_die)
	{
		pthread_mutex_lock(&st->p_log);
		if (st->stop == TRUE)
			return (pthread_mutex_unlock(&st->p_log), FALSE);
		st->stop = TRUE;
		printf("%10lu %6d %3s\n", time_diff(st->phs[id]->start, time),
			st->phs[id]->id + 1, "died");
		pthread_mutex_unlock(&st->p_log);
		return (FALSE);
	}
	return (TRUE);
}

int	eat(t_param *st, int id)
{
	if (alive(st, id) == FALSE)
		return (FALSE);
	if (try_take(st, id) == FALSE)
		return (FALSE);
	ft_log(st->phs[id], EAT);
	gettimeofday(&(st->phs[id]->last_meal), NULL);
	usleep(st->t_eat * 1000);
	if (alive(st, id) == FALSE)
		return (put_forks(st, id), FALSE);
	st->phs[id]->eaten++;
	put_forks(st, id);
	return (TRUE);
}

int	try_take(t_param *st, int id)
{
	int	n;

	n = (id + 1) % st->n_ph;
	if (alive(st, id) == 0)
		return (FALSE);
	if (st->phs[id]->fork == 1 && st->phs[n]->fork == 1)
		return (FALSE);
	if (id == st->n_ph - 1 && n == 0)
		ft_swap(&n, &id);
	pthread_mutex_lock(&st->phs[id]->mx_f);
	st->phs[id]->fork = TAKEN;
	pthread_mutex_lock(&st->phs[n]->mx_f);
	st->phs[n]->fork = TAKEN;
	if (n == st->n_ph - 1 && id == 0)
		ft_swap(&n, &id);
	ft_log(st->phs[id], FORK);
	ft_log(st->phs[id], FORK);
	return (TRUE);
}

void	put_forks(t_param *st, int id)
{
	int	n;

	n = (id + 1) % st->n_ph;
	st->phs[n]->fork = FREE;
	pthread_mutex_unlock(&st->phs[n]->mx_f);
	st->phs[id]->fork = FREE;
	pthread_mutex_unlock(&st->phs[id]->mx_f);
}
