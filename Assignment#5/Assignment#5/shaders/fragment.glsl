// ==========================================================================
// Vertex program for barebones GLFW boilerplate
//
// Author:  Sonny Chan, University of Calgary
// Date:    December 2015
// ==========================================================================
#version 410

// interpolated colour received from vertex stage
in vec2 uv;

// first output is mapped to the framebuffer's colour index by default
out vec4 FragmentColour;

uniform sampler2DRect imageTexture;

uniform int effects;		// Colour Effects and Edge Effects

mat3 verticalSobel = mat3(1, 2, 1,
						0, 0, 0,
						-1, -2, -1);

<<<<<<< HEAD
mat3 horizontalSobel = mat3(-1, 2, 1,
=======
mat3 horizontalSobel = mat3(-1, 0, 1,
>>>>>>> a4
						-2, 0, 2,
						-1, 0, -1);

mat3 unsharpSobel = mat3(0, -1, 0,
						-1, 5, -1,
						0, -1, 0);
																

void main(void)
{
    // write colour output without modification
    //FragmentColour = vec4(Colour, 0);
	vec4 temp = texture(imageTexture, uv);
	vec4 edgeEffectsVec;
	
	float value;
	
	
	// Colour Effects
	if(effects == 1){
		value = temp.x * 0.333 + temp.y * 0.333 + temp.z * 0.333;
		FragmentColour = vec4(value, value, value, 1);
	}
	
	if(effects == 2){
		value = temp.x * 0.299 + temp.y * 0.587 + temp.z * 0.114;
		FragmentColour = vec4(value, value, value, 1);
	}
	
	if(effects == 3){
		value = temp.x * 0.213 + temp.y * 0.715 + temp.z * 0.072;
		FragmentColour = vec4(value, value, value, 1);
	}
	
	if(effects == 4){
		value = temp.x * 0.1 + temp.y * 0.1 + temp.z * 0.8;
		FragmentColour = vec4(value, value, value, 1);	
	}
	
	if(effects == 0){
		FragmentColour = texture(imageTexture, uv);
	}
	
	
	// Edge Effects
	if(effects == 5){
		edgeEffectsVec = verticalSobel[0].x * texture(imageTexture, (uv + vec2(-1, 1))) + verticalSobel[0].y * texture(imageTexture, (uv + vec2(-1, 0))) + verticalSobel[0].z * texture(imageTexture, (uv + vec2(-1, -1))) + verticalSobel[2].x * texture(imageTexture, (uv + vec2(1, 1))) + verticalSobel[2].y * texture(imageTexture, (uv + vec2(1, 0))) + verticalSobel[2].z * texture(imageTexture, (uv + vec2(1, -1)));
		value = edgeEffectsVec.x * 0.333 + edgeEffectsVec.y * 0.333 + edgeEffectsVec.z * 0.333;		// convert image to grey and apply the filter to the luminance
		FragmentColour = vec4(value, value, value, 1);
	}
	
	if(effects == 6){
		edgeEffectsVec = horizontalSobel[0].x * texture(imageTexture, (uv + vec2(-1, 1))) + horizontalSobel[1].x * texture(imageTexture, (uv + vec2(0, 1))) + horizontalSobel[2].x * texture(imageTexture, (uv + vec2(1, 1))) + horizontalSobel[0].z * texture(imageTexture, (uv + vec2(-1, -1))) + horizontalSobel[1].z * texture(imageTexture, (uv + vec2(0, -1))) + horizontalSobel[2].z * texture(imageTexture, (uv + vec2(1, -1)));
		value = edgeEffectsVec.x * 0.333 + edgeEffectsVec.y * 0.333 + edgeEffectsVec.z * 0.333;		// convert image to grey and apply the filter to the luminance
		FragmentColour = vec4(value, value, value, 1);
	}
	
	if(effects == 7){
		edgeEffectsVec = unsharpSobel[0].y * texture(imageTexture, (uv + vec2(-1, 0))) + unsharpSobel[1].x * texture(imageTexture, (uv + vec2(0, 1))) + unsharpSobel[1].y * texture(imageTexture, (uv + vec2(0, 0))) + unsharpSobel[1].z * texture(imageTexture, (uv + vec2(0, -1))) + unsharpSobel[2].y * texture(imageTexture, (uv + vec2(1, 0)));
		value = edgeEffectsVec.x * 0.333 + edgeEffectsVec.y * 0.333 + edgeEffectsVec.z * 0.333;		// convert image to grey and apply the filter to the luminance
		FragmentColour = vec4(value, value, value, 1);
	}
	
	if(effects == 8){
		edgeEffectsVec = 0.04 * texture(imageTexture, (uv + vec2(-1, 1))) + 0.12 * texture(imageTexture, (uv + vec2(0, 1))) + 0.04 * texture(imageTexture, (uv + vec2(1, 1))) + 0.12 * texture(imageTexture, (uv + vec2(-1, 0))) + 0.36 * texture(imageTexture, (uv + vec2(0, 0))) + 0.12 * texture(imageTexture, (uv + vec2(1, 0))) + 0.04 * texture(imageTexture, (uv + vec2(-1, -1))) + 0.12 * texture(imageTexture, (uv + vec2(0, -1))) + 0.04 * texture(imageTexture, (uv + vec2(1, -1)));
		FragmentColour = vec4(edgeEffectsVec.x, edgeEffectsVec.y, edgeEffectsVec.z, 1);
	}
	

	if(effects == 9){
		edgeEffectsVec = 0.000131 * texture(imageTexture, (uv + vec2(-2, 2)))
		 + 0.002437 * texture(imageTexture, (uv + vec2(-1, 2)))
		  + 0.006312 * texture(imageTexture, (uv + vec2(0, 2)))
			 + 0.002437 * texture(imageTexture, (uv + vec2(1, 2)))
			  + 0.000131 * texture(imageTexture, (uv + vec2(2, 2)))
				 + 0.002437 * texture(imageTexture, (uv + vec2(-2, 1)))
				  + 0.045311 * texture(imageTexture, (uv + vec2(-1, 1)))
					 + 0.117369 * texture(imageTexture, (uv + vec2(0, 1)))
					  + 0.045311 * texture(imageTexture, (uv + vec2(1, 1)))
						 + 0.002437 * texture(imageTexture, (uv + vec2(2, 1)))
						  + 0.006312 * texture(imageTexture, (uv + vec2(-2, 0)))
							 + 0.117369 * texture(imageTexture, (uv + vec2(-1, 0)))
							  + 0.304019 * texture(imageTexture, (uv + vec2(0, 0)))
								 + 0.117369 * texture(imageTexture, (uv + vec2(1, 0)))
								  + 0.006312 * texture(imageTexture, (uv + vec2(2, 0)))
									 + 0.002437 * texture(imageTexture, (uv + vec2(-2, -1)))
									  + 0.045311 * texture(imageTexture, (uv + vec2(-1, -1)))
									 + 0.17369 * texture(imageTexture, (uv + vec2(0, -1)))
									  + 0.045311 * texture(imageTexture, (uv + vec2(1, -1)))
									 + 0.002437 * texture(imageTexture, (uv + vec2(2, -1)))
								  + 0.000131 * texture(imageTexture, (uv + vec2(-2, -2)))
							 + 0.002437 * texture(imageTexture, (uv + vec2(-1, -2)))
					  + 0.006312 * texture(imageTexture, (uv + vec2(0, -2)))
				 + 0.002437 * texture(imageTexture, (uv + vec2(1, -2)))
			 + 0.000131 * texture(imageTexture, (uv + vec2(2, -2)));
		FragmentColour = vec4(edgeEffectsVec.x, edgeEffectsVec.y, edgeEffectsVec.z, 1);
	}
	
	if(effects == 10){
		edgeEffectsVec = 0.000001 * texture(imageTexture, (uv + vec2(-2, 3)))
		 + 0.000016 * texture(imageTexture, (uv + vec2(-1, 3)))
		  + 0.000042 * texture(imageTexture, (uv + vec2(0, 3)))
			 + 0.000016 * texture(imageTexture, (uv + vec2(1, 3)))
			  + 0.000001 * texture(imageTexture, (uv + vec2(2, 3)))
				 + 0.000001 * texture(imageTexture, (uv + vec2(-3, 2)))
				  + 0.000131 * texture(imageTexture, (uv + vec2(-2, 2)))
					 + 0.002436 * texture(imageTexture, (uv + vec2(-1, 2)))
					  + 0.00631 * texture(imageTexture, (uv + vec2(0, 2)))
					 + 0.002436 * texture(imageTexture, (uv + vec2(1, 2)))
				  + 0.000131 * texture(imageTexture, (uv + vec2(2, 2)))
				 + 0.000001 * texture(imageTexture, (uv + vec2(3, 2)))
			  + 0.000016 * texture(imageTexture, (uv + vec2(-3, 1)))
			+ 0.002436 * texture(imageTexture, (uv + vec2(-2, 1)))
		  + 0.045297 * texture(imageTexture, (uv + vec2(-1, 1)))
			 + 0.117333 * texture(imageTexture, (uv + vec2(0, 1)))
				 + 0.045297 * texture(imageTexture, (uv + vec2(1, 1)))
					 + 0.002436 * texture(imageTexture, (uv + vec2(2, 1)))
						 + 0.000016 * texture(imageTexture, (uv + vec2(3, 1)))
							 + 0.000042 * texture(imageTexture, (uv + vec2(-3, 0)))
								  + 0.00631 * texture(imageTexture, (uv + vec2(-2, 0)))
										 + 0.117333 * texture(imageTexture, (uv + vec2(-1, 0)))
											  + 0.303926 * texture(imageTexture, (uv + vec2(0, 0)))
												 + 0.117333 * texture(imageTexture, (uv + vec2(1, 0)))
													  + 0.00631 * texture(imageTexture, (uv + vec2(2, 2)))
														+ 0.000042 * texture(imageTexture, (uv + vec2(3, 0)))
													+ 0.000016 * texture(imageTexture, (uv + vec2(-3, -1)))
												+ 0.002436 * texture(imageTexture, (uv + vec2(-2, -1)))
											+ 0.045297 * texture(imageTexture, (uv + vec2(-1, -1)))
										+ 0.117333 * texture(imageTexture, (uv + vec2(0, -1)))
									+ 0.045297 * texture(imageTexture, (uv + vec2(1, -1)))
								+ 0.002436 * texture(imageTexture, (uv + vec2(2, -1)))
							+ 0.000016 * texture(imageTexture, (uv + vec2(3, -1)))
						+ 0.000001 * texture(imageTexture, (uv + vec2(-3, -2)))
					+ 0.000131 * texture(imageTexture, (uv + vec2(-2, -2)))
						+ 0.002436 * texture(imageTexture, (uv + vec2(-1, -2)))
							+ 0.00631 * texture(imageTexture, (uv + vec2(0, -2)))
								+ 0.002436 * texture(imageTexture, (uv + vec2(1, -2)))
									+ 0.000131 * texture(imageTexture, (uv + vec2(2, -2)))
										+ 0.000001 * texture(imageTexture, (uv + vec2(3, -2)))
											+ 0.000001 * texture(imageTexture, (uv + vec2(-2, -3)))
												+ 0.000016 * texture(imageTexture, (uv + vec2(-1, -3)))
													+ 0.000042 * texture(imageTexture, (uv + vec2(0, -3)))
														+ 0.000016 * texture(imageTexture, (uv + vec2(1, -3)))
															+ 0.000001 * texture(imageTexture, (uv + vec2(2, -3)));
		FragmentColour = vec4(edgeEffectsVec.x, edgeEffectsVec.y, edgeEffectsVec.z, 1);
	}

	
	
	
	
	
}
