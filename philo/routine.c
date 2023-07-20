/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 11:26:46 by ymorozov          #+#    #+#             */
/*   Updated: 2023/07/19 16:13:19 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*act(void *a)
{
	t_philo	*ph;
	t_param	*base;

	ph = (t_philo *) a;
	base = ph->prm;
	gettimeofday(&ph->last_meal, NULL);
	if (base->n_ph == 1)
		return (ft_log(ph, FORK), usleep(base->t_die * 1000),
			ft_log(ph, "died"), NULL);
	while (base->stop == FALSE)
	{
		do_odd(base, ph->id);
		if (alive(base, ph->id) == FALSE)
			return (FALSE);
		if (eat(base, ph->id) == FALSE)
			continue ;
		if (base->n_eat_opt > 0 && check_nb(base) == TRUE)
			return (NULL);
		if (base->stop == TRUE)
			return (NULL);
		ph_sleep_think(base, ph->id);
	}
	return (NULL);
}

int	check_nb(t_param *st)
{
	int	i;
	int	res;

	i = -1;
	res = 0;
	pthread_mutex_lock(&st->p_log);
	while (++i < st->n_ph)
	{
		if (st->phs[i]->eaten >= st->n_eat_opt)
			res++;
		else
			break ;
	}
	if (res != st->n_ph)
		return (pthread_mutex_unlock(&st->p_log), FALSE);
	return (pthread_mutex_unlock(&st->p_log), TRUE);
}

int	ph_sleep_think(t_param *st, int id)
{
	if (st->stop == TRUE)
		return (FALSE);
	ft_log(st->phs[id], SLEEP);
	usleep(st->t_sleep * 1000);
	if (st->stop == TRUE)
		return (FALSE);
	ft_log(st->phs[id], THINK);
	return (TRUE);
}

void	do_odd(t_param *st, int id)
{
	if (id % 2 == 0 && st->phs[id]->init)
	{
		st->phs[id]->init = FALSE;
		ph_sleep_think(st, id);
	}
}
