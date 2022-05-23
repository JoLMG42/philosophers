/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:26:27 by jtaravel          #+#    #+#             */
/*   Updated: 2022/05/22 19:18:35 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_print_philo(char *txt, t_manage *manage)
{
	unsigned long long	t;
	int					value;

	pthread_mutex_lock(&manage->global_back->write);
	t = ft_get_time() - manage->global_back->time;
	pthread_mutex_lock(&manage->global_back->philo_a_eat);
	value = manage->global_back->value;
	pthread_mutex_unlock(&manage->global_back->philo_a_eat);
	if (value == 1)
		printf("%llu %d %s\n", t, manage->philo_place, txt);
	pthread_mutex_unlock(&manage->global_back->write);
}

void	*ft_routine(void *work)
{
	t_manage	*manage;
	int			value;

	manage = (t_manage *)work;
	if (manage->philo_place % 2 == 0)
		usleep(manage->global_back->teat);
	pthread_mutex_lock(&manage->global_back->philo_a_eat);
	value = manage->global_back->value;
	pthread_mutex_unlock(&manage->global_back->philo_a_eat);
	while (value)
	{
		pthread_mutex_lock(&manage->global_back->philo_a_eat);
		value = manage->global_back->value;
		pthread_mutex_unlock(&manage->global_back->philo_a_eat);
		ft_eat(manage);
		ft_sleep(manage);
		ft_think(manage);
		if (manage->global_back->n_philo % 2 != 0)
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
	if (manage->philo_place % 2 != 0)
		pthread_mutex_lock(&manage->global_back->forks[manage->left_fork]);
	else
		pthread_mutex_lock(&manage->global_back->forks[manage->right_fork]);
	ft_print_philo("has taken a fork", manage);
	if (manage->philo_place % 2 != 0)
		pthread_mutex_lock(&manage->global_back->forks[manage->right_fork]);
	else
		pthread_mutex_lock(&manage->global_back->forks[manage->left_fork]);
	ft_print_philo("has taken a fork", manage);
	ft_print_philo("is eating", manage);
	pthread_mutex_lock(&manage->nbr_eat);
	manage->last_eat = ft_get_time();
	pthread_mutex_unlock(&manage->nbr_eat);
	manage->eating = 1;
	ft_usleep(manage, manage->global_back->teat);
	pthread_mutex_lock(&manage->nbr_eat);
	manage->nbr_of_eat += 1;
	pthread_mutex_unlock(&manage->nbr_eat);
	manage->eating = 0;
}

void	ft_sleep(t_manage *manage)
{
	pthread_mutex_unlock(&manage->global_back->forks[manage->left_fork]);
	pthread_mutex_unlock(&manage->global_back->forks[manage->right_fork]);
	ft_print_philo("is sleeping", manage);
	ft_usleep(manage, manage->global_back->tsleep);
}
