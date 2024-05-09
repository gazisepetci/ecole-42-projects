
#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>

int	ft_basamak_sayisi(unsigned int c);
int	ft_uzunluk(unsigned long sayi);
int	ft_putchars(char c);
int	hexfunc(unsigned int sayi, char c);
int	printing(va_list liste, int tip);
int	ft_printf(const char *str, ...);
int	ft_uitoa(unsigned int n);
int	ft_array(char *str);
int	ptr_printer(unsigned long n);
int	ptr_print(unsigned long n);

#endif
