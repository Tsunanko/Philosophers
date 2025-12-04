/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijoja <ijoja@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:09:59 by ijoja             #+#    #+#             */
/*   Updated: 2025/11/30 19:09:59 by ijoja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	print_usage(char *prog)
{
	fprintf(stderr,
		"Usage: %s number_of_philosophers time_to_die time_to_eat "
		"time_to_sleep [times_must_eat]\n",
		prog);
	return (1);
}

static long	atolong(const char *s)
{
	long	res;
	int		index;

	res = 0;
	index = 0;
	while (s[index] >= '0' && s[index] <= '9')
	{
		res = res * 10 + (s[index] - '0');
		index++;
	}
	if (s[index] != '\0')
		return (-1);
	return (res);
}

static int	parse_optional(t_sim *sim, int argc, char **argv)
{
	long	value;

	sim->must_eat = -1;
	if (argc == 6)
	{
		value = atolong(argv[5]);
		if (value <= 0)
		{
			fprintf(stderr,
				"number_of_times_each_philosopher_must_eat must be positive.\n");
			return (1);
		}
		sim->must_eat = (int)value;
	}
	return (0);
}

int	parse_args(t_sim *sim, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (print_usage(argv[0]));
	sim->count = (int)atolong(argv[1]);
	sim->t_die = (int)atolong(argv[2]);
	sim->t_eat = (int)atolong(argv[3]);
	sim->t_sleep = (int)atolong(argv[4]);
	if (parse_optional(sim, argc, argv) != 0)
		return (1);
	if (sim->count <= 0 || sim->t_die <= 0
		|| sim->t_eat <= 0 || sim->t_sleep <= 0)
	{
		fprintf(stderr, "All timing values must be positive integers.\n");
		return (1);
	}
	sim->stop = 0;
	sim->finished = 0;
	sim->forks = NULL;
	sim->philos = NULL;
	return (0);
}
