/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adnane <adnane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:59:14 by adnane            #+#    #+#             */
/*   Updated: 2023/05/08 14:15:05 by adnane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_death(t_thread thread)
{
	int			i;
	long long	curr;

	i = 0;
	while (1)
	{
		if (i == thread.num_philo)
			i = 0;
		curr = get_period(thread.very_start);
		if (thread.info[i].ate == 1)
			curr = 0;
		if (curr - thread.info[i].last_meal >= thread.time_to_die)
		{
			print_message(thread.very_start, thread.info[i].id,
				"is dead", thread.info->shared_mutex);
			exit(0);
		}
		i++;
	}
}

void	create_threads(t_thread thread, char **argv)
{
	int			i;

	thread.very_start = get_time();
	thread.time_to_die = atoi(argv[2]);
	thread.time_to_sleep = atoi(argv[4]);
	thread.time_to_eat = atoi(argv[3]);
	i = -1;
	while (++i < thread.num_philo)
	{
		thread.info[i].id = i;
		thread.info[i].left_fork = &thread.forks[i];
		thread.info[i].right_fork = &thread.forks[(i + 1) % thread.num_philo];
		thread.info[i].shared_mutex = &thread.shared_print;
		thread.info[i].last_meal = get_period(thread.very_start);
		thread.info[i].thread_info = &thread;
		thread.info[i].ate = 0;
		pthread_create(&thread.philosophers[i],
			NULL, philosopher, &thread.info[i]);
	}
	check_death(thread);
}

int	main(int argc, char **argv)
{
	t_thread	thread;
	int			i;

	if (argc != 5)
	{
		printf("Usage: ./philo <number_of_philosophers> ");
		printf("<time_to_die> <time_to_eat> <time_to_sleep>\n");
		return (1);
	}
	thread.num_philo = atoi(argv[1]);
	thread.philosophers = malloc(thread.num_philo * sizeof(pthread_t));
	thread.forks = malloc(thread.num_philo * sizeof(pthread_mutex_t));
	thread.info = malloc(thread.num_philo * sizeof(t_philosopher_info));
	pthread_mutex_init(&thread.shared_print, NULL);
	i = -1;
	while (++i < thread.num_philo)
		pthread_mutex_init(&thread.forks[i], NULL);
	create_threads(thread, argv);
	i = -1;
	while (++i < thread.num_philo)
		pthread_join(thread.philosophers[i], NULL);
	i = -1;
	while (++i < thread.num_philo)
		pthread_mutex_destroy(&thread.forks[i]);
	return (0);
}
