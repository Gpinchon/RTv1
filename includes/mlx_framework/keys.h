/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinchon <gpinchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/20 15:12:31 by gpinchon          #+#    #+#             */
/*   Updated: 2016/06/20 17:08:16 by gpinchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

# define NULLEVENT			0
# define KEYPRESS			2
# define KEYRELEASE			3
# define BUTTONPRESS		4
# define BUTTONRELASE		5
# define MOUSEMOVE			6
# define BUTTONPRESSMASK	4
# define KEYPRESSMASK		(1L<<0)
# define MOUSEMOVEMASK		64

# ifdef __APPLE__
#  define A_KEY				0x00
#  define S_KEY				0x01
#  define D_KEY				0x02
#  define F_KEY				0x03
#  define H_KEY				0x04
#  define G_KEY				0x05
#  define Z_KEY				0x06
#  define X_KEY				0x07
#  define C_KEY				0x08
#  define V_KEY				0x09
#  define B_KEY				0x0B
#  define Q_KEY				0x0C
#  define W_KEY				0x0D
#  define E_KEY				0x0E
#  define R_KEY				0x0F
#  define Y_KEY				0x10
#  define T_KEY				0x11
#  define ONE				0x12
#  define TWO				0x13
#  define THREE				0x14
#  define FOUR				0x15
#  define SIX				0x16
#  define FIVE				0x17
#  define EQUAL				0x18
#  define NINE				0x19
#  define SEVEN				0x1A
#  define MINUS				0x1B
#  define EIGHT				0x1C
#  define ZERO				0x1D
#  define RIGHTBRACKET		0x1E
#  define O_KEY				0x1F
#  define U_KEY				0x20
#  define LEFTBRACKET		0x21
#  define I_KEY				0x22
#  define P_KEY				0x23
#  define L_KEY				0x25
#  define J_KEY				0x26
#  define QUOTE				0x27
#  define K_KEY				0x28
#  define SEMICOLON			0x29
#  define BACKSLASH			0x2A
#  define COMMA				0x2B
#  define SLASH				0x2C
#  define N_KEY				0x2D
#  define M_KEY				0x2E
#  define PERIOD			0x2F
#  define GRAVE				0x32
#  define KEYPADDECIMAL		0x41
#  define KEYPADMULTIPLY	0x43
#  define KEYPADPLUS		0x45
#  define KEYPADCLEAR		0x47
#  define KEYPADDIVIDE		0x4B
#  define KEYPADENTER		0x4C
#  define KEYPADMINUS		0x4E
#  define KEYPADEQUALS		0x51
#  define KEYPAD0			0x52
#  define KEYPAD1			0x53
#  define KEYPAD2			0x54
#  define KEYPAD3			0x55
#  define KEYPAD4			0x56
#  define KEYPAD5			0x57
#  define KEYPAD6			0x58
#  define KEYPAD7			0x59
#  define KEYPAD8			0x5B
#  define KEYPAD9			0x5C
#  define RETURN			0x24
#  define TAB				0x30
#  define SPACE				0x31
#  define DELETE			0x33
#  define ESCAPE			0x35
#  define COMMAND			0x37
#  define SHIFT				0x38
#  define CAPSLOCK			0x39
#  define OPTION			0x3A
#  define CONTROL			0x3B
#  define RIGHTSHIFT		0x3C
#  define RIGHTOPTION		0x3D
#  define RIGHTCONTROL		0x3E
#  define FUNCTION			0x3F
#  define F17				0x40
#  define VOLUMEUP			0x48
#  define VOLUMEDOWN		0x49
#  define MUTE				0x4A
#  define F18_KEY			0x4F
#  define F19_KEY			0x50
#  define F20_KEY			0x5A
#  define F5_KEY			0x60
#  define F6_KEY			0x61
#  define F7_KEY			0x62
#  define F3_KEY			0x63
#  define F8_KEY			0x64
#  define F9_KEY			0x65
#  define F11_KEY			0x67
#  define F13_KEY			0x69
#  define F16_KEY			0x6A
#  define F14_KEY			0x6B
#  define F10_KEY			0x6D
#  define F12_KEY			0x6F
#  define F15_KEY			0x71
#  define HELP				0x72
#  define HOME				0x73
#  define PAGEUP			0x74
#  define FORWARDDELETE 	0x75
#  define F4_KEY			0x76
#  define END				0x77
#  define F2_KEY			0x78
#  define PAGEDOWN			0x79
#  define F1_KEY			0x7A
#  define LEFTARROW			0x7B
#  define RIGHTARROW		0x7C
#  define DOWNARROW			0x7D
#  define UPARROW			0x7E
#  define MAX_KEYS			300

# else

#  define A_KEY				97
#  define D_KEY				100
#  define E_KEY				101
#  define Q_KEY				113
#  define S_KEY				115
#  define R_KEY				114
#  define W_KEY				119
#  define Z_KEY				122
#  define UP				65362
#  define DOWN				65364
#  define RIGHT				65363
#  define LEFT				65361
#  define ESC				65307
#  define PLUS				65451
#  define MINUS				65453
#  define NUM_0				65438
#  define NUM_1				65436
#  define NUM_2				65433
#  define NUM_3				65435
#  define NUM_4				65430
#  define NUM_5				65437
#  define NUM_6				65432
#  define NUM_7				65429
#  define NUM_8				65431
#  define NUM_9				65434
#  define MAX_EVENTS		70000

# endif
#endif
