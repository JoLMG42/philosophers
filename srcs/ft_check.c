/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:28:47 by jtaravel          #+#    #+#             */
/*   Updated: 2022/03/18 14:41:02 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_calc(t_manage *death)
{
	return (death->global_back->each_time_eat
		+ death->global_back->n_philo / 2 - 1);
}	

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
			&& death->nbr_of_eat >= ft_calc(death))
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

int	ft_check_args(int ac, char **av)
{
	int		i;
	char	*str;

	i = 1;
	if (ac != 5 && ac != 6)
		return (0);
	while (i < ac)
	{
		str = ft_itoa(ft_atoi(av[i]));
		if (av[i] == str)
		{
			free(str);
			printf("Wrong args");
			return (0);
		}
		free(str);
		i++;
	}
	return (1);
}
