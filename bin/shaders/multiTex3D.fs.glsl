#version 330 core

in vec2 vVertexTexture;

in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec2 vTexCoords; //
in vec4 vTotal;

out vec4 fFragColor;

uniform sampler2D uEarthTexture;
uniform sampler2D uCloudTexture;
uniform vec3 uKd;
uniform vec3 uKs;
uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;
uniform int uIsTransparent;

vec3 blinnPhong() {
// Directionnelle
    //return (uLightIntensity * (uKd*(dot( uLightDir_vs , vNormal_vs )) + uKs*pow(dot( (uLightDir_vs+normalize(-vPosition_vs))/2, vNormal_vs ),0.8)));
// Ponctuelle
    return (uLightIntensity/(distance( (vec3(vTotal.x+0.3,vTotal.y+0.5,vTotal.z-0)),uLightDir_vs)*distance((vec3(vTotal.x+0.3,vTotal.y+0.5,vTotal.z-0)),uLightDir_vs)) * (uKd*(dot( normalize(uLightDir_vs - vPosition_vs) , vNormal_vs )) + uKs*pow(dot( (normalize(uLightDir_vs - vPosition_vs)+normalize(-vPosition_vs))/2, vNormal_vs ),0.6)));
}

void main() {
    if(uIsTransparent == 0) {
        fFragColor = ((texture(uEarthTexture,vTexCoords)+texture(uCloudTexture,vTexCoords))*vec4(blinnPhong(),1));
        //fFragColor = vec4(blinnPhong(),1);
    } else {
        fFragColor = texture(uEarthTexture,vTexCoords);
    }
}
