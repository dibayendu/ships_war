#include "texture_loader_mac.h"

/*
 * The functions below have been directly taken from the course's website
 * and given functions for texturing.
 * Haven't quite explored how this works.
 */

int is_power_2(int val)
{
    int count = 0;
    while (val)
    {
        count += val & 1;
        val >>= 1;
    }
    return 1;//count == 1;
}

int texture_is_valid_dimensions(int width, int height)
{
    return is_power_2(width) && is_power_2(height);
}

void flip_data(char *data, int pitch, int height)
{
    /* Flip the rows of the image data in-place */
	
    char *row1 = data;
    char *row2 = data + (height - 1) * pitch;
    int x, y;
    char tmp;
	
    for (y = 0; y < height >> 1; y++)
    {
        for (x = 0; x < pitch; x++)
        {
            tmp = row1[x];
            row1[x] = row2[x];
            row2[x] = tmp;
        }
        row1 += pitch;
        row2 -= pitch;
    }
}

GLuint texture_load_data(unsigned char *data, int width, int height, 
                         int components, int pitch,
                         GLint internalFormat, GLenum format, GLenum type)
{
    GLuint id;
    int alignment;
    int row_length;
	
    /* If pitch is negative, flip order of rows from top-to-bottom to
	 bottom-to-top. */
    if (pitch < 0)
    {
        pitch = -pitch;
        flip_data(data, pitch, height);
    }
	
    if (pitch & 0x1)
        alignment = 1;
    else if (pitch & 0x2)
        alignment = 2;
    else
        alignment = 4;
    row_length = pitch / components;
	
    glPushClientAttrib(GL_CLIENT_PIXEL_STORE_BIT);
    glPixelStorei(GL_UNPACK_ALIGNMENT, alignment);
    glPixelStorei(GL_UNPACK_ROW_LENGTH, row_length);
	
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);      //we repeat the pixels in the edge of the texture, it will hide that 1px wide line at the edge of the cube, which you have seen in the video
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);      //we do it for vertically and horizontally (previous line)
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, 
                 type, data);

    glFinish();
	
    glPopClientAttrib();
	
    return id;
}

GLuint texture_load(const char *filename)
{
    FSSpec fss;
    ComponentInstance gi;
    Rect rect;
    GWorldPtr world;
	
    int width;
    int height;
    int pitch;
    unsigned char *buffer;
	
    GLuint id;
	
    NativePathNameToFSSpec(filename, &fss);
    GetGraphicsImporterForFile(&fss, &gi);
    GraphicsImportGetNaturalBounds(gi, &rect);
	
    width = rect.right;
    height = rect.bottom;
    pitch = width * 4;
    buffer = malloc(pitch * height);
    QTNewGWorldFromPtr(&world, k32ARGBPixelFormat, &rect, NULL, NULL, 0,
                       buffer, pitch);
	
    GraphicsImportSetGWorld(gi, world, NULL);
    GraphicsImportDraw(gi);
    DisposeGWorld(world);
    CloseComponent(gi);
	
    id = texture_load_data(buffer, width, height,
                           4, -pitch,
                           GL_RGBA, ARGB_FORMAT, ARGB_TYPE);
    free(buffer);
	
    return id;
}