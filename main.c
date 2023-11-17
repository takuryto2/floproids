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
float shipS = 15;
float shipAngle = -90;

struct valorasteroid {

    sfVector2f rock;
    sfVector2f dirock;
    sfVector2f strock;
    float RockS;
    float RockAng;
    sfTexture* textrock;
    sfSprite* sprtrock;
};

struct valorlaser {
    sfVector2f laser;
    sfVector2f dirlaser;
    sfVector2f strlaser;
    float laserS;
    float laserAng;
    sfTexture* textrlaser;
    sfSprite* sprtlaser;
};

void Delta() {
    sfTime dtime = sfClock_getElapsedTime(deltaclock);
    delta = sfTime_asMilliseconds(dtime);
    sfClock_restart(deltaclock);
}

//set up the fullscreen
void create() {
    WINDOW_X = sfVideoMode_getDesktopMode().width;
    WINDOW_Y = sfVideoMode_getDesktopMode().height;
    sfVideoMode mode = { WINDOW_X, WINDOW_Y, 32 };

    window = sfRenderWindow_create(mode, "mokeyroids", sfFullscreen, NULL);
    sfRenderWindow_setFramerateLimit(window, 144);

    deltaclock = sfClock_create();
    font1 = sfFont_createFromFile("Font/RetroGaming.ttf");
}

void wrapAround(sfSprite* sprtship ) {
    sfVector2f position = sfSprite_getPosition(sprtship);

    if (position.x > WINDOW_X) {
        shipX -= WINDOW_X + 2;
    }
    if (position.x < 0) {
        shipX += WINDOW_X - 2;
    }
    if (position.y > WINDOW_Y) {
        shipY -= WINDOW_Y + 2;
    }
    if (position.y < 0) {
        shipY += WINDOW_Y - 2;
    }
}

void summonrock(struct valorasteroid *mai) {
    //create and draws the asteroid
    sfFloatRect tx_rock = { 0,0,22,30 };
    mai->textrock = sfTexture_createFromFile("asteroids-asteroids(B)_0.png", &tx_rock);
    mai->sprtrock = sfSprite_create();
    sfVector2f scale = { 3.5f, 3.5f };
    mai->rock.x = 100;
    mai->rock.y = 100;
    sfSprite_setOrigin(mai->sprtrock, (sfVector2f) { 30, 30 });
    sfSprite_setScale(mai->sprtrock, scale);
    sfSprite_setTexture(mai->sprtrock, mai->textrock, true);
    sfSprite_setPosition(mai->sprtrock, (sfVector2f) { mai->rock.x, mai->rock.y });
    sfRenderWindow_drawSprite(window, mai->sprtrock, NULL);
}

void asteroid(struct valorasteroid *mai){
    
    mai->rock = (sfVector2f){ 0,0 };
    mai->dirock = (sfVector2f){ 0,0 };
    mai->strock = (sfVector2f){ 0,0 };
    mai->RockS = 1;
    mai->RockAng = -90;

    mai->RockAng = ((float)rand() / 360);
    mai->RockS = ((float)rand() / 5);

    mai->dirock.x = cosf(mai->RockAng * 3.1415 / 180);
    mai->dirock.y = sinf(mai->RockAng * 3.1415 / 180);
    mai->strock.x += mai->RockS * mai->rock.x * delta / 100.0;
    mai->strock.y += mai->RockS * mai->rock.y * delta / 100.0;
    mai->rock.x += mai->strock.x;
    mai->rock.y += mai->strock.y;
}

void summonlaser(struct valorlaser *mai) {
    //create and draws the asteroid
    sfFloatRect tx_laser = { 0,0,22,30 };
    mai->textrlaser = sfTexture_createFromFile("", &tx_laser);
    mai->sprtlaser = sfSprite_create();
    sfVector2f scale = { 3.5f, 3.5f };
    mai->laser.x = 100;
    mai->laser.y = 100;
    sfSprite_setOrigin(mai->sprtlaser, (sfVector2f) { 30, 30 });
    sfSprite_setScale(mai->sprtlaser, scale);
    sfSprite_setTexture(mai->sprtlaser, mai->textrlaser, true);
    sfSprite_setPosition(mai->sprtlaser, (sfVector2f) { mai->laser.x, mai->laser.y });
    sfRenderWindow_drawSprite(window, mai->sprtlaser, NULL);
}

void laser(struct valorlaser* mai) {
    mai->laser = (sfVector2f){ 0,0 };
    mai->dirlaser = (sfVector2f){ 0,0 };
    mai->strlaser = (sfVector2f){ 0,0 };
    mai->laserS = 1;
    mai->laserAng = -90;

    mai->laserAng = ((float)rand() / 360);
    mai->laserS = ((float)rand() / 5);

    mai->dirlaser.x = cosf(mai->laserAng * 3.1415 / 180);
    mai->dirlaser.y = sinf(mai->laserAng * 3.1415 / 180);
    mai->strlaser.x += mai->laserS * mai->laser.x * delta / 100.0;
    mai->strlaser.y += mai->laserS * mai->laser.y * delta / 100.0;
    mai->laser.x += mai->strlaser.x;
    mai->laser.y += mai->strlaser.y;
}

void colaser() {

}




int main() {
    struct valorasteroid mai;
    srand(time(0));
    create();
    summonrock(&mai);

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

        if (shipX > mai.rock.x + 30 && shipX < mai.rock.x - 30);
            shipX = 1920 / 2;
            shipY = 1080 / 2;
        if (shipY > mai.rock.y + 30 && shipX < mai.rock.x - 30);
            shipX = 1920 / 2;
            shipY = 1080 / 2;

        asteroid(&mai);
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
    sfSprite_destroy(mai.sprtrock);
    sfSprite_destroy(mai.textrock);
    sfClock_destroy(deltaclock);
    return 0;
}