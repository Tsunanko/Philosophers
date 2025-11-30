#include "philo.h"

static int  get_stop(t_sim *sim)
{
    int stop;

    pthread_mutex_lock(&sim->state);
    stop = sim->stop;
    pthread_mutex_unlock(&sim->state);
    return (stop);
}

static void update_meal(t_philo *philo)
{
    pthread_mutex_lock(&philo->sim->state);
    philo->last_meal = now_ms();
    philo->meals += 1;
    if (philo->sim->must_eat > 0 && philo->meals == philo->sim->must_eat)
        philo->sim->finished += 1;
    pthread_mutex_unlock(&philo->sim->state);
}

static void take_forks(t_philo *philo)
{
    pthread_mutex_t   *first;
    pthread_mutex_t   *second;

    if (philo->sim->count == 1)
    {
        pthread_mutex_lock(philo->left);
        print_status(philo, "has taken a fork");
        ms_sleep(philo->sim, philo->sim->t_die);
        pthread_mutex_unlock(philo->left);
        if (!get_stop(philo->sim))
        {
            print_status(philo, "died");
            pthread_mutex_lock(&philo->sim->state);
            philo->sim->stop = 1;
            pthread_mutex_unlock(&philo->sim->state);
        }
        return ;
    }
    first = philo->left;
    second = philo->right;
    if (philo->id % 2 == 0)
    {
        first = philo->right;
        second = philo->left;
    }
    pthread_mutex_lock(first);
    print_status(philo, "has taken a fork");
    pthread_mutex_lock(second);
    print_status(philo, "has taken a fork");
}

static int  think_delay(t_sim *sim)
{
    int delay;

    if (sim->count % 2 == 0)
        return (0);
    delay = (sim->t_die - (sim->t_eat + sim->t_sleep)) / 2;
    if (delay < 0)
        delay = 0;
    return (delay);
}

static void eat_sleep_think(t_philo *philo)
{
    take_forks(philo);
    if (philo->sim->count == 1)
        return ;
    update_meal(philo);
    print_status(philo, "is eating");
    ms_sleep(philo->sim, philo->sim->t_eat);
    pthread_mutex_unlock(philo->right);
    pthread_mutex_unlock(philo->left);
    print_status(philo, "is sleeping");
    ms_sleep(philo->sim, philo->sim->t_sleep);
    print_status(philo, "is thinking");
    ms_sleep(philo->sim, think_delay(philo->sim));
}

void    *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->id % 2 == 0)
        usleep(1000);
    while (!get_stop(philo->sim))
        eat_sleep_think(philo);
    return (NULL);
}

static void *monitor(void *arg)
{
    t_sim   *sim;
    int     i;

    sim = (t_sim *)arg;
    while (1)
    {
        i = 0;
        while (i < sim->count)
        {
            pthread_mutex_lock(&sim->state);
            if (!sim->stop && now_ms() - sim->philos[i].last_meal >= sim->t_die)
            {
                pthread_mutex_unlock(&sim->state);
                print_status(&sim->philos[i], "died");
                pthread_mutex_lock(&sim->state);
                sim->stop = 1;
                pthread_mutex_unlock(&sim->state);
                return (NULL);
            }
            if (sim->must_eat > 0 && sim->finished >= sim->count)
            {
                sim->stop = 1;
                pthread_mutex_unlock(&sim->state);
                return (NULL);
            }
            pthread_mutex_unlock(&sim->state);
            if (get_stop(sim))
                return (NULL);
            i++;
        }
        usleep(1000);
    }
    return (NULL);
}

int launch_simulation(t_sim *sim)
{
    pthread_t   watcher;
    int         i;

    i = 0;
    while (i < sim->count)
    {
        if (pthread_create(&sim->philos[i].thread, NULL, philo_routine,
                &sim->philos[i]) != 0)
            return (1);
        i++;
    }
    if (pthread_create(&watcher, NULL, monitor, sim) != 0)
        return (1);
    i = 0;
    while (i < sim->count)
        pthread_join(sim->philos[i++].thread, NULL);
    pthread_join(watcher, NULL);
    return (0);
}
