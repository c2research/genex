#ifndef COSINE_H
#define COSINE_H

#include <cmath>

#include "TimeSeries.hpp"
#include "Exception.hpp"

namespace genex {

class Cosine
{
public:
  data_t* init() const
  {
    auto newData = new data_t[3];
    newData[0] = newData[1] = newData[2] = 0;
    return newData;
  }

  data_t* reduce(data_t* next, data_t* prev, const data_t x_1, const data_t x_2) const
  {
    next[0] = prev[0] + pow(x_1, 2);
    next[1] = prev[1] + pow(x_2, 2);
    next[2] = prev[2] + x_1 * x_2;
    return next;
  }

  data_t norm(data_t* total, const TimeSeries& t_1, const TimeSeries& t_2) const
  {
    return total[2] / (sqrt(total[0] * total[1]));
  }

  data_t normDTW(data_t* total, const TimeSeries& t_1, const TimeSeries& t_2) const
  {
    return norm(total, t_1, t_2);
  }

  void clean(data_t* x) {
    delete[] x;
  }

};

} // namespace genex

#endif // COSINE_H
