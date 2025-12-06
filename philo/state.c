/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijoja <ijoja@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:09:59 by ijoja             #+#    #+#             */
/*   Updated: 2025/12/06 22:55:33 by ijoja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_simulation_stopped(t_sim *sim)
{
	int	value;

	pthread_mutex_lock(&sim->state);
	value = sim->stop;
	pthread_mutex_unlock(&sim->state);
	return (value);
}

void	stop_simulation(t_sim *sim)
{
	pthread_mutex_lock(&sim->state);
	sim->stop = 1;
	pthread_mutex_unlock(&sim->state);
}

void	update_philosopher_meal(t_philo *philo)
{
	int	required_meals;

	pthread_mutex_lock(&philo->sim->state);
	philo->meals++;
	philo->last_meal = get_current_time_ms();
	required_meals = philo->sim->must_eat;
	if (required_meals > 0 && philo->meals == required_meals)
		philo->sim->finished++;
	pthread_mutex_unlock(&philo->sim->state);
}
