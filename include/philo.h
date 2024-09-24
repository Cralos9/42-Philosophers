/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:44:36 by cacarval          #+#    #+#             */
/*   Updated: 2024/08/20 12:52:57 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# define RED "\e[1;31m"
# define RESET "\033[0m"
# define GREEN "\e[1;32m"
# define TAKE "\e[1;36mhas taken a fork\033[0m"
# define EAT "\e[1;32mis eating\033[0m"
# define SLEEP "\e[1;35mis sleeping\033[0m"
# define THINK "\e[1;33mis thinking\033[0m"
# define DIE "\e[1;31mdied\033[0m"
# define FINISH "f"

typedef struct s_info
{
	int				id;
	int				r_fork;
	int				l_fork;
	long long		last_eat;
	int				eat_count;
	struct s_philo	*philo;
	pthread_t		thread;

}				t_info;

typedef struct s_philo
{
	int				n_philos;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				times_to_eat;
	int				finish_eating;
	long long		start_time;
	int				ate_enough;
	t_info			*p_info;
	pthread_mutex_t	*fork_lock;
	pthread_mutex_t start_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	finish_lock;

}		t_philo;

int			ft_atoi(const char *str);
void		*start_eating(void *ptr);
void		set_table(t_philo *philo, int ac, char **argv);
void		call_philosophers(t_philo *philo);
void		exit_error(t_philo *philo, char *msg, int n);
long long	get_time(void);
int			is_time_to_finish(t_info *copy, int finish_order);
void		print_action(t_info *copy, const char *message);
void		advance_time(t_info *copy, long long stop);
int			is_someone_dead_or_full(t_info *copy);
void		destroy_padlocks(t_philo *philo);
void		finish_dinner(t_philo *philo);
void		clean_table(t_philo *philo);
void		dinner_monitor(t_philo *philo);

#endif