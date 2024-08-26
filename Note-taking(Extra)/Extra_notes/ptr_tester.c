#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_printf_char(int c, int *char_num)
{
	write (1, &c, 1);
	(*char_num)++;
}

void	ft_printf_str(char *str, int *char_num)
{
	if (!str)
	{
		write (1, "(null)", 6);
		*char_num += 6;
		return ;
	}
	while (*str)
	{
		ft_printf_char(*str, char_num);
		++str;
	}
}

// void	ft_printf_ptr_printer(uintptr_t ptr, int *char_num)
// {
// 	char	*base;
// 	char	value;

// 	base = "0123456789abcdef";
// 	value = base[ptr % 16];
// 	ptr /= 16;
// 	if (ptr > 0)
// 		ft_printf_ptr_printer(ptr, char_num);
// 	ft_printf_char(value, char_num);
// }

// void	ft_printf_ptr(uintptr_t ptr, int *char_num)
// {
// 	if (!ptr)
// 	{
// 		write (1, "(null)", 6);
// 		*char_num += 6;
// 		return ;
// 	}
// 	else
// 	{
// 		ft_printf_str("0x", char_num);
// 		ft_printf_ptr_printer(ptr, char_num);
// 	}
// }

void	ft_printf_ptr_printer(uintptr_t n, int *counter)
{
	char	*symbols;

	symbols = "0123456789abcdef";
	if (n < 16)
		ft_printf_char(symbols[n], counter);
	else
	{
		ft_printf_ptr_printer(n / 16, counter);
		ft_printf_ptr_printer(n % 16, counter);
	}
}

void	ft_printf_ptr(uintptr_t ptr, int *counter)
{
	if (!ptr)
		ft_printf_str("(nil)", counter);
	else
	{
		ft_printf_str("0x", counter);
		ft_printf_ptr_printer(ptr, counter);
	}
}


int main() {
    	int var = 42;
    	char *str = "Hello, world!";
    	int char_num = 0;

    	// Print the address of the variable 'var'
    	ft_printf_ptr((uintptr_t)&var, &char_num);
    	printf("\n");
    	printf("%d", char_num);
    	printf("\n");
	char_num = 0;
	printf("%p", &var);
	printf("\n");
	printf("%d", char_num);
	printf("\n");

	char_num = 0;
   	// Print the address of the string 'str'
    	ft_printf_ptr((uintptr_t)str, &char_num);
   	printf("\n");
   	printf("%d", char_num);
    	printf("\n");
	char_num = 0;
	printf("%p", str);
	printf("\n");
	printf("%d", char_num);
	printf("\n");
	printf("\\\\\\\\\\\\\\\\\\\\\\\n");
	printf("just to distinguish");
	char_num = printf("%s\n", "");
	printf("%d\n", char_num);
	char_num = 0;
	printf("just to distinguish");
	ft_printf_str("", &char_num);
	printf("\n");
	printf("%d\n", char_num);
	printf("%ld\n",  (unsigned int)-2147483648 % 4294967296);

    	return 0;
}
