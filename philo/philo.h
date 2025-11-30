/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijoja <ijoja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:09:59 by ijoja             #+#    #+#             */
/*   Updated: 2025/11/30 19:09:59 by ijoja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

struct s_philo;

typedef struct s_sim
{
	int			count;
	long		start_ms;
	int			t_die;
	int			t_eat;
	int			t_sleep;
	int			must_eat;
	int			stop;
	int			finished;
	pthread_mutex_t	print;
	pthread_mutex_t	state;
	pthread_mutex_t	*forks;
	struct s_philo	*philos;
}	t_sim;

typedef struct s_philo
{
	int			id;
	int			meals;
	long		last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	t_sim			*sim;
}	t_philo;

int			parse_args(t_sim *sim, int argc, char **argv);
int			setup_sim(t_sim *sim);
void		cleanup_sim(t_sim *sim);

long			now_ms(void);
long			elapsed_ms(long start);
void			ms_sleep(t_sim *sim, int duration);

void			print_status(t_philo *philo, const char *status);

int			get_stop(t_sim *sim);
void			set_stop(t_sim *sim);
void			record_meal(t_philo *philo);
void			*monitor(void *arg);

void			*philo_routine(void *arg);
int			launch_simulation(t_sim *sim);

#endif
