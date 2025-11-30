/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijoja <ijoja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:09:59 by ijoja             #+#    #+#             */
/*   Updated: 2025/11/30 19:09:59 by ijoja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

static int	check_starved(t_sim *sim, int idx)
{
	long	elapsed;

	pthread_mutex_lock(&sim->state);
	elapsed = now_ms() - sim->philos[idx].last_meal;
	if (!sim->stop && elapsed >= sim->t_die)
	{
		pthread_mutex_unlock(&sim->state);
		print_status(&sim->philos[idx], "died");
		set_stop(sim);
		return (1);
	}
	pthread_mutex_unlock(&sim->state);
	return (0);
}

static int	check_full(t_sim *sim)
{
	int	done;

	pthread_mutex_lock(&sim->state);
	done = (sim->must_eat > 0 && sim->finished >= sim->count);
	pthread_mutex_unlock(&sim->state);
	if (done)
		set_stop(sim);
	return (done);
}

void	*monitor(void *arg)
{
	t_sim	*sim;
	int		i;

	sim = (t_sim *)arg;
	while (!get_stop(sim))
	{
		i = 0;
		while (i < sim->count && !get_stop(sim))
		{
			if (check_starved(sim, i) || check_full(sim))
				return (NULL);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
