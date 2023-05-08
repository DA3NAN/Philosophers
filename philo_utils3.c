/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adnane <adnane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:44:57 by adnane            #+#    #+#             */
/*   Updated: 2023/05/08 15:56:04 by adnane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_thread_params(t_thread *thread, char **argv)
{
	thread->very_start = get_period(0);
	thread->time_to_die = atoi(argv[2]);
	thread->time_to_sleep = atoi(argv[4]);
	thread->time_to_eat = atoi(argv[3]);
}

void	create_philosopher(t_thread *thread, int i)
{
	thread->info[i].id = i;
	thread->info[i].left_fork = &thread->forks[i];
	thread->info[i].right_fork = &thread->forks[(i + 1) % thread->num_philo];
	thread->info[i].shared_mutex = &thread->shared_print;
	thread->info[i].last_meal = get_period(thread->very_start);
	thread->info[i].thread_info = thread;
	thread->info[i].ate = 0;
	pthread_create(&thread->philosophers[i],
		NULL, philosopher, &thread->info[i]);
}

void	create_philosophers(t_thread *thread)
{
	int	i;

	i = -1;
	while (++i < thread->num_philo)
		create_philosopher(thread, i);
}

void	create_death_checker(t_thread *thread)
{
	pthread_t	death_checker_thread;

	pthread_create(&death_checker_thread, NULL, death_checker, thread);
	pthread_join(death_checker_thread, NULL);
}

void	join_destroy_philosophers(t_thread *thread)
{
	int	i;

	i = -1;
	while (++i < thread->num_philo)
		pthread_join(thread->philosophers[i], NULL);
	pthread_mutex_destroy(&thread->shared_print);
	i = -1;
	while (++i < thread->num_philo)
		pthread_mutex_destroy(&thread->forks[i]);
}