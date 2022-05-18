#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int ft_strlen(char *str)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}

char *ft_strchr(char *str, char c)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if(*str == c)
			return (str);
		str++;
	}
	return (str);
}

char *ft_strjoin(char *s1, char *s2)
{
	int len1, len2;
	char *str;
	int i, j;
	len1 = 0;
	len2 = 0;
	// if (!*s1)
	// {
	// 	s1 = (char *)malloc(sizeof(char) * 1);
	// 	s1[0] = '\0';
	// }
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if(len1 + len2)
		str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	i = 0;
	j = -1;
	while (s1[++j])
		str[i++] = s1[j];
	j = -1;
	while (s2[++j])
		str[i++] = s2[j];
	// free(s1);
	str[i] = '\0';
	return (str);
}

// int main()
// {
// 	char *s1;
// 	char s2[10] = "si i ho";
// 	s1 = (char *)malloc(sizeof(char) * 1);
// 	s1[0] = '\0';
// 	char *str = ft_strjoin(s1, s2);
// 	printf("---%s---- \n", str);
// 	free(str);
// 	free(s1);
// }

// int main()
// {
// 	char s1[10] = "";
// 	char s2[10] = "si i ho";
// 	char *str = ft_strjoin(s1, s2);
// 	printf("---%s---- \n", str);
// 	free(str);
// 	// free(s1);
// }

char *read_line(int fd, unsigned int bs)
{
	char *str;
	int i;
	char *s;
	char *res;

	
	i = 0;
	str = malloc(sizeof(char) * (bs + 1));
	s = "";
	i = read(fd, str, bs);
	if (i)
		str[i] = '\0';
	else
	{
		free (str);
		return (NULL);
	}
	res = ft_strjoin(s, str);
	s = res;
	free(str);
	// printf("%d \n", ft_strchr(str, '\n')[0]);
	while (ft_strchr(s, '\n')[0] != '\n')
	{
		str = malloc(sizeof(char) * (bs + 1));
		i = read(fd, str, bs);
		// printf("%d\n", i);
		if (i)
		{
			str[i] = '\0';
			res = ft_strjoin(s, str);
			free (s);
			s = res;
			free (str);
		}
		else
		{
			free (str);
			return (s);
		}
	}

	// if (i)
	// printf("-----%s-----", s);
	return (s);
}

char *current_line(char *str)
{
	char *s;
	char *res;
	int len;

	s = ft_strchr(str, '\n');
	len = ft_strlen(str);
	res = (char *)malloc(sizeof(char) * (len + 1));
	int i = 0;
	while (str != s)
	{
		res[i] = *str;
		i++;
		str++;
	}
	if (*str == '\n')
	{
		str++;
		res[i] = '\n';
		i++;
	}
	res[i] = '\0'; 
	// conditional jump comes when you remove the above one. I think when you try to use a string which is not null terminated.
	// Conditional jump or move depends on uninitialised value(s)
	// ==95==    at 0x483EF49: strlen (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
	// ==95==    by 0x48C7D44: __vfprintf_internal (vfprintf-internal.c:1688)
	// ==95==    by 0x48B0D6E: printf (printf.c:33)
	// ==95==    by 0x1095F8: main (get_next_line.c:170)
	return (res);
}

void next_line(char **str)
{
	int count;

	count = 0;
	while (**str)
	{
		count++;
		(*str)++;
	}
	
}

char *get_next_line(int fd)
{
	int bs;
	static char *str;
	char *s;
	bs = BUFFER_SIZE;
	if (fd < 0 && bs <= 0)
		return (NULL);
	str = read_line(fd, bs);
	if(!str)
		return (NULL);
	s = current_line(str);
	if (!str)
		return (NULL);
	char *st = str;
	next_line(&str);
	free(st);
	return (s);
}

// int main()
// {
// 	int fd;
// 	char *str;

// 	fd = open("./gnlTester/files/empty", O_RDWR);
// 	str = get_next_line(fd);
// 	printf("-----%s-----", str);
// 	free (str);
// 	str = get_next_line(fd);
// 	printf("-----%s-----", str);
// 	free (str);

// 	return (0);
// }