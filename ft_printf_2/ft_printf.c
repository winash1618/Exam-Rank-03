#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

int ft_putchar(char c)
{
	write (1, &c, 1);
	return (1);
}

int ft_putstr(char *s)
{
	int i;

	i = 0;
	if (!s)
		return(ft_putstr("(null)"));
	while (*s)
		i += ft_putchar(*s++);
	return (i);
}

int ft_puthexaddr(unsigned long long num)
{
	char mod;
	char s[16] = "0123456789abcdef";
	int i;

	i = 0;
	if (num > 15)
	{
		mod = s[num % 16];
		num /= 16;
		i += ft_puthexaddr(num);
		i += ft_putchar(mod);
	}
	else
	{
		mod = s[num % 16];
		i += ft_putchar(mod);
	}
	return (i);
}

int ft_putaddr(unsigned long long num)
{
	int i;

	i = 0;
	i += ft_putstr("0x");
	i += ft_puthexaddr(num);
	return (i);
}

int ft_putint(int num)
{
	char mod;
	char s[10] = "0123456789";
	int i;

	i = 0;
	if (num == -2147483648)
	{
		i += ft_putstr("-2147483648");
		return (i);
	}
	if (num < 0)
	{
		i += ft_putchar('-');
		num = -num;
	}
	if (num > 9)
	{
		mod = s[num % 10];
		num /= 10;
		i += ft_putint(num);
		i += ft_putchar(mod);
	}
	else
	{
		mod = s[num % 10];
		i += ft_putchar(mod);
	}
	return (i);
}

int ft_puthex(unsigned int num, char c)
{
	char mod;
	int i;

	i = 0;
	if (c == 'x')
	{
		char s[16] = "0123456789abcdef";
		if (num > 15)
		{
			mod = s[num % 16];
			num /= 16;
			i += ft_puthex(num, c);
			i += ft_putchar(mod);
		}
		else
		{
			mod = s[num % 16];
			i += ft_putchar(mod);
		}
	}
	else if (c == 'X')
	{
		char s[16] = "0123456789ABCDEF";
		if (num > 15)
		{
			mod = s[num % 16];
			num /= 16;
			i += ft_puthex(num, c);
			i += ft_putchar(mod);
		}
		else
		{
			mod = s[num % 16];
			i += ft_putchar(mod);
		}
	}
	return (i);

}

int ft_putunint(unsigned int num)
{
	char mod;
	int i;
	char s[10] = "0123456789";

	i = 0;
	if (num > 9)
	{
		mod = s[num % 10];
		num /= 10;
		i += ft_putunint(num);
		i += ft_putchar(mod);
	}
	else
	{
		mod = s[num % 10];
		i += ft_putchar(mod);
	}
	return (i);
}

int ft_check(va_list pa, char c)
{
	int i;

	i = 0;
	if (c == 'c')
		i += ft_putchar(va_arg(pa, int));
	else if (c == 's')
		i += ft_putstr(va_arg(pa, char *));
	else if (c == 'p')
		i += ft_putaddr(va_arg(pa, unsigned long long));
	else if (c == 'd' || c == 'i')
		i += ft_putint(va_arg(pa, int));
	else if (c == 'x' || c == 'X')
		i += ft_puthex(va_arg(pa, unsigned int), c);
	else if (c == 'u')
		i += ft_putunint(va_arg(pa, unsigned int));
	else if (c == '%')
		i += ft_putchar(c);
	return (i);
}

int ft_printf(const char *s, ...)
{
	va_list pa;
	int i;

	i = 0;
	va_start(pa, s);
	while (*s)
	{
		if (*s == '%')
			i += ft_check(pa, *(++s));
		else
			i += ft_putchar(*s);
		s++;
	}
	va_end(pa);
	return (i);
}
