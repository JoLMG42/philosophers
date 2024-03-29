/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 17:02:36 by jtaravel          #+#    #+#             */
/*   Updated: 2022/05/22 18:37:25 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	ft_print_philo(char *txt, t_manage *manage, int i)
{
	unsigned long long	t;

	t = ft_get_time() - manage->global_back->time;
	sem_wait(manage->write);
	printf("%llu %d %s\n", t, i, txt);
	sem_post(manage->write);
}

void	ft_think(t_manage *manage, int i)
{
	ft_print_philo("is thinking", manage, i);
}

void	ft_sleep(t_manage *manage, int i)
{
	sem_post(manage->forks);
	sem_post(manage->forks);
	ft_print_philo("is sleeping", manage, i);
	ft_usleep(manage, manage->global_back->tsleep);
}

void	ft_eat(t_manage *manage, int i)
{
	sem_wait(manage->forks);
	ft_print_philo("has taken a fork", manage, i);
	sem_wait(manage->forks);
	ft_print_philo("has taken a fork", manage, i);
	ft_print_philo("is eating", manage, i);
	ft_check_death(manage, manage->global_back->teat, i);
	manage[i].last_eat = ft_get_time();
	manage[i].nbr_of_eat++;
}

void	*ft_routine(void *work, int i)
{
	t_manage	*manage;

	manage = (t_manage *)work;
	if (i % 2 == 0)
		usleep(1000);
	while (1)
	{
		ft_eat(manage, i);
		ft_sleep(manage, i);
		ft_think(manage, i);
		ft_check_eat(manage);
		if (manage->global_back->n_philo)
			usleep(100);
	}
	return (NULL);
}
