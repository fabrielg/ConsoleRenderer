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

t_position	create_position(int x, int y)
{
	t_position	pos;

	pos.x = x;
	pos.y = y;
	return (pos);
}

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

void	draw_line(t_position pos1, t_position pos2, t_window window)
{
	int	dx;
	int	dy;
	int	m;
	int	y;

	dx = pos2.x - pos1.x;
	dy = pos2.y - pos1.y;
	m = dy / dx;	// dx can't be 0
	/*printf(
		"Pos 1 : x = %d	y = %d \n\
		Pos 2 : x = %d	y = %d \n\n\
		dx = x2 - x1 = %d - %d = %d \n\
		dy = y2 - y1 = %d - %d = %d \n\
		m = dy / dx = %d / %d = %d \n\n",
		pos1.x,
		pos1.y,
		pos2.x,
		pos2.y,
		pos2.x,
		pos1.x,
		dx,
		pos2.y,
		pos1.y,
		dy,
		dy,
		dx,
		m
	);*/
	for (int x = pos1.x; x < pos2.x; x++)
	{
		y = m * (x - pos1.x) + pos1.y;
		/*printf("x = %d; y = %d\n", x, y);*/
		write_in_buffer('#', window.buffer.string, window.buffer.size, position_to_index(create_position(x, y), window.width));
	}
}

int	main(int ac, char **av)
{
	t_window window;

	if (ac == 2 || 1)
	{
		init_window(&window, 64, 32);
		if (window.buffer.string)
		{
			t_position	pos1 = create_position(2, 6);
			t_position	pos2 = create_position(5, 19);
			draw_line(pos1, pos2, window);
			printf("%s\n", window.buffer.string);
			free(window.buffer.string);
		}
	}
	return (0);
}