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

void	display_position(t_position pos_to_print)
{
	printf("x = %d; y = %d\n", pos_to_print.x, pos_to_print.y);
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
		buffer[i] = ' ';
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

void	display_border(t_window window)
{
	int	i;
	int	j;

	i = 0;
	while (i < window.height)
	{
		j = 0;
		while (j < window.width)
		{
			printf("-");
			j++;
		}
		printf("\n");
		i++;
	}
}

void	display_buffer(t_window window)
{
	int	i;
	int	x;
	int	y;

	x = 0;
	while (i < window.buffer.size)
	{
		if (x >= window.width)
		{
			x = 0;
			printf("\n");
		}
		printf("%c", window.buffer.string[i]);
		i++;
		x++;
	}
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
	int	p;
	int	dist_no_step;
	int	dist_step;

	dx = abs(pos2.x - pos1.x);
	dy = abs(pos2.y - pos1.y);
	p = 2 * dy - dx;
	dist_no_step = 2 * dy;
	dist_step = 2 * (dy - dx);

	int	x, y, x_end;
	if (pos1.x > pos2.x)
	{
		x = pos2.x;
		y = pos2.y;
		x_end = pos1.x;
	}
	else
	{
		x = pos1.x;
		y = pos1.y;
		x_end = pos2.x;
	}

	while (x < x_end)
	{
		x++;
		if (p < 0)
			p += dist_no_step;
		else
		{
			y++;
			p += dist_step;
		}
		write_in_buffer('#', window.buffer.string, window.buffer.size, position_to_index(create_position(x, y), window.width));
	}
}

int	main(int ac, char **av)
{
	t_window window;

	if (ac == 2 || 1)
	{
		init_window(&window, 4*64, 4*32);
		display_border(window);
		if (window.buffer.string)
		{
			t_position	pos1 = create_position(0, 0);
			t_position	pos2 = create_position(2*64, 2*32);
			draw_line(pos1, pos2, window);
			printf("%s\n", window.buffer.string);
			display_buffer(window);
			free(window.buffer.string);
		}
	}
	return (0);
}