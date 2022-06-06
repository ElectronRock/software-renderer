#include "renderer.h"
#include "model.h"
#include "line.h"
#include "rmath.h"
#include <cstdint>

namespace renderer {

    void convert_draw(vector3f p1, vector3f p2, tga_image& in_image, const tga_image::color& in_color) {
        p1.x = (p1.x + 1) * in_image.size().first / 2;
        p1.y = (1 - p1.y ) * in_image.size().second / 2;
        p2.x = (p2.x + 1) * in_image.size().first / 2;
        p2.y = (1 - p2.y) * in_image.size().second / 2;
        line::brezenhaim({(int)p1.x, (int)p1.y}, {(int)p2.x, (int)p2.y}, [&](int x, int y){in_image.set(x, y, in_color);});
    }

    void wireframe(const model& in_model, tga_image& in_image, const tga_image::color& in_color) {
        auto&& vertices = in_model.get_vert();
        for(auto&& [p0, p1, p2] : in_model.get_trian()) {
            convert_draw(vertices[p0], vertices[p1], in_image, in_color);
            convert_draw(vertices[p1], vertices[p2], in_image, in_color);
            convert_draw(vertices[p2], vertices[p0], in_image, in_color);
        }
    }

    vector3i to_ss(const vector3f& p, tga_image& in_image) {
        vector3i p_new;
        p_new.x = (p.x + 1) * in_image.size().first / 2;
        p_new.y = (p.y + 1) * in_image.size().second / 2;
        p_new.z = (p.z + 1) * 255;
        return p_new;
    }

    void raster_triangle(vector3i p1, vector3i p2, vector3i p3,
        std::vector<int>& z_buffer,  tga_image& in_image, const tga_image::color& in_color) {
        if (!((p1.x == p2.x && p1.x == p3.x)||(p1.y == p2.y && p1.y == p3.y))) {

            if (p1.y > p2.y)
                std::swap(p1, p2);
            if (p1.y > p3.y)
                std::swap(p1, p3);
            if (p2.y > p3.y)
                std::swap(p2, p3);

            vector3i p1p2 = p2 - p1;
            vector3i p1p3 = p3 - p1;
            vector3i p2p3 = p3 - p2;

            for (int y = p1.y; y < p2.y; y++) {
                double alpha = (double) (y - p1.y) / (p2.y - p1.y);
                double beta = (double) (y - p1.y) / (p3.y - p1.y);
                vector3i t1 = p1 + p1p2 * alpha;
                vector3i t2 = p1 + p1p3 * beta;
                if (t1.x > t2.x)
                    std::swap(t1, t2);
                vector3i t2t1 = t2 - t1;
                for (int x = t1.x; x < t2.x; x++) {
                    auto phi = (x - t1.x) / (t2.x - t1.x);
                    auto cur_p = p1 + t2t1 * phi;
                    if(z_buffer[y * in_image.size().first + x] < cur_p.z) {
                        in_image.set(x, y, in_color);
                        z_buffer[y * in_image.size().first + x] = cur_p.z;
                    }
                }
            }
            for (int y = p2.y; y < p3.y; y++) {
                double alpha = (double) (y - p2.y) / (p3.y - p2.y);
                double beta = (double) (y - p1.y) / (p3.y - p1.y);
                vector3i t1 = p2 + p2p3 * alpha;
                vector3i t2 = p1 + p1p3 * beta;
                if (t1.x > t2.x)
                    std::swap(t1, t2);
                vector3i t2t1 = t2 - t1;
                for (int x = t1.x; x < t2.x; x++) {
                    auto phi = (x - t1.x) / (t2.x - t1.x);
                    auto cur_p = p1 + t2t1 * phi;
                    if(z_buffer[y * in_image.size().first + x] < cur_p.z) {
                        in_image.set(x, y, in_color);
                        z_buffer[y * in_image.size().first + x] = cur_p.z;
                    }
                }
            }
        }
    }

    void raster(const model& in_model, tga_image& in_image) {
        // z buffer
        std::vector z_buffer(in_image.size().first * in_image.size().second, std::numeric_limits<int>::min());
        auto&& vertices = in_model.get_vert();

        for(auto&& [p0, p1, p2] : in_model.get_trian()) {

            const vector3f direction(0,0,-1);

            vector3f p0p1 = vertices[p1] - vertices[p0];
            vector3f p0p2 = vertices[p2] - vertices[p0];
            vector3f normal = cross(p0p2,p0p1);
            normal.normalize();

            const auto intensity = dot(normal, direction);

            tga_image::color color{ uint8_t(intensity * 255), uint8_t(intensity * 255),
                uint8_t(intensity * 255), uint8_t(intensity * 255) };
            if (intensity > 0)
                raster_triangle(to_ss(vertices[p0], in_image), to_ss(vertices[p1], in_image), to_ss(vertices[p2], in_image),
                    z_buffer, in_image, color);
        }
    }

}