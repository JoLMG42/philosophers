/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:27:43 by jtaravel          #+#    #+#             */
/*   Updated: 2022/03/02 19:48:49 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (ac != 5 && ac != 6)
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

unsigned long long ft_get_time(void)
{
	struct	timeval time;
	unsigned long long ms;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ms);
}

void    ft_init_mutex(t_global *global)
{
        int     i;

        i = 0;
        global->forks = malloc(sizeof(pthread_mutex_t) * (global->n_philo));
        if (!global->forks)
                return ;
        while (i < global->n_philo)
        {
                pthread_mutex_init(&global->forks[i], NULL);
                i++;
        }
}

t_manage	*ft_init_struct_2(t_global *global)
{
	t_manage *manage;
	int	i;

	i = 0;
	manage = malloc(sizeof(t_manage) * global->n_philo);
	while (i < global->n_philo)
	{
		manage[i].philo_place = i + 1;
		manage[i].left_fork = i;
		manage[i].right_fork = (i + 1) % global->n_philo;
		manage[i].eating = 0;
		manage[i].nbr_of_eat = 0;
		pthread_mutex_init(&manage[i].eat, NULL);
		manage[i].global_back = global;
		i++;
	}
	return (manage);
}


void	ft_init_struct(t_global *global, char **av, int ac)
{
	global->n_philo = ft_atoi(av[1]);
	global->tdeath = ft_atoi(av[2]);
	global->teat = ft_atoi(av[3]);
	global->tsleep = ft_atoi(av[4]);
	if (ac == 6)
		global->each_time_eat = ft_atoi(av[5]);
	global->work = ft_init_struct_2(global);
}

void	ft_print_philo(char *txt, t_manage *manage)
{
	unsigned long long t;

	pthread_mutex_lock(&manage->global_back->write);
	t = ft_get_time() - manage->global_back->time;
	printf("%llu\tPhilosopher %d %s\n", t, manage->philo_place, txt);
	pthread_mutex_unlock(&manage->global_back->write);
}

void	ft_think(t_manage *manage)
{
	ft_print_philo("think", manage);
}

void	ft_eat(t_manage *manage)
{
	pthread_mutex_lock(&manage->global_back->forks[manage->left_fork]);
	ft_print_philo("take left fork", manage);
	pthread_mutex_lock(&manage->global_back->forks[manage->right_fork]);
	ft_print_philo("take right fork", manage);
	//pthread_mutex_lock(&manage->eat);
	ft_print_philo("eat", manage);
	manage->nbr_of_eat++;
	if (manage->nbr_of_eat == manage->global_back->each_time_eat)
		exit(0);
	manage->last_eat = ft_get_time();
	manage->eating = 1;
	usleep(manage->global_back->teat * 1000);
	//pthread_mutex_unlock(&manage->eat);
	manage->eating = 0;
}

void	ft_sleep(t_manage *manage)
{
	pthread_mutex_unlock(&manage->global_back->forks[manage->left_fork]);
	pthread_mutex_unlock(&manage->global_back->forks[manage->right_fork]);
	ft_print_philo("sleeps", manage);
	usleep(manage->global_back->tsleep * 1000);

}

void	*ft_routine(void *work)
{
	t_manage	*manage;

	manage = (t_manage *)work;
	while(1)
	{
	ft_eat(manage);
	ft_sleep(manage);
	ft_think(manage);
	usleep(100);
	}
	//ft_print_philo(manage);
	return (NULL);
}

void	ft_init_thread(t_global *global)
{
	int	i;

	global->time = ft_get_time();
	pthread_mutex_init(&global->write, NULL);
	i = 0;
	while (i < global->n_philo)
	{
		global->work[i].last_eat = ft_get_time();
		pthread_create(&global->work[i].philo_thread, NULL, &ft_routine, &global->work[i]);
		i++;
		usleep(100);
	}
	i = 0;
	while (i < global->n_philo)
	{
		pthread_join(global->work[i].philo_thread, NULL);
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
