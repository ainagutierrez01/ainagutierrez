// Global variables from the CPU
uniform mat4 u_model;
uniform mat4 u_viewprojection;

// Variables to pass to the fragment shader
varying vec2 v_uv;
varying vec3 v_world_position;
varying vec3 v_world_normal;
varying vec3 u_ip;

// Variables for light equation
uniform vec3 u_light;
uniform vec3 u_camera;
uniform float u_alpha;
uniform vec3 u_ka;
uniform vec3 u_kd;
uniform vec3 u_ks;
uniform vec3 u_ia;
uniform vec3 u_id;
uniform vec3 u_is;

void main()
{	
	v_uv = gl_MultiTexCoord0.xy;

	// Convert local position to world space
	vec3 world_position = (u_model * vec4( gl_Vertex.xyz, 1.0)).xyz;

	// Convert local normal to world space
	vec3 world_normal = (u_model * vec4( gl_Normal.xyz, 0.0)).xyz;

	// Pass them to the fragment shader interpolated
	v_world_position = world_position;
	v_world_normal = world_normal;

    vec3 N = normalize(v_world_normal);
    vec3 L = normalize(u_light - v_world_position);
    vec3 V = normalize(u_camera - v_world_position);
    vec3 R = normalize(reflect(-L, N));

    u_ip = (u_ka * u_ia) + (u_kd * clamp(dot(L, N), 0.0, 1.0) * u_id) + (u_alpha * pow(clamp(dot(R, V), 0.0, 1.0), u_alpha) * u_is);

	// Project the vertex using the model view projection matrix
	gl_Position = u_viewprojection * vec4(world_position, 1.0); //output of the vertex shader
}


