/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:32:37 by jtaravel          #+#    #+#             */
/*   Updated: 2022/03/18 14:12:52 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_manage
{
	unsigned long long	time;
	unsigned long long	last_eat;
	int					right_fork;
	int					left_fork;
	int					eating;
	int					philo_place;
	int					nbr_of_eat;
	int					release;
	struct s_global		*global_back;
	pthread_mutex_t		nbr_eat;
	pthread_t			philo_thread;
	pthread_t			philo_death;
	pthread_mutex_t		eat;
}	t_manage;

typedef struct s_global
{
	unsigned long long	time;
	int					n_philo;
	int					tdeath;
	int					teat;
	int					tsleep;
	int					each_time_eat;
	int					test;
	int					value;
	t_manage			*work;
	pthread_mutex_t		philo_a_eat;
	pthread_mutex_t		write;
	pthread_mutex_t		*forks;
}	t_global;

void				ft_free(t_global *global);
int					ft_atoi(const char *str);
char				*ft_itoa(int n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
unsigned long long	ft_get_time(void);
void				*ft_check_death(void *work);
int					ft_check_args(int ac, char **av);
void				*ft_routine(void *work);
void				ft_print_philo(char *txt, t_manage *manage);
void				ft_think(t_manage *manage);
void				ft_eat(t_manage *manage);
void				ft_sleep(t_manage *manage);
void				ft_init_struct(t_global *global, char **av, int ac);
t_manage			*ft_init_struct_2(t_global *global);
void				ft_init_mutex(t_global *global);
void				ft_init_thread(t_global *global);

#endif
