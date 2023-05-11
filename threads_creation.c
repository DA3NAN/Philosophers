/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_creation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adnane <adnane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:44:57 by adnane            #+#    #+#             */
/*   Updated: 2023/05/11 17:41:44 by adnane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_philosopher(t_thread *thread, int i)
{
	thread->info[i].id = i;
	thread->info[i].eating_count_mutex = &thread->ec_mutex[i];
	thread->info[i].last_meal_mutex = &thread->lm_mutex[i];
	thread->info[i].left_fork = &thread->forks[i];
	thread->info[i].right_fork = &thread->forks[(i + 1) % thread->num_philo];
	thread->info[i].shared_mutex = &thread->shared_print;
	thread->info[i].last_meal = get_period(thread->very_start);
	thread->info[i].thread_info = thread;
	thread->info[i].eating_count = 0;
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

void	create_death_eat_checker(t_thread *thread)
{
	pthread_t	death_checker_thread;
	pthread_t	eat_count;

	pthread_create(&death_checker_thread, NULL, death_checker, thread);
	if (thread->e_c != -1)
		pthread_create(&eat_count, NULL, eat_counter, thread);
	pthread_join(death_checker_thread, NULL);
	if (thread->e_c != -1)
		pthread_join(eat_count, NULL);
}

void	join_philosophers(t_thread *thread)
{
	int	i;

	i = -1;
	while (++i < thread->num_philo)
		pthread_join(thread->philosophers[i], NULL);
}

void	destroy_mutexes(t_thread *thread)
{
	int	i;

	pthread_mutex_destroy(&thread->shared_print);
	i = -1;
	while (++i < thread->num_philo)
	{
		pthread_mutex_destroy(&thread->forks[i]);
		pthread_mutex_destroy(&thread->lm_mutex[i]);
		pthread_mutex_destroy(&thread->ec_mutex[i]);
	}
}
