#include "MergeMethods.h"

using boost::optional;
using std::function;
using std::string;
using std::unordered_map;
using namespace ow_dynamic_terrain;

const unordered_map<string, const MergeMethods::MergeMethod &> MergeMethods::m_mapOperationNameToOperationFunction = {
  { "keep", MergeMethods::keep }, { "replace", MergeMethods::replace }, { "add", MergeMethods::add },
  { "sub", MergeMethods::sub },   { "min", MergeMethods::min },         { "max", MergeMethods::max },
};

const MergeMethods::MergeMethod MergeMethods::keep = [](float current_value, float new_value) { return current_value; };

const MergeMethods::MergeMethod MergeMethods::replace = [](float current_value, float new_value) { return new_value; };

const MergeMethods::MergeMethod MergeMethods::add = [](float current_value, float new_value) {
  return current_value + new_value;
};

const MergeMethods::MergeMethod MergeMethods::sub = [](float current_value, float new_value) {
  return current_value - new_value;
};

const MergeMethods::MergeMethod MergeMethods::min = [](float current_value, float new_value) {
  return std::min(current_value, new_value);
};

const MergeMethods::MergeMethod MergeMethods::max = [](float current_value, float new_value) {
  return std::max(current_value, new_value);
};

optional<const MergeMethods::MergeMethod &> MergeMethods::mergeOperationFromString(const string &operation)
{
  auto it = m_mapOperationNameToOperationFunction.find(operation);
  if (it == m_mapOperationNameToOperationFunction.end())
    return optional<const MergeMethods::MergeMethod &>();
  return it->second;
}