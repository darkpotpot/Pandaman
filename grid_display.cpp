#include "grid_display.h"
#include "cell.h"

#include <iostream>
using namespace std;

void text_display(Grid& grid){
    Cell* toto;
    for (int i=0; i < grid.mHeight; i++){
        for (int j=0; j < grid.mWidth; j++){
            switch (grid.is_accessible(i, j)){
                case true:
                    cout << "-";
                    break;
                case false:
                    cout << "*";
                    break;
            }
        }
        cout << endl;
    }
}
