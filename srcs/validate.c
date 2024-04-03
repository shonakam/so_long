/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 00:32:24 by shonakam          #+#    #+#             */
/*   Updated: 2024/04/04 04:13:09 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	init_validator(t_validator *validator, t_data *data)
{
	size_t	index;

	validator->now = current_locate(data);
	validator->collectbles = 0;
	validator->goal = 0;
	validator->mark = (size_t *)malloc(sizeof(size_t) * (data->w * data->h));
	if (!validator->mark)
		exit(EXIT_FAILURE);
	index = 0;
	while (index < (data->w * data->h))
	{
		validator->mark[index++] = 0;
	}
	validator->mark[validator->now] = 1;
}

static int	resolve_map(t_validator	*v, t_data *data)
{
	size_t	next;
	ssize_t	i;

	if (v->collectbles == data->state.c_flag && v->goal > 0)
		return (1);
	i = -1;
	printf("now%zu\n",  v->now);
	printf("C:%d\n",  v->collectbles);
	printf("G:%d\n",  v->goal);
	while (i++ < 4)
	{
		next = v->now + data->moves[i];
		if (data->map[next].field != '1' && v->mark[next] == 0)
		{
			v->now = next;
			if (data->map[v->now].field == 'C')
				v->collectbles++;
			else if (data->map[v->now].field == 'E')
				v->goal++;
			v->mark[v->now] = 1;
			if (resolve_map(v, data) == 1)
				return (1);
			// 一つ前の座標に戻る
			v->now -= data->moves[i];
			i = 0;
		}
	}
	return (0);
}

void	validate_map(t_data *data)
{
	t_validator	validator;

	init_validator(&validator, data);
	printf("%d\n",  data->state.c_flag);
	// exit(0);
	if (resolve_map(&validator, data) == 0)
	{
		free(validator.mark);
		free_data(data, 0);
		perror("This map does not allow access to E or C.\n");
		exit(EXIT_FAILURE);
	}
	free(validator.mark);
}
