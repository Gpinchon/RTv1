# include <rt.h>

float	trowbridge_reitz_specular(t_vec3 normal, t_vec3 viewdir, t_vec3 lightdir, float spec_power)
{					
	t_vec3 hdir;
	float NdotH;
	hdir = vec3_normalize(vec3_add(lightdir, viewdir));
	NdotH = vec3_dot(normal, hdir);
	return pow(1 / (1 + (1 - pow(NdotH, 2)) * spec_power), 2);
}

float	blinn_phong_specular(t_vec3 normal, t_vec3 viewdir, t_vec3 lightdir, float spec_power)
{
	t_vec3 hdir;
	hdir = vec3_normalize(vec3_add(lightdir, viewdir));
	return (pow(vec3_dot(hdir, normal), spec_power));
}

float oren_nayar_diffuse(t_vec3 normal, t_vec3 viewdir, t_vec3 lightdir, t_mtl mtl)
{
	float	fact[7];

	fact[0] = vec3_dot(lightdir, normal);
	fact[1] = vec3_dot(normal, viewdir);
	fact[2] = vec3_dot(lightdir, viewdir) - fact[0] * fact[1];
	fact[3] = float_lerp(1.0, fmax(fact[0], fact[1]), float_step(0.0, fact[2]));
	fact[4] = mtl.roughness * mtl.roughness;
	fact[5] = 1.0 + fact[4] * (mtl.albedo / (fact[4] + 0.13) + 0.5 / (fact[4] + 0.33));
	fact[6] = 0.45 * fact[4] / (fact[4] + 0.09);
	return clamp(mtl.albedo * fmax(0.0, fact[0]) * (fact[5] + fact[6] * fact[2] / fact[3]) / M_PI, 0, 1);
}

float	lambert_diffuse(t_vec3 normal, t_vec3 viewdir, t_vec3 lightdir, t_mtl mtl)
{
	return (clamp(mtl.albedo * vec3_dot(normal, lightdir) + mtl.roughness, 0, 1));
	return (viewdir.x);
}

t_vec3	compute_lightdir(t_light l, t_vec3 position)
{
	if (l.type == POINT || l.type == SPOT)
		return (vec3_normalize(vec3_substract(l.position, position)));
	else if (l.type == DIRECTIONAL)
		return (vec3_normalize(l.position));
	return (vec3_normalize(l.position));
}