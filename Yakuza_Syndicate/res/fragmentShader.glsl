
uniform sampler2D texture;

uniform vec4 teamColor;

void main() {
    vec2 texCoord = gl_TexCoord[0].xy;
    vec4 texPixel = texture2D(texture, texCoord);
    if(texPixel == vec4(0, 0, 0, 1) && gl_Color != vec4(1, 1, 1, 1)){
        texPixel = vec4(1, 1, 1, 1);
    }

    vec4 switchToColor = vec4(1, 0, 1, 1); //Magenta
    vec4 switchToShade = vec4(1, 1, 0, 1); //Yellow
    float alpha = min(gl_Color.a, texPixel.a);
    gl_FragColor = gl_Color * texPixel;
    if((gl_Color == switchToColor && alpha > 0.3) || texPixel == switchToColor) {
        gl_FragColor = teamColor;
    }
    else if((gl_Color == switchToShade && alpha > 0.3) || texPixel == switchToShade) {
        gl_FragColor = teamColor * vec4(0.8, 0.8, 0.8, 1);
    }
}