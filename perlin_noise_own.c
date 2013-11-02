/* coherent noise function over 1, 2 or 3 dimensions */
/* (copyright Ken Perlin) */

#include "perlin_noise_own.h"

GLuint terrain_perlin_noise_own;

float Noise(int x, int y)
{
	int n = x + y * 57;
	n = pow( (n<<13), n);
	float value = ( 1.0 - ( (n * (n * n * 15731 + 789221) 
								+ 1376312589) & 0x7fffffff) / 1073741824.0); 
	return value;
}


float SmoothNoise1(float x, float y)
{
	float corners = ( Noise(x-1, y-1)+Noise(x+1, y-1)+
							Noise(x-1, y+1)+Noise(x+1, y+1) ) / 16;
	float sides   = ( Noise(x-1, y)  +Noise(x+1, y)  +
						Noise(x, y-1)  +Noise(x, y+1) ) /  8;
	float center  =  Noise(x, y) / 4;
	
	return corners + sides + center;
}

/* cosine interpolation*/
float Interpolate(float a, float b, float x)
{
	float ft = x * 3.1415927;
	float f = (1 - cos(ft)) * .5;

	return  a*(1-f) + b*f;
}

float InterpolatedNoise(float x, float y)
{
	int integer_X = (int)x;
	float fractional_X = x - integer_X;

	int integer_Y    = (int)y;
	float fractional_Y = y - integer_Y;

	float v1 = SmoothNoise1(integer_X, integer_Y);
	float v2 = SmoothNoise1(integer_X + 1, integer_Y);
	float v3 = SmoothNoise1(integer_X, integer_Y + 1);
	float v4 = SmoothNoise1(integer_X + 1, integer_Y + 1);

	float i1 = Interpolate(v1 , v2 , fractional_X);
	float i2 = Interpolate(v3 , v4 , fractional_X);

	return Interpolate(i1 , i2 , fractional_Y);
}

float PerlinNoise_2D(float x, float y)
{
	float total = 0;
	float p = .001f;//persistence;
	float n = 2.0f; //Number of octaves;

	int i = 0;
	for(i = 0; i < n; i++)
	{
		float frequency = pow(2, i);
		float amplitude = pow(p, i);

		total = total + InterpolatedNoise(x * frequency, y * frequency) 
																* amplitude;
	}

	return total;
}

void draw_terrain_own_noise(float starting_row, float ending_row, float starting_col, float ending_col, float counter)
{
	float x,z;
	float total_row_lines = waves.rows;
	float total_column_lines = waves.cols;
	float row_counter = INITIAL_TEXTURE;
	for(z=starting_row; z<=ending_row; z+=counter)
	{
		float column_counter = INITIAL_TEXTURE;
		glBegin(GL_TRIANGLE_STRIP);
		for(x=starting_col; x<=ending_col; x+=counter)
		{
			float y = PerlinNoise_2D(x, z);
			glTexCoord2f((row_counter/total_row_lines), (column_counter/total_column_lines));
			glVertex3f(x, y, z);
			
			y = PerlinNoise_2D(x, z+0.1);
			glTexCoord2f(((row_counter+1)/total_row_lines), (column_counter/total_column_lines));
			glVertex3f(x, y, z+0.1);
		
			column_counter++;
		}
		glEnd();
		row_counter++;
	}
}

void display_personal_perlin_noise(float starting_row, float ending_row, 
				float starting_col, float ending_col, float counter, 
					GLOBAL_Rotate rotate, GLOBAL_Translate translate, 
						float depth)
{
	glPushMatrix();
	glTranslatef(translate.posX, translate.posY - depth, translate.posZ); 
	glRotatef(rotate.rotX, 1.0f, 0.0f, 0.0f); 
	glRotatef(rotate.rotY, 0.0f, 1.0f, 0.0f); 
	glRotatef(rotate.rotZ, 0.0f, 0.0f, 1.0f); 
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, terrain_perlin_noise_own);
	draw_terrain_own_noise(starting_row, ending_row, starting_col, ending_col, counter);
	glDisable(GL_TEXTURE_2D);
	drawAxes();
	glPopMatrix();
}

void initialise_terrain_perlin_noise_own(void)
{
	terrain_perlin_noise_own = texture_load("images/sand.jpg");
	if (!terrain_perlin_noise_own)
	{
		printf("Terrain texture cannot be loaded. Exiting!\n");
		exit(EXIT_FAILURE);
	}	
}
