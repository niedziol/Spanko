#include "object.h"

class Obstacle : public Object {
    public:
        Obstacle(int n, std::vector<Point> &vertices) : Object(n, vertices) {}
        void randomise();
};