/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijoja <ijoja@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:09:59 by ijoja             #+#    #+#             */
/*   Updated: 2025/12/06 22:30:12 by ijoja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philosopher_status(t_philo *philo, const char *status)
{
	long	time;

	pthread_mutex_lock(&philo->sim->print);
	if (!is_simulation_stopped(philo->sim))
	{
		time = calculate_elapsed_time_ms(philo->sim->start_ms);
		printf("%ld %d %s\n", time, philo->id, status);
	}
	pthread_mutex_unlock(&philo->sim->print);
}
