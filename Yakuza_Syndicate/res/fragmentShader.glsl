
uniform sampler2D texture;

uniform vec4 teamColor;

void main() {
    vec2 texCoord = gl_TexCoord[0].xy;
    vec4 texPixel = texture2D(texture, texCoord);

    vec4 switchToColor = vec4(1, 0, 1, 1); //Magenta
    vec4 switchToShade = vec4(1, 1, 0, 1); //Yellow

    if(texPixel == switchToColor || (gl_Color == switchToColor && texPixel.a > 0.5)) {
        gl_FragColor = teamColor;
    }
    else if(texPixel == switchToShade){
        gl_FragColor = teamColor * vec4(0.8, 0.8, 0.8, 1);
    }
    else{
        gl_FragColor = gl_Color * texPixel;
    }

}