#include <Cell.hpp>
#include <Grid.hpp>
#include <time.h>
#include <string.h>

int main(){
    try{
        Event evt; Font font; Text text;
        RenderWindow window(VideoMode(size*GRID_SIZE,size*GRID_SIZE),"Polymap Generation",Style::Close);
        RenderTexture texture;
        texture.create(size*GRID_SIZE,size*GRID_SIZE);
        texture.clear(SHADOW);
        GridInit(GRID_SIZE,texture);
        if (!font.loadFromFile("./fonts/Poppins-Bold.ttf")) cout<<"Font not Found"<<endl;
        else{
            cout<<"Font Loaded"<<endl;
            text.setFont(font);
            text.setString("Execution Time :");
            text.setCharacterSize(24);
            text.setStyle(Text::Bold | Text::Underlined);
            text.setPosition(100,0);
        }
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
                    if(!(a==0 || b==0 || a==GRID_SIZE-1 || b==GRID_SIZE-1)){    // To avoid edge cases
                        uint32_t x = index(a,b,GRID_SIZE);
                        switch (evt.mouseButton.button){
                            case Mouse::Left: grid[x].isActive = true; break;
                            case Mouse::Right: grid[x].isActive = false; break;
                            default: break;
                        }
                    } 
                }
                if(evt.type == Event::KeyPressed && evt.key.code == Keyboard::S){
                    Image img = texture.getTexture().copyToImage();
                    img.saveToFile("./Cast.png");
                    cout<<"Image exported Successfully"<<endl;    
                }
            } 

            // TODO: Refreshing the Scene
            window.clear();
            texture.clear();

            DrawGrid(texture);

            if(evt.type == sf::Event::MouseButtonPressed){
                clock_t start = clock();
                createEdges(texture);
                clock_t end = clock();

                double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                text.setString("Execution Time : "+std::to_string(cpu_time_used*1e6)+" ms");
                texture.draw(text);
            }else{
                createEdges(texture);
                texture.draw(text);
            }
            
            texture.display();
            window.draw(Sprite(texture.getTexture()));
            window.display();
        }
    }catch(string err){
        cerr<<err<<endl;
        return EXIT_FAILURE;
    }
}