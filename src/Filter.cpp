
#include "config.h"
#include "Filter.h"


/******************************************************************************
 * Filter
 */

Filter::Filter(int size)
{
    _data = new float[size];
}


Filter::~Filter()
{
    delete[] _data;
}

float
Filter::filter(float input)
{
    return input;
}

/******************************************************************************
 * Mean Filter
 */

MeanFilter::MeanFilter(int size)
: Filter(size)
{

}

MeanFilter::~MeanFilter()
{

}

float
MeanFilter::filter(float input)
{
    return input;
}


/******************************************************************************
 * Median Filter
 */

MedianFilter::MedianFilter(int size)
: Filter(size)
{

}

MedianFilter::~MedianFilter()
{

}

float
MedianFilter::filter(float input)
{
    return input;
}
