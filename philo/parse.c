/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijoja <ijoja@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 19:09:59 by ijoja             #+#    #+#             */
/*   Updated: 2025/12/06 22:55:33 by ijoja            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	display_usage_message(char *prog)
{
	fprintf(stderr,
		"Usage: %s number_of_philosophers time_to_die time_to_eat "
		"time_to_sleep [times_must_eat]\n",
		prog);
	return (1);
}

static long	convert_string_to_long(const char *s)
{
	long	res;
	long	prev;
	int		i;

	res = 0;
	i = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		prev = res;
		res = res * 10 + (s[i] - '0');
		if (res < prev)
			return (-1);
		i++;
	}
	if (s[i] != '\0')
		return (-1);
	return (res);
}

static int	parse_optional_argument(t_sim *sim, int argc, char **argv)
{
	long	value;

	sim->must_eat = -1;
	if (argc == 6)
	{
		value = convert_string_to_long(argv[5]);
		if (value <= 0)
		{
			fprintf(stderr, "number_of_times_each_philosopher_"
				"must_eat must be positive.\n");
			return (1);
		}
		sim->must_eat = (int)value;
	}
	return (0);
}

int	parse_args(t_sim *sim, int argc, char **argv)
{
	long	value;

	if (argc < 5 || argc > 6)
		return (display_usage_message(argv[0]));
	value = convert_string_to_long(argv[1]);
	sim->count = (int)value;
	value = convert_string_to_long(argv[2]);
	sim->t_die = (int)value;
	value = convert_string_to_long(argv[3]);
	sim->t_eat = (int)value;
	value = convert_string_to_long(argv[4]);
	sim->t_sleep = (int)value;
	if (parse_optional_argument(sim, argc, argv) != 0)
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
