#pragma once
#include <sil/sil.hpp>

void only_green(sil::Image& image); // Ne garder que le vert

void invert_colors(sil::Image& image); // Inverser les couleurs

void black_and_white(sil::Image& image); // Noir et blanc

void negative(sil::Image& image); // Négatif

void gradient(sil::Image& image); // Dégradé noir et blance

void mirror(sil::Image& image); // Image miroir

void noise(sil::Image& image); // Noise

void rotate(sil::Image& image); // 90deg rotation

void rgb_split(sil::Image& image); // RGB split

void brightness(sil::Image& image, float brightness = 2.0f); // Luminosité

void circle(sil::Image& image, glm::vec2 center, int radius, int thickness = 5, float r = 1.0f, float g = 1.0f, float b = 1.0f);

void rectangle(sil::Image& image, glm::vec2 center, int width, int height, float r = 1.0f, float g = 1.0f, float b = 1.0f);

void rosace(sil::Image& image, const int count = 6);

void mosaic(sil::Image& image, const int size);

void mirror_mosaic(sil::Image& image, const int size);

void glitch(sil::Image& image);

void mandelbrot(sil::Image& image);

void histogram_normalization(sil::Image& image);

void diamond_square(sil::Image& image, float roughness);