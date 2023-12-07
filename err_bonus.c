/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehkekli <mehkekli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:05:16 by mehkekli          #+#    #+#             */
/*   Updated: 2023/12/05 16:05:18 by mehkekli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "lib/libft/libft.h"
#include "so_long_bonus.h"

void	ft_exiterr(int err_no, char *err, t_state *state)
{
	ft_dispose(state);
	ft_putendl_fd("Error", 2);
	ft_putstr_fd("excited with (", 2);
	ft_putnbr_fd(err_no, 2);
	ft_putstr_fd("): ", 2);
	ft_putendl_fd(err, 2);
	exit(err_no);
}
