#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <random>
#include <string>
using namespace sf;

struct fruit{
    int x;
    int y;
};

struct snake{
    int x;
    int y;
};

int score = 0;
bool game = true;
snake Snake[100];
fruit Fruit;
int size_of_block = 30;
int screen_width = size_of_block * 30;
int screen_height = size_of_block * 25;
int snake_size = 3;
int direction = 0;


void game_action(){
    for(int i = snake_size;i > 0;--i){
        Snake[i].x = Snake[i-1].x;
        Snake[i].y = Snake[i-1].y;
    }
    if(direction == 0){
        Snake[0].x++;
    }else if(direction == 1){
        Snake[0].x--;
    }else if(direction == 2){
        Snake[0].y++;
    }else if(direction == 3){
        Snake[0].y--;
    }

    if((Snake[0].x == Fruit.x) && (Snake[0].y == Fruit.y)){
        snake_size++;
        int forRandx = screen_width/size_of_block - 1;
        int forRandy = screen_height/size_of_block - 1;
        Fruit.x = rand() % forRandx + 1;
        Fruit.y = rand() % forRandy + 1;
        score++;
    }
    for(int i = 1;i < snake_size;i++){
        if(Snake[0].x == Snake[i].x && Snake[0].y == Snake[i].y){
            game = false;
        }
    }
    int vx = screen_width/size_of_block;
    int vy = screen_height/size_of_block;
    if(Snake[0].x > vx-1){
        Snake[0].x = 0;
    }
    else if(Snake[0].x < 0){
        Snake[0].x = vx-1;
    }
    else if(Snake[0].y > vy-1){
        Snake[0].y = 0;
    }
    else if(Snake[0].y < 0){
        Snake[0].y = vy-1;
    };

}

int main()
{   
    Texture textures;
    textures.loadFromFile("snake-graphics.png");
    Text scoreBoard;
    Font font;
    font.loadFromFile("fonti.ttf");
    scoreBoard.setString("Score: " + std::to_string(score));
    scoreBoard.setFont(font);
    scoreBoard.setPosition(Vector2f(size_of_block,0));
    scoreBoard.setCharacterSize(20);
    scoreBoard.setFillColor(Color::Black);
    for(int i = 0;i < snake_size;++i){
        Snake[i].x = 1;
        Snake[i].y = 1;
    }
    SoundBuffer buffer;
    buffer.loadFromFile("SOSS.wav");
    Sound song;
    song.setBuffer(buffer);
    song.setLoop(true);
   // song.play();

    srand(time(NULL));
    Clock clock;
    float chrono = 0;
    float delay = 0.1; 

    RenderWindow window(sf::VideoMode(screen_width,screen_height), "Snake Game");
    Texture back_texture;
    back_texture.loadFromFile("background.jpg");
    Sprite background;
    background.setTexture(back_texture);
    background.scale(Vector2f(screen_width/1680.f,screen_height/1050.f));
    background.setPosition(Vector2f(0,0));

    Sprite snake_head_up;
    snake_head_up.setTexture(textures);
    snake_head_up.setTextureRect(IntRect(192,0,64,64));
    snake_head_up.scale(Vector2f(30.f/64.f,30.f/64.f));

    Sprite snake_head_down;
    snake_head_down.setTexture(textures);
    snake_head_down.setTextureRect(IntRect(256,64,64,64));
    snake_head_down.scale(Vector2f(30.f/64.f,30.f/64.f));

    Sprite snake_head_right;
    snake_head_right.setTexture(textures);
    snake_head_right.setTextureRect(IntRect(256,0,64,64));
    snake_head_right.scale(Vector2f(30.f/64.f,30.f/64.f));

    Sprite snake_head_left;
    snake_head_left.setTexture(textures);
    snake_head_left.setTextureRect(IntRect(192,64,64,64));
    snake_head_left.scale(Vector2f(30.f/64.f,30.f/64.f));
   

    Sprite snake_rotation_left_up;
    snake_rotation_left_up.setTexture(textures);
    snake_rotation_left_up.setTextureRect(IntRect(128,0,64,64));
    snake_rotation_left_up.scale(Vector2f(30.f/64.f,30.f/64.f));

    Sprite snake_rotation_right_up;
    snake_rotation_right_up.setTexture(textures);
    snake_rotation_right_up.setTextureRect(IntRect(0,0,64,64));
    snake_rotation_right_up.scale(Vector2f(30.f/64.f,30.f/64.f));

    Sprite snake_rotation_left_down;
    snake_rotation_left_down.setTexture(textures);
    snake_rotation_left_down.setTextureRect(IntRect(128,128,64,64));
    snake_rotation_left_down.scale(Vector2f(30.f/64.f,30.f/64.f));

    Sprite snake_rotation_right_down;
    snake_rotation_right_down.setTexture(textures);
    snake_rotation_right_down.setTextureRect(IntRect(0,64,64,64));
    snake_rotation_right_down.scale(Vector2f(30.f/64.f,30.f/64.f));

    Sprite snake_horizontal;
    snake_horizontal.setTexture(textures);
    snake_horizontal.setTextureRect(IntRect(64,0,64,64));
    snake_horizontal.scale(Vector2f(30.f/64.f,30.f/64.f));


    Sprite snake_vertical;
    snake_vertical.setTexture(textures);
    snake_vertical.setTextureRect(IntRect(128,64,64,64));
    snake_vertical.scale(Vector2f(30.f/64.f,30.f/64.f));

    Sprite tale_up;
    tale_up.setTexture(textures);
    tale_up.setTextureRect(IntRect(256,192,64,64));
    tale_up.scale(Vector2f(30.f/64.f,30.f/64.f));
    
    Sprite tale_down;
    tale_down.setTexture(textures);
    tale_down.setTextureRect(IntRect(192,128,64,64));
    tale_down.scale(Vector2f(30.f/64.f,30.f/64.f));

    Sprite tale_right;
    tale_right.setTexture(textures);
    tale_right.setTextureRect(IntRect(192,192,64,64));
    tale_right.scale(Vector2f(30.f/64.f,30.f/64.f));

    Sprite tale_left;
    tale_left.setTexture(textures);
    tale_left.setTextureRect(IntRect(256,128,64,64));
    tale_left.scale(30.f/64.f,30.f/64.f);

    Sprite apple;
    apple.setTexture(textures);
    apple.setTextureRect(IntRect(0,192,64,64));
    apple.scale(Vector2f(30.f/64.f,30.f/64.f));

    int forRandx = screen_width/size_of_block - 1;
    int forRandy = screen_height/size_of_block - 1;
    Fruit.x = rand() % forRandx + 1;
    Fruit.y = rand() % forRandy + 1;
    Sprite graphics[100];

    window.setFramerateLimit(60);
    while (window.isOpen()){
    float time = clock.getElapsedTime().asSeconds();
    clock.restart();
    chrono += time;
    Event event;
    if(!game){
        window.clear();
        window.close();
    }
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
    
    if(Keyboard::isKeyPressed(Keyboard::Left)){
        if(direction != 0)
        direction = 1;
    }if(Keyboard::isKeyPressed(Keyboard::Right)){
        if(direction != 1)
        direction = 0;
    }if(Keyboard::isKeyPressed(Keyboard::Down)){
        if(direction != 3)
        direction = 2;
    }if(Keyboard::isKeyPressed(Keyboard::Up)){
        if(direction != 2)
        direction = 3;
    }

    if(chrono >= delay){
        chrono = 0;
        game_action();
     for(int i = 0; i < snake_size;++i){
        if(i == 0){
            if(direction == 0){
                snake_head_right.setPosition(Vector2f(Snake[i].x * size_of_block,Snake[i].y * size_of_block));
                graphics[i] = snake_head_right;
            }else if(direction == 1){
                snake_head_left.setPosition(Vector2f(Snake[i].x * size_of_block,Snake[i].y * size_of_block));
            graphics[i] = snake_head_left;
            }else if(direction == 2){
                snake_head_down.setPosition(Vector2f(Snake[i].x * size_of_block,Snake[i].y * size_of_block));
                graphics[i] = snake_head_down;
            }else{
                snake_head_up.setPosition(Vector2f(Snake[i].x * size_of_block,Snake[i].y * size_of_block));
                graphics[i] = snake_head_up;
            }
        }else if(i != snake_size-1){
            if(Snake[i-1].x == Snake[i].x + 1 && Snake[i-1].y == Snake[i].y && Snake[i+1].y == Snake[i].y + 1 && Snake[i+1].x == Snake[i].x){
                snake_rotation_right_up.setPosition(Vector2f(Snake[i].x * size_of_block,Snake[i].y * size_of_block));
                graphics[i] = snake_rotation_right_up;
            }else if(Snake[i-1].x == Snake[i].x - 1 && Snake[i-1].y == Snake[i].y && Snake[i+1].y == Snake[i].y + 1 && Snake[i+1].x == Snake[i].x){
                snake_rotation_left_up.setPosition(Vector2f(Snake[i].x * size_of_block,Snake[i].y * size_of_block));
                graphics[i] = snake_rotation_left_up;
            }else if(Snake[i+1].x == Snake[i].x + 1 && Snake[i+1].y == Snake[i].y && Snake[i-1].y == Snake[i].y + 1 && Snake[i-1].x == Snake[i].x){
                snake_rotation_right_up.setPosition(Vector2f(Snake[i].x * size_of_block,Snake[i].y * size_of_block));
                graphics[i] = snake_rotation_right_up;
            }else if(Snake[i+1].x == Snake[i].x - 1 && Snake[i+1].y == Snake[i].y && Snake[i-1].y == Snake[i].y + 1 && Snake[i-1].x == Snake[i].x){
                snake_rotation_left_up.setPosition(Vector2f(Snake[i].x * size_of_block,Snake[i].y * size_of_block));
                graphics[i] = snake_rotation_left_up;
            }else if(Snake[i-1].x == Snake[i].x - 1 && Snake[i-1].y == Snake[i].y && Snake[i+1].y == Snake[i].y - 1 && Snake[i+1].x == Snake[i].x){
                snake_rotation_left_down.setPosition(Vector2f(Snake[i].x * size_of_block,Snake[i].y * size_of_block));
                graphics[i] = snake_rotation_left_down;
            }else if(Snake[i+1].x == Snake[i].x - 1 && Snake[i+1].y == Snake[i].y && Snake[i-1].y == Snake[i].y - 1 && Snake[i-1].x == Snake[i].x){
                snake_rotation_left_down.setPosition(Vector2f(Snake[i].x * size_of_block,Snake[i].y * size_of_block));
                graphics[i] = snake_rotation_left_down;
            }else if(Snake[i+1].x == Snake[i].x + 1 && Snake[i+1].y == Snake[i].y && Snake[i-1].y == Snake[i].y - 1 && Snake[i-1].x == Snake[i].x){
                snake_rotation_right_down.setPosition(Vector2f(Snake[i].x * size_of_block,Snake[i].y * size_of_block));
                graphics[i] = snake_rotation_right_down;
            }else if(Snake[i-1].x == Snake[i].x + 1 && Snake[i-1].y == Snake[i].y && Snake[i+1].y == Snake[i].y - 1 && Snake[i+1].x == Snake[i].x){
                snake_rotation_right_down.setPosition(Vector2f(Snake[i].x * size_of_block,Snake[i].y * size_of_block));
                graphics[i] = snake_rotation_right_down;
            }else if(Snake[i-1].y == Snake[i+1].y){
                snake_horizontal.setPosition(Vector2f(Snake[i].x * size_of_block,Snake[i].y * size_of_block));
                graphics[i] = snake_horizontal;
            }else if(Snake[i-1].x == Snake[i+1].x){
                snake_vertical.setPosition(Vector2f(Snake[i].x * size_of_block,Snake[i].y * size_of_block));
                graphics[i] = snake_vertical;
            }      
        }else{
            if(Snake[i-1].y > Snake[i].y && Snake[i-1].y - Snake[i].y <= 1){
                tale_up.setPosition(Vector2f(Snake[i].x * size_of_block,Snake[i].y * size_of_block));
                graphics[i] = tale_up;
            }else if(Snake[i-1].y < Snake[i].y && Snake[i-1].y - Snake[i].y >= -1){
                tale_down.setPosition(Vector2f(Snake[i].x * size_of_block,Snake[i].y * size_of_block));
                graphics[i] = tale_down;
            }else if(Snake[i-1].x > Snake[i].x){
                tale_left.setPosition(Vector2f(Snake[i].x * size_of_block,Snake[i].y * size_of_block));
                graphics[i] = tale_left;
            }else if (Snake[i-1].x < Snake[i].x){
                tale_right.setPosition(Vector2f(Snake[i].x * size_of_block,Snake[i].y * size_of_block));
                graphics[i] = tale_right;
            }
        }
    scoreBoard.setString("Score: " + std::to_string(score));
    }
    }

    window.clear(); 
    window.draw(background);
    for(int i = 0; i < snake_size;++i){
        window.draw(graphics[i]);
    }
    apple.setPosition(Vector2f(Fruit.x * size_of_block,Fruit.y * size_of_block));
    window.draw(apple);
    window.draw(scoreBoard);
    window.display();
    }
    return 0;
}
