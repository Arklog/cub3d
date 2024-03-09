/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pducloux <pducloux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:20:13 by pducloux          #+#    #+#             */
/*   Updated: 2024/03/08 16:02:28 by pducloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

/**
 * ID of the textures in the map file,
 * EG 0x4f42 is "NO" in 2 byte representation
 */
# ifdef LITTLE_ENDIAN
#  define NORTH_ID		0x4f4e
#  define SOUTH_ID		0x4f53
#  define WEST_ID		0x4557
#  define EAST_ID		0x4145
#  define FLOOR_ID		0x46
#  define CEILING_ID	0x43
# else
#  define NORTH_ID		0x4e4f
#  define SOUTH_ID		0x534f
#  define WEST_ID		0x5745
#  define EAST_ID		0x4541
#  define FLOOR_ID		0x46
#  define CEILING_ID	0x43
# endif

# define ESC 			65307
# define KEY_A 			97
# define KEY_D 			100
# define KEY_W 			119
# define KEY_S 			115
# define KEY_LEFT		65361
# define KEY_RIGHT		65363
# define WIN_LENGHT 	1440
# define WIN_HEIGHT 	900
# define TILE 			256


/**
 * The map symbols
 */
# define WALL '1'
# define EMPTY '0'
# define NORTH 'N'
# define SOUTH 'S'
# define WEST 'W'
# define EAST 'E'
# define NONE ' '
# define PLAYERSTR "NSWE"
# define MAP_ALLOWED_CHAR "NSEW01 \f\n\r\t\v"


/**
 * Is used to check if each texture is loaded
 * same as 0011111 in binary
 */
# define TEXTURES_FLAG_FULL 63


/**
 * The error codes
 */
typedef enum e_errors {
	E_NO_ERROR = 0,
	E_INVALID_ARGUMENTS,
	E_MLX_INIT,
	E_MLX_WINDOW,
	E_MLX_IMAGE,
	E_MLX_LOOP_HOOK,
	E_MLX_LOOP,
	E_MAP_ERROR,
	E_MAP_FILE_ERROR,
	E_MAP_INVALID_EXTENSION,
	E_MAP_INVALID_DIMENSIONS,
	E_MAP_INVALID_CHAR,
	E_MAP_INVALID_WALL,
	E_MAP_NO_STARTPOS,
	E_MAP_MULTIPLE_STARTPOS,
	E_TEXTURE_ERROR,
	E_TEXTURE_MISSING,
	E_TEXTURE_ALREADY_LOADED,
	E_TEXTURE_INVALID_PATH,
	E_COLOR_INVALID,
	E_ALLOCATION_FAILURE,
	E_IO_ERROR,
	E_ERROR_COUNT,
}	t_errors;


/**
 * The index of the textures one loaded in the buffer
 */
typedef enum e_texture_index {
	TEXTURE_NORTH,
	TEXTURE_SOUTH,
	TEXTURE_WEST,
	TEXTURE_EAST,
	TEXTURE_FLOOR,
	TEXTURE_CEILING,
	TEXTURE_COUNT,
}	t_texture_index;


/**
 * The differents kinds of texture, is used to allow some kind
 * of polymorphism
 */
typedef enum e_texture_type {
	T_COLOR,
	T_TEXTURE,
	T_ANIMATED_TEXTURE,
}	t_texture_type;

#endif //CUB3D_DEFINES_H
