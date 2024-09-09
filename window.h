#ifndef WINDOW_H
# define WINDOW_H

typedef struct	s_window t_window;
typedef struct	s_buffer t_buffer;

struct s_buffer
{
	char	*string;
	int	size;
};

struct s_window
{
	int	width;
	int	height;
	t_buffer buffer;
};

#endif