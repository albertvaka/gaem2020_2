#pragma once

/* Copyright (c) 2007-2012 Eliot Eshelman
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */

/* 2D, 3D and 4D Simplex Noise functions return 'random' values in (-1, 1).

This algorithm was originally designed by Ken Perlin, but my code has been
adapted from the implementation written by Stefan Gustavson (stegu@itn.liu.se)

Raw Simplex noise functions return the value generated by Ken's algorithm.

Scaled Raw Simplex noise functions adjust the range of values returned from the
traditional (-1, 1) to whichever bounds are passed to the function.

Multi-Octave Simplex noise functions compine multiple noise values to create a
more complex result. Each successive layer of noise is adjusted and scaled.

Scaled Multi-Octave Simplex noise functions scale the values returned from the
traditional (-1,1) range to whichever range is passed to the function.

In many cases, you may think you only need a 1D noise function, but in practice
2D  is almost always better.  For instance, if you're using the current frame
number  as the parameter for the noise, all objects will end up with the same
noise value  at each frame. By adding a second parameter on the second
dimension, you can ensure that each gets a unique noise value and they don't
all look identical.
*/

#include <functional>

namespace Simplex {

// Multi-octave Simplex noise
// For each octave, a higher frequency/lower amplitude function will be added to the original.
// The higher the persistence [0-1], the more of each succeeding octave will be added.
float octave_noise_2d(const float octaves,
                    const float persistence,
                    const float scale,
                    const float x,
                    const float y);
float octave_noise_3d(const float octaves,
                    const float persistence,
                    const float scale,
                    const float x,
                    const float y,
                    const float z);
float octave_noise_4d(const float octaves,
                    const float persistence,
                    const float scale,
                    const float x,
                    const float y,
                    const float z,
                    const float w);


// Scaled Multi-octave Simplex noise
// The result will be between the two parameters passed.
float scaled_octave_noise_2d(  const float octaves,
                            const float persistence,
                            const float scale,
                            const float loBound,
                            const float hiBound,
                            const float x,
                            const float y);
float scaled_octave_noise_3d(  const float octaves,
                            const float persistence,
                            const float scale,
                            const float loBound,
                            const float hiBound,
                            const float x,
                            const float y,
                            const float z);
float scaled_octave_noise_4d(  const float octaves,
                            const float persistence,
                            const float scale,
                            const float loBound,
                            const float hiBound,
                            const float x,
                            const float y,
                            const float z,
                            const float w);

// Scaled Raw Simplex noise
// The result will be between the two parameters passed.
float scaled_raw_noise_2d( const float loBound,
                        const float hiBound,
                        const float x,
                        const float y);
float scaled_raw_noise_3d( const float loBound,
                        const float hiBound,
                        const float x,
                        const float y,
                        const float z);
float scaled_raw_noise_4d( const float loBound,
                        const float hiBound,
                        const float x,
                        const float y,
                        const float z,
                        const float w);


// Raw Simplex noise - a single noise value.
float raw_noise_2d(const float x, const float y);
float raw_noise_3d(const float x, const float y, const float z);
float raw_noise_4d(const float x, const float y, const float, const float w);

float dot(const int* g, const float x, const float y);
float dot(const int* g, const float x, const float y, const float z);
float dot(const int* g, const float x, const float y, const float z, const float w);


//void DebugDraw(sf::RenderTarget& window, float tileSize, std::function<float(int x, int y)> noisefunc);

}