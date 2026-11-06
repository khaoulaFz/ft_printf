/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khafaouz <khafaouz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 15:50:40 by khafaouz          #+#    #+#             */
/*   Updated: 2026/11/06 04:16:26 by khafaouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
// putchar function

int    ft_putchar_count(char c)
{


	write(1, &c, 1);
	return (1);
}

// str length
int	ft_strlen(char *s)
{
	int	i;
	
	i = 0;
	while(s[i])
		i++;
	return (i);
}
// putstr function
int    ft_putstr(char *str)
{
	int	i;

	i = 0;
	if(!str)
	{
		write(1, "(null)",6);
		return(6);
	}
    while(str[i]) 
    {
        write(1, &str[i], 1);
        i++;
    }
	return (i);
}

//  putnbr function
int	ft_putnbr(int nbr)
{
	long	n;
	int		count;

	n = nbr;
	count = 0;
	if (n < 0)
	{
		count += ft_putchar_count('-');
		n = -n;
	}
	if (n > 9)
			count += ft_putnbr(n / 10);
	count += ft_putchar_count(n % 10 + '0');
	return (count);
}

// putnbr_base function
int	ft_putnbr_base(unsigned int nbr, char *base)
{
	unsigned int	n;
	int				count;
	int				base_len;

	n = nbr;
	count = 0;
	base_len = ft_strlen(base);
	if (n >= (unsigned int)base_len)
			count += ft_putnbr_base(n / base_len, base);
	count += ft_putchar_count(base[n % base_len]);
	return (count);
}
int     ft_putptr(void *ptr)
{
    char *hex ;
	int	count;
	hex = "0123456789abcdef";
    unsigned long long ptr_cpy ;
	ptr_cpy = (unsigned long long)ptr;
	count = 0;
	if (!ptr)
	{
		count = ft_putstr("(nil)");
		return (count);

	}
    if (ptr_cpy >= 16)
    {
        ft_putptr((void *)(ptr_cpy / 16));	
    }
	
    count += ft_putchar_count(hex[ptr_cpy % 16]);
	return (count);
}
// the main printf function

int	handle_format(va_list args, char specifier)
{
	if (specifier == 'c')
		return (ft_putchar_count(va_arg(args, int)));
	else if (specifier == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (specifier == 'd' || specifier == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (specifier == 'u')
		return (ft_putnbr_base(va_arg(args, unsigned int),
				"0123456789"));
	else if (specifier == 'x')
		return (ft_putnbr_base(va_arg(args, unsigned int), "0123456789abcdef"));
	else if (specifier == 'X') 
		return (ft_putnbr_base(va_arg(args, unsigned int),"0123456789ABCDEF"));
	else if (specifier == 'p')
	{
		ft_putstr("0x");
		return (ft_putptr(va_arg(args, void *)) + 2);
	}
	else if (specifier == '%')
		return (ft_putchar_count('%'));
	return (0);
}
int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%' && *(format + 1))
		{
			format++;
			count += handle_format(args, *format);
		}
		else if (*format != '%')
		{
			count += ft_putchar_count(*format);
		}
		format++;
	}
	va_end(args);
	return (count);
}

#include <stdio.h>
int main()
{

	int count  = ft_printf("%x\n", 30);
	printf("%d",count);
}// putnbr function