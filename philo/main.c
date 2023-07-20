/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:09:49 by ymorozov          #+#    #+#             */
/*   Updated: 2023/07/19 15:51:49 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep 
// [number_of_times_each_philosopher_must_eat]

int	main(int argc, char **argv)
{
	t_param	start;
	t_philo	*ph;
	int		i;

	if (argc < 5 || argc > 6)
		return (write(2, "Invalid number of arguments.\n", 29), 1);
	ft_structs_init(&start);
	if (ft_parse_param(argv, argc, &start) == 1)
		return (write(2, "Invalid arguments.\n", 20), 1);
	ft_structs_init_next(&start);
	i = -1;
	while (++i < start.n_ph)
	{
		ph = start.phs[i];
		ph->prm = &start;
		pthread_create(&(ph->tread), NULL, &act, ((void *) ph));
	}
	i = -1;
	while (++i < start.n_ph)
		pthread_join(start.phs[i]->tread, NULL);
	return (free_ph_i(&start, start.n_ph), 0);
}

void	ft_structs_init(t_param *st)
{
	st->n_ph = 0;
	st->t_die = 0;
	st->t_eat = 0;
	st->t_sleep = 0;
	st->n_eat_opt = 0;
	st->stop = FALSE;
	pthread_mutex_init(&st->p_log, NULL);
}

int	ft_structs_init_next(t_param *st)
{
	int	i;

	st->phs = malloc(sizeof(t_philo) * st->n_ph);
	if (st->phs == NULL)
		return (1);
	i = -1;
	while (++i < st->n_ph)
	{
		st->phs[i] = malloc(sizeof(t_philo));
		if (st->phs[i] == NULL)
			return (free_ph_i(st, i), 1);
		st->phs[i]->id = i;
		st->phs[i]->fork = FREE;
		st->phs[i]->init = TRUE;
		if (st->n_eat_opt > 0)
			st->phs[i]->eaten = 0;
		else
			st->phs[i]->eaten = -1;
		pthread_mutex_init(&st->phs[i]->mx_f, NULL);
		gettimeofday(&(st->phs[i])->start, NULL);
	}
	return (0);
}

int	ft_parse_param(char **argv, int argc, t_param *st)
{
	if (ft_atoi_new(argv[1], &st->n_ph) == 1)
		return (1);
	if (st->n_ph == 0)
		return (1);
	if (ft_atoi_new(argv[2], &st->t_die) == 1 || st->t_die < 0)
		return (1);
	if (ft_atoi_new(argv[3], &st->t_eat) == 1 || st->t_eat < 0)
		return (1);
	if (ft_atoi_new(argv[4], &st->t_sleep) == 1 || st->t_sleep < 0)
		return (1);
	if (argc == 6)
	{
		if (ft_atoi_new(argv[5], &st->n_eat_opt) == 1 || st->n_eat_opt < 0)
			return (1);
	}
	return (0);
}

void	free_ph_i(t_param *st, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&st->phs[i]->mx_f);
		free(st->phs[i]);
		i++;
	}
	pthread_mutex_destroy(&st->p_log);
	free(st->phs);
}
