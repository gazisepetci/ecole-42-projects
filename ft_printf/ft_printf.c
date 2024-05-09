
#include "ft_printf.h"

int	ptr_printer(unsigned long n)
{
	char			*str;
	int				len;
	char			*dizi;
	int				i;

	dizi = "0123456789abcdef";
	len = ft_uzunluk(n);
	i = len;
	str = calloc(len, sizeof(char));
	if (n == 0)
		return (write(1, "0", 1));
	while (n > 0)
	{
		str[--i] = dizi[n % 16];
		n = n / 16;
	}
	ft_array(str);
	free(str);
	return (0);
}

int	ptr_print(unsigned long n)
{
	int	i;

	i = 1;
	ft_putchars('0');
	ft_putchars('x');
	ptr_printer(n);
	while (n >= 16)
	{
		n = n / 16;
		i++;
	}
	return (i + 2);
}

int	hexfunc(unsigned int sayi, char c)
{
	char			*str;
	int				len;
	char			*dizi;
	int				i;

	if (c == 'X')
		dizi = "0123456789ABCDEF";
	else
		dizi = "0123456789abcdef";
	len = ft_uzunluk(sayi);
	i = len;
	str = calloc(len, sizeof(char));
	if (sayi == 0)
		return (write(1, "0", 1));
	while (sayi > 0)
	{
		str[--i] = dizi[sayi % 16];
		sayi = sayi / 16;
	}
	ft_array(str);
	free(str);
	return (len);
}

int	printing(va_list liste, int tip)
{
	char	*a;
	int		i;

	i = 0;
	if (tip == 'c')
		i += ft_putchars(va_arg(liste, int));
	else if (tip == 'd' || tip == 'i')
	{
		a = ft_itoa(va_arg(liste, int));
		i += ft_array(a);
		free(a);
	}
	else if (tip == 's')
		i += ft_array(va_arg(liste, char *));
	else if (tip == 'p')
		i += ptr_print(va_arg(liste, unsigned long));
	else if (tip == 'x' || tip == 'X')
		i += hexfunc(va_arg(liste, unsigned int), tip);
	else if (tip == 'u')
		i += ft_uitoa(va_arg(liste, unsigned int));
	else if (tip == '%')
		i += ft_putchars('%');
	return (i);
}

int	ft_printf(const char *str, ...)
{
	va_list	liste;
	int		i;
	int		len;

	va_start(liste, str);
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			len += printing(liste, str[i]);
		}
		else
		{
			ft_putchar_fd(str[i], 1);
			len++;
		}
		i++;
	}
	va_end(liste);
	return (len);
}
// int main()
// {
// 	char *s = "\0";

// 	ft_printf("%s", 56);
// }
