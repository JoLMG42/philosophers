/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:30:29 by jtaravel          #+#    #+#             */
/*   Updated: 2022/03/01 19:04:52 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long ft_get_time(void)
{
	struct	timeval time;
	unsigned long long ms;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ms);
}


int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	 ft_check_args(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac != 5)// || ac != 6)
		return (0);
	while (av[i])
	{
		if (ft_strlen(av[i]) != ft_strlen(ft_itoa(ft_atoi(av[i]))))
		{
			printf("Wrong args");
			return (0);
		}
		i++;
	}
	return (1);
}

t_work	*ft_init_struct_2(t_global *global)
{
	t_work	*all;
	int	i;

	i = 0;
	all = malloc(sizeof(t_work *) * global->philo);
	while (i < global->philo)
	{
		all[i].left_fork = i;
		all[i].right_fork = (i + 1) % global->philo;
		all[i].eating = 0;
		all[i].nbr_of_eat = 0;
		pthread_mutex_init(&all[i].eat, NULL);
		i++;
	}
	return (all);
}



void	ft_init_struct(t_global *global, char **av, int ac)
{
	global->philo = ft_atoi(av[1]);
	global->tdeath = ft_atoi(av[2]);
	global->teat = ft_atoi(av[3]);
	global->tsleep = ft_atoi(av[4]);
	if (ac == 6)
		global->each_time_eat = ft_atoi(av[5]);
	global->philo_work = ft_init_struct_2(global);
}


void	*ft_routine(void *philo_work)
{
	t_work *work;

	work = philo_work;
	ft_eat(work);
	ft_sleep(work);
	ft_think(work);
}

void	ft_init_mutex(t_global *global)
{
	int	i;

	i = 0;
	global->forks = malloc(sizeof(pthread_mutex_t) * global->philo);
	while (i < global->philo)
	{
		pthread_mutex_init(&global->forks[i], NULL);
		i++;
	}
}

void	ft_init_thread(t_global *global)
{
	int	i;
	pthread_t	thread;

	global->time = ft_get_time();
	pthread_mutex_init(&global->write, NULL);
	i = 0;
	while (i <= global->philo)
	{
		global->philo_work[i].last_eat = ft_get_time();
		pthread_create(&thread, NULL, &ft_routine, &global->philo_work[i]);
		i++;
	}
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
}
