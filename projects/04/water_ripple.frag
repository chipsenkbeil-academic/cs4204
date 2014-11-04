uniform float t;
uniform sampler2D leaf;
uniform sampler2D sky;

//varying float u, v;

void main()
{
    vec4 skyColor = texture2D(sky,gl_TexCoord[0].st);
    vec4 leafColor = texture2D(leaf,gl_TexCoord[0].st);    
    leafColor.a = 0.5;
    gl_FragColor = mix(skyColor, leafColor, leafColor.a);
}
