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
		"time_to_sleep [times_must_eat]\\n", prog);
	return (1);
}

static long	atolong(const char *s)
{
	long	res;
	int	i;

	res = 0;
	i = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + (s[i] - '0');
		i++;
	}
	if (s[i] != '\0')
		return (-1);
	return (res);
}

static int	parse_optional(t_sim *sim, int argc, char **argv)
{
	long	tmp;

	sim->must_eat = -1;
	if (argc == 6)
	{
		tmp = atolong(argv[5]);
		if (tmp <= 0)
		{
			fprintf(stderr,
				"number_of_times_each_philosopher_must_eat "
				"must be a positive integer.\\n");
			return (1);
		}
		sim->must_eat = (int)tmp;
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
		fprintf(stderr,
			"All timing and philosopher counts must be positive integers.\\n");
		return (1);
	}
	sim->stop = 0;
	sim->finished = 0;
	sim->forks = NULL;
	sim->philos = NULL;
	return (0);
}
