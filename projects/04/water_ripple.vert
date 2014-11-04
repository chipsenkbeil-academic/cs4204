uniform float t;
const float pi = 3.1415926535;
const float num_ripples = 20.0;
const float height = 0.13;

void main()
{
    // The distance from the center
    float xDistance = gl_Vertex.x / 10.0;
    float yDistance = gl_Vertex.y / 10.0;
    float distance = sqrt((xDistance * xDistance) + (yDistance * yDistance));

    // Get the disposition from the base vertex
    float disposition = sin(distance * 2.0 * pi * num_ripples + t);

    // Calculate the new position
    vec3 normal = normalize(gl_Normal);
    vec3 update = gl_Vertex.xyz - normal * disposition * height;
    gl_Position = gl_ModelViewProjectionMatrix * vec4(update, 1.0);

    // Store the texture information for the fragment shader
    gl_TexCoord[0] = gl_MultiTexCoord0;
}

