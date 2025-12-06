/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijoja <ijoja@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:09:59 by ijoja             #+#    #+#             */
/*   Updated: 2025/12/06 22:55:33 by ijoja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	initialize_philosophers(t_sim *sim)
{
	int	i;

	pthread_mutex_lock(&sim->state);
	sim->start_ms = get_current_time_ms();
	i = 0;
	while (i < sim->count)
	{
		sim->philos[i].last_meal = sim->start_ms;
		i++;
	}
	pthread_mutex_unlock(&sim->state);
	return (0);
}

static int	create_philosopher_threads(t_sim *sim)
{
	int	i;
	int	j;

	i = 0;
	while (i < sim->count)
	{
		if (pthread_create(&sim->philos[i].thread, NULL,
				philosopher_routine, &sim->philos[i]) != 0)
		{
			stop_simulation(sim);
			j = 0;
			while (j < i)
			{
				pthread_join(sim->philos[j].thread, NULL);
				j++;
			}
			return (1);
		}
		i++;
	}
	return (0);
}

static void	wait_for_philosopher_threads(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->count)
	{
		pthread_join(sim->philos[i].thread, NULL);
		i++;
	}
}

int	start_simulation(t_sim *sim)
{
	pthread_t	watcher;

	if (initialize_philosophers(sim) != 0)
		return (1);
	if (create_philosopher_threads(sim) != 0)
		return (1);
	if (pthread_create(&watcher, NULL, monitor_philosophers, sim) != 0)
	{
		stop_simulation(sim);
		wait_for_philosopher_threads(sim);
		return (1);
	}
	wait_for_philosopher_threads(sim);
	pthread_join(watcher, NULL);
	return (0);
}
