/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_lifecycle.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:36:38 by ralena            #+#    #+#             */
/*   Updated: 2022/01/23 16:46:22 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	start_threads(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->number_of_philosophers)
	{
		pthread_create(&state->philo[i].thread, NULL, \
		(void *)&threads_life_support, &state->philo[i]);
		i += 2;
	}
	usleep(1000);
	i = 1;
	while (i < state->number_of_philosophers)
	{
		pthread_create(&state->philo[i].thread, NULL, \
		(void *)&threads_life_support, &state->philo[i]);
		i += 2;
	}
}

int	threads_tracking(t_state *state)
{
	int				i;
	unsigned long	t;

	while (1)
	{
		i = 0;
		while (i < state->number_of_philosophers)
		{
			if (state->eat_philo == state->number_of_philosophers)
				return (3);
			t = timer();
			if (t - state->philo[i].last_eat_time >= \
			(unsigned long)state->time_to_die)
			{
				state->died = 1;
				print_philosopher_state(2, &state->philo[i]);
				return (2);
			}
			i++;
		}
		usleep(1000);
	}
	return (1);
}

void	threads_join(t_state *state)
{
	int	i;

	i = 0;
	while (i < state->number_of_philosophers)
	{
		pthread_join(state->philo[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < state->number_of_philosophers)
	{
		pthread_mutex_destroy(&state->fork[i]);
		i++;
	}
}

int	threads_life_support_additional(t_philo *philo)
{
	unsigned long	time;

	if (philo->data->number_of_philosophers == 1)
		return (1);
	pthread_mutex_lock(&philo->data->fork[philo->right_fork]);
	if (print_philosopher_state(10, philo) == 1)
	{
		pthread_mutex_unlock(&philo->data->fork[philo->left_fork]);
		pthread_mutex_unlock(&philo->data->fork[philo->right_fork]);
		return (1);
	}
	if (print_philosopher_state(11, philo) == 1)
	{
		pthread_mutex_unlock(&philo->data->fork[philo->left_fork]);
		pthread_mutex_unlock(&philo->data->fork[philo->right_fork]);
		return (1);
	}
	time = timer();
	while (timer() < time + (unsigned long)philo->data->time_to_eat)
		usleep(100);
	philo->last_eat_time = timer();
	philo->eat_time++;
	pthread_mutex_unlock(&philo->data->fork[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->fork[philo->right_fork]);
	return (0);
}

void	*threads_life_support(t_philo *philo)
{
	unsigned long	time;

	while (philo->eat_time != philo->data->number_of_times_must_eat
		&& !philo->data->died)
	{
		pthread_mutex_lock(&philo->data->fork[philo->left_fork]);
		if (print_philosopher_state(10, philo) == 1)
		{	
			pthread_mutex_unlock(&philo->data->fork[philo->left_fork]);
			return (NULL);
		}
		if (threads_life_support_additional(philo) == 1)
			return (NULL);
		if (philo->eat_time == philo->data->number_of_times_must_eat)
			break ;
		if (print_philosopher_state(12, philo))
			return (NULL);
		time = timer();
		while (timer() < time + (unsigned long)philo->data->time_to_sleep)
			usleep(100);
		if (print_philosopher_state(13, philo))
			return (NULL);
	}
	philo->data->eat_philo++;
	return (NULL);
}
