#include "philo.h"

long    now_ms(void)
{
    struct timeval  tv;

    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long    elapsed_ms(long start)
{
    return (now_ms() - start);
}

void    ms_sleep(t_sim *sim, int duration)
{
    long    end;
    int     stop;

    end = now_ms() + duration;
    while (now_ms() < end)
    {
        stop = 0;
        if (sim)
        {
            pthread_mutex_lock(&sim->state);
            stop = sim->stop;
            pthread_mutex_unlock(&sim->state);
        }
        if (stop)
            break ;
        usleep(1000);
    }
}
