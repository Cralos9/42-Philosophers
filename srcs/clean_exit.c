/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:28:00 by cacarval          #+#    #+#             */
/*   Updated: 2023/09/28 14:07:58 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_table(t_philo *philo)
{
	free(philo->p_info);
	free(philo->fork_lock);
}

void	destroy_padlocks(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->n_philos)
		pthread_mutex_destroy(&philo->fork_lock[i]);
	clean_table(philo);
	pthread_mutex_destroy(&philo->print_lock);
	pthread_mutex_destroy(&philo->eat_lock);
	pthread_mutex_destroy(&philo->finish_lock);
}

void	finish_dinner(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->n_philos)
		pthread_join(philo->p_info[i].thread, NULL);
	destroy_padlocks(philo);
}

void	dinner_monitor(t_philo *philo)
{
	int	i;
	int	flag;

	flag = 1;
	while (flag)
	{
		i = -1;
		philo->ate_enough = 0;
		while (++i < philo->n_philos)
		{
			if (1 && is_someone_dead_or_full(&philo->p_info[i]))
				flag = 0;
		}
		usleep(10);
	}
	finish_dinner(philo);
}
