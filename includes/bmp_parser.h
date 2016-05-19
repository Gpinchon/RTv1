#ifndef BMP_PARSER_H
# define BMP_PARSER_H

# pragma pack(1)
typedef struct	s_bmp_header
{
	char		type[2];
	unsigned	size;
	short		reserved1;
	short		reserved2;
	unsigned	data_offset;
}				t_bmp_header;

typedef struct	s_bmp_info
{
	unsigned	header_size;
	int			width;
	int			height;
	short		color_planes;
	short		bpp;
	unsigned	compression_method;
	unsigned	size;
	int			horizontal_resolution;
	int			vertical_resolution;
	int			colors;
	int			important_colors;
}				t_bmp_info;
# pragma pack()

typedef struct	s_bmp_parser
{
	int					fd;
	t_bmp_header		header;
	unsigned			size_read;
	unsigned int		width, height;
}				t_bmp_parser;

#endif