#ifndef GRID
#define GRID

#include <Cell.hpp>
#include <vector>
#include <iostream>
using namespace std;

#define GRID_SIZE 20

std::vector<Cell> grid;
const Color SHADOW = Color::Black;

int index(int i,int j,int n){
    if(i<0 || j<0 || i>n-1 || j>n-1) throw std::string("Index out of Bounds");
    return j+i*n;
}

//TODO: Initializes the Grid
void GridInit(int n,RenderTexture& w){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            Cell x = Cell(i,j);
            if(i==0) x.isLeft = false;
            if(i==n-1) x.isRight = false;
            if(j==0) x.isTop = false;
            if(j==n-1) x.isBottom = false;
            x.drawCell(w);
            grid.push_back(x);
        }
    }
}

void DrawGrid(RenderTexture& win){
    for(int i=0;i<GRID_SIZE;i++){
        for(int j=0;j<GRID_SIZE;j++){
            if(grid[index(i,j,GRID_SIZE)].isActive){
                if(i!=0){
                    bool val = grid[index(i-1,j,GRID_SIZE)].isActive;
                    grid[index(i-1,j,GRID_SIZE)].isRight = !val;
                    grid[index(i,j,GRID_SIZE)].isLeft = !val;
                    if(val) grid[index(i-1,j,GRID_SIZE)].drawCell(win);
                }
                if(j!=0){
                    bool val = grid[index(i,j-1,GRID_SIZE)].isActive;
                    grid[index(i,j-1,GRID_SIZE)].isBottom = !val;
                    grid[index(i,j,GRID_SIZE)].isTop = !val;
                    if(val) grid[index(i,j-1,GRID_SIZE)].drawCell(win);
                }
                if(i!=GRID_SIZE-1){
                    bool val = grid[index(i+1,j,GRID_SIZE)].isActive;
                    grid[index(i+1,j,GRID_SIZE)].isLeft = !val;
                    grid[index(i,j,GRID_SIZE)].isRight = !val;
                    if(val) grid[index(i+1,j,GRID_SIZE)].drawCell(win);
                }
                if(j!=GRID_SIZE-1){
                    bool val = grid[index(i,j+1,GRID_SIZE)].isActive;
                    grid[index(i,j+1,GRID_SIZE)].isTop = !val;
                    grid[index(i,j,GRID_SIZE)].isBottom = !val;
                    if(val) grid[index(i,j+1,GRID_SIZE)].drawCell(win);
                }
                grid[index(i,j,GRID_SIZE)].drawCell(win);
            }
        }
    }
}

#endif //GRID