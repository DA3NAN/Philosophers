/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adnane <adnane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:59:14 by adnane            #+#    #+#             */
/*   Updated: 2023/03/27 17:04:26 by adnane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long    get_time()
{
    struct timeval tmp;
    long long    curr_time;
    
    gettimeofday(&tmp, NULL);
    curr_time = (tmp.tv_sec * 1000) + (tmp.tv_usec / 1000);
    return(curr_time);
}

long long    get_period(long long start_time)
{
    struct timeval tmp;
    long long    curr_time;
    
    gettimeofday(&tmp, NULL);
    curr_time = (tmp.tv_sec * 1000) + (tmp.tv_usec / 1000);
    return(curr_time - start_time);
}

void *philosopher(void* arg) {
    philosopher_info* info;
    pthread_mutex_t* left_fork;
    pthread_mutex_t* right_fork;
    int id;
    int time_to_die;
    int time_to_sleep;
    int time_to_eat;
    long long very_start;
    long long start_time;
    long long end_time;

	info = (philosopher_info*)arg;
	id = info->id;
	left_fork = info->left_fork;
	right_fork = info->right_fork;
	time_to_die = info->time_to_die;
	time_to_sleep = info->time_to_sleep;
	time_to_eat = info->time_to_eat;
    very_start = get_time();
    while (1) {
        printf("|%lld|, Philosopher %d is thinking...\n", get_period(very_start), id);
        pthread_mutex_lock(left_fork);
        printf("|%lld|, Philosopher %d picked up the left fork.\n", get_period(very_start), id);
        pthread_mutex_lock(right_fork);
        printf("|%lld|, Philosopher %d picked up the right fork.\n", get_period(very_start), id);
        printf("|%lld|, Philosopher %d is eating...\n", get_period(very_start), id);
        start_time = get_time();
        while (1) {
            end_time = get_time();
            if (end_time - start_time >= time_to_die) {
                printf("|%lld|, Philosopher %d has died!\n", get_period(very_start), id);
                exit(0);
            }
            if (end_time - start_time >= time_to_eat) {
                break;
            }
            //Sleep for a short amount of time to reduce CPU usage
            // usleep(1000);
        }
        pthread_mutex_unlock(right_fork);
        printf("|%lld|, Philosopher %d put down the right fork.\n", get_period(very_start), id);
        pthread_mutex_unlock(left_fork);
        printf("|%lld|, Philosopher %d put down the left fork.\n", get_period(very_start), id);
        printf("|%lld|, Philosopher %d is sleeping...\n", get_period(very_start), id);
        usleep(time_to_sleep * 1000);
    }
}

int main(int argc, char** argv) {
    int num_philosophers;
    pthread_t *philosophers;
    pthread_mutex_t *forks;
    philosopher_info *info;

    if (argc != 5) {
        printf("Usage: ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep>\n");
        return 1;
    }
    num_philosophers = atoi(argv[1]);
    philosophers = malloc(num_philosophers * sizeof(pthread_t));
    forks = malloc(num_philosophers * sizeof(pthread_mutex_t));
    info = malloc(num_philosophers * sizeof(philosopher_info));
    // Initialize the mutexes for the forks
    for (int i = 0; i < num_philosophers; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }
    // Initialize the philosopher info
    for (int i = 0; i < num_philosophers; i++) {
        info[i].id = i;
        info[i].left_fork = &forks[i];
        info[i].right_fork = &forks[(i + 1) % num_philosophers];
        info[i].time_to_die = atoi(argv[2]);
        info[i].time_to_sleep = atoi(argv[4]);
        info[i].time_to_eat = atoi(argv[3]);

        pthread_create(&philosophers[i], NULL, philosopher, &info[i]);
    }
    // Wait for the philosophers to finish
    for (int i = 0; i < num_philosophers; i++) {
        pthread_join(philosophers[i], NULL);
    }
    // Destroy the mutexes
    for (int i = 0; i < num_philosophers; i++) {
        pthread_mutex_destroy(&forks[i]);
    }
    return 0;
}
