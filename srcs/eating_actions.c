/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:13:20 by cacarval          #+#    #+#             */
/*   Updated: 2023/09/28 14:11:32 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_time_to_finish(t_info *copy, int finish_order)
{
	pthread_mutex_lock(&copy->philo->finish_lock);
	if (finish_order || copy->philo->finish_eating)
	{
		if (finish_order)
			copy->philo->finish_eating = 1;
		pthread_mutex_unlock(&copy->philo->finish_lock);
		return (1);
	}
	pthread_mutex_unlock(&copy->philo->finish_lock);
	return (0);
}

int	is_someone_dead_or_full(t_info *copy)
{
	pthread_mutex_lock(&copy->philo->eat_lock);
	if (get_time() - copy->last_eat >= copy->philo->time_to_die)
	{
		print_action(copy, DIE);
		is_time_to_finish(copy, 1);
		pthread_mutex_unlock(&copy->philo->eat_lock);
		return (1);
	}
	else if (copy->philo->times_to_eat > 0
		&& copy->eat_count >= copy->philo->times_to_eat)
	{
		copy->philo->ate_enough++;
		if (copy->philo->ate_enough >= copy->philo->n_philos)
		{
			is_time_to_finish(copy, 1);
			print_action(copy, FINISH);
			pthread_mutex_unlock(&copy->philo->eat_lock);
			return (1);
		}
	}
	pthread_mutex_unlock(&copy->philo->eat_lock);
	return (0);
}

void	time_to_eat(t_info *copy)
{
	if (copy->id % 2 == 0)
	{
		pthread_mutex_lock(&copy->philo->fork_lock[copy->l_fork]);
		pthread_mutex_lock(&copy->philo->fork_lock[copy->r_fork]);
	}
	else
	{
		pthread_mutex_lock(&copy->philo->fork_lock[copy->r_fork]);
		pthread_mutex_lock(&copy->philo->fork_lock[copy->l_fork]);
	}
	print_action(copy, TAKE);
	print_action(copy, TAKE);
	print_action(copy, EAT);
	copy->last_eat = get_time();
	copy->eat_count++;
	advance_time(copy, copy->philo->time_to_eat);
	pthread_mutex_lock(&copy->philo->eat_lock);
	pthread_mutex_unlock(&copy->philo->eat_lock);
	pthread_mutex_unlock(&copy->philo->fork_lock[copy->r_fork]);
	pthread_mutex_unlock(&copy->philo->fork_lock[copy->l_fork]);
}

int	lone_philosopher(t_philo *philo)
{
	print_action(&philo->p_info[0], TAKE);
	advance_time(&philo->p_info[0], philo->time_to_die);
	print_action(&philo->p_info[0], DIE);
	is_time_to_finish(&philo->p_info[0], 1);
	return (0);
}

void	*start_eating(void *ptr)
{
	t_info	*copy;

	copy = (t_info *) ptr;
	while (1)
	{
		if (copy->philo->n_philos == 1)
		{
			lone_philosopher(copy->philo);
			return (0);
		}
		if (is_time_to_finish(copy, 0))
			return (0);
		time_to_eat(copy);
		print_action(copy, SLEEP);
		advance_time(copy, copy->philo->time_to_sleep);
		print_action(copy, THINK);
		if (copy->philo->n_philos % 2 != 0
			&& copy->philo->n_philos <= 127)
			advance_time(copy, copy->philo->time_to_eat);
	}
	return (0);
}
