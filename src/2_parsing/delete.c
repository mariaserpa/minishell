#include "../../includes/minishell.h"

void	ft_bzero(void*s, size_t n)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	p = (unsigned char *)s;
	while (i < n)
	{
		*p = 0;
		i++;
		p++;
	}
}

t_list	*ft_lst_last(t_list*lst)
{
	if (!lst)
		return (0);
	while (lst -> next)
		lst = lst -> next;
	return (lst);
}

char	*ft_strdup(const char*src)
{
	int		i;
	int		len;
	char	*dest;

	len = ft_strlen(src);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (dest == 0)
		return (0);
	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	*ft_calloc(size_t number, size_t size)
{
	void	*dest;

	dest = (void *)malloc(number * size);
	if (dest == 0)
		return (0);
	ft_bzero(dest, number * size);
	return (dest);
}

t_command	*ft_lst_last_command(t_command*lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int	ft_strcmp(char*s1, char*s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

void	ft_lstadd_back(t_list**lst, t_list*new)
{
	t_list	*last;

	last = ft_lst_last(*lst);
	if (!last)
	{
		*lst = new;
		return ;
	}
	last -> next = new;
}

int	ft_isalnum(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') \
		|| (c >= '0' && c <= '9'));
}
static int	n_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static long int	abs_value(int n)
{
	long int	nb;

	nb = 1;
	if (n < 0)
		nb *= -n;
	else
		nb *= n;
	return (nb);
}

char	*ft_itoa(int n)
{
	unsigned int		nb;
	int					sign;
	int					len;
	char				*dest;

	sign = 0;
	if (n < 0)
		sign = 1;
	len = n_len(n);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (0);
	dest[len] = '\0';
	nb = abs_value(n);
	while (len > 0)
	{
		dest[len - 1] = '0' + nb % 10;
		nb /= 10;
		len--;
	}
	if (sign == 1)
		dest[0] = '-';
	return (dest);
}

char	*ft_strjoin(char const*s1, char const*s2)
{
	char	*dest;
	size_t	i;
	size_t	j;

	dest = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (dest == 0)
		return (0);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		dest[j] = s1[i];
		i++;
		j++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		dest[j] = s2[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

int	ft_strncmp(const char*s1, const char*s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && i < n - 1 && (s1[i] || s2[i]))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_substr(char const*s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (s == 0)
		return (0);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == 0)
		return (0);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
