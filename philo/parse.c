#include "philo.h"

static long   atolong(const char *s)
{
    long    res;
    int     i;

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

int parse_args(t_sim *sim, int argc, char **argv)
{
    long    tmp;

    if (argc < 5 || argc > 6)
    {
        fprintf(stderr, "Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [times_must_eat]\n", argv[0]);
        return (1);
    }
    sim->count = (int)atolong(argv[1]);
    sim->t_die = (int)atolong(argv[2]);
    sim->t_eat = (int)atolong(argv[3]);
    sim->t_sleep = (int)atolong(argv[4]);
    sim->must_eat = -1;
    if (argc == 6)
    {
        tmp = atolong(argv[5]);
        if (tmp <= 0)
        {
            fprintf(stderr, "number_of_times_each_philosopher_must_eat must be a positive integer.\n");
            return (1);
        }
        sim->must_eat = (int)tmp;
    }
    if (sim->count <= 0 || sim->t_die <= 0 || sim->t_eat <= 0 || sim->t_sleep <= 0)
    {
        fprintf(stderr, "All timing and philosopher counts must be positive integers.\n");
        return (1);
    }
    sim->stop = 0;
    sim->finished = 0;
    sim->forks = NULL;
    sim->philos = NULL;
    return (0);
}
