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
        // TODO :: implement
    }

}