#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

int ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		str++;
		i++;
	}
	return (i);
}

int	ft_putchar (int c)
{

	write (1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	len;

	if (!str)
	{
		len = ft_putstr("(null)");
		return (len);
	}
	len = ft_strlen(str);
	while (*str)
		ft_putchar(*str++);
	return (len);
}

int ft_putint(int num)
{
	int i = 0;
	char s[10] = "0123456789";
	char c;
	if (num == -2147483648)
	{
		i += ft_putstr("-2147483648");
		return (i);
	}
	if (num < 0)
	{
		num = -num;
		i += ft_putchar('-');
	}
	if (num > 9)
	{
		c = s[num % 10];
		num /= 10;
		i += ft_putint(num);
		i += ft_putchar(c);
	}
	else
	{
		c = s[num % 10];
		i += ft_putchar(c);
	}
	return (i);
}

int ft_puthex(unsigned int num, char c)
{
	int i = 0;
	char ch;

	if (num < 0)
		num = -num;
	if (c == 'x')
	{
		char s[16] = "0123456789abcdef";
		if (num > 15)
		{
			ch = s[num % 16];
			num /= 16;
			i += ft_puthex(num, c);
			i += ft_putchar(ch);
		}
		else
		{
			ch = s[num];
			i += ft_putchar(ch);
		}
	}
	else
	{
		char s[16]= "0123456789ABCDEF";
		if (num > 15)
		{
			ch = s[num % 16];
			num /= 16;
			i += ft_puthex(num, c);
			i += ft_putchar(ch);
		}
		else
		{
			ch = s[num];
			i += ft_putchar(ch);
		}
	}
	return (i);
}

int ft_putaddhex(unsigned long long num)
{
	int i = 0;
	char ch;
	char s[16] = "0123456789abcdef";
	if (num > 15)
	{
		ch = s[num % 16];
		num /= 16;
		i += ft_putaddhex(num);
		i += ft_putchar(ch);
	}
	else
	{
		ch = s[num];
		i += ft_putchar(ch);
	}
	
	return (i);
}

int ft_putaddr(unsigned long long num)
{
	int	i;

	i = 0;
	i += ft_putstr("0x");
	i += ft_putaddhex(num);
	return (i);
}

int ft_putunint (unsigned int num)
{
	int	i;

	i = 0;
	char s[10] = "0123456789";
	char c;
	if (num > 2147483647)
	{
		c = s[num % 10];
		num /= 10;
		i += ft_putunint(num);
		i += ft_putchar(c);
	}
	else
	{
		i += ft_putint(num);
	}
	return (i);
}

int	ft_check(va_list ap, char c)
{
	int	i;

	i = 0;
	if (c == 'c')
		i += ft_putchar(va_arg(ap, int));
	else if (c == 's')
		i += ft_putstr(va_arg(ap, char *));
	else if (c == 'd' || c == 'i')
		i += ft_putint(va_arg(ap, int));
	else if (c == 'x' || c == 'X')
		i += ft_puthex(va_arg(ap, unsigned int), c);
	else if (c == 'p')
		i += ft_putaddr(va_arg(ap, unsigned long long));
	else if (c == 'u')
		i += ft_putunint(va_arg(ap, unsigned int));
	else if (c == '%')
		i += ft_putchar(c);
	return (i);
}

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	int		i;

	va_start (ap, s);
	i = 0;
	while (*s)
	{
		if (*s == '%')
			i += ft_check(ap, *(++s));
		else
			i += ft_putchar(*s);
		s++;
	}
	return (i);
}

// int main ()
// {
// 	char c;
// 	int i;
// 	int j;
// 	i = ft_printf("%x", 123);
// 	j = printf("%x", 123);
// 	printf("\n%d %d", i, j);
// 	return (0);
// }
