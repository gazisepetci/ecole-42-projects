
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void	ft_putnbr(int n);

void	ft_bitreverse(int bit)
{
	static int	i;
	static int	text;

	if (bit == SIGUSR2)
	{
		text = text ^ (1 << i);
		i++;
	}
	else
		i++;
	if (i == 8)
	{
		write(1, &text, 1);
		i = 0;
		text = 0;
	}
}

int	main(void)
{
	write(1, "PID: ", 5);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	signal(SIGUSR1, ft_bitreverse);
	signal(SIGUSR2, ft_bitreverse);
	while (1)
		pause();
	return (0);
}
