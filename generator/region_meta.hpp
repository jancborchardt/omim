#pragma once

#include "generate_info.hpp"

#include "indexer/feature_meta.hpp"

namespace feature
{
bool ReadRegionData(string const & countryName, RegionData & data);
}  // namespace feature
