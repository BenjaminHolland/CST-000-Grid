#pragma once
#include "Grid.h"
#include <stdexcept>
//Provides specialized visistors for filling grids.
template <class item_t, class alloc_t = allocator<item_t>>
class GridBuilder {
private:
    Grid<item_t, alloc_t>& target;
public:
    GridBuilder(Grid<item_t, alloc_t>& grid) :target(grid) {

    }
    template <class itr_t>
    GridBuilder& FillRow(size_t row, itr_t begin, itr_t end) {
        itr_t itr = begin;
        try {
            target.VisitRow(row, [&itr, end](item_t& item) {
                if (itr == end) {
                    std::runtime_error("Early Termination");
                } else {
                    item = *itr;
                    itr++;
                }
            });
        } catch (std::runtime_error&) {
            //We terminated the visitation loop early, this is fine.
            //We really should make Grid take a function that returns some kind of return code
            //that can control visitation, but I'm lazy and don't need it right now. 
        }
        return (*this);
    }
};