#include "philo.h"

void    print_status(t_philo *philo, const char *status)
{
    long    timestamp;
    int     stopped;

    pthread_mutex_lock(&philo->sim->print);
    pthread_mutex_lock(&philo->sim->state);
    stopped = philo->sim->stop;
    pthread_mutex_unlock(&philo->sim->state);
    if (!stopped)
    {
        timestamp = elapsed_ms(philo->sim->start_ms);
        printf("%ld %d %s\n", timestamp, philo->id, status);
    }
    pthread_mutex_unlock(&philo->sim->print);
}
