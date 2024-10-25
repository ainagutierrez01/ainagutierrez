#version 330

varying vec3 v_world_normal;
varying vec3 v_world_position;
varying vec2 v_uv;

uniform sampler2D u_texture;
uniform sampler2D u_normal_map;

uniform vec3 u_light;
uniform vec3 u_camera;
uniform float u_alpha;
uniform vec3 u_ka;
uniform vec3 u_kd;
uniform vec3 u_ks;
uniform vec3 u_ia;
uniform vec3 u_id;
uniform vec3 u_is;
uniform vec3 u_opt;
uniform mat4 u_model;
uniform int u_flag;

void main() {
    vec4 texture_color = texture2D(u_texture, v_uv);
    vec3 final_normal;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 u_ip;

    if (u_opt.z == 1) {
        vec3 normal_map = 2.0 * texture2D(u_normal_map, v_uv).rgb - 1.0;
        vec3 world_normal = normalize(mat3(u_model) * normal_map);
        float mix_factor = 0.5;
        final_normal = mix(world_normal, normal_map, mix_factor);
    } else {
        final_normal = v_world_normal;
    }

    vec3 N = normalize(final_normal);
    vec3 L = normalize(u_light - v_world_position);
    vec3 V = normalize(u_camera - v_world_position);
    vec3 R = normalize(reflect(-L, N));

    vec3 ka = u_ia * texture_color.rgb;
    vec3 kd = texture_color.rgb;
    float alpha = texture_color.a;

    if (u_opt.x == 1) {
        ambient = ka * u_ia;
        diffuse =u_kd * clamp(dot(L, N), 0.0, 1.0) * u_id;
        specular = u_alpha * pow(clamp(dot(R, V), 0.0, 1.0), u_alpha) * u_is;

    
       
    } 

    else if(u_opt.x==0){
         ambient = u_ka * u_ia;
        diffuse =u_kd * clamp(dot(L, N), 0.0, 1.0) * u_id;
        specular = u_alpha * pow(clamp(dot(R, V), 0.0, 1.0), u_alpha) * u_is;

        
    }
    if (u_opt.y == 0) {
        vec3 ambient = u_ka * u_ia;
        vec3 diffuse = u_kd * clamp(dot(L, N), 0.0, 1.0) * u_id;
        vec3 specular = u_alpha * pow(clamp(dot(R, V), 0.0, 1.0), u_alpha) * u_is;
     
    }


    else if (u_opt.y == 1) {
         ambient = u_ka * u_ia;
         diffuse = kd * clamp(dot(L, N), 0.0, 1.0) * u_id;
         specular = alpha * pow(clamp(dot(R, V), 0.0, 1.0), u_alpha) * u_is;
     
    }

  

      if (u_flag == 0) {
            vec3 u_ip = ambient + (diffuse+ specular) / dot(L, L);
            gl_FragColor = vec4(u_ip, 1.0);
        } else {
            vec3 u_ip = (diffuse + specular) / dot(L, L);
            gl_FragColor = vec4(u_ip, 1.0);
        }
   

    
}
