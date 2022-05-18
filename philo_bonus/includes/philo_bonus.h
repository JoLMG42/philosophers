/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtaravel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:52:45 by jtaravel          #+#    #+#             */
/*   Updated: 2022/05/18 17:18:13 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H

# define PHILO_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <wait.h>

typedef struct s_manage
{
	unsigned long long	time;
	unsigned long long	last_eat;
	int					nb_fork;
	int					eating;
	int					philo_place;
	sem_t				*d_value;
	sem_t				*write;
	sem_t				*forks;
	int					nbr_of_eat;
	int					release;
	pid_t				frk;
	struct s_global		*global_back;
	pthread_t			philo_thread;
	pthread_t			philo_death;
}	t_manage;

typedef struct s_global
{
	int					n_philo;
	int					tdeath;
	int					teat;
	int					tsleep;
	unsigned long long	time;
	int					each_time_eat;
	t_manage			*work;

}	t_global;

int					ft_atoi(const char *str);
char				*ft_itoa(int n);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
unsigned long long	ft_get_time(void);
int					ft_check_args(int ac, char **av);
void				ft_print_philo(char *txt, t_manage *manage, int i);
void				ft_think(t_manage *manage, int i);
void				ft_sleep(t_manage *manage, int i);
void				ft_eat(t_manage *manage, int i);
void				*ft_routine(void *work, int i);
void				ft_check_eat(t_manage *manage);
void				ft_check_death(t_manage *manage,
						unsigned long long t, int i);
t_manage			*ft_init_struct_2(t_global *global);
void				ft_init_struct(t_global *global, char **av, int ac);
void				ft_init_thread(t_global *global);

#endif
