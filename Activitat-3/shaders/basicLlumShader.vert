#version 330 core

//-------------------------------
in vec3 vertex;
in vec3 normal;
in vec3 matamb;
in vec3 matdiff;
in vec3 matspec;
in float matshin;

out vec4 vertexSCO;
out vec3 normalSCO;

out vec3 matamb_interp;
out vec3 matdiff_interp;
out vec3 matspec_interp;
out float matshin_interp;
//-------------------------------
uniform mat4 proj;
uniform mat4 view;
uniform mat4 TG;

uniform vec3 posFocusSCA;
out vec4 posFocusSCO;

uniform vec3 posSnitchEsq;
uniform vec3 posSnitchDre;
out vec4 posSnitchEsqSCO;
out vec4 posSnitchDreSCO;
//-------------------------------
out vec3 fColor;


void main()
{	
    fColor = matdiff;
    matamb_interp  = matamb;
    matdiff_interp = matdiff;
    matspec_interp = matspec;
    matshin_interp = matshin;

    mat3 NormalMatrix = transpose(inverse(mat3(view * TG)));
    normalSCO = NormalMatrix * normal;
    vertexSCO = view * TG * vec4(vertex, 1.0);

    posSnitchEsqSCO = view * TG * vec4(posSnitchEsq, 1.0);
    posSnitchDreSCO = view * TG * vec4(posSnitchDre, 1.0);

    posFocusSCO = inverse(view) * vec4(posFocusSCA, 1);

    gl_Position = proj *  vertexSCO;
}
