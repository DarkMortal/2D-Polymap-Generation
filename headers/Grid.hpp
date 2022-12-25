#ifndef GRID
#define GRID

#include <Cell.hpp>
#include <Edge.hpp>

#include <vector>
#include <iostream>
#include <math.h>
using namespace std;

#define GRID_SIZE 20

vector<Cell> grid;
vector<Edge> edgeList;
const Color SHADOW = Color::Black;

int index(uint16_t i,uint16_t j,uint16_t n){
    if(i<0 || j<0 || i>n-1 || j>n-1) 
        throw std::string("Index out of Bounds");
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
    for(int i=1;i<GRID_SIZE-1;i++){
        for(int j=1;j<GRID_SIZE-1;j++){

            if(grid[index(i,j,GRID_SIZE)].isActive){
                // some convinient indices
                uint16_t t = index(i,j,GRID_SIZE);       // This
                uint16_t w = index(i-1,j,GRID_SIZE);     // West  
                uint16_t e = index(i+1,j,GRID_SIZE);     // East
                uint16_t n = index(i,j-1,GRID_SIZE);     // North
                uint16_t s = index(i,j+1,GRID_SIZE);     // South

                if(i!=0){
                    bool val = grid[w].isActive;
                    grid[w].isRight = !val;
                    grid[t].isLeft = !val;
                    if(val) grid[w].drawCell(win);
                }
                if(j!=0){
                    bool val = grid[n].isActive;
                    grid[n].isBottom = !val;
                    grid[t].isTop = !val;
                    if(val) grid[n].drawCell(win);
                }
                if(i!=GRID_SIZE-1){
                    bool val = grid[e].isActive;
                    grid[e].isLeft = !val;
                    grid[t].isRight = !val;
                    if(val) grid[e].drawCell(win);
                }
                if(j!=GRID_SIZE-1){
                    bool val = grid[s].isActive;
                    grid[s].isTop = !val;
                    grid[t].isBottom = !val;
                    if(val) grid[s].drawCell(win);
                }
                grid[t].drawCell(win);
            }
        }
    }
}

// TODO: Create edgelist from polymap and draw it on the screen
void createEdges(RenderTexture& win){
    // Refreshing the edgeList
    edgeList.clear();
    for(int i=1;i<GRID_SIZE-1;i++){
        for(int j=1;j<GRID_SIZE-1;j++){
            grid[index(i,j,GRID_SIZE)].top = 
            grid[index(i,j,GRID_SIZE)].bottom = 
            grid[index(i,j,GRID_SIZE)].right = 
            grid[index(i,j,GRID_SIZE)].left = -1;
        }
    }

    for(int i=1;i<GRID_SIZE-1;i++){
        for(int j=1;j<GRID_SIZE-1;j++){
            // some convinient indices
            uint16_t t = index(i,j,GRID_SIZE);      // This
            uint16_t w = index(i-1,j,GRID_SIZE);    // West  
            uint16_t e = index(i+1,j,GRID_SIZE);    // East
            uint16_t n = index(i,j-1,GRID_SIZE);    // North
            uint16_t s = index(i,j+1,GRID_SIZE);    // South

            // If this cell is active, check if needs edges
            if(grid[t].isActive){
                // If this cell doesn't have a western neighbour, it needs a western edge
                if(grid[t].isLeft){
                    // If northern neighbour has a western edge, we can extend that downward
                    // NOTE: We're not checking if southern or eastern neighbours have edges 
                    // since we're iterating from top-bottom and left-right
                    if(grid[n].isLeft && grid[n].isActive){
                        edgeList[grid[n].left].y2 += size;
                        grid[t].left = grid[n].left;
                    }
                    // Else we need to create a new Edge and add it to our edgeList
                    else{
                        edgeList.push_back(Edge(
                            grid[t].getX()*size,        //x1
                            grid[t].getY()*size,        //y1
                            grid[t].getX()*size,        //x2
                            grid[t].getY()*size+size    //y2
                        ));
                        grid[t].left = edgeList.size()-1;
                    }
                }
                if(grid[t].isBottom){
                    // If western neighbour has a southern edge, we can extend that downward
                    if(grid[w].isBottom && grid[w].isActive){
                        edgeList[grid[w].bottom].x2 += size;
                        grid[t].bottom = grid[w].bottom;
                    }
                    else{
                        edgeList.push_back(Edge(
                            grid[t].getX()*size,        //x1
                            grid[t].getY()*size+size,   //y1
                            grid[t].getX()*size+size,   //x2
                            grid[t].getY()*size+size    //y2
                        ));
                        grid[t].bottom = edgeList.size()-1;
                    }
                }
                if(grid[t].isRight){
                    // If northern neighbour has a eastern edge, we can extend that downward
                    if(grid[n].isRight && grid[n].isActive){
                        edgeList[grid[n].right].y2 += size;
                        grid[t].right = grid[n].right;
                    }
                    else{
                        edgeList.push_back(Edge(
                            grid[t].getX()*size+size,   //x1
                            grid[t].getY()*size,        //y1
                            grid[t].getX()*size+size,   //x2
                            grid[t].getY()*size+size    //y2
                        ));
                        grid[t].right = edgeList.size()-1;
                    }
                }
                if(grid[t].isTop){
                    // If western neighbour has a southern edge, we can extend that downward
                    if(grid[w].isTop && grid[w].isActive){
                        edgeList[grid[w].top].x2 += size;
                        grid[t].top = grid[w].top;
                    }
                    else{
                        edgeList.push_back(Edge(
                            grid[t].getX()*size,        //x1
                            grid[t].getY()*size,        //y1
                            grid[t].getX()*size+size,   //x2
                            grid[t].getY()*size         //y2
                        ));
                        grid[t].top = edgeList.size()-1;
                    }
                }
            }
        }
    }
    // TODO: Draw the edges
    for(Edge& e:edgeList) e.drawEdge(win);
}

#endif //GRID