/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:33:07 by cacarval          #+#    #+#             */
/*   Updated: 2023/09/28 14:08:21 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	advance_time(t_info *copy, long long stop)
{
	long long	begin;

	begin = get_time();
	while (!is_time_to_finish(copy, 0) && (get_time() - begin) < stop)
		usleep(100);
}

void	exit_error(t_philo *philo, char *msg, int n)
{
	printf(RED"Error: %s\n"RESET, msg);
	if (n == 1)
		clean_table(philo);
	if (n == 2)
		destroy_padlocks(philo);
	if (n == 3)
		finish_dinner(philo);
	exit(1);
}

void	print_action(t_info *copy, const char *message)
{
	long long	time;

	pthread_mutex_lock(&copy->philo->print_lock);
	if (!is_time_to_finish(copy, 0))
	{
		time = get_time() - copy->philo->start_time;
		printf("[%lld] %d %s\n", time, copy->id, message);
	}
	pthread_mutex_unlock(&copy->philo->print_lock);
	if (message[0] == 'f' && copy->philo->times_to_eat > 1)
		printf(GREEN"Philosophers ate %i times\n"RESET,
			copy->philo->times_to_eat);
	if (message[0] == 'f' && copy->philo->times_to_eat == 1)
		printf(GREEN"Philosophers ate %i time\n"RESET, 
			copy->philo->times_to_eat);
}

long long	get_time(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return ((timeval.tv_sec * 1000) + (timeval.tv_usec / 1000));
}

int	ft_atoi(const char *str)
{
	int	a;
	int	i;

	a = 0;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (0);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		a = (a * 10) + (str[i] - '0');
		i++;
	}
	if (str[i] < 0 || str[i] > 9)
		return (-1);
	return (a);
}
