/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adnane <adnane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 22:09:11 by adnane            #+#    #+#             */
/*   Updated: 2023/05/08 17:36:55 by adnane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher(void *arg)
{
	t_philosopher_info	*info;

	info = (t_philosopher_info *)arg;
	if (info->id % 2 == 0)
		usleep(info->thread_info->time_to_eat * 1000);
	while (1)
	{
		pick_up_forks(info);
		eat(info);
		put_down_forks(info);
		sleep_and_think(info);
	}
}

void	pick_up_forks(t_philosopher_info *info)
{
	pthread_mutex_lock(info->left_fork);
	print_message(info->thread_info->very_start, info->id,
		"picked up the left fork.", info->shared_mutex);
	pthread_mutex_lock(info->right_fork);
	print_message(info->thread_info->very_start, info->id,
		"picked up the right fork.", info->shared_mutex);
}

void	eat(t_philosopher_info *info)
{
	print_message(info->thread_info->very_start, info->id,
		"is eating...", info->shared_mutex);
	info->ate = 1;
	usleep(info->thread_info->time_to_eat * 1000);
	info->last_meal = get_period(info->thread_info->very_start);
	if (info->thread_info->e_c && info->eating_count < info->thread_info->e_c)
		info->eating_count++;
	info->ate = 0;
}

void	put_down_forks(t_philosopher_info *info)
{
	pthread_mutex_unlock(info->right_fork);
	print_message(info->thread_info->very_start, info->id,
		"put down the right fork.", info->shared_mutex);
	pthread_mutex_unlock(info->left_fork);
	print_message(info->thread_info->very_start, info->id,
		"put down the left fork.", info->shared_mutex);
}

void	sleep_and_think(t_philosopher_info *info)
{
	print_message(info->thread_info->very_start, info->id,
		"is sleeping...", info->shared_mutex);
	usleep(info->thread_info->time_to_sleep * 1000);
	print_message(info->thread_info->very_start, info->id,
		"is thinking...", info->shared_mutex);
}
