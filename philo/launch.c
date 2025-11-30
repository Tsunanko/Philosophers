/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijoja <ijoja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:09:59 by ijoja             #+#    #+#             */
/*   Updated: 2025/11/30 19:09:59 by ijoja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	launch_simulation(t_sim *sim)
{
	pthread_t	watcher;
	int		i;

	i = 0;
	while (i < sim->count)
	{
		if (pthread_create(&sim->philos[i].thread, NULL,
		philo_routine, &sim->philos[i]) != 0)
		return (1);
		i++;
	}
	if (pthread_create(&watcher, NULL, monitor, sim) != 0)
	return (1);
	i = 0;
	while (i < sim->count)
	pthread_join(sim->philos[i++].thread, NULL);
	pthread_join(watcher, NULL);
	return (0);
}
