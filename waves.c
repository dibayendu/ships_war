#include "waves.h"

GLOBAL_Waves waves; /* declared in waves.h */
GLOBAL_Normal normalDraw; /* declared in waves.h */

GLOBAL_Translate translateGrid; /* declared in waves.h */
GLOBAL_Rotate rotateGrid; /* declared in waves.h */

float lightPosition[] = {0.0f, 0.0f, 1.0f, 0.5f};

GLuint waterTexture;

/* draws the normal line with 0.1f of length from the axis of the grid. */
void drawNormalLine(float x, float y, float z, float normalX, float normalY, float normalZ)
{
	// Calculating the x,y,z co-ordinates of the normal
	float distance = getLength((normalX-x), (normalY-y), (normalZ-z));
	float normalLength = normalDraw.normalLength;
	float n = normalDraw.normalLength;
	float m = distance - n;
	
	//Dividing in the ration m:n
	float newX = ((normalX * n) + (x * m)) / (m+n);
	float newY = ((normalY * n) + (y * m)) / (m+n);
	float newZ= ((normalZ * n) + (z * m)) / (m+n);

	glColor3fv(colour.green);
	glBegin(GL_LINES);
	glVertex3f(x, y, z);
	glVertex3f(newX, newY, newZ);
	glEnd();
	glColor3fv(colour.white); // again making default colour to white..
}

void calculateAndDrawNormalLine(float x, float z)
{
	float y = getYAxisValue(x,z);
	GLOBAL_NORMAL_OF_A_POINT normal = calculateNormal(x, y, z);
	drawNormalLine(x, y, z, normal.X, normal.Y, normal.Z);
}

/*
 * goes through the rows and columns to draw the normals
 */
void drawNormal(void)
{
	int i, j;
	float width_row_ratio = ((float)waves.width / (float)waves.rows);
	float length_col_ratio = ((float)waves.length /(float)waves.cols); 
	float start_row = (float)(waves.width / 2) * (-1);
	for(j = 0 ; j < waves.rows; j++)
	{
		for(i = 0; i < waves.cols; i++)
		{
			float start_col = (float)(waves.length / 2) * (-1);
			float z = start_row + (width_row_ratio * j);
			float x = start_col + (length_col_ratio * i);
			calculateAndDrawNormalLine(x, z);
		
			z = start_row + (width_row_ratio * (j + 1));
			calculateAndDrawNormalLine(x, z);
		}
	}
}

/*
 * Shows the normals in the grid whenever necessary.
 */
void showNormal()
{
	if (normalDraw.linesEnabled == TRUE)
		drawNormal();
}

/*
 * Calculates the unit length of the vector.
 */
float getLength(float normalX, float normalY, float normalZ)
{
	return sqrt( (normalX*normalX) + (normalY*normalY) + (normalZ*normalZ) );
}

/*
 * Calculates the Normal value of the axis.
 */
float getNormalAxisValue(float axis1, float axis2)
{	
	float dy_dx_of_sinAxis = cosf((waves.noOfWaves*K*axis1) 
								  +	(waves.noOfWaves*PI*timing.calculatedTime))
	* sinf((waves.noOfWaves*K*axis2) 
		   + (waves.noOfWaves*PI*timing.calculatedTime))
	* waves.noOfWaves*K;
	float normalOfAxis = AMPLITUDE * dy_dx_of_sinAxis * waves.scaleFactor;
	
	return normalOfAxis;
}

/*
 * Calculates the value of the y point when x and z is given by using mathematical sin functions
 */
float getYAxisValue(float xAxis, float zAxis)
{
	float sinX = sinf((waves.noOfWaves*K*xAxis) 
					  + (waves.noOfWaves*PI*timing.calculatedTime));
	float sinZ = sinf((waves.noOfWaves*K*zAxis) 
					  + (waves.noOfWaves*PI*timing.calculatedTime));
	float sinY = AMPLITUDE * sinX * sinZ * waves.scaleFactor;
	
	return sinY;
}

/* normalises a point using gl functions when user asks for. */
void normalise_point(float x, float y, float z)
{
	if (normalDraw.shadowsEnabled == TRUE)
	{
		GLOBAL_NORMAL_OF_A_POINT normal = calculateNormal(x, y, z);
		glNormal3f(-normal.X, normal.Y, -normal.Z);
	}
}

/* does three different functionalities here. Normalises point and does 2D texturing. */
void normalise_draw_and_texture_coordinates(float x, float z, 
											float row_counter, float column_counter,
											float total_row_lines, float total_column_lines)
{
	float y = getYAxisValue(x,z);
	normalise_point(x, y, z);
	glTexCoord2f((row_counter/total_row_lines), (column_counter/total_column_lines));
	glVertex3f(x, y, z);
}

/* caculates triangle points in the row and draws them. */
void draw_single_row(int row_counter, float start_row, float width_row_ratio, float length_col_ratio)
{
	int i;
	float start_col = (float)(waves.length / 2) * (-1);
	glBegin(GL_TRIANGLE_STRIP);
	for(i = 0; i < waves.cols+1; i++)
	{
		float z = start_row + (width_row_ratio * row_counter);
		float x = start_col + (length_col_ratio * i);
		normalise_draw_and_texture_coordinates(x, z, row_counter, i, 
											   waves.rows, waves.cols);
		
		z = start_row + (width_row_ratio * (row_counter + 1));
		normalise_draw_and_texture_coordinates(x, z, (row_counter+1), 
												i, waves.rows, waves.cols);
	}
	glEnd();
}

/* Disables and enables shadows whenever required by the user */
void enable_shadow_lighting(void)
{
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

/* Disable lighting and shadows after making the water grid */
void disable_shadow_lighting(void)
{
	glDisable(GL_NORMALIZE);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
}

/* Draws the columns for the water grid to begin with. */
void draw_columns_rows()
{
	int i;
	
	float width_row_ratio = ((float)waves.width / (float)waves.rows);
	float length_col_ratio = ((float)waves.length /(float)waves.cols); 
	float start_row = (float)(waves.width / 2) * (-1);
	for(i = 0 ; i < waves.rows; i++)
	{
		draw_single_row(i, start_row, width_row_ratio, length_col_ratio);
	}
}

/*
 * Draws the water grid
 */
void drawGrid(void)
{
	glPolygonMode(GL_FRONT_AND_BACK, waves.polygonMode);
	
	if (normalDraw.shadowsEnabled == TRUE)
		enable_shadow_lighting();
	
	draw_columns_rows();
	
	if (normalDraw.shadowsEnabled == TRUE)
		disable_shadow_lighting();
}

/* mathematically calculates the normal of a point and return the struct*/
GLOBAL_NORMAL_OF_A_POINT calculateNormal(float x, float y, float z)
{
	GLOBAL_NORMAL_OF_A_POINT normal = {ZERO, ZERO, ZERO};

	normal.X = getNormalAxisValue(x, z);
	normal.Y = normalDraw.normalY;
	normal.Z = getNormalAxisValue(z, x);
	float unitLength = getLength(normal.X, normal.Y, normal.Z);
	
	// Divides the axis by unit length
	normal.X /=unitLength;	normal.Y /=unitLength;	normal.Z /=unitLength;
	
	return normal;
}


/* initialising the grid and the drawing of the normals */
void initGrid(void)
{
	GLOBAL_Translate initTranslateGrid = {0.0f, 0.0f, 0.0f};
	GLOBAL_Rotate initRotateGrid = {0.0f, 0.0f, 0.0f};
	
	GLOBAL_Waves initialWaves = {40, 40, 5, 5, 10, 0.1f, GL_FILL, 
		2.0f, -0.2f};
	GLOBAL_Normal initialNormalDraw = {1.0f, FALSE, TRUE, 0.1f};
	
	waves = initialWaves;
	normalDraw = initialNormalDraw;
	translateGrid = initTranslateGrid;
	rotateGrid = initRotateGrid;
	
	waterTexture = texture_load("images/water.jpg");
	if (!waterTexture)
    {
        printf("Water texture cannot be loaded. Exiting!\n");
        exit(EXIT_FAILURE);
    }	
}

/* displays the water and the sea bed beneath. */
void display_waves(void)
{
	glPushMatrix();
	glTranslatef(translateGrid.posX, translateGrid.posY, translateGrid.posZ);
	glRotatef(rotateGrid.rotX, THIS, NOT_THIS, NOT_THIS);
	glRotatef(rotateGrid.rotY, NOT_THIS, THIS, NOT_THIS);
	glRotatef(rotateGrid.rotZ, NOT_THIS, NOT_THIS, THIS);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, lightPosition);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightPosition);
	
	glEnable(GL_BLEND);
	glColor4fv(colour.alphaBlend);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);	
	glEnable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, waterTexture);
	
	drawGrid();
	
	glDisable(GL_TEXTURE_2D);
	
	showNormal();
	drawAxes();
	
	glPopMatrix();
}
