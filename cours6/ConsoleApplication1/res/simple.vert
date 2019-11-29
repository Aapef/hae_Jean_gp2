#version 120

uniform float time;

void main()
{
	// transform the vertex position
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	if(gl_Vertex.x > 0.5) gl_Position.x -= 0.02*cos(time);
	if(gl_Vertex.x < 0.5) gl_Position.x += 0.02*cos(time);
	if(gl_Vertex.y > 0.5) gl_Position.y -= 0.02*cos(time+ 3.14);
	if(gl_Vertex.y < 0.5) gl_Position.y += 0.02*cos(time+ 3.14);
	gl_Position.x += 0.1*cos(time);
	gl_Position.y += 0.1*sin(time);
	


    // transform the texture coordinates
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0 ;

    // forward the vertex color

    gl_FrontColor = gl_Color * (gl_TexCoord[0].x + 0.5f);
		
	
}