/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_and_initialization.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:36:35 by ralena            #+#    #+#             */
/*   Updated: 2022/01/23 16:46:22 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parse_arguments_to_state(int argc, char **argv, t_state *state)
{
	state->number_of_philosophers = ft_atoi(argv[1]);
	state->time_to_die = ft_atoi(argv[2]);
	state->time_to_eat = ft_atoi(argv[3]);
	state->time_to_sleep = ft_atoi(argv[4]);
	if (state->number_of_philosophers < 0 || state->time_to_die < 0
		|| state->time_to_eat < 0 || state->time_to_sleep < 0)
		return (error(ERROR_ARG));
	if (argc == 6)
	{
		state->number_of_times_must_eat = ft_atoi(argv[5]);
		if (state->number_of_times_must_eat < 0)
			return (error(ERROR_ARG));
	}
	else
		state->number_of_times_must_eat = -1;
	if (state->number_of_philosophers > 200)
		return (error(ERROR_NUM_PHILO));
	state->eat_philo = 0;
	state->died = 0;
	return (0);
}

int	init_state(t_state *state)
{
	int	i;

	state->philo = malloc(sizeof(t_philo) * state->number_of_philosophers);
	if (!state->philo)
		return (1);
	state->fork = malloc(sizeof(pthread_mutex_t)
			* state->number_of_philosophers);
	if (!state->fork)
	{
		free(state->philo);
		return (1);
	}
	i = 0;
	while (i < state->number_of_philosophers)
	{
		pthread_mutex_init(&state->fork[i], NULL);
		init_philo(state, i);
		i++;
	}
	return (0);
}

void	init_philo(t_state *state, int i)
{
	state->philo[i].num_philo = i + 1;
	state->philo[i].left_fork = i;
	if (i == state->number_of_philosophers - 1)
		state->philo[i].right_fork = 0;
	else
		state->philo[i].right_fork = i + 1;
	state->philo[i].data = state;
	state->philo[i].eat_time = 0;
	state->philo[i].last_eat_time = timer();
}
