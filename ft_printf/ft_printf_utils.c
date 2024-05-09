
#include "ft_printf.h"

int	ft_basamak_sayisi(unsigned int c)
{
	int	i;

	i = 0;
	while (c > 0)
	{
		i++;
		c = c / 10;
	}
	return (i);
}

int	ft_array(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (ft_array("(null)"));
	while (str[len] != '\0')
		len += ft_putchars(str[len]);
	return (len);
}

int	ft_uzunluk(unsigned long sayi)
{
	int	i;

	i = 0;
	if (sayi == 0)
		return (1);
	while (sayi > 0)
	{
		sayi = (sayi / 16);
		i++;
	}
	return (i);
}

int	ft_putchars(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_uitoa(unsigned int n)
{
	int			len;
	char		*str;

	len = ft_basamak_sayisi(n);
	str = (char *)malloc(sizeof(char) * len + 1);
	str[len] = '\0';
	if (n == 0)
	{
		free(str);
		return (write(1, "0", 1));
	}
	while (n > 0)
	{
		str[--len] = (n % 10) + 48;
		n = n / 10;
	}
	len = ft_array(str);
	free(str);
	return (len);
}
