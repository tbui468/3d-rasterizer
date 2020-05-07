#ifndef SHAPE_H
#define SHAPE_H

#define _USE_MATH_DEFINES
#include <vector>
#include <math.h>
#include "Math.hpp"
#include "Vertex.hpp"

namespace paint {

class Shape {
public:
    static Vertex makeRectangle(float width, float height){
        Vertex vertex;

        vertex.vertexArray.emplace_back(-width/2.0f, -height/2.0f);
        vertex.vertexArray.emplace_back(width/2.0f, -height/2.0f);
        vertex.vertexArray.emplace_back(width/2.0f, height/2.0f);
        vertex.vertexArray.emplace_back(-width/2.0f, height/2.0f);

        vertex.normalArray.emplace_back(0.0f, -1.0f);
        vertex.normalArray.emplace_back(1.0f, 0.0f);
        vertex.normalArray.emplace_back(0.0f, 1.0f);
        vertex.normalArray.emplace_back(-1.0f, 0.0f);

        vertex.indexArray.emplace_back(0,1,0);  
        vertex.indexArray.emplace_back(1,2,1);
        vertex.indexArray.emplace_back(2,3,2);
        vertex.indexArray.emplace_back(3,0,3);

        return vertex;
    }


    //8 sided circle (4 flares)
    static Vertex makeCircle(float radius) {
        return makeStar(radius, radius, 3);
    }

    static Vertex makeTriangle(float radius) {
        return makeStar(radius/2.0f, radius, 3);
    }

    //make star
    static Vertex  makeStar(float innerRadius, float outerRadius, unsigned int flares) {
        //first flare starts at top
        float angleIncrement = 2.0f * float(M_PI) / float(flares);
        float flareAngle = 0.0f;
        float insideAngle = angleIncrement / 2.0f;

        Vertex vertex;

        //vertex array
        for(unsigned int i = 0; i < flares; ++i) {
            //vertex pos
            vertex.vertexArray.emplace_back(outerRadius * cos(flareAngle), outerRadius * sin(flareAngle));
            vertex.vertexArray.emplace_back(innerRadius * cos(insideAngle), innerRadius * sin(insideAngle));


            flareAngle += angleIncrement;
            insideAngle += angleIncrement;
        }

        for(unsigned int i = 0; i < flares * 2; ++i) {
            //normal vertex
            Vec2 vec = vertex.vertexArray.at((i+1)%(flares*2)) - vertex.vertexArray.at(i);
            vec = vec * (1/vec.magnitude()); //normalize
            //rotate ccw by pi/2
            Mat2 rot = {{0.0f, -1.0f},{1.0f, 0.0f}};
            vec = rot * vec;
            vertex.normalArray.emplace_back(vec.x, vec.y);

            //index array
            vertex.indexArray.emplace_back(i, (i+1)%(flares*2), i); //replace zero with actual normal vector index
        }

        return vertex;
    }




};


}

#endif //SHAPE_H