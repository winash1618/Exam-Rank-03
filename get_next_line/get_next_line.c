#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define BUFFER_SIZE 41

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (*str)
	{
		str++;
		i++;
	}
	return (i);
}

char *ft_strchr(char *str, char c)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == c)
			return (str);
		str++;
	}
	return (NULL);
}

char *ft_strjoin(char *s1, char *s2)
{
	int len1;
	int len2;
	char *str;
	int i;
	int j;

	if(!*s1)
		s1 = "";
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	i = -1;
	j = 0;
	while (s1[++i])
		str[j++] = s1[i];
	i = -1;
	while (s2[++i])
		str[j++] = s2[i];
	str[j] = '\0';
	return (str);
}

char *read_line(int fd, unsigned int buf)
{
	char *s;
	char *str;
	int i;

	str = (char *)malloc(sizeof(char) * buf);
	s = "";
	i = read(fd, str, buf);
	//printf("%d ", i);
	if (i)
		s = ft_strjoin(s, str);
	// s = ft_strchr(str, '\n');
	// printf("%s \n", s);
	// exit (1);
	while (!ft_strchr(str, '\n') && i)
	{
		i = read(fd, str, buf);
		//printf("=====%d====", i);
		if (i < 0)
			return (NULL);
		if(i)
			s = ft_strjoin(s, str);
		//printf("%s %d\n", s, i);
	}
	free (str);
	return (s);
}

char *get_current_line(char *str)
{
	int i;
	char *s;
	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	s = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] != '\n' && str[i])
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

void next_line(char **str)
{
	while (**str != '\n' && **str)
		(*str)++;
}

char *get_next_line(int fd)
{
	unsigned int buf;
	static char *str;
	char *s;

	buf = BUFFER_SIZE;
	// printf("hi");
	if (fd < 0 && buf <= 0)
		return (NULL);
	str = read_line(fd, buf);
	// printf("----%s----***", str);
	s = get_current_line(str);
	// printf("----%s----+++++", str);
	next_line(&str);
	// printf("----%s----", str);
	return (s);
}

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main()
{
	int fd;
	char *str;
	fd = 1;
	fd = open("foo.txt", O_RDWR | O_CREAT ,S_IRWXU | S_IRWXG | S_IRWXO); 
	printf("%d", fd);
	str = get_next_line(fd);
	str = get_next_line(fd);
    printf ("%s\n", str);
}