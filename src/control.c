/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkocan <hkocan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:13:49 by hkocan            #+#    #+#             */
/*   Updated: 2024/06/10 16:31:56 by hkocan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool control_dead(t_table *table)
{
	pthread_mutex_lock(&table->is_anyone_dead);
	if (table->dead == true)
	{
		pthread_mutex_unlock(&table->is_anyone_dead);
		return (true);
	}
	else
	{
		pthread_mutex_unlock(&table->is_anyone_dead);
		return (false);
	}
}
