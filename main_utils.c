/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adnane <adnane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:04:53 by adnane            #+#    #+#             */
/*   Updated: 2023/05/11 17:42:27 by adnane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	allocate(t_thread *thread)
{
	thread->philosophers = malloc(thread->num_philo * sizeof(pthread_t));
	thread->forks = malloc(thread->num_philo * sizeof(pthread_mutex_t));
	thread->lm_mutex = malloc(thread->num_philo * sizeof(pthread_mutex_t));
	thread->ec_mutex = malloc(thread->num_philo * sizeof(pthread_mutex_t));
	thread->info = malloc(thread->num_philo * sizeof(t_philosopher_info));
}

void	initialize_mutexes(t_thread thread)
{
	int	i;

	i = -1;
	while (++i < thread.num_philo)
	{
		pthread_mutex_init(&thread.forks[i], NULL);
		pthread_mutex_init(&thread.lm_mutex[i], NULL);
		pthread_mutex_init(&thread.ec_mutex[i], NULL);
	}
	pthread_mutex_init(&thread.shared_print, NULL);
}

void	set_thread_params(t_thread *thread, char **argv)
{
	thread->very_start = get_period(0);
	thread->time_to_die = atoi(argv[2]);
	thread->time_to_sleep = atoi(argv[4]);
	thread->time_to_eat = atoi(argv[3]);
	thread->e_c = -1;
	if (argv[5])
		thread->e_c = atoi(argv[5]);
}

void	create_threads(t_thread thread, char **argv)
{
	set_thread_params(&thread, argv);
	create_philosophers(&thread);
	create_death_eat_checker(&thread);
	join_philosophers(&thread);
	destroy_mutexes(&thread);
}

void	free_all(t_thread *thread)
{
	free(thread->philosophers);
	free(thread->forks);
	free(thread->info);
	free(thread->lm_mutex);
	free(thread->ec_mutex);
}
