/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijoja <ijoja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:09:59 by ijoja             #+#    #+#             */
/*   Updated: 2025/11/30 19:09:59 by ijoja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			main(int argc, char **argv)
{
	t_sim			sim;

	if (parse_args(&sim, argc, argv) != 0)
		return (1);
	if (setup_sim(&sim) != 0)
	{
		cleanup_sim(&sim);
		return (1);
	}
	if (launch_simulation(&sim) != 0)
	{
		cleanup_sim(&sim);
		return (1);
	}
	cleanup_sim(&sim);
	return (0);
}
