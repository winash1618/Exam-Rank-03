#include <stdio.h>
#include "ft_printf.h"
int main()
{
	ft_printf("%x\n", -2147483648);
	printf("%x", -2147483648);
	return (0);
}