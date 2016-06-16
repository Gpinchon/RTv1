void initcam( t_vec3 a_Pos, t_vec3 a_Target )
{
	// set eye and screen plane position
	t_vec3 m_Origin = new_vec3( 0, 0, -5 );
	t_vec3 m_P1 = new_vec3( -4,  3, 0 );
	t_vec3 m_P2 = new_vec3(  4,  3, 0 );
	t_vec3 m_P3 = new_vec3(  4, -3, 0 );
	t_vec3 m_P4 = new_vec3( -4, -3, 0 );
	// calculate camera matrix
	t_vec3 zaxis = vec3_substract(a_Target, a_Pos);
	zaxis = vec3_normalize(zaxis);
	t_vec3 up = new_vec3( 0, 1, 0 );
	t_vec3 xaxis = vec3_cross(up, zaxis);
	t_vec3 yaxis = vec3_cross(xaxis, vec3_negate(zaxis));
	t_mat4 cam_mat;
	cam_mat.m[0] = xaxis.x, cam_mat.m[1] = xaxis.y, cam_mat.m[2] = xaxis.z;
	cam_mat.m[4] = yaxis.x, cam_mat.m[5] = yaxis.y, cam_mat.m[6] = yaxis.z;
	cam_mat.m[8] = zaxis.x, cam_mat.m[9] = zaxis.y, cam_mat.m[10] = zaxis.z;
	cam_mat = m4_invert(cam_mat);
	cam_mat.m[3] = a_Pos.x, cam_mat.m[7] = a_Pos.y, cam_mat.m[11] = a_Pos.z;
	// move camera
	m_Origin = m4_mult_vec3(cam_mat, m_Origin );
	m_P1 = m4_mult_vec3(cam_mat, m_P1 );
	m_P2 = m4_mult_vec3(cam_mat, m_P2 );
	m_P3 = m4_mult_vec3(cam_mat, m_P3 );
	m_P4 = m4_mult_vec3(cam_mat, m_P4 );
	// calculate screen plane interpolation vectors
	t_vec3 m_DX = vec3_scale(vec3_substract(m_P2, m_P1), (1.0f / m_Width));
	t_vec3 m_DY = vec3_scale(vec3_substract(m_P4, m_P1), (1.0f / m_Height));
}