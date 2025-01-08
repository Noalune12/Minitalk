# include <signal.h>
# include <unistd.h>
# include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

char	*reallocate_message(char *message, char c, int len)
{
	char	*ret;
	int		i;

	i = 0;
	ret = malloc(sizeof(char) * (len + 2));
	if (!ret)
	{
		free(message);
		exit(EXIT_FAILURE);
	}
	while (message[i])
	{
		ret[i] = message[i];
		i++;
	}
	ret[i] = c;
	ret[i + 1] = '\0';
	return (ret);
}

char	*store_message(char c, int i, char *message)
{
	char	*temp;

	if (i == 0)
	{
		message = malloc(2 * sizeof(char));
		message[0] = c;
		message[1] = '\0';
		//if !message
	}
	else if (c == '\0')
	{
		printf("message = %s\n\n", message);
		free(message);
	}
	else
	{
		// printf("last else");
		temp = message;
		message = reallocate_message(message, c, i);
		if (!message)
		{
			free(temp);
			exit(EXIT_FAILURE);
		}
		free(temp);
	}

	// printf("message = %s\n\n", message);
	return (message);
}

int main()
{
	char a = 'h';
	char b = 'e';
	char c = 'l';
	char d = 'l';
	char e = 'o';
	char *str;

	str = NULL;
	str = store_message(a, 0, str);
	str = store_message(b, 1, str);
	str = store_message(c, 2, str);
	str = store_message(d, 3, str);
	str = store_message(e, 4, str);
	str = store_message('\0', 5, str);

}
