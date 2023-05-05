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

void *philosopher(void* arg) {
    philosopher_info* info = (philosopher_info*)arg;
    int id = info->id;
    pthread_mutex_t* left_fork = info->left_fork;
    pthread_mutex_t* right_fork = info->right_fork;
    int time_to_die = info->time_to_die;
    int time_to_sleep = info->time_to_sleep;
    int time_to_eat = info->time_to_eat;

    time_t start_time;
    time_t end_time;

    while (1) {
        printf("Philosopher %d is thinking...\n", id);

        pthread_mutex_lock(left_fork);
        printf("Philosopher %d picked up the left fork.\n", id);

        pthread_mutex_lock(right_fork);
        printf("Philosopher %d picked up the right fork.\n", id);

        printf("Philosopher %d is eating...\n", id);
        time(&start_time);

        while (1) {
            time(&end_time);
            if (end_time - start_time >= time_to_die / 1000) {
                printf("Elapsed : %ld, Philosopher %d has died!\n", (end_time - start_time) * 1000, id);
                exit(0);
            }

            if (end_time - start_time >= time_to_eat / 1000) {
                break;
            }

            // Sleep for a short amount of time to reduce CPU usage
            // usleep(1000);
        }

        pthread_mutex_unlock(right_fork);
        printf("Philosopher %d put down the right fork.\n", id);

        pthread_mutex_unlock(left_fork);
        printf("Philosopher %d put down the left fork.\n", id);

        printf("Philosopher %d is sleeping...\n", id);
        usleep(time_to_sleep);
    }
}

int main(int argc, char** argv) {
    int num_philosophers = atoi(argv[1]);
    pthread_t philosophers[num_philosophers];
    pthread_mutex_t forks[num_philosophers];
    philosopher_info info[num_philosophers];

    if (argc != 5) {
        printf("Usage: ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep>\n");
        return 1;
    }

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
        info[i].time_to_sleep = atoi(argv[3]);
        info[i].time_to_eat = atoi(argv[4]);

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
