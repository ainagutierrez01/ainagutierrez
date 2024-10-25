// This variables comes from the vertex shader
// They are baricentric interpolated by pixel according to the distance to every vertex
varying vec3 v_world_normal;
varying vec2 v_uv;
varying vec3 u_ip;
void main()
{
	// Set the ouput color per pixel
	//vec3 color = normalize(v_world_normal);
	gl_FragColor = vec4( u_ip, 1.0 );
}