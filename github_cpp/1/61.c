
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


namespace filler
{
    
    namespace dfs
    {
        
        animation fillSolid(PNG& img, int x, int y, RGBAPixel fillColor,
                int tolerance, int frameFreq);

        
        animation fillGrid(PNG& img, int x, int y, RGBAPixel gridColor,
                           int gridSpacing, int tolerance, int frameFreq);

        
        animation fillGradient(PNG& img, int x, int y, RGBAPixel fadeColor1,
                RGBAPixel fadeColor2, int radius, int tolerance,
                int frameFreq);

        
        animation fill(PNG& img, int x, int y, colorPicker& fillColor,
                       int tolerance, int frameFreq);
    }

    
    namespace bfs
    {
        
        animation fillSolid(PNG& img, int x, int y, RGBAPixel fillColor,
                int tolerance, int frameFreq);

        
        animation fillGrid(PNG& img, int x, int y, RGBAPixel gridColor,
                int gridSpacing, int tolerance, int frameFreq);

        
        animation fillGradient(PNG& img, int x, int y, RGBAPixel fadeColor1,
                RGBAPixel fadeColor2, int radius, int tolerance,
                int frameFreq);

        
        animation fill(PNG& img, int x, int y, colorPicker& fillColor,
                       int tolerance, int frameFreq);
    }

    
    template <template <class T> class OrderingStructure>
    animation fill(PNG& img, int x, int y, colorPicker& fillColor,
                   int tolerance, int frameFreq);

    bool checkTol(RGBAPixel & a, RGBAPixel & b, int tolerance);
}
#include "filler.cpp"
#endif
