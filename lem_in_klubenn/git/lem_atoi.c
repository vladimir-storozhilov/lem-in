#include "lem_in.h"

int			atoi_lem(char *str, t_lem0 *st0)
{
	long long	res;
	int			sign;
	int			len;
	int			err;

	sign = 1;
	res = 0;
	len = 0;
	err = 0;
	if (str[len] == '-' && ++err)
	{
		sign = -1;
		len++;
	}
	else if (str[len] == '+' && ++err)
		len++;
	while (str[len] >= '0' && str[len] <= '9' && len <= 11)
	{
		res = res * 10 + (str[len] - '0');
		len++;
	}
	if ((res > 2147483647 && sign == 1) || (res > 2147483648 && sign == -1)
		|| len > 11 || str[len] || (len == 1 && err == 1))
		error_management(st0, "ERROR: wrong number");
	return ((int)res * sign);
}