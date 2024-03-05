/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducloux <pducloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:28:59 by pducloux          #+#    #+#             */
/*   Updated: 2024/03/05 15:57:57 by pducloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <sys/types.h>
# include "defines.h"


typedef struct s_pos {
	int	x;
	int	y;
}	t_pos;


typedef struct s_player {
	t_pos	pos;
	float	xx;
	float	yy;
	float	rad;
}	t_player;


/**
 * @brief The parser structure
 *
 * @var buffer		The buffer containing the file content
 * @var buffer_size	The size of the buffer
 * @var lines		The lines of the file
 * @var nlines		The number of lines
 * @var line_index	The current line index, is used to keep track while parsing
 */
typedef struct s_parser {
	char	*buffer;
	size_t	buffer_size;
	char	**lines;
	size_t	nlines;
	size_t	line_index;
}	t_parser;


/**
 * @brief The map structure
 * 
 * @var	buffer		The buffer containing the map
 * @var	buffer_size	The size of the buffer
 * @var	width		The width of the map
 * @var	height		The height of the map
 */
typedef struct s_map {
	char	*buffer;
	char	**map;
	size_t	width;
	size_t	height;
	t_pos	starting_pos;
}	t_map;


# ifdef LITTLE_ENDIAN

typedef union u_color {
	struct {
		u_int8_t	a;
		u_int8_t	r;
		u_int8_t	g;
		u_int8_t	b;
	};
	u_int32_t	value;
}	t_color;

# else

typedef union u_color {
	struct {
		u_int8_t	b;
		u_int8_t	g;
		u_int8_t	r;
		u_int8_t	a;
	};
	u_int32_t	value;
}	t_color;

# endif


/**
 * @brief A texture
 * 
 * @var data		Mlx texure data
 * @var width		Width of the texture
 * @var heigth		Height of the texture
 * @var bpp			Bytes per pixel
 * @var line_size	Line size
 * @var	endian		Big or little (big is 1, little 0)
 */
typedef struct s_texture_simple {
	void	*data;
	int		width;
	int		height;
	char	*raw;
	int		bpp;
	int		line_size;
	int		endian;
}	t_texture_simple;

/**
 * @brief Represent an animated texture
 * 
 * @var	texures		A texture buffer
 * @var count		Numer of texture in the buffer
 * @var current		Current index of the texture in the buffer
 */
typedef struct s_animated_texture {
	t_texture_simple	*textures;
	size_t				count;
	size_t				current;
}	t_animated_texture;

union u_texture {
	t_color				color;
	t_texture_simple	texture;
	t_animated_texture	animated_texture;
};

typedef struct s {
	t_texture_type	type;
	union u_texture	u_data;
}	t_texture;

typedef struct s_cub3d {
	t_parser		parser;
	t_map			map;
	t_texture		textures[TEXTURE_COUNT];
	struct s_mlx {
		void	*mlx;
		void	*window;
	} mlx;
}	t_cub3d;

#endif //CUB3D_TYPES_H
