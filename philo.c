#include "./includes/philo.h"

unsigned long long ft_get_time(void)
{
	struct	timeval time;
	unsigned long long ms;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ms);
}

void	ft_free(t_global *global)
{
	int	i;

	i = 0;
	while (i < global->n_philo)
	{
		pthread_mutex_destroy(&global->forks[i]);
		i++;
	}
	free(global->forks);
	pthread_mutex_destroy(&global->write);
	free(global->work);
	free(global);
}

int	main(int ac, char **av)
{
	t_global *global;

	global = malloc(sizeof(t_global));
	if (!ft_check_args(ac, av))
	{
		printf("Error args");
		exit(0);
	}
	ft_init_struct(global, av, ac);
	ft_init_mutex(global);
	ft_init_thread(global);
	ft_free(global);
}
