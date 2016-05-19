#include "mlx_framework.h"
#include "internal_framework.h"

t_rgba	rgb_to_rgba(t_rgb a)
{
	return ((t_rgba){
		a.r, a.g,
		a.b, 255
	});
}

t_rgba	rgba_add(t_rgba a, t_rgba b)
{
	return ((t_rgba){
		a.r + b.r,
		a.g + b.g,
		a.b + b.b,
		a.a + b.a
	});
}

t_rgba	rgba_multiply(t_rgba a, t_rgba b)
{
	return ((t_rgba){
		a.r * b.r,
		a.g * b.g,
		a.b * b.b,
		a.a * b.a
	});
}

t_rgba	rgba_scale(t_rgba a, double b)
{
	return ((t_rgba){
		a.r * b,
		a.g * b,
		a.b * b,
		a.a * b
	});
}