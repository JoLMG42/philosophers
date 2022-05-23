/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:18:09 by jtaravel          #+#    #+#             */
/*   Updated: 2022/05/23 10:47:33 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philo.h"

void	ft_usleep(t_manage *manage, unsigned long long t)
{
	unsigned long long	time_start;

	time_start = ft_get_time();
	while (time_start + t >= ft_get_time())
	{
		usleep(10);
		pthread_mutex_lock(&manage->global_back->philo_a_eat);
		if (manage->global_back->value == 0)
		{
			pthread_mutex_unlock(&manage->global_back->philo_a_eat);
			return ;
		}
		pthread_mutex_unlock(&manage->global_back->philo_a_eat);
	}
}

unsigned long long	ft_get_time(void)
{
	struct timeval		time;
	unsigned long long	ms;

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
	pthread_mutex_destroy(&global->philo_a_eat);
	free(global->work);
	free(global);
}

int	ft_check_args(int ac, char **av)
{
	int		i;
	int		j;

	i = 1;
	if (ac != 5 && ac != 6)
		return (0);
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_global	*global;

	global = malloc(sizeof(t_global));
	if (!ft_check_args(ac, av) || ft_atoi(av[1]) == 0)
	{
		free(global);
		printf("Error args");
		return (0);
	}
	if (ft_atoi(av[1]) == 1)
	{
		printf ("0 1 has taken a fork\n");
		usleep(ft_atoi(av[2]) * 1000);
		printf ("%d 1 died\n", ft_atoi(av[2]));
		free(global);
		return (0);
	}
	ft_init_struct(global, av, ac);
	ft_init_mutex(global);
	if (global->each_time_eat == 0)
		;
	else
		ft_init_thread(global);
	ft_free(global);
}
