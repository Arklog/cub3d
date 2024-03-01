//
// Created by pierre on 2/5/24.
//

#ifndef TYPES_H
# define TYPES_H

# include <sys/types.h>
# include "defines.h"

typedef struct s_pos {
	int x;
	int y;
} t_pos;

typedef struct s_player {
	t_pos	pos;
	float	xx;
	float	yy;
	float	rad;
} t_player;

typedef struct s_map {
	struct {
		char	*filename;
		char	*raw_data;
		size_t	buffer_size;
	} file;
	const char      **buffer;
	const char		**lines;textures
	size_t			nlines;
	unsigned int	width;
	unsigned int	height;
} t_map;

typedef union u_color {
	struct {
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;
	};
	unsigned int value;
} t_color;

typedef struct s_texture_simple {
	char	*path;
	void	*data;
	int 	width;
	int 	height;
} t_texture_simple;

typedef struct s_animated_texture {
	t_texture_simple	*textures;
	size_t		count;
	size_t		current;
} t_animated_texture;

typedef struct s {
	t_texture_type type;
	union {
		t_color color;
		t_texture_simple texture;
		t_animated_texture animated_texture;
	} data;
} t_texture;

typedef struct s_cub3d {
	t_map			map;
	t_texture	textures[TEXTURE_COUNT];
	struct s_mlx {
		void	*mlx;
		void	*window;
	} mlx;
} t_cub3d;

#endif //CUB3D_TYPES_H
