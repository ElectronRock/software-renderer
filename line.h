/* Copyright (C) 2022 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/software-renderer
 */

#pragma once

#include <vector>
#include <cmath>

struct point final {
    int x;
    int y;
};

namespace line {

    template<typename TPointSetter>
    void brezenhaim(point p1, point p2, TPointSetter&& setter) {
        bool reversed = false;
        if (std::abs(p1.x - p2.x) < std::abs(p1.y - p2.y)) {
            reversed = true;
            std::swap(p1.x, p1.y);
            std::swap(p2.x, p2.y);
        }
        if (p1.x > p2.x) {
            std::swap(p1, p2);
        }
        float Dy = (float)(p2.y - p1.y) / (float)(p2.x - p1.x);
        float cur_y = p1.y;
        for(int cur_x = p1.x; cur_x < p2.x; cur_x++) {
            cur_y += Dy;
            if(!reversed) setter(cur_x, (int)cur_y);
            else setter((int)cur_y, cur_x);
        }
    }

}
