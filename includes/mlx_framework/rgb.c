#include "mlx_framework.h"
#include "internal_framework.h"

t_rgb	rgba_to_rgb(t_rgba a)
{
	return ((t_rgb){
		a.r, a.g, a.b
	});
}

t_rgb	rgb_add(t_rgb a, t_rgb b)
{
	return ((t_rgb){
		a.r + b.r,
		a.g + b.g,
		a.b + b.b,
	});
}

t_rgb	rgb_multiply(t_rgb a, t_rgb b)
{
	return ((t_rgb){
		a.r * b.r,
		a.g * b.g,
		a.b * b.b
	});
}

t_rgb	rgb_scale(t_rgb a, double b)
{
	return ((t_rgb){
		a.r * b,
		a.g * b,
		a.b * b
	});
}

t_rgb	rgb_divide(t_rgb a, double b)
{
	return ((t_rgb){
		a.r / b,
		a.g / b,
		a.b / b
	});
}