
varying vec2 v_uv;
uniform float u_option;
uniform sampler2D u_texture;
uniform sampler2D u_texture2;
uniform float u_time;
uniform float u_speed;

void main() {
    gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);

    if(u_option ==1.1){

        vec3 color = mix(vec3(0.0,0.0,1.0), vec3(1.0,0.0,0.0), v_uv.x);
	    gl_FragColor = vec4(color,1.0);
    
    }

    if(u_option==1.2){
        vec2 center = vec2(0.5, 0.5);
	    gl_FragColor = distance(v_uv, center) * vec4(1.0, 1.0, 1.0, 1.0);
    }

    if(u_option==1.3){
       float sin = sin(20*3.14*v_uv.x);
       float cos = cos(20*3.14*v_uv.y);
       vec3 color = vec3(sin,0.0, cos);
       gl_FragColor = vec4(color, 1.0);
    }

    if(u_option==1.4){
        vec2 grid = vec2 (30,30);
	    gl_FragColor = vec4(floor(v_uv*grid)/grid, 0.0,1.0);
    }

    if(u_option==1.5){
        float square = mod(floor(v_uv.x * 10.0) + floor(v_uv.y * 10.0), 2.0);
        vec3 color = vec3(square);
        gl_FragColor = vec4(color, 1.0);
    }

    if(u_option==1.6){
        float y = step(v_uv.y, 0.3*sin(2.0*3.14*v_uv.x)+0.5);
        vec3 color = vec3(0.0, 0.0, 0.0);
        color = mix(vec3(0.0, 1.0, 0.0), vec3(0.0, 0.0, 0.0), distance(v_uv.y, y));
        gl_FragColor = vec4(color, 1.0);
    }



    if(u_option==2.1){
        vec4 texture_color = texture2D(u_texture2, vec2(v_uv.x, 1.0 - v_uv.y));
        float color = (texture_color.r + texture_color.g + texture_color.b) / 3.0;
        gl_FragColor = vec4(vec3(color), texture_color.a);
    }


    if(u_option==2.2){
        vec4 texture_color = texture2D(u_texture2, vec2(v_uv.x, 1.0 - v_uv.y));
        gl_FragColor = vec4(1.0) - texture_color;
    }

    if(u_option==2.3){
        vec4 texture_color = texture2D(u_texture2, vec2(v_uv.x, 1.0 - v_uv.y));
        float color = (texture_color.r + texture_color.g) / 2.0; 
        gl_FragColor = vec4(color, color, 0.0, texture_color.a);
    }

    if(u_option==2.4){
        vec4 texture_color = texture2D(u_texture2, vec2(v_uv.x, 1.0 - v_uv.y)); 
        const float threshold = 0.5;
        float color = (texture_color.r + texture_color.g + texture_color.b) / 3.0;
        gl_FragColor = vec4(vec3(step(threshold, color)), texture_color.a);
    }

    if(u_option==2.5){
      vec4 texture_color = texture2D(u_texture2, vec2(v_uv.x, 1.0 - v_uv.y)); 
      vec2 center = vec2(0.5, 0.5);
      float d = distance(center, v_uv);
	  gl_FragColor = (1-d) * texture_color;
    }

    if (u_option==2.6){
        vec4 color = vec4(0.0);
        const float u_texelSize=0.01;
        color += texture2D(u_texture2, vec2(v_uv.x, 1.0 - v_uv.y) + vec2(0.0, u_texelSize));
        color += texture2D(u_texture2, vec2(v_uv.x, 1.0 - v_uv.y) + vec2(0.0, -u_texelSize));
        color += texture2D(u_texture2, vec2(v_uv.x, 1.0 - v_uv.y) + vec2(u_texelSize, 0.0));
        color += texture2D(u_texture2, vec2(v_uv.x, 1.0 - v_uv.y) + vec2(-u_texelSize, 0.0));
        color += texture2D(u_texture2, vec2(v_uv.x, 1.0 - v_uv.y) + vec2(-u_texelSize, u_texelSize));
        color += texture2D(u_texture2, vec2(v_uv.x, 1.0 - v_uv.y) + vec2(u_texelSize, -u_texelSize));
        color += texture2D(u_texture2, vec2(v_uv.x, 1.0 - v_uv.y) + vec2(u_texelSize, u_texelSize));
        color += texture2D(u_texture2, vec2(v_uv.x, 1.0 - v_uv.y) + vec2(-u_texelSize, -u_texelSize));
        
        gl_FragColor = color / 9.0;
     }

     if (u_option==3.1){

        float bright = abs(cos(u_time)); 
        vec4 texColor = texture2D(u_texture, v_uv);
        vec3 finalColor = texColor.rgb * bright;
        gl_FragColor = vec4(finalColor, texColor);


     }

     if (u_option==3.2){
       vec2 size = vec2(2000,800);
        vec2 mosaic = floor(v_uv*size/(u_time*2))*(u_time*2)/size;
        gl_FragColor = texture2D(u_texture, mosaic);

     }
}