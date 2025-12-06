/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijoja <ijoja@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:09:59 by ijoja             #+#    #+#             */
/*   Updated: 2025/12/06 22:09:06 by ijoja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * MS_PER_SEC) + (tv.tv_usec / MS_PER_SEC));
}

long	calculate_elapsed_time_ms(long start)
{
	return (get_current_time_ms() - start);
}

void	sleep_milliseconds(t_sim *sim, int duration)
{
	long	end;

	end = get_current_time_ms() + duration;
	while (!is_simulation_stopped(sim) && get_current_time_ms() < end)
		usleep(US_PER_MS);
}
