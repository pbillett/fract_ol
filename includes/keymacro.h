/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keymacro.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbillett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 14:44:56 by pbillett          #+#    #+#             */
/*   Updated: 2017/04/12 11:57:35 by pbillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYMACRO_H
# define KEYMACRO_H

# if MACROKEY == 1
#  define EXIT 53
#  define KEY_W 13
#  define KEY_D 2
#  define KEY_C 8
#  define KEY_E 14
#  define KEY_F 3
#  define KEY_V 9
#  define KEY_R 15
#  define KEY_G 5
#  define KEY_B 11
#  define KEY_T 17
#  define KEY_H 4
#  define KEY_N 45
#  define KEY_P 35
#  define KEY_TAB 48
#  define KEY_TILD 50
#  define L_ARROW 123
#  define R_ARROW 124
#  define U_ARROW 126
#  define D_ARROW 125
#  define BACKSLASH 47
#  define EXCLAMMARK 44
#  define INSERT 117
#  define NUM_U 91
#  define NUM_D 84
#  define NUM_R 88
#  define NUM_L 86
#  define NUM_1 83
#  define NUM_2 84
#  define NUM_3 85
#  define NUM_4 86
#  define ZOOM_P 69
#  define ZOOM_M 78
#  define PAGE_U 116
#  define PAGE_D 121
#  define KEY_1 18
#  define KEY_2 19
#  define KEY_3 20
#  define KEY_4 21
#  define KEY_5 23
#  define KEY_I 34
#  define F1 23
#  define F2 83
#  define F3 84
#  define F4 85
#  define SPACE 49
#  define MOUSE_R 2
# else
#  define EXIT 65307
#  define KEY_W 122
#  define KEY_D 100
#  define KEY_C 99
#  define KEY_E 101
#  define KEY_F 102
#  define KEY_V 118
#  define KEY_R 114
#  define KEY_G 103
#  define KEY_B 98
#  define KEY_T 116
#  define KEY_H 104
#  define KEY_N 110
#  define KEY_P 112
#  define KEY_TAB 65289
#  define KEY_TILD 48
#  define L_ARROW 65361
#  define R_ARROW 65363
#  define U_ARROW 65362
#  define D_ARROW 65364
#  define BACKSLASH 33
#  define EXCLAMMARK 58
#  define INSERT 65379
#  define NUM_U 65431
#  define NUM_D 65433
#  define NUM_R 65432
#  define NUM_L 65430
#  define NUM_1 65436
#  define NUM_2 65433
#  define NUM_3 65435
#  define NUM_4 65430
#  define ZOOM_P 65451
#  define ZOOM_M 65453
#  define PAGE_U 65365
#  define PAGE_D 65366
#  define KEY_1 38
#  define KEY_2 233
#  define KEY_3 34
#  define KEY_4 39
#  define KEY_5 40
#  define KEY_I 105
#  define F1 65470
#  define F2 65471
#  define F3 65472
#  define F4 65473
#  define SPACE 32
#  define MOUSE_R 3
# endif
#endif
