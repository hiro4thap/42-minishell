/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 21:23:20 by jhughes           #+#    #+#             */
/*   Updated: 2024/03/30 15:10:15 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_UTILS_H
# define FT_PRINTF_UTILS_H

# ifdef __linux__
#  define ON_LINUX 1
# endif
# ifndef __linux__
#  define ON_LINUX 0
# endif

# include <unistd.h>

typedef int	t_bool;

# define TRUE 1
# define FALSE 0

typedef struct s_format
{
	char	conversion;
	t_bool	use_field_width;
	t_bool	use_precision;
	t_bool	f_zero;
	t_bool	f_dash;
	t_bool	f_sign;
	t_bool	f_space;
	t_bool	f_hash;
	int		field_width;
	int		precision;
	char	sign;
}	t_format;

int		print_i(int n, t_format *format, t_bool *error);
int		print_s(char *s, t_format *format, t_bool *error);
int		print_c(char c, t_format *format, t_bool *error);
int		print_u(unsigned long n, t_format *format, t_bool *error);
int		print_p(void *p, t_format *format, t_bool *error);

int		apply_sign(t_format *format, t_bool *error);
long	ft_power(unsigned int nb, size_t power);
int		set_base(char type);
int		int_length(int n);
int		int_length_ul(unsigned long n, unsigned long base);

int		write_e(int fd, const char *buffer, size_t bytes, t_bool *error);
int		putchar_e(char c, int fd, t_bool *error);
int		putchars_e(char c, int count, int fd, t_bool *error);
int		putnbr_e(int n, int fd, t_bool *error);
int		putnbr_u_e(unsigned long u, char type, int fd, t_bool *error);

#endif
