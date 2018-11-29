#include "bars.h"
#include "insertionsort.h"

InsertionSort::InsertionSort()
{
    highlight = {0,0,0,0};
    pointer = {0,0,0,0};
    temp = {0,0,0,0};
    i = j = 1;
    sorted = false;
}

void InsertionSort::isAlgorithm(SDL_Rect* rectArray)
{
    // test if the sort has been completed. 'i' represents the outside loop.
    if(i == 100)
    {
        updateHighlightPointer();
        sorted = true;
        return;
    }
    // if the inside loop has made it all the way to the start of the array.
    if(j == 0)
    {
        i++;
        j = i;
        updateHighlightPointer();
        return;
    }
    // if the current element is larger the the one before it, move on.
    if(rectArray[j].h >= rectArray[j-1].h)
    {
        i++;
        j = i;
        updateHighlightPointer();
        return;
    }
    else
    {
        temp.h = rectArray[j].h;
        rectArray[j].h = rectArray[j-1].h;
        rectArray[j-1].h = temp.h;

        temp.y = rectArray[j].y;
        rectArray[j].y = rectArray[j-1].y;
        rectArray[j-1].y = temp.y;

        updateHighlightPointer();
        j--;
        return;
    }
}

void InsertionSort::updateHighlightPointer()
{
    if(i == 99)
    {
        pointer = {0,0,0,0};
        highlight = {0,0,0,0};
    }
    else
    {
        pointer = {200+(j*6),380,6,6};
        highlight = {200+(j*6)-1, 25, 6, 355};
    }
}

void InsertionSort::renderInsertionSort(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0x50, 0x50, 0x50, 0xFF);  // gray
    SDL_RenderFillRect(renderer, &highlight);                  // draw highlight
    SDL_SetRenderDrawColor(renderer, 0xff, 0x00, 0x00, 0xFF);  // red
    SDL_RenderFillRect(renderer, &pointer);                    // draw pointer
}

void InsertionSort::reset()
{
    highlight = {0,0,0,0};
    pointer = {0,0,0,0};
    temp = {0,0,0,0};
    i = j = 1;
    sorted = false;
}

bool InsertionSort::isSorted()  { return sorted; }
