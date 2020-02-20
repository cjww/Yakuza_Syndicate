
uniform sampler2D texture;

uniform vec4 teamColor;

void main() {
    vec2 texCoord = gl_TexCoord[0].xy;
    //texCoord.x = 1.0 - texCoord.x;
    vec4 texPixel = texture2D(texture, texCoord); 
    if(texPixel == vec4(1, 0, 1, 1)){
        gl_FragColor = teamColor;
    }
    else if(texPixel == vec4(1, 1, 0, 1)){
        gl_FragColor = teamColor * vec4(0.8, 0.8, 0.8, 1);
    }
    else{
        gl_FragColor = gl_Color * texPixel;
    }

}