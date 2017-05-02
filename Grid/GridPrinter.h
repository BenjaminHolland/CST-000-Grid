#pragma once
#include "Grid.h"
#include <iostream>
#include <functional>
#include <string>
//Provides specialized visitors for printing grids to output streams.
template <class item_t, class alloc_t = allocator<item_t>>
class GridPrinter {
private:
    Grid<item_t, alloc_t>& target;
public:
    GridPrinter(Grid<item_t, alloc_t>& grid) :target(grid) {

    }

    //Print the specified row to the output stream.
    GridPrinter& PrintRow(std::ostream& dst, size_t idx) {
        target.VisitRow(idx, [&dst](const item_t& item) {
            dst << item << " ";
        });
        return (*this);
    }

    //Print the specified row to the output stream using the specified serializer.
    GridPrinter& PrintRow(std::ostream& dst, size_t idx, std::function<std::string(const item_t&)> to_string) {
        target.VisitRow(idx, [&dst](const item_t& item) {
            dst << to_string(item) << " ";
        });
        return (*this);
    }

    //Print the specified column to the output stream.
    GridPrinter& PrintColumn(std::ostream& dst, size_t idx) {
        target.VisitColumn(idx, [&dst](const item_t& item) {
            dst << item << " ";
        });
        return (*this);
    }

    //Print the specified column to the output stream using the specified serializer.
    GridPrinter& PrintColumn(std::ostream& dst, size_t idx, std::function<string(const item_t&)> to_string) {
        target.VisitColumn(idx, [&dst](const item_t& item) {
            dst << to_string(item) << " ";
        });
        return (*this);
    }
};