#pragma once

#include <string>

#include "Parsable.h"
#include "SetIntersection.h"

class Rucksack : public Parsable
{
public:
    void Parse(std::string_view data);
    
    std::string_view Partition1() const { return partition_1; }
    std::string_view Partition2() const { return partition_2; }

    std::string GetCommonItems() const;

    template<class... Ts>
    std::string GetCommonItems(Ts&&... ts) const
    {
        std::string result;
        set_intersection(std::back_inserter(result), GetMergedAndSortedPartitions(), ts.GetMergedAndSortedPartitions() ...);
        result.erase(std::unique(result.begin(), result.end()), result.end());
        return result;
    }

private:
    std::string GetMergedAndSortedPartitions() const
    {
        auto result = partition_1 + partition_2;
        std::ranges::sort(result);
        return result;
    }

    std::string partition_1;
    std::string partition_2;
};