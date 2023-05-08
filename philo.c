/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adnane <adnane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:59:14 by adnane            #+#    #+#             */
/*   Updated: 2023/05/08 16:02:32 by adnane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*death_checker(void *arg)
{
	t_thread	*thread;
	int			i;
	long long	curr;

	thread = (t_thread *)arg;
	while (1)
	{
		i = -1;
		while (++i < thread->num_philo)
		{
			curr = get_period(thread->very_start);
			if (thread->info[i].ate == 1)
				curr = 0;
			if (curr - thread->info[i].last_meal >= thread->time_to_die)
			{
				print_message(thread->very_start, thread->info[i].id,
					"is dead", thread->info->shared_mutex);
				exit(0);
			}
		}
		usleep(10000);
	}
}

void	create_threads(t_thread thread, char **argv)
{
	int	i;

	set_thread_params(&thread, argv);
	if (!is_valid_int(thread.time_to_die) || !is_valid_int(thread.time_to_sleep)
		|| !is_valid_int(thread.time_to_eat) || !is_valid_int(thread.num_philo))
	{
		printf("All arguments must be positive integers.\n");
		return ;
	}
	i = -1;
	while (++i < thread.num_philo)
		pthread_mutex_init(&thread.forks[i], NULL);
	pthread_mutex_init(&thread.shared_print, NULL);
	create_philosophers(&thread);
	create_death_checker(&thread);
	join_destroy_philosophers(&thread);
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
	free(thread.philosophers);
	free(thread.forks);
	free(thread.info);
	return (0);
}
