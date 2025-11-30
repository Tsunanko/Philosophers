/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijoja <ijoja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:09:59 by ijoja             #+#    #+#             */
/*   Updated: 2025/11/30 19:09:59 by ijoja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static void handle_single(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	print_status(philo, "has taken a fork");
	ms_sleep(philo->sim, philo->sim->t_die);
	pthread_mutex_unlock(philo->left);
	if (!get_stop(philo->sim))
	{
		print_status(philo, "died");
		set_stop(philo->sim);
	}
}

static void pick_fork(pthread_mutex_t *fork, t_philo *philo)
{
	pthread_mutex_lock(fork);
	print_status(philo, "has taken a fork");
}

static void take_forks(t_philo *philo)
{
	pthread_mutex_t   *first;
	pthread_mutex_t   *second;

	if (philo->sim->count == 1)
		return (handle_single(philo));
	first = philo->left;
	second = philo->right;
	if (philo->id % 2 == 0)
	{
		first = philo->right;
		second = philo->left;
	}
	pick_fork(first, philo);
	pick_fork(second, philo);
}

static void eat_sleep_think(t_philo *philo)
{
	int delay;

	take_forks(philo);
	if (philo->sim->count == 1)
		return ;
	record_meal(philo);
	print_status(philo, "is eating");
	ms_sleep(philo->sim, philo->sim->t_eat);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
	print_status(philo, "is sleeping");
	ms_sleep(philo->sim, philo->sim->t_sleep);
	print_status(philo, "is thinking");
	delay = 0;
	if (philo->sim->count % 2 != 0)
	{
		delay = (philo->sim->t_die - (philo->sim->t_eat
					+ philo->sim->t_sleep)) / 2;
		if (delay < 0)
			delay = 0;
	}
	ms_sleep(philo->sim, delay);
}

void    *philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!get_stop(philo->sim))
		eat_sleep_think(philo);
	return (NULL);
}
