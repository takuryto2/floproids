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


sfFont* font1;
sfRenderWindow* window;

float shipX = 1920 / 2;
float shipY = 1080 / 2;
float shipS = 30;
float shipAngle = -90;

int Delta() {
    sfTime dtime = sfClock_getElapsedTime(deltaclock);
    delta = sfTime_asMilliseconds(dtime);
    sfClock_restart(deltaclock);
}

//set up the fullscreen
int create() {
    WINDOW_X = sfVideoMode_getDesktopMode().width;
    WINDOW_Y = sfVideoMode_getDesktopMode().height;
    sfVideoMode mode = { WINDOW_X, WINDOW_Y, 32 };

    window = sfRenderWindow_create(mode, "mokeyroids", sfFullscreen, NULL);
    sfRenderWindow_setFramerateLimit(window, 144);

    deltaclock = sfClock_create();
    font1 = sfFont_createFromFile("Font/RetroGaming.ttf");
}

int wrapAround(sfSprite* sprtship) {
    sfVector2f position = sfSprite_getPosition(sprtship);

    if (position.x > WINDOW_X) {
        shipX -= WINDOW_X + 2;
    }
    else if (position.x < 0) {
        shipX += WINDOW_X - 2;
    }

    if (position.y > WINDOW_Y) {
        shipY -= WINDOW_Y + 2;
    }
    else if (position.y < 0) {
        shipY += WINDOW_Y - 2;
    }
}

int astéroides() {
    sfFloatRect tx_rock = { 0,0,22,30 };
    sfTexture* textrock = sfTexture_createFromFile("asteroids-asteroids(B)_0.png", &tx_rock);
    sfSprite* sprtrock = sfSprite_create();
    sfVector2f scale = { 3.5f, 3.5f };
    sfSprite_setOrigin(sprtrock, (sfVector2f) { 11, 15 });
    sfSprite_setScale(sprtrock, scale);
    sfSprite_setTexture(sprtrock, textrock, true);
    sfSprite_setPosition(sprtrock, (sfVector2f) { shipX, shipY });
}

int main() {
    srand(time(0));
    create();
    
    sfVector2f dir = (sfVector2f){ 0,0 };
    sfVector2f str = (sfVector2f){ 0,0 };

    //set up the ship sprite
    sfFloatRect tx_rect = {0,0,22,30};
    sfTexture* textrship = sfTexture_createFromFile("asteroids-ship0.png", &tx_rect);
    sfSprite* sprtship = sfSprite_create();
    sfVector2f scale = { 3.5f, 3.5f };
    sfSprite_setOrigin(sprtship, (sfVector2f) { 11, 15 });
    sfSprite_setScale(sprtship, scale);
    sfSprite_setTexture(sprtship, textrship, true);
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

        if (sfKeyboard_isKeyPressed(sfKeyUp)) {

            dir.x = cosf(shipAngle * 3.1415 / 180);
            dir.y = sinf(shipAngle * 3.1415 / 180);
            if (fabs(str.x + shipS * dir.x * delta / 100.0) < fabs(150.0 * dir.x * delta / 100.0)) {
                str.x += shipS * dir.x * delta / 100.0;
            }
            else {
                str.x = 0;
            }

            if (fabs(str.y + shipS * dir.y * delta / 100.0) < fabs(150.0 * dir.y * delta / 100.0)) {
                str.y += shipS * dir.y * delta / 100.0;
            }
            else {
                str.y = 0;
            }
        }

        //player mouvment
        if (sfKeyboard_isKeyPressed(sfKeyLeft)) {
          shipAngle -= 3;        
        }

        if (sfKeyboard_isKeyPressed(sfKeyRight)) {
            shipAngle += 3;
        }

        shipX += str.x;
        shipY += str.y;

        float a_length = sqrt(str.x * str.x + str.y * str.y);
        if (a_length != 0) {
            float normalized_x = str.x / a_length;
            float normalized_y = str.y / a_length;

            str.x -= 0.17 * normalized_x;
            str.y -= 0.17 * normalized_y;
        }

        wrapAround(sprtship);
        
        sfSprite_setRotation(sprtship, shipAngle + 90);
        sfSprite_setPosition(sprtship, (sfVector2f) { shipX, shipY });

        Delta();

        if (sfKeyboard_isKeyPressed(sfKeyEscape)) { sfRenderWindow_close(window); } //quit

        
        sfRenderWindow_clear(window, sfTransparent);
        sfRenderWindow_drawSprite(window, sprtship,NULL);
        sfRenderWindow_display(window);
    }
    sfRenderWindow_destroy(window);
    sfSprite_destroy(sprtship);
    sfTexture_destroy(textrship);
 
    sfClock_destroy(deltaclock);
    return 0;
}