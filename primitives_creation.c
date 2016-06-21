# include <rt.h>

t_primitive	new_sphere(t_vec3 position, float radius)
{
	t_primitive	p;

	p.radius = radius;
	p.radius2 = p.radius * p.radius;
	p.position = position;
	//p.intersect = intersect_sphere;
	//p.normal = sphere_normal;
	p.type = SPHERE;
	return(p);
}

t_primitive	new_cylinder(t_vec3 position, t_vec3 direction, float radius, float size)
{
	t_primitive	p;

	p.radius = radius;
	p.radius2 = p.radius * p.radius;
	p.size = size;
	p.position = position;
	p.direction = direction;
	//p.intersect = intersect_cylinder;
	//p.normal = cylinder_normal;
	p.type = CYLINDER;
	return(p);
}

t_primitive	new_cone(t_vec3 position, t_vec3 direction, float radius, float size)
{
	t_primitive	p;

	p.radius = TO_RADIAN(radius);
	p.radius2 = p.radius * p.radius;
	p.size = size;
	p.position = position;
	p.direction = direction;
	//p.intersect = intersect_cone;
	//p.normal = cone_normal;
	p.type = CONE;
	return(p);
}

t_primitive	new_plane(t_vec3 position, t_vec3 direction)
{
	t_primitive	p;

	p.position = position;
	p.direction = direction;
	//p.intersect = intersect_plane;
	//p.normal = plane_normal;
	p.type = PLANE;
	return(p);
}