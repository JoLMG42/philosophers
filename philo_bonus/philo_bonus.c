/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:48:27 by jtaravel          #+#    #+#             */
/*   Updated: 2022/05/18 17:13:25 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo_bonus.h"

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
	free(global->work);
	free(global);
}

int	main(int ac, char **av)
{
	t_global	*global;

	global = malloc(sizeof(t_global));
	if (!ft_check_args(ac, av))
	{
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
	sem_unlink("forks");
	global->work->forks = sem_open("forks", O_CREAT, 0644, global->n_philo);
	sem_unlink("write");
	global->work->write = sem_open("write", O_CREAT, 0644, 1);
	ft_init_thread(global);
	ft_free(global);
}
