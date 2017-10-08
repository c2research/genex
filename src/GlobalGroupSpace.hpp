#ifndef GROUPS_EQUAL_LENGTH_SET_H
#define GROUPS_EQUAL_LENGTH_SET_H

#include "LocalLengthGroupSpace.hpp"
#include "TimeSeries.hpp"
#include "TimeSeriesSet.hpp"
#include "distance/Distance.hpp"
#include "Group.hpp"

#include <vector>
#include <fstream>

namespace genex {

/**
 *  The set of all groups of equal lengths for a dataset
 */
class GroupsEqualLengthSet
{
public:

  /**
   *  @brief The constructor for the GroupsEqualLengthSet
   *
   *  @param dataset the dataset to group
   *  @param threshold the threshold for similarity within a group
   */
  GroupsEqualLengthSet(const TimeSeriesSet& dataset) : dataset(dataset) {};

  /**
   *  @brief The deconstructor for the GroupsEqualLengthSet
   */
  ~GroupsEqualLengthSet(void)
  {
    reset();
  }

  /**
   *  @brief clears the groups
   */
  void reset(void);

  /**
   *  @brief groups the dataset into groups of equal length
   *    using the metric to determine similarity
   *
   *  @param metric the metric used to group by
   *  @param threshold the threshold to be group with
   *  @return the number of groups it creates
   */
  int group(const std::string& distance_name, data_t threshold);
 
  /**
   *  @brief gets the most similar sequence in the dataset
   *
   *  @param query gets most similar sequence to the query
   *  @return the best match in the dataset
   */
  candidate_time_series_t getBestMatch(const TimeSeries& query);

  std::vector<TimeSeries> kNN(const TimeSeries& data, int k);

  void saveGroups(std::ofstream &fout, bool groupSizeOnly) const;
  int loadGroups(std::ifstream &fin);

  /**
   *  @brief returns true if dataset is grouped
   */
  bool grouped(void) const;

private:

  std::vector<GroupsEqualLength*> groupsEqualLength;
  const TimeSeriesSet& dataset;
  dist_t pairwiseDistance;
  dist_t warpedDistance;
  std::string distanceName;

  void loadDistance(const std::string& distanceName);
};

vector<int> generateTraverseOrder(int queryLength, int totalLength);

} // namespace genex
#endif //GROUPS_EQUAL_LENGTH_SET_H