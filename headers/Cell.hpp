#ifndef CELL
#define CELL

#include <SFML/Graphics.hpp>
#define CELLWIDTH size+borderWidth
using namespace sf;

const uint16_t size = 30,borderWidth = 3;
const Vector2f cellSize(size,size),borderSize(size,borderWidth);
const Color cellColor = Color::Blue, borderColor = Color::White;

class Cell{
    uint16_t posX,posY;
    public: 
        bool isLeft,isBottom,isRight,isTop,isActive;
        int16_t top,left,bottom,right;     // Edge IDs
        Cell(int a,int b):posX(a),posY(b){
            isActive=false;
            isLeft=isBottom=isRight=isTop=true;
            top=left=bottom=right=-1;
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
}

#endif //CELL