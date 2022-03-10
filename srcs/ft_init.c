/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:27:27 by jtaravel          #+#    #+#             */
/*   Updated: 2022/03/10 15:33:18 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_init_thread(t_global *global)
{
	int	i;
	//pthread_t death;
	//pthread_t a_eat;

	global->time = ft_get_time();
	pthread_mutex_init(&global->write, NULL);
	i = 0;
	while (i < global->n_philo)
	{
		global->work[i].last_eat = ft_get_time();
		pthread_create(&global->work[i].philo_thread, NULL, &ft_routine, &global->work[i]);
		pthread_create(&global->work[i].philo_death, NULL, &ft_check_death, &global->work[i]);
		//pthread_create(&global->work[i].philo_a_eat, NULL, &ft_check_eat, &global->work[i]);
		i++;
		usleep(100);
	}
	i = 0;
	while (i < global->n_philo)
	{
		pthread_join(global->work[i].philo_thread, NULL);
		pthread_join(global->work[i].philo_death, NULL);
	//	pthread_join(global->work[i].philo_a_eat, NULL);
		i++;
	}

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
	global->test = 1;
	global->value = 1;
	if (ac == 6)
	{
		global->test = 0;
		global->each_time_eat = ft_atoi(av[5]);
	}
	global->work = ft_init_struct_2(global);
}
