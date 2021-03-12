/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 11:37:59 by hasv              #+#    #+#             */
/*   Updated: 2021/03/12 05:44:01 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

extern double	g_width;
extern double	g_height;
extern t_list	*g_first_cam;
extern t_color	g_background_color;
extern t_list	*g_memory;
extern int		g_sepia;

t_parsed_data	*ft_init_pd(void)
{
	t_parsed_data	*ret;

	ret = ft_malloc_save(sizeof(t_parsed_data));
	ret->cameras = 0;
	ret->lights = 0;
	ret->objects = 0;
	return (ret);
}

double			ft_stof(char *line)
{
	char	**temp;

	temp = ft_split(line, ".");
	if (!temp[1])
	{
		if (!ft_isdigit(temp[0]))
			ft_exit(0, "Incorrect float/int value!");
		return ((double)(ft_atoi(temp[0])));
	}
	if (!ft_isdigit(temp[0]) || !ft_isdigit(temp[1]))
		ft_exit(0, "Incorrect float/int value!");
	return ((double)ft_atoi(temp[0])
		+ ((double)ft_atoi(temp[1])
		/ pow(10, ft_strlen(temp[1]))));
}

t_color			ft_stoc(char *line)
{
	char	**temp;

	temp = ft_split(line, ",");
	if (!temp[0] || !temp[1] || !temp[2])
		ft_exit(0, "Incorrect color description!");
	return ((t_color){ft_stof(temp[0]), ft_stof(temp[1]), ft_stof(temp[2])});
}

t_point			ft_stop(char *line)
{
	char	**temp;

	temp = ft_split(line, ",");
	if (!temp[0] || !temp[1] || !temp[2])
		ft_exit(0, "Incorrect point description!");
	return ((t_point){ft_stof(temp[0]), ft_stof(temp[1]), ft_stof(temp[2])});
}
