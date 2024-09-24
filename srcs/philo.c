/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cacarval <cacarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:44:57 by cacarval          #+#    #+#             */
/*   Updated: 2024/08/20 14:45:53 by cacarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_threads(t_philo *philo)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&philo->start_lock);
	while (++i < philo->n_philos)
	{
		if (pthread_create(&philo->p_info[i].thread, NULL,
				start_eating, &philo->p_info[i]))
			exit_error(philo, RED"Couldn't create thread"RESET, 3);
	}
	philo->start_time = get_time();
	i = -1;
	while(++i < philo->n_philos)
		philo->p_info[i].last_eat = philo->start_time;
	pthread_mutex_unlock(&philo->start_lock);
	return (0);
}

void	start_locks(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->n_philos)
	{
		if (pthread_mutex_init(&philo->fork_lock[i], NULL))
			exit_error(philo, RED"Couldn't init fork mutex"RESET, 2);
	}
	if (pthread_mutex_init(&philo->start_lock, NULL))
		exit_error(philo, RED"Couldn't init print mutex"RESET, 2);
	if (pthread_mutex_init(&philo->print_lock, NULL))
		exit_error(philo, RED"Couldn't init print mutex"RESET, 2);
	if (pthread_mutex_init(&philo->eat_lock, NULL))
		exit_error(philo, RED"Couldn't init eat mutex"RESET, 2);
	if (pthread_mutex_init(&philo->finish_lock, NULL))
		exit_error(philo, RED"Couldn't init finish mutex"RESET, 2);
}

void	call_philosophers(t_philo *philo)
{
	int	i;

	i = -1;
	philo->p_info = malloc(sizeof(t_philo) * philo->n_philos);
	philo->fork_lock = malloc(sizeof(pthread_mutex_t) * philo->n_philos);
	if (!philo->p_info || !philo->fork_lock)
		exit_error(philo, RED"Couldn't create the philosophers"RESET, 1);
	while (++i < philo->n_philos)
	{
		philo->start_time = get_time();
		philo->p_info[i].id = i + 1;
		philo->p_info[i].l_fork = i;
		philo->p_info[i].r_fork = (i + 1) % philo->n_philos;
		philo->p_info[i].eat_count = 0;
		philo->p_info[i].last_eat = philo->start_time;
		philo->p_info[i].philo = philo;
	}
}

void	set_table(t_philo *philo, int ac, char **argv)
{
	if (ac < 5 || ac > 6)
		exit_error(NULL, RED"Wrong number of arguments"RESET, 0);
	philo->n_philos = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (ac == 6)
		philo->times_to_eat = ft_atoi(argv[5]);
	else
		philo->times_to_eat = -1;
	if ((philo->n_philos < 1 || philo->time_to_die < 1
			|| philo->time_to_eat < 1 || philo->time_to_sleep < 1)
		|| (ac == 6 && philo->times_to_eat < 1))
		exit_error(NULL, RED"Wrong input"RESET, 0);
	philo->finish_eating = 0;
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	set_table(&philo, argc, argv);
	call_philosophers(&philo);
	start_locks(&philo);
	start_threads(&philo);
	dinner_monitor(&philo);
}
