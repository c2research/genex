#include "GroupCentroid.hpp"
#include "Exception.hpp"
#include <iostream>//debug

namespace genex {

void GroupCentroid::addTimeSeries(const TimeSeries& data)
{
  std::cout << "addTimeSeries " << this->getLength() << " " << data.getLength()<< '\n';

  *(this) += (data);
  this->count++;
  this->cacheValid = false;
}

data_t& GroupCentroid::operator[](int idx)
{
  if (idx < 0 || idx >= this->getLength()) {
    throw GenexException("Index is out of range");
  }

  // if the cache is not valid refresh the values
  if (!(this->cacheValid))
  {
    for (int i = 0; i < this->getLength(); i++)
    {
      this->cachedAverages[i] = this->data[i] / this->count;
    }
    cacheValid = true;
  }

  return this->cachedAverages[idx];
}

const data_t& GroupCentroid::getSumValue(int idx) const
{
  if (idx < 0 || idx >= this->getLength()) {
    throw GenexException("Index is out of range");
  }
  return this->data[idx];
}

}// namespace genex
