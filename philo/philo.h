/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijoja <ijoja@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:09:59 by ijoja             #+#    #+#             */
/*   Updated: 2025/12/06 22:55:33 by ijoja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MS_PER_SEC		1000
# define US_PER_MS		1000
# define MONITOR_INTERVAL_US	1000

struct	s_philo;

typedef struct s_sim
{
	int				count;
	long			start_ms;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				must_eat;
	int				stop;
	int				finished;
	pthread_mutex_t	print;
	pthread_mutex_t	state;
	pthread_mutex_t	*forks;
	struct s_philo	*philos;
}	t_sim;

typedef struct s_philo
{
	int				id;
	int				meals;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	t_sim			*sim;
}	t_philo;

int		parse_args(t_sim *sim, int argc, char **argv);
int		initialize_simulation(t_sim *sim);
void	cleanup_simulation(t_sim *sim);

long	get_current_time_ms(void);
long	calculate_elapsed_time_ms(long start);
void	sleep_milliseconds(t_sim *sim, int duration);

void	print_philosopher_status(t_philo *philo, const char *status);

int		is_simulation_stopped(t_sim *sim);
void	stop_simulation(t_sim *sim);
void	update_philosopher_meal(t_philo *philo);
void	*monitor_philosophers(void *arg);

void	*philosopher_routine(void *arg);
int		start_simulation(t_sim *sim);

#endif
