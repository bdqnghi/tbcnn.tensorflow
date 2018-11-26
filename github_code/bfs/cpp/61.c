/**
 * @file filler.h
 * Defintion of a filler namespace.
 *
 * @author Chase Geigle
 * @date Fall 2012
 */
#ifndef _FILLER_H_
#define _FILLER_H_

#include "png.h"
#include "stack.h"
#include "queue.h"
#include "solidColorPicker.h"
#include "gridColorPicker.h"
#include "gradientColorPicker.h"
#include "animation.h"
#include <iostream>
using std::cout;

/**
 * filler namespace: specifies a set of functions for performing flood
 * fills on images. Adapted from MP4 authored by CS225 staff, Fall 2010.
 *
 * @author Chase Geigle
 * @date Fall 2012
 */
namespace filler
{
    /**
     * dfs namespace: specifies a set of filler functions for doing fills
     * on images employing a depth-first-search approach.
     *
     * @note All of the functions in this namespace should call the generic
     *  filler::dfs::fill function with the the correct color picker
     *  parameter (except for, of course, filler::dfs::fill itself).
     *
     * @author Chase Geigle
     * @date Fall 2012
     */
    namespace dfs
    {
        /**
         * Performs a flood fill on the given image using a solid color,
         * employing a depth-first-search approach.
         *
         * @param img The image to be filled.
         * @param x The starting x coordinate for the fill.
         * @param y The starting y coordinate for the fill.
         * @param fillColor The color of the fill.
         * @param tolerance How far away colors are allowed to be to
         *  still be included in the fill: this is given as squared euclidean
         *  distance in RGB space (i.e. \f$(c1.red - c2.red)^2 +
           (c1.green - c2.green)^2 + (c1.blue - c2.blue)^2)\f$.
         * @param frameFreq How frequently to add a frame to the
         *  animation, in pixels. For instance, if frameFreq == 1, a frame is
         *  added when every pixel is filled. If frameFreq == 10, a frame is
         *  added after every 10 pixels is filled.
         * @return An animation that shows the fill progressing over the image.
         */
        animation fillSolid(PNG& img, int x, int y, RGBAPixel fillColor,
                int tolerance, int frameFreq);

        /**
         * Performs a flood fill on the given image using a grid,
         * employing a depth-first-search approach.
         *
         * @param img The image to be filled.
         * @param x The starting x coordinate for the fill.
         * @param y The starting y coordinate for the fill.
         * @param gridColor The color the lines of the grid should appear.
         * @param gridSpacing The width and height of the cells of the grid.
         * @param tolerance How far away colors are allowed to be to still be
         * included in the fill: this is given as squared
         * euclidean distance in RGB space (i.e. \f$(c1.red - c2.red)^2 +
           (c1.green - c2.green)^2 + (c1.blue - c2.blue)^2)\f$.
         * @param frameFreq How frequently to add a frame to the animation, in
         *  pixels. For instance, if frameFreq == 1, a frame is added when every
         *  pixel is filled. If frameFreq == 10, a frame is added after every 10
         *  pixels is filled.
         * @return An animation that shows the fill progressing over the image.
         */
        animation fillGrid(PNG& img, int x, int y, RGBAPixel gridColor,
                           int gridSpacing, int tolerance, int frameFreq);

        /**
         * Performs a flood fill on the given image using a gradient, employing
         * a depth-first-search approach.
         *
         * @param img The image to be filled.
         * @param x The starting x coordinate for the fill.
         * @param y The starting y coordinate for the fill.
         * @param fadeColor1 The starting color of the gradient.
         * @param fadeColor2 The ending color of the gradient.
         * @param radius The radius for the gradient.
         * @param tolerance How far away colors are allowed to be to still be
         *  included in the fill: this is given as squared euclidean distance in
         *  RGB space (i.e. \f$(c1.red - c2.red)^2 +
            (c1.green - c2.green)^2 + (c1.blue - c2.blue)^2)\f$.
         * @param frameFreq How frequently to add a frame to the animation, in
         *  pixels. For instance, if frameFreq == 1, a frame is added when every
         *  pixel is filled. If frameFreq == 10, a frame is added after every 10
         *  pixels is filled.
         * @return An animation that shows the fill progressing over the image.
         */
        animation fillGradient(PNG& img, int x, int y, RGBAPixel fadeColor1,
                RGBAPixel fadeColor2, int radius, int tolerance,
                int frameFreq);

        /**
         * Performs a flood fill on the given image using the given color
         * picker, employing a depth-first-search approach.
         *
         * @param img Image to do the filling on.
         * @param x X coordinate to start the fill from.
         * @param y Y coordinate to start the fill from.
         * @param fillColor The colorPicker to be used for the fill.
         * @param tolerance How far away colors are allowed to be to still be
         *  included in the fill: this is given as squared euclidean distance in
         *  RGB space (i.e. \f$(c1.red - c2.red)^2 + (c1.green -
            c2.green)^2 + (c1.blue - c2.blue)^2)\f$.
         * @param frameFreq How frequently to add a frame to the animation, in
         *  pixels. For instance, if frameFreq == 1, a frame is added when every
         *  pixel is filled. If frameFreq == 10, a frame is added after every 10
         *  pixels is filled.
         * @return An animation that shows the fill progressing over the image.
         */
        animation fill(PNG& img, int x, int y, colorPicker& fillColor,
                       int tolerance, int frameFreq);
    }

    /**
     * bfs namespace: specifies a set of filler functions for doing fills
     * on images employing a breadth-first-search approach.
     *
     * @note All of the functions in this namespace should call the generic
     *  filler::bfs::fill function with the correct color picker parameter
     *  (except for, of course, filler::bfs::fill itself).
     *
     * @author Chase Geigle
     * @date Fall 2012
     */
    namespace bfs
    {
        /**
         * Performs a flood fill on the given image using a solid color,
         * employing a breadth-first-search approach.
         *
         * @param img The image to be filled.
         * @param x The starting x coordinate for the fill.
         * @param y The starting y coordinate for the fill.
         * @param fillColor The color of the fill.
         * @param tolerance How far away colors are allowed to be to still be
         *  included in the fill: this is given as squared euclidean distance in
         *  RGB space (i.e. \f$(c1.red - c2.red)^2 +
            (c1.green - c2.green)^2 + (c1.blue - c2.blue)^2)\f$.
         * @param frameFreq How frequently to add a frame to the animation, in
         *  pixels. For instance, if frameFreq == 1, a frame is added when every
         *  pixel is filled. If frameFreq == 10, a frame is added after every 10
         *  pixels is filled.
         * @return An animation that shows the fill progressing over the image.
         */
        animation fillSolid(PNG& img, int x, int y, RGBAPixel fillColor,
                int tolerance, int frameFreq);

        /**
         * Performs a flood fill on the given image using a grid, employing a
         * breadth-first-search approach.
         *
         * @param img The image to be filled.
         * @param x The starting x coordinate for the fill.
         * @param y The starting y coordinate for the fill.
         * @param gridColor The color the lines of the grid should appear.
         * @param gridSpacing The width and height of the cells of the grid.
         * @param tolerance How far away colors are allowed to be to still be
         *  included in the fill: this is given as squared euclidean distance in
         *  RGB space (i.e. \f$(c1.red - c2.red)^2 +
            (c1.green - c2.green)^2 + (c1.blue - c2.blue)^2)\f$.
         * @param frameFreq How frequently to add a frame to the animation, in
         *  pixels. For instance, if frameFreq == 1, a frame is added when every
         *  pixel is filled. If frameFreq == 10, a frame is added after every 10
         *  pixels is filled.
         * @return An animation that shows the fill progressing over the image.
         */
        animation fillGrid(PNG& img, int x, int y, RGBAPixel gridColor,
                int gridSpacing, int tolerance, int frameFreq);

        /**
         * Performs a flood fill on the given image using a gradient,
         * employing a breadth-first-search approach.
         *
         * @param img The image to be filled.
         * @param x The starting x coordinate for the fill.
         * @param y The starting y coordinate for the fill.
         * @param fadeColor1 The starting color of the gradient.
         * @param fadeColor2 The ending color of the gradient.
         * @param radius The radius for the gradient.
         * @param tolerance How far away colors are allowed to be to still
         *  be included in the fill: this is given as squared euclidean
         *  distance in RGB space (i.e. \f$(c1.red - c2.red)^2 + (c1.green -
            c2.green)^2 + (c1.blue - c2.blue)^2)\f$.
         * @param frameFreq How frequently to add a frame to the animation,
         *  in pixels. For instance, if frameFreq == 1, a frame is added
         *  when every pixel is filled. If frameFreq == 10, a frame is added
         *  after every 10 pixels is filled.
         * @return An animation that shows the fill progressing over the
         *  image.
         */
        animation fillGradient(PNG& img, int x, int y, RGBAPixel fadeColor1,
                RGBAPixel fadeColor2, int radius, int tolerance,
                int frameFreq);

        /**
         * Performs a flood fill on the given image using the given color
         * picker, employing a breadth-first-search approach.
         *
         * @param img Image to do the filling on.
         * @param x X coordinate to start the fill from.
         * @param y Y coordinate to start the fill from.
         * @param fillColor The colorPicker to be used for the fill.
         * @param tolerance How far away colors are allowed to be to still be
         *  included in the fill: this is given as squared euclidean distance in
         *  RGB space (i.e. \f$(c1.red - c2.red)^2 + (c1.green -
            c2.green)^2 + (c1.blue - c2.blue)^2)\f$.
         * @param frameFreq How frequently to add a frame to the animation, in
         *  pixels. For instance, if frameFreq == 1, a frame is added when every
         *  pixel is filled. If frameFreq == 10, a frame is added after every 10
         *  pixels is filled.
         * @return An animation that shows the fill progressing over the image.
         */
        animation fill(PNG& img, int x, int y, colorPicker& fillColor,
                       int tolerance, int frameFreq);
    }

    /**
     * General filling function: a general helper that should be invoked by
     * all of the public fill functions with the appropriate color picker
     * for that type of fill.
     *
     * For example, filler::dfs::fillSolid should call fill with the
     * correct ordering structure as its template parameter, passing in a
     * solidColorPicker.
     *
     * filler::bfs::fillGradient should call fill with a different ordering
     * structure as its template parameter, passing in a
     * gradientColorPicker.
     *
     * @param img Image to do the filling on.
     * @param x X coordinate to start the fill from.
     * @param y Y coordinate to start the fill from.
     * @param fillColor The colorPicker to be used for the fill.
     * @param tolerance How far away colors are allowed to be to still be
     *  included in the fill: this is given as squared euclidean distance in
     *  RGB space (i.e. \f$(c1.red - c2.red)^2 + (c1.green -
        c2.green)^2 + (c1.blue - c2.blue)^2)\f$.
     * @param frameFreq How frequently to add a frame to the animation, in
     *  pixels. For instance, if frameFreq == 1, a frame is added when every
     *  pixel is filled. If frameFreq == 10, a frame is added after every 10
     *  pixels is filled.
     * @return An animation that shows the fill progressing over the image.
     */
    template <template <class T> class OrderingStructure>
    animation fill(PNG& img, int x, int y, colorPicker& fillColor,
                   int tolerance, int frameFreq);

    bool checkTol(RGBAPixel & a, RGBAPixel & b, int tolerance);
}
#include "filler.cpp"
#endif
