/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralena <ralena@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:36:41 by ralena            #+#    #+#             */
/*   Updated: 2022/01/23 16:49:39 by ralena           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_parameters(unsigned long time_to_output, int num, char *str)
{
	printf("%lu %d %s", time_to_output, num, str);
	return (0);
}

int	print_philosopher_state(int flag, t_philo *philo)
{
	if (philo->data->died && flag != 2)
		return (1);
	if (flag == 10)
		return (print_parameters((unsigned long)(timer() - \
		philo->data->time_start), philo->num_philo, "has taken a fork\n"));
	if (flag == 11)
		return (print_parameters((unsigned long)(timer() - \
		philo->data->time_start), philo->num_philo, "is eating\n"));
	if (flag == 12)
		return (print_parameters((unsigned long)(timer() - \
		philo->data->time_start), philo->num_philo, "is sleeping\n"));
	if (flag == 13)
		return (print_parameters((unsigned long)(timer() - \
		philo->data->time_start), philo->num_philo, "is thinking\n"));
	if (flag == 2)
		return (print_parameters((unsigned long)(timer() - \
		philo->data->time_start), philo->num_philo, "died\n"));
	return (0);
}

unsigned long	timer(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	error(int error_type)
{
	if (error_type == ERROR_NUM_ARG)
		printf("Error: wrong number of arguments\n");
	else if (error_type == ERROR_ARG)
		printf("Error: wrong arguments\n");
	else if (error_type == ERROR_NUM_PHILO)
		printf("Error: wrong number of philosophers\n");
	return (1);
}

int	ft_atoi(char *nptr)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\n'
		|| *nptr == '\r' || *nptr == '\v' || *nptr == '\f')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + *nptr - 48;
		nptr++;
	}
	return (result * sign);
}
