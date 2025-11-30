/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijoja <ijoja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:09:59 by ijoja             #+#    #+#             */
/*   Updated: 2025/11/30 19:09:59 by ijoja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int get_stop(t_sim *sim)
{
	int stop;

	pthread_mutex_lock(&sim->state);
	stop = sim->stop;
	pthread_mutex_unlock(&sim->state);
	return (stop);
}

void	set_stop(t_sim *sim)
{
	pthread_mutex_lock(&sim->state);
	sim->stop = 1;
	pthread_mutex_unlock(&sim->state);
}

void	record_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->state);
	philo->last_meal = now_ms();
	philo->meals += 1;
	if (philo->sim->must_eat > 0 && philo->meals == philo->sim->must_eat)
		philo->sim->finished += 1;
	pthread_mutex_unlock(&philo->sim->state);
}
