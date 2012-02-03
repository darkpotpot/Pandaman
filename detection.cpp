#include <math.h>
#include <algorithm>
#include <list>
#include "detection.h"
#include "cell.h"

#include <iostream>

using namespace std;

//test function
void display_traversed_cases(int x1,int y1,int x2, int y2)
{
    cout<<"==========="<<endl;
    list<Point2d> traversed_cases;
    int x_min = min(x1, x2)-1;
    int x_max = max(x1,x2)+1;
    int y_min = min(y1, y2)-1;
    int y_max = max(y1,y2)+1;
    int height = y_max -y_min;
    int width = x_max-x_min;
    char* c = new char[(width+1)*(height+1)];
    for(int idx=0;idx<width*height;idx++)
        {c[idx] = '_';}
    get_traversed_cases( x1, y1, x2,  y2, traversed_cases);

    for(list<Point2d>::iterator it = traversed_cases.begin();
        it!=traversed_cases.end();
        it++)
    {c[((*it).get_y()-y_min)*width+(*it).get_x()-x_min] = 'X';
    cout<<" pos : "<<(*it).get_x()<< ", "<<(*it).get_y()<<endl;
    
    }
    c[(y1-y_min)*width+x1-x_min] = 'O';
    c[(y2-y_min)*width+x2-x_min] = 'O';
    for(int idx_y =0;idx_y<height;idx_y++) 
    {
        for(int idx_x =0;idx_x<width;idx_x++)
        {
        cout<<c[(idx_y)*width+(idx_x)];
        }
        cout<<endl;
    }
    cout<<"++++++++++"<<endl;
    delete[] c;
}

void get_traversed_cases(int x1,int y1,int x2, int y2, list<Point2d>& traversed_cases)
{
    int x_max = max(x1,x2);
    int x_min = min(x1,x2);
    int y_max = max(y1,y2);
    int y_min = min(y1,y2);
    if (x2==x1)
    {
        for(int y=y_min; y<=y_max;y++)
            { traversed_cases.push_back(Point2d(x1,y)); }
    }
    else
    {
        float a = ((float)(y2-y1))/((float)(x2-x1));
        float b = y1-a*x1;
        
        for(int x=x_min; x<x_max;x++)
        {
            float fx = (float)x;
            float y_start = (fx-0.5f)*a+b;
            float y_end = (fx+0.5f)*a+b;
            for(int y=(int)floor(min(y_start, y_end)); y<=(int)ceil(max(y_start, y_end));y++)
            {
                if ((x>=x_min)&&(x<=x_max)&&(y>=y_min) &&(y<=y_max))
                { traversed_cases.push_back(Point2d(x,y)); }
            }
        }
    }

}

bool is_visible(int x1,int y1,int x2, int y2, Grid* grid)
{
    list<Point2d> traversed_cases;
    get_traversed_cases( x1, y1, x2,  y2, traversed_cases);
    for (list<Point2d>::iterator it = traversed_cases.begin(); it!=traversed_cases.end();it++)
        {
            if (!grid->is_accessible(it->get_x(), it->get_y()))
                {
                    return false;
                }
        }
    return true;
}

void get_panda_pos_ifp(Grid* grid, int x, int y, bool& panda_detected, int& panda_x, int& panda_y, int dist)
{
    panda_detected = false;
    int start_x = x-dist;
    if (start_x<0)
        {start_x=0;}
    int end_x = x+dist;
    if (end_x>=grid->getWidth())
        {end_x=grid->getWidth()-1;}

    int start_y = y-dist;
    if (start_y<0)
        {start_y=0;}
    int end_y = y+dist;
    if (end_y>=grid->getHeight())
        {end_y=grid->getHeight()-1;}
    
    for (int x_case=start_x;x_case<=end_x;x_case++)
    {
        for (int y_case=start_y;y_case<end_y;y_case++)
        {
            list<CellElem*> cellElems = grid->getCellElems(x_case, y_case);
            for (list<CellElem*>::iterator it =cellElems.begin();
                it!=cellElems.end();
                it++)
            {
                if ((*it)->getType()==CHARACTER)
                {
                    panda_x = x_case;
                    panda_y = y_case;
                    if (is_visible(x,y,panda_x, panda_y, grid))
                    {
                        panda_detected = true;
                        return;
                    }
                    else
                    {
                        panda_detected = false;
                        return;
                    }
                }
            }
        }
    }
}