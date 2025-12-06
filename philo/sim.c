/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijoja <ijoja@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:09:59 by ijoja             #+#    #+#             */
/*   Updated: 2025/12/06 22:55:33 by ijoja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	destroy_fork_mutexes(t_sim *sim, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		i++;
	}
	free(sim->forks);
	sim->forks = NULL;
	return (1);
}

static int	initialize_mutexes(t_sim *sim)
{
	int	i;

	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->count);
	if (!sim->forks)
		return (1);
	i = 0;
	while (i < sim->count)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL) != 0)
			return (destroy_fork_mutexes(sim, i));
		i++;
	}
	if (pthread_mutex_init(&sim->print, NULL) != 0)
		return (destroy_fork_mutexes(sim, sim->count));
	if (pthread_mutex_init(&sim->state, NULL) != 0)
	{
		pthread_mutex_destroy(&sim->print);
		return (destroy_fork_mutexes(sim, sim->count));
	}
	return (0);
}

static void	assign_forks_to_philosophers(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->count)
	{
		sim->philos[i].id = i + 1;
		sim->philos[i].meals = 0;
		sim->philos[i].last_meal = 0;
		sim->philos[i].left = &sim->forks[i];
		sim->philos[i].right = &sim->forks[(i + 1) % sim->count];
		sim->philos[i].sim = sim;
		i++;
	}
}

int	initialize_simulation(t_sim *sim)
{
	if (initialize_mutexes(sim) != 0)
		return (1);
	sim->philos = malloc(sizeof(t_philo) * sim->count);
	if (!sim->philos)
		return (1);
	sim->start_ms = 0;
	assign_forks_to_philosophers(sim);
	return (0);
}

void	cleanup_simulation(t_sim *sim)
{
	int	i;

	if (sim->forks)
	{
		i = 0;
		while (i < sim->count)
		{
			pthread_mutex_destroy(&sim->forks[i]);
			i++;
		}
		free(sim->forks);
	}
	if (sim->philos)
		free(sim->philos);
	pthread_mutex_destroy(&sim->print);
	pthread_mutex_destroy(&sim->state);
}
