#include <assert.h>

#include "utils.h"

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

void handle_glfw_error(char *func_name)
{
    const char *description;
    int code = glfwGetError(&description);
    fprintf(stderr, "/!\\ GLFW error %i using %s: %s\n", code, func_name, description);
}

void handle_glew_error(int code, char *func_name)
{
    fprintf(stderr, "/!\\ GLEW error %i using %s: %s\n", code, func_name, glewGetErrorString(code));
}

int get_file_length(FILE *file)
{
    fseek(file, 0L, SEEK_END);
    int length = ftell(file);
    fseek(file, 0L, SEEK_SET);
    return length;
}

GLuint load_dds(const char *imagepath)
{
    unsigned char header[124];

    FILE *file = fopen(imagepath, "rb");
    assert(file != NULL);

    /* verify the type of file */
    char filecode[4];
    fread(filecode, 1, 4, file);
    if (strncmp(filecode, "DDS ", 4) != 0)
    {
        fclose(file);
        return 0;
    }

    /* get the surface desc */
    fread(&header, 124, 1, file);

    unsigned int height = *(unsigned int *)&(header[8]);
    unsigned int width = *(unsigned int *)&(header[12]);
    unsigned int linearSize = *(unsigned int *)&(header[16]);
    unsigned int mipMapCount = *(unsigned int *)&(header[24]);
    unsigned int fourCC = *(unsigned int *)&(header[80]);

    unsigned char *buffer;
    unsigned int bufsize;
    /* how big is it going to be including all mipmaps? */
    bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    buffer = (unsigned char *)malloc(bufsize * sizeof(unsigned char));
    fread(buffer, 1, bufsize, file);
    /* close the file pointer */
    fclose(file);

    unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
    unsigned int format;
    switch (fourCC)
    {
    case FOURCC_DXT1:
        format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
        break;
    case FOURCC_DXT3:
        format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
        break;
    case FOURCC_DXT5:
        format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
        break;
    default:
        free(buffer);
        return 0;
    }

    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    unsigned int offset = 0;

    /* load the mipmaps */
    for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
    {
        unsigned int size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;
        glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
                               0, size, buffer + offset);

        offset += size;
        width /= 2;
        height /= 2;

        // Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
        if (width < 1)
            width = 1;
        if (height < 1)
            height = 1;
    }

    free(buffer);

    return textureID;
}
