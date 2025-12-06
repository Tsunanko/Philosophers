/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijoja <ijoja@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:09:59 by ijoja             #+#    #+#             */
/*   Updated: 2025/12/06 22:55:33 by ijoja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	handle_single_philosopher(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	print_philosopher_status(philo, "has taken a fork");
	sleep_milliseconds(philo->sim, philo->sim->t_die);
	pthread_mutex_unlock(philo->left);
	if (!is_simulation_stopped(philo->sim))
	{
		print_philosopher_status(philo, "died");
		stop_simulation(philo->sim);
	}
}

static void	lock_and_announce_fork(pthread_mutex_t *fork, t_philo *philo)
{
	pthread_mutex_lock(fork);
	print_philosopher_status(philo, "has taken a fork");
}

static void	acquire_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (philo->sim->count == 1)
		return (handle_single_philosopher(philo));
	first = philo->left;
	second = philo->right;
	if (philo->id % 2 == 0)
	{
		first = philo->right;
		second = philo->left;
	}
	lock_and_announce_fork(first, philo);
	lock_and_announce_fork(second, philo);
}

static void	perform_philosopher_cycle(t_philo *philo)
{
	int	delay;
	int	total_time;

	acquire_forks(philo);
	if (philo->sim->count == 1)
		return ;
	update_philosopher_meal(philo);
	print_philosopher_status(philo, "is eating");
	sleep_milliseconds(philo->sim, philo->sim->t_eat);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
	print_philosopher_status(philo, "is sleeping");
	sleep_milliseconds(philo->sim, philo->sim->t_sleep);
	print_philosopher_status(philo, "is thinking");
	delay = 0;
	if (philo->sim->count % 2 != 0)
	{
		total_time = philo->sim->t_eat + philo->sim->t_sleep;
		delay = (philo->sim->t_die - total_time) / 2;
		if (delay < 0)
			delay = 0;
	}
	sleep_milliseconds(philo->sim, delay);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	int		initial_delay;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->sim->state);
	philo->last_meal = get_current_time_ms();
	pthread_mutex_unlock(&philo->sim->state);
	if (philo->id % 2 == 0)
	{
		initial_delay = philo->sim->t_eat / 2;
		sleep_milliseconds(philo->sim, initial_delay);
	}
	while (!is_simulation_stopped(philo->sim))
		perform_philosopher_cycle(philo);
	return (NULL);
}
