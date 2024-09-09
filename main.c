#include <stdio.h>
#include <stdlib.h>
#include "colors.h"
#include "window.h"

void write_color(char *str, int color)
{
	printf("\e[%dm%s\n", color, str);
}

typedef struct s_position
{
	int	x;
	int	y;
}	t_position;

int	position_to_index(t_position pos, int width)
{
	return (pos.y * (width + 1) + pos.x);
}

void	write_in_buffer(char c, char *buffer, int size, int position)
{
	if (position < size)
		buffer[position] = c;
}

void	clear_buffer(char *buffer, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		buffer[i] = '\0';
}

char	*init_buffer(int size)
{
	char *buffer;

	buffer = malloc(size);
	if (!buffer)
		return (NULL);
	clear_buffer(buffer, size);
	return (buffer);
}

void init_window(t_window *window, int width, int height)
{
	int	size;

	if (width < 0)
		width = 0;
	if (height < 0)
		height = 0;
	window->width = width;
	window->height = height;
	size = sizeof(char) * ((width + 1) * height);
	window->buffer.size = size;
	window->buffer.string = init_buffer(size + sizeof(char));
}

int	main(int ac, char **av)
{
	t_window window;

	if (ac == 2 || 1)
	{
		init_window(&window, 64, 32);
		if (window.buffer.string)
		{
			free(window.buffer.string);
		}
	}
	return (0);
}