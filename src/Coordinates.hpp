#ifndef COORDINATES_H
#define COORDINATES_H


struct Coordinates {
    int x;
    int y;

    bool operator==(const Coordinates& other) {
        return this->x == other.x && this->y == other.y;
    }
};

#endif //COORDINATES_H