/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:26:27 by jtaravel          #+#    #+#             */
/*   Updated: 2022/03/10 16:35:24 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_print_philo(char *txt, t_manage *manage)
{
	unsigned long long t;

	pthread_mutex_lock(&manage->global_back->write);
	t = ft_get_time() - manage->global_back->time;
	if (manage->global_back->value == 1)
		printf("%llu %d %s\n", t, manage->philo_place, txt);
	pthread_mutex_unlock(&manage->global_back->write);
}

void	*ft_routine(void *work)
{
	t_manage	*manage;

	manage = (t_manage *)work;
	while(manage->global_back->value)
	{
	ft_eat(manage);
	ft_sleep(manage);
	ft_think(manage);
	usleep(100);
	}
	return (NULL);
}

void	ft_think(t_manage *manage)
{
	ft_print_philo("is thinking", manage);
}

void	ft_eat(t_manage *manage)
{
	if (manage->global_back->n_philo % 2 != 0)
		pthread_mutex_lock(&manage->global_back->forks[manage->left_fork]);
	else
		pthread_mutex_lock(&manage->global_back->forks[manage->right_fork]);
	ft_print_philo("has taken a fork", manage);
	if (manage->global_back->n_philo % 2 != 0)
		pthread_mutex_lock(&manage->global_back->forks[manage->right_fork]);
	else
		pthread_mutex_lock(&manage->global_back->forks[manage->left_fork]);
	ft_print_philo("has taken a fork", manage);
	/*pthread_mutex_lock(&manage->global_back->forks[manage->left_fork]);
	ft_print_philo("has taken a fork", manage);
	pthread_mutex_lock(&manage->global_back->forks[manage->right_fork]);
	ft_print_philo("has taken a fork", manage);*/
	//pthread_mutex_lock(&manage->eat);
	ft_print_philo("is eating", manage);
	manage->nbr_of_eat += 1;
	/*if (manage->global_back->test == 0)
	{
		if (test >= (manage->global_back->each_time_eat))
		{
			free(manage->global_back->forks);
			free(manage->global_back);
			free(manage);
			exit(0);
		}
	}*/
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
	ft_print_philo("is sleeping", manage);
	usleep(manage->global_back->tsleep * 1000);

}
