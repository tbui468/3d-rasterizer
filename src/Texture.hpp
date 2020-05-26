#ifndef TEXTURE_H
#define TEXTURE_H

#include <windows.h>
#include <wingdi.h>
#include <string>
#include <fstream>

namespace paint {

class Texture {
private:
    Uint32* m_buffer;
    int m_width;
    int m_height;
public:
    Texture(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        BITMAPFILEHEADER bmFileHeader;
        file.read((char*)(&bmFileHeader), sizeof(bmFileHeader));

        BITMAPINFOHEADER bmInfoHeader;
        file.read((char*)(&bmInfoHeader), sizeof(bmInfoHeader));

        assert(bmInfoHeader.biBitCount == 24); //24 bit image (1 byte per color channel)
        assert(bmInfoHeader.biCompression == BI_RGB); //no compression, rgb only

        m_width = bmInfoHeader.biWidth;
        m_height = bmInfoHeader.biHeight;

        m_buffer = new Uint32[m_width * m_height];

        file.seekg(bmFileHeader.bfOffBits); //move to the start of the image information

        //each row size is a multiple of 4.
        //each pixel value is 3 bytes
        const int padding = (4 - m_width % 4) % 4;

        for(int row = m_height - 1; row >= 0; --row) {
            for(int col = 0; col < m_width; ++col) {
                putPixel(col, row, (char)file.get(), (char)file.get(), (char)file.get());
            }
            file.seekg(padding, std::ios::cur); //jump past the padding at end of rowp
        }
    }

    ~Texture() {
        delete[] m_buffer;
    }
    Texture(const Texture& other) = delete;
    Texture(Texture&& other) = delete;
    Texture& operator=(const Texture& other) = delete;
    Texture& operator=(Texture&& other) = delete;

    Uint32* getTexture() const {
        return m_buffer;
    }

    unsigned int getWidth() const {
        return m_width;
    }

    unsigned int getHeight() const {
        return m_height;
    }


private:
    void putPixel(int x, int y, char r, char g, char b)
    {
        //convert rgb to hex
        Uint32 color;
        color = r;
        color <<= 8;
        color += g;
        color <<= 8;
        color += b;
        color <<= 8;
        color += 0xff;
        m_buffer[y * m_width + x] = color;
    }
};

} // namespace paint

#endif //TEXTURE_H