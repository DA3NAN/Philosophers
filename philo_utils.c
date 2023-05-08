/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adnane <adnane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 22:09:11 by adnane            #+#    #+#             */
/*   Updated: 2023/05/08 14:11:46 by adnane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	tmp;
	long long		curr_time;

	gettimeofday(&tmp, NULL);
	curr_time = (tmp.tv_sec * 1000) + (tmp.tv_usec / 1000);
	return (curr_time);
}

long long	get_period(long long start_time)
{
	return (get_time() - start_time);
}

void	print_message(long long very_start, int id,
			const char *message, pthread_mutex_t *shared_mutex)
{
	pthread_mutex_lock(shared_mutex);
	printf("|%lld| Philosopher %d %s\n", get_period(very_start), id, message);
	pthread_mutex_unlock(shared_mutex);
}

void	*philosopher(void *arg)
{
	t_philosopher_info	*info;

	info = (t_philosopher_info *)arg;
	if (info->id % 2 == 0)
		usleep(info->thread_info->time_to_eat * 1000);
	while (1)
	{
		pthread_mutex_lock(info->left_fork);
		print_message(info->thread_info->very_start, info->id,
			"picked up the left fork.", info->shared_mutex);
		pthread_mutex_lock(info->right_fork);
		print_message(info->thread_info->very_start, info->id,
			"picked up the right fork.", info->shared_mutex);
		print_message(info->thread_info->very_start, info->id,
			"is eating...", info->shared_mutex);
		info->ate = 1;
		usleep(info->thread_info->time_to_eat * 1000);
		info->last_meal = get_period(info->thread_info->very_start);
		info->ate = 0;
		pthread_mutex_unlock(info->right_fork);
		print_message(info->thread_info->very_start, info->id,
			"put down the right fork.", info->shared_mutex);
		pthread_mutex_unlock(info->left_fork);
		print_message(info->thread_info->very_start, info->id,
			"put down the left fork.", info->shared_mutex);
		print_message(info->thread_info->very_start, info->id,
			"is sleeping...", info->shared_mutex);
		usleep(info->thread_info->time_to_sleep * 1000);
		print_message(info->thread_info->very_start, info->id,
			"is thinking...", info->shared_mutex);
	}
}
