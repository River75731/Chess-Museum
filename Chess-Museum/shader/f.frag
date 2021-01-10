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

	float diffuse  = NdotL >= 0.0 ? 1.0 * NdotL : 0.0;
	float specular = pow(NdotH, 32.0);

	gl_FragColor = vec4(0.1) + diffuse * texture2D(gSampler, TexCoord0.st);
	// * texture2D(gSampler, TexCoord0.st)
}


