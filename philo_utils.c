/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adnane <adnane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 22:09:11 by adnane            #+#    #+#             */
/*   Updated: 2023/05/10 17:01:58 by adnane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher(void *arg)
{
	t_philosopher_info	*info;

	info = (t_philosopher_info *)arg;
	if ((info->id + 1) % 2 == 0)
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
	int id_left = info->id;
    int id_right = (info->id + 1) % info->thread_info->num_philo;

    // Acquire locks in ascending order of IDs
    if (id_left < id_right) {
        pthread_mutex_lock(info->left_fork);
        print_message(info->thread_info->very_start, info->id + 1,
            "picked up the left fork.", info->shared_mutex);
        pthread_mutex_lock(info->right_fork);
        print_message(info->thread_info->very_start, info->id + 1,
            "picked up the right fork.", info->shared_mutex);
    } else {
        pthread_mutex_lock(info->right_fork);
        print_message(info->thread_info->very_start, info->id + 1,
            "picked up the right fork.", info->shared_mutex);
        pthread_mutex_lock(info->left_fork);
        print_message(info->thread_info->very_start, info->id + 1,
            "picked up the left fork.", info->shared_mutex);
    }
}

void	eat(t_philosopher_info *info)
{
	print_message(info->thread_info->very_start, info->id + 1,
		"is eating...", info->shared_mutex);
	// info->ate = 1;
	pthread_mutex_lock(info->last_meal_mutex);
	info->last_meal = get_period(info->thread_info->very_start);
	pthread_mutex_unlock(info->last_meal_mutex);
	usleep(info->thread_info->time_to_eat * 1000);
	pthread_mutex_lock(info->eating_count_mutex);
	if (info->thread_info->e_c != -1 && info->eating_count < info->thread_info->e_c)
		info->eating_count++;
	pthread_mutex_unlock(info->eating_count_mutex);
	// info->ate = 0;
}

void	put_down_forks(t_philosopher_info *info)
{
	pthread_mutex_unlock(info->right_fork);
	print_message(info->thread_info->very_start, info->id + 1,
		"put down the right fork.", info->shared_mutex);
	pthread_mutex_unlock(info->left_fork);
	print_message(info->thread_info->very_start, info->id + 1,
		"put down the left fork.", info->shared_mutex);
}

void	sleep_and_think(t_philosopher_info *info)
{
	print_message(info->thread_info->very_start, info->id + 1,
		"is sleeping...", info->shared_mutex);
	usleep(info->thread_info->time_to_sleep * 1000);
	print_message(info->thread_info->very_start, info->id + 1,
		"is thinking...", info->shared_mutex);
}
