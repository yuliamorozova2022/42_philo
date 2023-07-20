/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymorozov <ymorozov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:11:19 by ymorozov          #+#    #+#             */
/*   Updated: 2023/07/19 16:08:29 by ymorozov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"

# define TRUE 1
# define FALSE 0

# define FREE 0
# define TAKEN 1

typedef struct s_philo
{
	unsigned int	id;
	unsigned int	fork;
	struct timeval	start;
	struct timeval	last_meal;
	pthread_t		tread;
	pthread_mutex_t	mx_f;
	unsigned int	eaten;
	unsigned int	init;
	void			*prm;
}	t_philo;

typedef struct s_param
{
	long			n_ph;
	long			t_die;
	long			t_eat;
	long			t_sleep;
	long			n_eat_opt;
	unsigned int	stop;
	pthread_mutex_t	p_log;
	t_philo			**phs;
}	t_param;

//	utils.c
int				ft_atoi_new(const char *str, long *nbr);
void			ft_log(t_philo *ph, char *msg);
unsigned long	time_diff(struct timeval start, struct timeval end);

//	main.c
void			ft_structs_init(t_param *st);
int				ft_structs_init_next(t_param *st);
int				ft_parse_param(char **argv, int argc, t_param *st);
void			free_ph_i(t_param *st, int n);

// actions.c
int				alive(t_param *st, int id);
int				try_take(t_param *st, int id);
void			put_forks(t_param *st, int id);
int				eat(t_param *st, int id);

//  routine.c
int				check_nb(t_param *st);
int				ph_sleep_think(t_param *st, int id);
void			do_odd(t_param *st, int id);
void			*act(void *a);

#endif