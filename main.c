#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SFML/Window.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>

typedef int bool;
#define true 1
#define false 0

int WINDOW_X = 1200;
int WINDOW_Y = 1200;

float delta = 0;

sfClock* deltaclock;
sfClock* animclock;
int nframe = 0;
int anim_time = 75; 

sfFont* font1;
sfRenderWindow* window;

int Delta() {
    sfTime dtime = sfClock_getElapsedTime(deltaclock);
    delta = sfTime_asMilliseconds(dtime);
    sfClock_restart(deltaclock);
}

int create() {
    WINDOW_X = sfVideoMode_getDesktopMode().width;
    WINDOW_Y = sfVideoMode_getDesktopMode().height;
    sfVideoMode mode = { WINDOW_X, WINDOW_Y, 32 };

    window = sfRenderWindow_create(mode, "mokeyroids", sfFullscreen, NULL);
    sfRenderWindow_setFramerateLimit(window, 144);

    deltaclock = sfClock_create();
    animclock = sfClock_create();
    font1 = sfFont_createFromFile("Font/RetroGaming.ttf");
}

int main() {
    srand(time(0));
    create();

    int shipX = 0;
    int shipY = 0;
    int shipS = 0;
    

    //set up the ship sprite
    sfFloatRect tx_rect = {0,0,22,30};
    sfTexture* textr = sfTexture_createFromFile("asteroids-ship0.png", &tx_rect);
    sfSprite* sprtship = sfSprite_create();
    sfVector2f scale = { 4.5f, 4.5f };
    sfSprite_setScale(sprtship, scale);
    sfSprite_setTexture(sprtship, textr, true);
    sfSprite_setPosition(sprtship, (sfVector2f) { shipX, shipY });
    
    //set up view charging
    sfFloatRect view_rectangle = {0,0,0,0};
    sfView* new_view = sfView_createFromRect(view_rectangle);

    while (sfRenderWindow_isOpen(window)) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }
        if (event.type == sfEvtKeyPressed) {
            if (event.key.code == sfKeyLeft) {

            }
            else if (event.key.code == sfKeyRight) {

            }
            else if (event.key.code == sfKeyUp)&shipS < 3; {
                shipS = shipS+0.2;
                
            }
            
        }
            Delta();

        if (sfKeyboard_isKeyPressed(sfKeyEscape)) { sfRenderWindow_close(window); } //quit

        
        sfRenderWindow_clear(window, sfTransparent);
        sfRenderWindow_drawSprite(window, sprtship,NULL);
        sfRenderWindow_display(window);
    }
    sfRenderWindow_destroy(window);
    sfClock_destroy(deltaclock);
    return 0;
}