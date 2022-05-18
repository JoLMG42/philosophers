/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:28:47 by jtaravel          #+#    #+#             */
/*   Updated: 2022/05/16 16:09:30 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	ft_death(t_manage *death)
{
	pthread_mutex_unlock(&death->nbr_eat);
	ft_print_philo("died", death);
	pthread_mutex_lock(&death->global_back->philo_a_eat);
	death->global_back->value = 0;
	pthread_mutex_unlock(&death->global_back->philo_a_eat);
}

static void	ft_finish_eat(t_manage *death)
{
	pthread_mutex_unlock(&death->nbr_eat);
	pthread_mutex_lock(&death->global_back->philo_a_eat);
	death->global_back->value = 0;
	pthread_mutex_unlock(&death->global_back->philo_a_eat);
}

void	*ft_check_death(void *work)
{
	t_manage	*death;
	int			value;

	value = 1;
	death = (t_manage *)work;
	while (value)
	{
		pthread_mutex_lock(&death->nbr_eat);
		if ((ft_get_time() >= death->global_back->tdeath + death->last_eat))
		{
			ft_death(death);
			break ;
		}
		else if (death->global_back->each_time_eat
			&& death->nbr_of_eat > death->global_back->each_time_eat)
		{
			ft_finish_eat(death);
			break ;
		}
		pthread_mutex_unlock(&death->nbr_eat);
		pthread_mutex_lock(&death->global_back->philo_a_eat);
		value = death->global_back->value;
		pthread_mutex_unlock(&death->global_back->philo_a_eat);
	}
	return (NULL);
}

static int	ft_isdigit(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
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
