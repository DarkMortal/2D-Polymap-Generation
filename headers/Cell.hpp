#ifndef CELL
#define CELL

#include <SFML/Graphics.hpp>
#define CELLWIDTH size+borderWidth
using namespace sf;

const int size = 30,borderWidth = 3;
const Vector2f cellSize(size,size),borderSize(size,borderWidth);
const Color cellColor = Color::Blue, borderColor = Color::White;

class Cell{
    int posX,posY;
    public: 
        bool isLeft,isBottom,isRight,isTop,isActive;
        Cell(int a,int b):posX(a),posY(b){
            isActive=false;
            isLeft=isBottom=isRight=isTop=true;
        }
        void drawCell(RenderTexture&);
        int getX() const { return posX; }
        int getY() const { return posY; }
};

void Cell::drawCell(RenderTexture& window){
    RectangleShape cell(cellSize);
    cell.setFillColor(cellColor);
    cell.setPosition(posX*size,posY*size);
    window.draw(cell);
    if(isLeft){
        RectangleShape left(borderSize);
        left.setFillColor(borderColor);
        left.setRotation(90);
        left.setPosition(size*posX,size*posY);
        window.draw(left);
    }
    if(isBottom){
        RectangleShape bottom(borderSize);
        bottom.setFillColor(borderColor);
        bottom.setPosition(size*posX,size*(posY+1));
        window.draw(bottom);
    }
    if(isRight){
        RectangleShape right(borderSize);
        right.setFillColor(borderColor);
        right.setRotation(90);
        right.setPosition(size*(posX+1),size*posY);
        window.draw(right);
    }
    if(isTop){
        RectangleShape top(borderSize);
        top.setFillColor(borderColor);
        top.setPosition(size*posX,size*posY);
        window.draw(top);
    }
}

#endif //CELL