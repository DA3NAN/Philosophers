/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_threads.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adnane <adnane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 16:55:28 by adnane            #+#    #+#             */
/*   Updated: 2023/05/11 17:34:31 by adnane           ###   ########.fr       */
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

static void	check_for_count(t_thread *thread, int done_eating_count)
{
	int	i;

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
}

void	*eat_counter(void *arg)
{
	t_thread	*thread;
	int			done_eating_count;

	thread = (t_thread *)arg;
	done_eating_count = 0;
	while (1)
	{
		done_eating_count = 0;
		check_for_count(thread, done_eating_count);
		usleep(1000);
	}
}
