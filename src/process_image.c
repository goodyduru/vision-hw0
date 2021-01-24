#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"

float get_pixel(image im, int x, int y, int c)
{
    x = (x < 0) ? 0 : x;
    y = (y < 0) ? 0 : y;
    c = (c < 0) ? 0 : c;

    x = (x >= im.w) ? im.w - 1 : x;
    y = (y >= im.h) ? im.h - 1 : y;
    c = (c >= im.c) ? im.c - 1 : c;
    int index = x + im.w*y + im.w*im.h*c;
    return im.data[index];
}

void set_pixel(image im, int x, int y, int c, float v)
{
    if ( x < 0 || x >= im.w || y < 0 || y >= im.h || c < 0 || c >= im.c ) {
        return;
    }
    int index = x + im.w*y +im.w*im.h*c;
    im.data[index] = v;
}

image copy_image(image im)
{
    image copy = make_image(im.w, im.h, im.c);
    int i, j, k;
    for ( i = 0; i < copy.w; i++ ) {
        for ( j = 0; j < copy.h; j++ ) {
            for ( k = 0; k < copy.c; k++ ) {
                float pixel = get_pixel(im, i, j, k);
                set_pixel(copy, i, j, k, pixel);
            }
        }
    }
    free_image(im);
    return copy;
}

image rgb_to_grayscale(image im)
{
    assert(im.c == 3);
    image gray = make_image(im.w, im.h, 1);
    int i, j;
    for ( i = 0; i < gray.w; i++ ) {
        for ( j = 0; j < gray.h; j++ ) {
            float red = get_pixel(im, i, j, 0);
            float green = get_pixel(im, i, j, 1);
            float blue = get_pixel(im, i, j, 2);
            float pixel = 0.299 * red + 0.587 * green + .114 * blue;
            set_pixel(gray, i, j, 0, pixel);
        }
    }
    free_image(im);
    return gray;
}

void shift_image(image im, int c, float v)
{
    int i, j;
    for ( i = 0; i < im.w; i++ ) {
        for ( j = 0; j < im.h; j++ ) {
            float pixel = get_pixel(im, i, j, c);
            set_pixel(im, i, j, c, pixel + v);
        }
    }
}

void clamp_image(image im)
{
    int i, j, k;
    for ( i = 0; i < im.w; i++ ) {
        for (j = 0; j < im.h; j++ ) {
            for ( k = 0; k < im.c; k++ ) {
                float pixel = get_pixel(im, i, j, k);
                pixel = ( pixel < 0.0 ) ? 0.0 : pixel;
                pixel = ( pixel > 1.0 ) ? 1.0 : pixel;
                set_pixel(im, i, j, k, pixel);
            }
        }
    }
}


// These might be handy
float three_way_max(float a, float b, float c)
{
    return (a > b) ? ( (a > c) ? a : c) : ( (b > c) ? b : c) ;
}

float three_way_min(float a, float b, float c)
{
    return (a < b) ? ( (a < c) ? a : c) : ( (b < c) ? b : c) ;
}

void rgb_to_hsv(image im)
{
    int i, j;
    for ( i = 0; i < im.w; i++ ) {
        for (j = 0; j < im.h; j++ ) {
            float red = get_pixel(im, i, j, 0);
            float green = get_pixel(im, i, j, 1);
            float blue = get_pixel(im, i, j, 2);
            float value = three_way_max(red, green, blue);
            float saturation = 0.0;
            float chroma = 0.0;

            //chroma is difference between maximum pixel and minimum pixel
            if ( value > 0 ) {
                chroma = value - three_way_min(red, green, blue);
                saturation = chroma / value;
            }
            float value_max = value + 1e-5;
            float value_min = value - 1e-5;
            float quasi_hue = 0.0;
            float hue = 0.0;
            if ( chroma > 0.0) {
                if ( red > value_min && red < value_max ) {
                    quasi_hue = (green - blue) / chroma;
                }
                else if ( green > value_min && green < value_max ) {
                    quasi_hue = (( blue - red ) / chroma ) + 2.0;
                }
                else {
                    quasi_hue = ((red - green) / chroma) + 4.0;
                }
            }

            if ( quasi_hue < 0 ) {
                hue = (quasi_hue / 6) + 1;
            }
            else {
                hue = quasi_hue / 6;
            }
            set_pixel(im, i, j, 0, hue);
            set_pixel(im, i, j, 1, saturation);
            set_pixel(im, i, j, 2, value);
        }
    }
}

void hsv_to_rgb(image im)
{
    // TODO Fill this in
}
