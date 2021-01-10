in vec3 normal;
in vec3 lightVec;
in vec3 viewVec;

in vec2 TexCoord0;

uniform sampler2D gSampler;

void main(){
	vec3 norm = normalize(normal);
	vec3 L = normalize(lightVec);
	vec3 V = normalize(viewVec);
	vec3 halfAngle = normalize(L + V);
	float NdotL = dot(L, norm);
	float NdotH = clamp(dot(halfAngle, norm), 0.0, 1.0);

    // "Half-Lambert" technique for more pleasing diffuse term
	float diffuse  = 1.0 * NdotL;
	float specular = pow(NdotH, 32.0);

    if (NdotL > 0.0)
	    gl_FragColor = diffuse * texture2D(gSampler, TexCoord0.st) + vec4(specular * 0.2);
    else
        gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
}


