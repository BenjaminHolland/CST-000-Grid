#pragma once
#include <memory>
#include <algorithm>
#include <functional>

//Dynamically Sized, Non-Resizeable Grid Class.
//Provides Visitor-Pattern access to rows and columns
template <class item_t,class alloc_t=std::allocator<item_t>>
class Grid {
private:
    item_t* data;
    size_t width, height;
public:
    Grid(size_t width, size_t height) :width(width), height(height),data(nullptr) {
        alloc_t a;
        data=std::allocator_traits<alloc_t>::allocate(a, width*height);
        item_t* ptr = data;
        while (ptr != data + width*height) {
            std::allocator_traits<alloc_t>::construct(a, ptr);
            ptr++;
        }
    }
    Grid(const Grid &copied) :width(copied.width), height(copied.height), data(nullptr){
        alloc_t a;
        data = std::allocator_traits<alloc_t>::allocate(a, width*height);
        std::copy(copied.data, copied.data + width*height, data);
    }
    Grid(Grid &&moved) :width(moved.width), height(moved.height), data(moved.data) {
        alloc_t a;
        moved.data = nullptr;
        moved.width = moved.height=0;
        
    }
    ~Grid() {
        alloc_t a;
        if (data != nullptr) {
            item_t* ptr = data;
            while (ptr != data + width*height) {
                std::allocator_traits<alloc_t>::destroy(a, ptr);
                ptr++;
            }
            std::allocator_traits<alloc_t>::deallocate(a,data, width*height);
            width = height = 0;
            data = nullptr;
        }
    }
    inline size_t Height() const {
        return height;
    }
    
    inline size_t Width() const {
        return width;
    }

    item_t& At(size_t x, size_t y) {
        return data[y*width + x];
    }

    const item_t& At(size_t x, size_t y) const {
        return data[y*width + x];
    }
    
    
    Grid& VisitRow(size_t row, std::function<void(const item_t&)> visitor) const {
        //Get a pointer to the first item in the row.
        item_t* itr = data + row*width;
        //Get a pointer to after the last item in the row.
        item_t* row_end = data + (row + 1)*width;
        
        //iterate through the row, visiting each item using the provided visitor function.
        while (itr != row_end) {
            visitor(*itr);
            itr++;
        }
        return (*this);
    }

    Grid& VisitRow(size_t row, std::function<void(item_t&)> visitor) {
        item_t* itr = data + row*width;
        item_t* row_end = data + (row + 1)*width;
        while (itr != row_end) {
            visitor(*itr);
            itr++;
        }
        return (*this);
    }

    Grid& VisitColumn(size_t col, std::function<void(item_t&)> visitor) {
        item_t* itr = data + col;
        item_t* col_end = data + width*height;
        while (itr < col_end) {
            visitor(*itr);
            itr += width;
        }
        return (*this);
    }

    Grid& VisitColumn(size_t col, std::function<void(const item_t&)> visitor) const{
        item_t* itr = data + col;
        item_t* col_end = data + width*height;
        while (itr < col_end) {
            visitor(*itr);
            itr += width;
        }
        return (*this);
    }
    
};