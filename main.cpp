#include <Cell.hpp>
#include <Grid.hpp>
#include <unistd.h>

int main(){
    try{
        Event evt;
        RenderWindow window(VideoMode((CELLWIDTH)*GRID_SIZE,(CELLWIDTH)*GRID_SIZE),"2D Ray Casting",Style::Close);
        RenderTexture texture;
        texture.create((CELLWIDTH)*GRID_SIZE,(CELLWIDTH)*GRID_SIZE);
        texture.clear(SHADOW);
        GridInit(GRID_SIZE,texture);
        while(window.isOpen()){
            while(window.pollEvent(evt)){
                if(evt.type == Event::Closed){
                    window.close();
                    cout<<"Window Closed"<<endl;
                    return EXIT_SUCCESS;
                }

                if (evt.type == sf::Event::MouseButtonPressed){
                    uint32_t a = evt.mouseButton.x/size;
                    uint32_t b = evt.mouseButton.y/size;
                    uint32_t x = index(a,b,GRID_SIZE);
                    switch (evt.mouseButton.button){
                        case Mouse::Left: grid[x].isActive = true; break;
                        case Mouse::Right: grid[x].isActive = false; break;
                        default: break;
                    }
                }

                if(evt.type == Event::KeyPressed && evt.key.code == Keyboard::S){
                    Image img = texture.getTexture().copyToImage();
                    img.saveToFile("./Cast.png");
                    cout<<"Image exported Successfully"<<endl;
                }

            }
            window.clear();
            texture.clear();
            DrawGrid(texture);
            texture.display();
            window.draw(Sprite(texture.getTexture()));
            window.display();
        }
    }catch(string err){
        cerr<<err<<endl;
        return EXIT_FAILURE;
    }
}
