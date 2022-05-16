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
	{
		str[i] = s1[j];
		i++;
	}
	j = -1;
	while (s2[++j])
	{
		str[i] = s2[j];
		i++;
	}
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
	str = NULL;

	
	i = 0;
	str = malloc(sizeof(char) * (bs + 1));
	s = "";
	i = read(fd, str, bs);
	if (i)
		str[i] = '\0';
	s = ft_strjoin(s, str);
	// printf("%d \n", ft_strchr(str, '\n')[0]);
	// while (ft_strchr(str, '\n')[0] == '\n')
	// {

	// }
	// if (i)
	// printf("-----%s-----", s);
	free (str);
	return (s);
}

char *get_next_line(int fd)
{
	int bs;
	static char *str;
	bs = BUFFER_SIZE;
	if (fd < 0 && bs <= 0)
		return (NULL);
	str = read_line(fd, bs);
	return (str);
}

int main()
{
	int fd;
	char *str;

	fd = open("./gnlTester/files/41_with_nl", O_RDWR);
	str = get_next_line(fd);
	printf("-----%s-----", str);
	free (str);
	return (0);
}