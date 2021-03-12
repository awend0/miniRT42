/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasv <hasv@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 01:57:54 by hasv              #+#    #+#             */
/*   Updated: 2021/03/12 03:44:43 by hasv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini_rt.h"

extern double	g_height;
extern double	g_width;
extern t_list	*g_first_cam;
extern t_color	g_background_color;
extern t_list	*g_memory;

int		ft_add_header(t_mlxvars *vars, int padding_size, int fd)
{
	unsigned char	*header;
	int				size;
	int				ret;

	header = ft_malloc_save(14 * sizeof(unsigned char));
	size = 54 + (vars->img.bbp / 8 * g_height + padding_size) * g_width;
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	header[2] = (unsigned char)(size);
	header[3] = (unsigned char)(size >> 8);
	header[4] = (unsigned char)(size >> 16);
	header[5] = (unsigned char)(size >> 24);
	header[10] = (unsigned char)(54);
	ret = write(fd, header, 14);
	return (ret);
}

int		ft_add_info(t_mlxvars *vars, int fd)
{
	unsigned char	*info;
	int				ret;

	info = ft_malloc_save(40 * sizeof(unsigned char));
	info[0] = (unsigned char)(40);
	info[4] = (unsigned char)((int)g_height);
	info[5] = (unsigned char)((int)g_height >> 8);
	info[6] = (unsigned char)((int)g_height >> 16);
	info[7] = (unsigned char)((int)g_height >> 24);
	info[8] = (unsigned char)((int)g_width);
	info[9] = (unsigned char)((int)g_width >> 8);
	info[10] = (unsigned char)((int)g_width >> 16);
	info[11] = (unsigned char)((int)g_width >> 24);
	info[12] = (unsigned char)(1);
	info[14] = (unsigned char)(vars->img.bbp);
	ret = write(fd, info, 40);
	return (ret);
}

int		ft_create_bmp(t_mlxvars *vars)
{
	int				padding_size;
	int				fd;
	unsigned char	*padding;
	int				i;
	int				ret;

	ret = 0;
	padding = ft_malloc_save(3 * sizeof(unsigned char));
	padding_size = (4 - ((int)g_height * vars->img.bbp / 8) % 4) % 4;
	if (!(fd = open("img.bmp",
		O_CREAT | O_TRUNC | O_WRONLY, 0644)))
		ft_exit(0, "File can't be created.");
	ret += ft_add_header(vars, padding_size, fd);
	ret += ft_add_info(vars, fd);
	i = g_height;
	while (i >= 0)
	{
		ret += write(fd, vars->img.addr + (i * (int)g_width *
			vars->img.bbp / 8), vars->img.line_len);
		ret += write(fd, padding, padding_size);
		i--;
	}
	close(fd);
	return (ret);
}

void	ft_bmp(int argc, char *argv[])
{
	t_mlxvars	vars;

	vars.data = ft_parser(argc, argv);
	vars.mlx = mlx_init();
	vars.img.img = mlx_new_image(vars.mlx, g_height, g_width);
	vars.img.addr = mlx_get_data_addr(vars.img.img,
		&vars.img.bbp, &vars.img.line_len, &vars.img.endian);
	ft_draw(&vars, 1);
	printf("Image saved in img.bmp!\n");
	ft_exit(&vars, 0);
}
