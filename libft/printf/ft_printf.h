/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schevall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 16:32:39 by schevall          #+#    #+#             */
/*   Updated: 2017/02/06 11:37:57 by schevall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "../libft.h"

typedef struct		s_flags
{
	int				hash;
	int				dash;
	int				plus;
	int				spaced;
	int				zero;
}					t_flags;

typedef struct		s_length
{
	int				l;
	int				j;
	int				h;
	int				z;
}					t_length;

typedef struct		s_param
{
	struct s_flags	flags;
	struct s_length	length;
	char			conv;
	int				width;
	int				prec;
	int				size_arg;
	int				size_tot;
	int				size_s_tot;
	int				base;
}					t_param;

int					ft_printf(const char *format, ...);
void				get_params(const char **format, va_list ap,
															t_param *params);
void				init_params(t_param *params);
void				re_init_params(t_param *params);
int					is_flag(char c);
int					is_length(char c);
int					is_signed_conv(int conv);
int					is_unsigned_conv(int conv);
int					is_hexa(int conv);
int					is_octal(int conv);
int					is_oct_or_hex(int conv);
intmax_t			get_signed_arg(va_list ap, t_param *params);
intmax_t			get_unsigned_arg(va_list ap, t_param *params);
int					format_tree(char **s, va_list ap, t_param *params);
char				*format_signed(char *str_arg, va_list ap, t_param *params);
int					width_for_zero(int i, t_param *p);
int					put_zeros_for_signed(char *str, int i, t_param *p, int tok);
char				*format_unsign(char *str_arg, va_list ap, t_param *params);
int					get_base(t_param *params);
int					ft_nbrlen_base(uintmax_t arg, int base);
void				sizer_for_pconv(t_param *p, uintmax_t arg);
int					opt_for_p_conv(int i, char *str, t_param *p);
void				sizer_precz_argz(t_param *p);
void				width_hashed(t_param *p, uintmax_t arg);
int					apply_zero(t_param *p, int i, char *str, uintmax_t arg);
void				case_precz_argz(t_param *p);
char				*format_string(char *str_arg, va_list ap, t_param *params);
char				*format_char(char *str_arg, va_list ap, t_param *params);
char				*format_wchar(char *str_arg, va_list ap, t_param *params);
char				*format_wstring(char *str_arg, va_list ap, t_param *params);
int					get_wchar_size(wint_t arg);
char				*spec_for_wstring(char *str_arg, t_param *params, int tok);
void				create_str_arg(char **str_arg, t_param *params);
int					apply_width(int i, t_param *params);
int					apply_prec(int i, char *str_arg, t_param *params);
int					apply_hash(int i, char *str_arg, t_param *params);
#endif
