#include <image-utils.hpp>
#include <sil/sil.hpp>
#include <random.hpp>
#include <iostream>
//include <glm/gtx/polar_coordinates.hpp>
#include <complex>

void only_green(sil::Image& image) // Ne garder que le vert
{
    for (glm::vec3& color : image.pixels())
    {
        color.r = 0.f;
        color.b = 0.f;
    }
}

void invert_colors(sil::Image& image) // Inverser les couleurs
{
    for (glm::vec3& color : image.pixels())
    {
        float tmp = color.r;
        color.r = color.b;
        color.b = tmp;
    }
}

void black_and_white(sil::Image& image) // Noir et blanc
{
    for (glm::vec3& color : image.pixels())
    {
        float gray = (color.r + color.g + color.b) / 3.f;
        color.r = gray;
        color.g = gray;
        color.b = gray;
    }
}

void negative(sil::Image& image) // Négatif
{
    for (glm::vec3& color : image.pixels())
    {
        color.r = 1.f - color.r;
        color.g = 1.f - color.g;
        color.b = 1.f - color.b;
    }
}

void gradient(sil::Image& image) // Dégradé noir et blance
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y).r = x / static_cast<float>(image.width());
            image.pixel(x, y).g = x / static_cast<float>(image.width());
            image.pixel(x, y).b = x / static_cast<float>(image.width());
        }
    }
}

void mirror(sil::Image& image) // Image miroir
{
    sil::Image finalImage{image.width(), image.height()};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            finalImage.pixel(x, y) = image.pixel(image.width() - x - 1, y);
        }
    }
    image = finalImage;
}

void noise(sil::Image& image) // Noise
{
    for (glm::vec3& color : image.pixels())
    {
        color.r += random_float(-0.5f, 0.5f);
        color.g += random_float(-0.5f, 0.5f);
        color.b += random_float(-0.5f, 0.5f);
    }
}

void rotate(sil::Image& image) // 90deg rotation
{
    sil::Image finalImage{image.height(), image.width()};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            finalImage.pixel(y, x) = image.pixel(x, y);
        }
    }
    image = finalImage;
}

void rgb_split(sil::Image& image) // RGB split
{
    sil::Image finalImage{image.width(), image.height()};
    const int decalage = 30;
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if(x + decalage >= image.width())
                finalImage.pixel(x, y).r = 0;
            else
                finalImage.pixel(x, y).r = image.pixel(x + decalage, y).r;
            finalImage.pixel(x, y).g = image.pixel(x, y).g;
            if(x - decalage < 0)
                finalImage.pixel(x, y).b = 0;
            else
                finalImage.pixel(x, y).b = image.pixel(x - decalage, y).b;
        }
    }
    image = finalImage;
}

void brightness(sil::Image& image, float brightness) // Luminosité
{
    for (glm::vec3& color : image.pixels())
    {
        color.r *= color.r * brightness;
        color.g *= color.g * brightness;
        color.b *= color.b * brightness;
    }
}

void circle(sil::Image& image, glm::vec2 center, int radius, int thickness, float r, float g, float b)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if(glm::distance(center, glm::vec2{x, y}) < radius && glm::distance(center, glm::vec2{x, y}) > radius - thickness)
            {
                image.pixel(x, y).r = r;
                image.pixel(x, y).g = g;
                image.pixel(x, y).b = b;
            }
        }
    }
}

void rectangle(sil::Image& image, glm::vec2 center, int width, int height, float r, float g, float b)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if(x > center.x - width && x < center.x + width && y > center.y - height && y < center.y + height)
            {
                image.pixel(x, y).r = r;
                image.pixel(x, y).g = g;
                image.pixel(x, y).b = b;
            }
        }
    }
}

void rosace(sil::Image& image, const int count) {
    const glm::vec2 center = {image.height() / 2, image.width() / 2};
    const float radius = 150.0f;
    circle(image, center, radius, 2, 1.0f, 1.0f, 1.0f);
    for (int i = 1; i <= count; i++)
    {
        std::cout << i << std::endl;
        const double angle = ((2*M_PI) / count) * i;
        glm::vec2 coordinates = radius * glm::vec2{std::cos(angle),  std::sin(angle)};

        // coordinates *= 150;

        coordinates.x += center.x;
        coordinates.y += center.y;

        circle(image, coordinates, radius, 2, 0.0f, 0.0f, 1.0f);
    }
}

void mosaic(sil::Image& image, const int size) {
    sil::Image finalImage{image.width(), image.height()};
    for (int x {0}; x < image.width(); x++)
    {
        for (int y {0}; y < image.height(); y++)
        {
            std::cout << " X " << x << " |  Y " << y << std::endl;
            const glm::vec2 pixel {
                (x * size) % image.width(), 
                (y * size) % image.height()
            };
            std::cout << "fX " << pixel.x << " | fY " << pixel.y << std::endl;
            finalImage.pixel(x, y) = image.pixel(pixel.x, pixel.y);
        }
    }
    image = finalImage;
}

void mirror_mosaic(sil::Image& image, const int size) {
    sil::Image finalImage{image.width(), image.height()};
    for (int x {0}; x < image.width(); x++)
    {
        for (int y {0}; y < image.height(); y++)
        {
            std::cout << " X " << x << " |  Y " << y << std::endl;
            glm::vec2 pixel {
                (x * size) % image.width(), 
                (y * size) % image.height()
            };

            if((x / (image.width() / size)) % 2 == 1) {
                pixel.x = image.width() - 1 - pixel.x;
            }

            if((y / (image.height() / size)) % 2 == 1) {
                pixel.y = image.height() - 1 - pixel.y;
            }

            std::cout << "fX " << pixel.x << " | fY " << pixel.y << std::endl;
            // finalImage.pixel(x, y) = image.pixel(image.width() - 1 - pixel.x, image.height() - 1 - pixel.y );
            finalImage.pixel(x, y) = image.pixel(pixel.x, pixel.y );
        }
    }
    image = finalImage;
}

struct Glitch {
    glm::vec2 size;
    glm::vec2 origin;
    glm::vec2 destination;
};

Glitch random_glitch(const sil::Image image) {
    const int min_width = 10;
    const int max_width = 40;
    const int min_height = 1;
    const int max_height = 15;

    Glitch glitch {
        glm::vec2{
            random_int(min_width, max_width),
            random_int(min_height, max_height)
        },
        glm::vec2{
            random_int(0, image.width()),
            random_int(0, image.height())
        },
        glm::vec2{
            random_int(0, image.width()),
            random_int(0, image.height())
        }
    };

    return glitch;
};

void glitch(sil::Image& image) {
    const int nb_of_glitches = random_int(150, 300);

    sil::Image finalImage = image;

    for (int i = 0; i < nb_of_glitches; i++)
    {
        Glitch glitch = random_glitch(image);

        for (int x {0}; x < glitch.size.x; x++)
        {
            for (int y {0}; y < glitch.size.y; y++) {
                finalImage.pixel(
                    std::min(static_cast<int>(glitch.destination.x) + x, image.width() - 1),
                    std::min(static_cast<int>(glitch.destination.y) + y, image.height() - 1)
                ) = image.pixel(
                    std::min(static_cast<int>(glitch.origin.x) + x, image.width() - 1),
                    std::min(static_cast<int>(glitch.origin.y) + y, image.height() - 1)
                );
            }
        }
    }

    image = finalImage;
}

void mandelbrot(sil::Image& image) {

    for (int x {0}; x < image.width(); x++)
    {
        for (int y {0}; y < image.height(); y++)
        {
            std::complex<float> c {
                2.0f * x / image.width() - 1.5f,
                2.0f * y / image.height() - 1.0f
            };

            std::complex<float> z {0, 0};

            float n = 0;
            while (std::abs(z) < 2 && n < 100)
            {
                z = z * z + c;
                n++;
            }

            n /= 50;

            image.pixel(x, y).r = n;
            image.pixel(x, y).g = n;
            image.pixel(x, y).b = n;
        }
    }
}

// void tramage(sil::Image& image) {

// }

void histogram_normalization(sil::Image& image) {
    float min_brightness = 1.0f;
    float max_brightness = 0.0f;

    for (glm::vec3 color : image.pixels())
    {
        const float brightness = (color.r + color.g + color.b) / 3;
        min_brightness = std::min(min_brightness, brightness);
        max_brightness = std::max(max_brightness, brightness);
    }

    std::cout << "min: " << min_brightness << " max: " << max_brightness << std::endl;

    for (glm::vec3 color : image.pixels())
    {
        color.r = (color.r - min_brightness) / (max_brightness - min_brightness);
        color.g = (color.g - min_brightness) / (max_brightness - min_brightness);
        color.b = (color.b - min_brightness) / (max_brightness - min_brightness);
    }
}

void print_2D_vector(const std::vector<std::vector<float>>& vector)
{
    for (const std::vector<float>& v : vector)
    {
        for (float f : v)
        {
            if(f)
                std::cout << static_cast<int>(f*10) << " ";
            else
                std::cout << "-" << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void diamond_step(std::vector<std::vector<float>>& height_map, int chunk_size, float roughness)
{
    int half = chunk_size / 2;

    for(int y = 0; y < height_map.size(); y += half)
    {
        for(int x = (y + half) % chunk_size; x < height_map.size(); x += chunk_size)
        {
            std::cout << "DIAMOND STEP x: " << x << " y: " << y << std::endl;
            
            float avg = 0.0f;

            if (y - half >= 0)
            {
                avg += height_map.at(y - half).at(x);
            }
            if (y + half < height_map.size())
            {
                avg += height_map.at(y + half).at(x);
            }
            if (x - half >= 0)
            {
                avg += height_map.at(y).at(x - half);
            }
            if (x + half < height_map.size())
            {
                avg += height_map.at(y).at(x + half);
            }

            avg /= 4.0f;

            height_map[y][x] = avg + random_float(-0.8f, 0.8f) * roughness;
        }
    }
}

void square_step(std::vector<std::vector<float>>& height_map, int chunk_size, float roughness)
{
    int half = chunk_size / 2;
    for (int y = 0; y < height_map.size() - 1 ; y += chunk_size)
    {
        for (int x = 0; x < height_map.size() - 1; x += chunk_size)
        {
            std::cout << "SQUARE STEP x: " << x << " y: " << y << std::endl;
            height_map[y + half][x + half] = (
                height_map.at(y).at(x) 
                + height_map.at(y).at(x + chunk_size) 
                + height_map.at(y + chunk_size).at(x)
                + height_map.at(y + chunk_size).at(x + chunk_size)
            ) / 4.0f + random_float(-0.08f, 0.08f) * roughness;

        }
    }
}


void diamond_square(sil::Image& image, float roughness = 200.f)
{
    int height_map_size = image.width(); // Assuming width and height are the same

    std::vector<std::vector<float>> height_map(height_map_size, std::vector<float>(height_map_size, 0.0f));

    height_map_size -= 1;

    height_map.at(0).at(0) = 0.2f; // random_float(0.0f, 1.0f);
    height_map.at(0).at(height_map_size) = 0.8f; // random_float(0.0f, 1.0f);
    height_map.at(height_map_size).at(0) = 0.5f; // random_float(0.0f, 1.0f);
    height_map.at(height_map_size).at(height_map_size) = 0.1f; // random_float(0.0f, 1.0f);

    int chunk_size = height_map_size;

    while (chunk_size > 1)
    {
        square_step(height_map, chunk_size, roughness);
        // print_2D_vector(height_map);
        diamond_step(height_map, chunk_size, roughness);
        // print_2D_vector(height_map);
        chunk_size /= 2;
        roughness /= 2;
    }

    // print_2D_vector(height_map);
    
    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            image.pixel(x, y).r = height_map.at(x).at(y);
            image.pixel(x, y).g = height_map.at(x).at(y);
            image.pixel(x, y).b = height_map.at(x).at(y);
        }
    }

    // int step = size - 1;

    // while (step > 1) {
    //     int half_step = step / 2;

    //     // Diamond step
    //     for (int x = half_step; x < size; x += step) {
    //         for (int y = half_step; y < size; y += step) {
    //             float top_left = get_pixel(image, x - half_step, y - half_step);
    //             float top_right = get_pixel(image, x - half_step, y + half_step);
    //             float bottom_left = get_pixel(image, x + half_step, y - half_step);
    //             float bottom_right = get_pixel(image, x + half_step, y + half_step);

    //             float avg = (top_left + top_right + bottom_left + bottom_right) / 4.0f;
    //             float random_val = random_float(0.0f, 1.0f);

    //             set_pixel(image, x, y, avg + random_val * ((float)half_step / size));
    //         }
    //     }

    //     // Square step
    //     for (int x = 0; x < size; x += half_step) {
    //         for (int y = (x + half_step) % step; y < size; y += step) {
    //             float sum = 0.0f;
    //             int count = 0;

    //             if (x >= half_step) {
    //                 sum += get_pixel(image, x - half_step, y);
    //                 count++;
    //             }
    //             if (x + half_step < size) {
    //                 sum += get_pixel(image, x + half_step, y);
    //                 count++;
    //             }
    //             if (y >= half_step) {
    //                 sum += get_pixel(image, x, y - half_step);
    //                 count++;
    //             }
    //             if (y + half_step < size) {
    //                 sum += get_pixel(image, x, y + half_step);
    //                 count++;
    //             }

    //             float avg = sum / count;
    //             float random_val = random_float(0.0f, 1.0f);

    //             set_pixel(image, x, y, avg + random_val * ((float)half_step / size));
    //         }
    //     }

    //     step = half_step;
    // }
}