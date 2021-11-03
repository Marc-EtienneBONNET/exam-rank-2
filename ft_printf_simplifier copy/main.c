#include <stdio.h>
int ft_printf(char *str, ...);

int main()
{
    char *str = "Bon courage pour l'exam";
    char *str_2 = NULL;

    printf("res : (%d)\n", ft_printf("%s", str_2));
    printf("res : (%d)\n", ft_printf("Bonjour messieux (%s)", str));
    printf("res : (%d)\n", ft_printf("Bonjour messieux (%x), (%x)",127, 2147483647));
    printf("res : (%d)\n", ft_printf("Bonjour messieux (%d), (%d), (%d)", 42, -2147483648, 2147483647));
}