#include "terrain_perlin_noise.h"

/* drawing the perlin terrain here by giving start and end point rows and columns. */
void draw_perlin_noise_terrain(float start_row, float end_row,
							   float start_col, float end_col,
							   float counter)
{
	float z = 0;
	glColor3f(1.0f, 1.0f, 1.0f);
	printf("\nstartcol= %f\tend_row = %f\tstart_col = %f\yend_col = %f\tcounter = %f\n",
		   start_row, end_row, start_col, end_col, counter);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (z = -6.0f; z <= 6.0f; z+= 0.1f) {
		float x;
		printf("\nhere\n");
		glBegin(GL_TRIANGLE_STRIP);
		for (x = -6.0f; x <= 6.0f; x += 0.1f) {
			float vec[] = {0, 0};
			vec[0] = x;
			vec[1] = z;
			float y = noise2(vec);
			glVertex3f(x, y, z);

			printf("\ny = %f\n", y);
			
			vec[0] = x;
			vec[1] = z+counter;
			y = noise2(vec);
			glVertex3f(x, y, z+counter);
			printf("\ny = %f\n", y);
		}
		glEnd();
	}
}

void initialise_perlin_noise_terrain()
{

}