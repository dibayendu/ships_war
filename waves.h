#ifndef WAVES_H
#define WAVES_H

#include "gl.h"
#include "axes.h"
#include "utility.h"
#include "texture_loader_mac.h"

#define AMPLITUDE -0.5f
#define LAMBDA 1.0f
#define K PI/LAMBDA
#define WAVE_HEIGHT 0.1
#define MAXIMUM_WAVE_HEIGHT 0.5
#define MINIMUM_WAVE_HEIGHT 0.0

typedef struct
{
	int rows;
	int cols;
	int length;
	int width;
	int constant;
	float scaleFactor;
	GLenum polygonMode;
	float noOfWaves;
	float seaBedDepth;
}GLOBAL_Waves;

typedef struct
{
	float normalY;
	int linesEnabled;
	int shadowsEnabled;
	float normalLength;
}GLOBAL_Normal;

typedef struct
{
	float X;
	float Y;
	float Z;
}GLOBAL_NORMAL_OF_A_POINT;

extern GLOBAL_Waves waves;  /* initialised in waves.c */
extern GLOBAL_Normal normalDraw; /* initialised in waves.c */
extern GLOBAL_Translate translateGrid; /* initialised in waves.c */
extern GLOBAL_Rotate rotateGrid; /* initialised in waves.c */

void drawSeaBed(void);
void drawGrid(void);
float getYAxisValue(float, float);
float getNormalAxisValue(float, float);
float getLength(float, float, float);
void drawNormal(void);
void showNormal(void);
void initGrid(void);
void display_waves(void);
void drawNormalLine(float, float, float, float, float, float);
GLOBAL_NORMAL_OF_A_POINT calculateNormal(float, float, float);
void calculateAndDrawNormalLine(float, float);
float calculate_lines(float, float);
void normalise_point(float, float, float);
void normalise_draw_and_texture_coordinates(float, float, float, float, float, float);
void draw_single_row(int, float, float, float);
void enable_shadow_lighting(void);
void disable_shadow_lighting(void);
void draw_columns_rows(void);

#endif

