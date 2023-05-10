/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adnane <adnane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:59:14 by adnane            #+#    #+#             */
/*   Updated: 2023/05/10 17:35:21 by adnane           ###   ########.fr       */
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
			pthread_mutex_lock(thread->info[i].last_meal_mutex);
			curr = get_period(thread->very_start) - thread->info[i].last_meal;
			pthread_mutex_unlock(thread->info[i].last_meal_mutex);
			if (curr >= thread->time_to_die)
			{
				print_message(thread->very_start, thread->info[i].id + 1,
					"died", thread->info->shared_mutex);
				exit(0);
			}
		}
		usleep(1000);
	}
}

void	*eat_counter(void *arg)
{
	t_thread	*thread;
	int			i;
	int			done_eating_count;

	thread = (t_thread *)arg;
	done_eating_count = 0;
	while (1)
	{
		done_eating_count = 0;
		i = -1;
		while (++i < thread->num_philo)
		{
			pthread_mutex_lock(thread->info[i].eating_count_mutex);
			if (thread->info[i].eating_count >= thread->e_c)
				done_eating_count++;
			if (done_eating_count == thread->num_philo)
			{
				pthread_mutex_lock(&thread->shared_print);
				printf("|%lld| All philosophers have eaten enough.\n",
					get_period(thread->very_start));
				pthread_mutex_unlock(&thread->shared_print);
				exit (0);
			}
			pthread_mutex_unlock(thread->info[i].eating_count_mutex);
		}
		usleep(1000);
	}
}

void	create_threads(t_thread thread, char **argv)
{
	int	i;

	set_thread_params(&thread, argv);
	i = -1;
	while (++i < thread.num_philo)
	{
		pthread_mutex_init(&thread.forks[i], NULL);
		pthread_mutex_init(&thread.lm_mutex[i], NULL);
		pthread_mutex_init(&thread.ec_mutex[i], NULL);
	}
	pthread_mutex_init(&thread.shared_print, NULL);
	create_philosophers(&thread);
	create_death_eat_checker(&thread);
	join_philosophers(&thread);
	destroy_mutexes(&thread);
}

int	main(int argc, char **argv)
{
	t_thread	thread;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: ./philo <number_of_philosophers> ");
		printf("<time_to_die> <time_to_eat> <time_to_sleep>");
		printf("[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	if (!is_num(argv) || !is_valid_int(argv[2])
		|| !is_valid_int(argv[4])
		|| !is_valid_int(argv[3])
		|| !is_valid_int(argv[1])
		|| (argv[5] && !is_valid_int(argv[5])))
	{
		printf("All arguments must be positive integers.\n");
		return (1);
	}
	thread.num_philo = atoi(argv[1]);
	thread.philosophers = malloc(thread.num_philo * sizeof(pthread_t));
	thread.forks = malloc(thread.num_philo * sizeof(pthread_mutex_t));
	thread.lm_mutex = malloc(thread.num_philo * sizeof(pthread_mutex_t));
	thread.ec_mutex = malloc(thread.num_philo * sizeof(pthread_mutex_t));
	thread.info = malloc(thread.num_philo * sizeof(t_philosopher_info));
	create_threads(thread, argv);
	free_all(&thread);
	return (0);
}
