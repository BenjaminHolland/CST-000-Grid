#include "Grid.h"
#include "GridBuilder.h"
#include "GridPrinter.h"
#include <iostream>
using namespace std;






int main(int argc, char* argv[]) {
    Grid<bool> adj(3, 3);
    
    bool data[3][3] = {
        {false,true,false},
        {false,false,true},
        {true,false,false}
    };

    GridBuilder<bool> bldr(adj);
    for (int row = 0; row < 3; row++) {
        bldr.FillRow(row, begin(data[row]), end(data[row]));
    }

    GridPrinter<bool> prntr(adj);
    for (int col = 0; col < adj.Width(); col++) {
        prntr.PrintColumn(cout, col);
        cout << endl;
    }
}