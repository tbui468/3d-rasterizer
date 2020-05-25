#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

namespace paint {

class Texture {
private:
    Uint32* m_buffer;
    unsigned int m_width;
    unsigned int m_height;
public:
    Texture(const std::string& filename) {

    }
};


}

#endif //TEXTURE_H