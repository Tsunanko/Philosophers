/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijoja <ijoja@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:09:59 by ijoja             #+#    #+#             */
/*   Updated: 2025/12/06 22:55:33 by ijoja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_if_philosopher_starved(t_sim *sim, int idx)
{
	long	elapsed;
	long	current_time;

	pthread_mutex_lock(&sim->state);
	if (sim->stop)
	{
		pthread_mutex_unlock(&sim->state);
		return (0);
	}
	current_time = get_current_time_ms();
	elapsed = current_time - sim->philos[idx].last_meal;
	if (elapsed >= sim->t_die)
	{
		pthread_mutex_unlock(&sim->state);
		print_philosopher_status(&sim->philos[idx], "died");
		stop_simulation(sim);
		return (1);
	}
	pthread_mutex_unlock(&sim->state);
	return (0);
}

static int	check_if_all_philosophers_finished(t_sim *sim)
{
	int	done;
	int	all_finished;

	pthread_mutex_lock(&sim->state);
	all_finished = (sim->must_eat > 0 && sim->finished >= sim->count);
	done = all_finished;
	pthread_mutex_unlock(&sim->state);
	if (done)
		stop_simulation(sim);
	return (done);
}

void	*monitor_philosophers(void *arg)
{
	t_sim	*sim;
	int		i;

	sim = (t_sim *)arg;
	while (!is_simulation_stopped(sim))
	{
		i = 0;
		while (i < sim->count && !is_simulation_stopped(sim))
		{
			if (check_if_philosopher_starved(sim, i)
				|| check_if_all_philosophers_finished(sim))
				return (NULL);
			i++;
		}
		usleep(MONITOR_INTERVAL_US);
	}
	return (NULL);
}
