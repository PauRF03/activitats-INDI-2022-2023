#version 330 core

in vec3 fColor;
in vec3 matamb_interp;
in vec3 matdiff_interp;
in vec3 matspec_interp;
in float matshin_interp;

in vec4 vertexSCO;
in vec3 normalSCO;
in vec4 posFocusSCO;

uniform vec3 llumAmbient;
uniform vec3 colFocus;

in vec4 posSnitchEsqSCO;
in vec4 posSnitchDreSCO;

uniform vec3 colSnitchEsq;
uniform vec3 colSnitchDre;

uniform int translucid;
//--------------------------------------
out vec4 FragColor;
//--------------------------------------

//-------------------------------------------------------
//   Funció de soroll per fer efectes especials amb el shader
//	<https://www.shadertoy.com/view/4dS3Wd>
//	By Morgan McGuire @morgan3d, http://graphicscodex.com
//-------------------------------------------------------
float hash(float n) { return fract(sin(n) * 1e4); }
float hash(vec2 p) { return fract(1e4 * sin(17.0 * p.x + p.y * 0.1) * (0.1 + abs(sin(p.y * 13.0 + p.x)))); }

float noise(vec2 x) {
	vec2 i = floor(x);
	vec2 f = fract(x);

	// Four corners in 2D of a tile
	float a = hash(i);
	float b = hash(i + vec2(1.0, 0.0));
	float c = hash(i + vec2(0.0, 1.0));
	float d = hash(i + vec2(1.0, 1.0));

	// Same code, with the clamps in smoothstep and common subexpressions
	// optimized away.
	vec2 u = f * f * (3.0 - 2.0 * f);
        return mix(a, b, u.x) + (c - a) * u.y * (1.0 - u.x) + (d - b) * u.x * u.y-0.5;
}

//--------------------------------------
//    Funcions del model de Phong
//--------------------------------------

vec3 Ambient() {
    return llumAmbient * matamb_interp;
}

vec3 Difus (vec3 NormSCO, vec3 L, vec3 colFocus)
{
    // Tant sols retorna el terme difús
    // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats
    vec3 colRes = vec3(0);
    // Càlcul component difusa, si n'hi ha
    if (dot (L, NormSCO) > 0)
      colRes = colFocus * matdiff_interp * dot (L, NormSCO);
    return (colRes);
}

vec3 Especular (vec3 NormSCO, vec3 L, vec4 vertSCO, vec3 colFocus)
{
    // Tant sols retorna el terme especular!
    // Els vectors rebuts com a paràmetres (NormSCO i L) estan normalitzats
    vec3 colRes = vec3 (0);
    // Si la llum ve de darrera o el material és mate no fem res
    if ((dot(NormSCO,L) < 0) || (matshin_interp == 0))
      return colRes;  // no hi ha component especular

    // Calculem R i V
    vec3 R = reflect(-L, NormSCO); // equival a: 2.0*dot(NormSCO,L)*NormSCO - L;
    vec3 V = normalize(-vertSCO.xyz); // perquè la càmera està a (0,0,0) en SCO

    if (dot(R, V) < 0)
      return colRes;  // no hi ha component especular

    // Calculem i retornem la component especular
    float shine = pow(max(0.0, dot(R, V)), matshin_interp);
    return (matspec_interp * colFocus * shine);
}


//--------------------------------------
//    Mètode main
//--------------------------------------
void main()
{
    vec3 L = posFocusSCO.xyz - vertexSCO.xyz;
    vec3 llumDifosa = Difus(normalize(normalSCO), normalize(L), colFocus);
    vec3 llumEspecular = Especular(normalize(normalSCO), normalize(L), vertexSCO, colFocus);

    vec3 LEsq = posSnitchEsqSCO.xyz - vertexSCO.xyz;
    vec3 llumDifEsq = Difus(normalize(normalSCO), normalize(LEsq), colSnitchEsq);
    vec3 llumEspEsq = Especular(normalize(normalSCO), normalize(LEsq), vertexSCO, colSnitchEsq);

    vec3 LDre = posSnitchDreSCO.xyz - vertexSCO.xyz;
    vec3 llumDifDre = Difus(normalize(normalSCO), normalize(LDre), colSnitchDre);
    vec3 llumEspDre = Especular(normalize(normalSCO), normalize(LDre), vertexSCO, colSnitchEsq);

    if(translucid == 0){
        FragColor = vec4(llumDifosa + llumEspecular + Ambient() + llumEspEsq + llumDifEsq + llumEspDre + llumDifDre, 1);
    }else{
        FragColor = vec4(llumDifosa + llumEspecular + Ambient() + llumEspEsq + llumDifEsq + llumEspDre + llumDifDre, 0.5);
    }
}
