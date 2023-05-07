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

void print_message(long long very_start, int id, const char* message, pthread_mutex_t* shared_mutex)
{
    pthread_mutex_lock(shared_mutex);
    printf("|%lld|, Philosopher %d %s\n", get_period(very_start), id, message);
    pthread_mutex_unlock(shared_mutex);
}

void *philosopher(void* arg) {
    philosopher_info*   info;
    pthread_mutex_t*    left_fork;
    pthread_mutex_t*    right_fork;
    pthread_mutex_t*    shared_mutex;
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
    shared_mutex = info->shared_mutex;
	time_to_die = info->time_to_die;
	time_to_sleep = info->time_to_sleep;
	time_to_eat = info->time_to_eat;
    very_start = get_time();
    while (1) {
        print_message(very_start, id, "is thinking...", shared_mutex);
        pthread_mutex_lock(left_fork);
        print_message(very_start, id, "picked up the left fork.", shared_mutex);
        pthread_mutex_lock(right_fork);
        print_message(very_start, id, "picked up the right fork.", shared_mutex);
        print_message(very_start, id, "is eating...", shared_mutex);
        start_time = get_time();
        while (1) {
            end_time = get_time();
            if (end_time - start_time >= time_to_die) {
                print_message(very_start, id, "has died!", shared_mutex);
                exit(0);
            }
            if (end_time - start_time >= time_to_eat) {
                break;
            }
            //Sleep for a short amount of time to reduce CPU usage
            // usleep(1000);
        }
        pthread_mutex_unlock(right_fork);
        print_message(very_start, id, "put down the right fork.", shared_mutex);
        pthread_mutex_unlock(left_fork);
        print_message(very_start, id, "put down the left fork.", shared_mutex);
        print_message(very_start, id, "is sleeping...", shared_mutex);
        usleep(time_to_sleep * 1000);
    }
}

int main(int argc, char** argv) {
    int num_philosophers;
    pthread_t *philosophers;
    pthread_mutex_t *forks;
    pthread_mutex_t shared_print;
    philosopher_info *info;

    if (argc != 5) {
        printf("Usage: ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep>\n");
        return 1;
    }
    num_philosophers = atoi(argv[1]);
    philosophers = malloc(num_philosophers * sizeof(pthread_t));
    forks = malloc(num_philosophers * sizeof(pthread_mutex_t));
    info = malloc(num_philosophers * sizeof(philosopher_info));
    // Initialize the mutexes for the forks, shared_print
    pthread_mutex_init(&shared_print, NULL);
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
        info[i].shared_mutex = &shared_print;
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
