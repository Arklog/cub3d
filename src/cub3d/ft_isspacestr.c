#include "cub3d.h"

int	ft_isspacestr(const char *str)
{
	while (*str && ft_isspace(*str))
		++str;
	return (!(*str));
}

int	ft_isspacedigitstr(const char *str)
{
	while (*str && (ft_isspace(*str) || ft_isdigit(*str)))
		++str;
	return (!(*str));
}
