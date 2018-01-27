#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "SDL2_gfxPrimitives.h"
#include <time.h>
#define WIDTH 500
#define HEIGHT 500
#define snakex 50
#define snakey 40
int rando(){

    return rand()%400+50;
}
int applex,appley;
int act=0;
int action=1;
int quit = 0;
int slength=0;
int turnx[10000]={0},turny[10000]={0},turndir[10000]={0},turn=0,turnstatus[1000][1000]={0};
int circlex[10000]={0},circley[10000]={0},circledir[10000]={0};
int menu=0;

int i=0,j=0;
int endgame(){
    for (int k = 2; k <slength ; ++k) {


        if(circlex[k]>snakex + i-30&&circlex[k]<snakex+i+30&&circley[k]>snakey + j-30&&circley[k]<snakey+j+30){
            return 1;
        }
    }
    return 0;
}

int check(int x){
    if(x>500){
        x=x-500;
    }

    if(x<0){
        x=x+500;
    }

    return x;
}

void move(SDL_Renderer *renderer,int action,int *x,int *y){
    *x=check(*x);
    *y=check(*y);
    if (action==1) {


        *x=*x+1;

    }
    if (action==2) {
        *y=*y+1;

    }
    if (action==3) {
        *x=*x-1;

    }
    if (action==4){

        *y=*y-1;

    }
    filledCircleRGBA(renderer, *x, *y, 15, 0,0XFF,0,0xFF);
    aacircleRGBA(renderer, *x, *y, 15, 0XFF,0XFF,0XFF,0xFF);
    aacircleRGBA(renderer, *x, *y, 16, 0XFF,0XFF,0XFF,0xFF);
    return;
}
int main() {


    applex=rando();
    appley=rando();
    srand((int)time(0));
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        printf ("SDL_Init Error: %s", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Snake", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    if (window == NULL)
    {
        printf ("SDL_CreateWindow Error: %s", SDL_GetError());
        SDL_Quit();
        return 2;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        SDL_DestroyWindow(window);
        printf ("SDL_CreateRenderer Error: %s", SDL_GetError());
        SDL_Quit();
        return 3;
    }
    SDL_Event e;






    while(!quit){

        if(menu==0){
            if (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT)
                    quit = 1;
                else if( e.type == SDL_KEYDOWN ) {
                    switch( e.key.keysym.sym ) {
                        case SDLK_1:
                            menu=1;
                            break;
                        case SDLK_2:
                            menu=2;
                            break;

                    }
                }
            }
            SDL_SetRenderDrawColor(renderer, 0, 0, 0xFF, 0xFF);
            SDL_RenderClear(renderer);

            stringRGBA(renderer,180,70,"welcome to snake!!!",0xFF,0xFF,0xFF,0xFF);
            stringRGBA(renderer,90,150,"choose your map",0xFF,0xFF,0xFF,0xFF);
            stringRGBA(renderer,90,250,"1-map1",0xFF,0xFF,0xFF,0xFF);
            stringRGBA(renderer,90,350,"2-map2",0xFF,0xFF,0xFF,0xFF);



            SDL_RenderPresent(renderer);
            SDL_Delay(10);
        }
        if(menu==1) {
            if (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT)
                    quit = 1;
                else if (e.type == SDL_KEYDOWN) {
                    switch (e.key.keysym.sym) {
                        case SDLK_UP:
                            if (action == 2 ||
                                (fabs(snakex + i - turnx[turn - 1]) < 30 && fabs(snakey + j - turny[turn - 1]) < 30)) {
                                if (action == 2) {
                                    break;
                                }
                                act = 4;
                                break;
                            }
                            turnx[turn] = snakex + i;
                            turny[turn] = snakey + j;
                            turndir[turn] = 4;
                            for (int k = 0; k < slength; ++k) {
                                turnstatus[k][turn] = 1;
                            }
                            turn++;

                            action = 4;
                            break;
                        case SDLK_DOWN:
                            if (action == 4 ||
                                (fabs(snakex + i - turnx[turn - 1]) < 30 && fabs(snakey + j - turny[turn - 1]) < 30)) {
                                if (action == 4) {
                                    break;
                                }
                                act = 2;
                                break;
                            }
                            turnx[turn] = snakex + i;
                            turny[turn] = snakey + j;
                            turndir[turn] = 2;
                            for (int k = 0; k < slength; ++k) {
                                turnstatus[k][turn] = 1;
                            }
                            turn++;


                            action = 2;
                            break;
                        case SDLK_LEFT:
                            if (action == 1 ||
                                (fabs(snakex + i - turnx[turn - 1]) < 30 && fabs(snakey + j - turny[turn - 1]) < 30)) {
                                if (action == 1) {
                                    break;
                                }
                                act = 3;
                                break;
                            }
                            turnx[turn] = snakex + i;
                            turny[turn] = snakey + j;
                            turndir[turn] = 3;
                            for (int k = 0; k < slength; ++k) {
                                turnstatus[k][turn] = 1;
                            }
                            turn++;

                            action = 3;
                            break;
                        case SDLK_RIGHT:
                            if (action == 3 ||
                                (fabs(snakex + i - turnx[turn - 1]) < 30 && fabs(snakey + j - turny[turn - 1]) < 30)) {
                                act = 1;
                                break;
                            }
                            turnx[turn] = snakex + i;
                            turny[turn] = snakey + j;
                            turndir[turn] = 1;
                            for (int k = 0; k < slength; ++k) {
                                turnstatus[k][turn] = 1;
                            }
                            turn++;

                            action = 1;
                            break;
                    }
                }
            }
            switch (act) {
                case 4:
                    if (action == 2 ||
                        (fabs(snakex + i - turnx[turn - 1]) < 30 && fabs(snakey + j - turny[turn - 1]) < 30)) {
                        if (action == 2) {
                            break;
                        }
                        act = 4;
                        break;
                    }
                    turnx[turn] = snakex + i;
                    turny[turn] = snakey + j;
                    turndir[turn] = 4;
                    for (int k = 0; k < slength; ++k) {
                        turnstatus[k][turn] = 1;
                    }
                    turn++;
                    act = 0;

                    action = 4;
                    break;
                case 2:
                    if (action == 4 ||
                        (fabs(snakex + i - turnx[turn - 1]) < 30 && fabs(snakey + j - turny[turn - 1]) < 30)) {
                        if (action == 4) {
                            break;
                        }
                        act = 2;
                        break;
                    }
                    turnx[turn] = snakex + i;
                    turny[turn] = snakey + j;
                    turndir[turn] = 2;
                    for (int k = 0; k < slength; ++k) {
                        turnstatus[k][turn] = 1;
                    }
                    turn++;
                    act = 0;


                    action = 2;
                    break;
                case 3:
                    if (action == 1 ||
                        (fabs(snakex + i - turnx[turn - 1]) < 30 && fabs(snakey + j - turny[turn - 1]) < 30)) {
                        if (action == 1) {
                            break;
                        }
                        act = 3;
                        break;
                    }
                    turnx[turn] = snakex + i;
                    turny[turn] = snakey + j;
                    turndir[turn] = 3;
                    for (int k = 0; k < slength; ++k) {
                        turnstatus[k][turn] = 1;
                    }
                    turn++;
                    act = 0;

                    action = 3;
                    break;
                case 1:
                    if (action == 3 ||
                        (fabs(snakex + i - turnx[turn - 1]) < 30 && fabs(snakey + j - turny[turn - 1]) < 30)) {
                        if (action == 3) {
                            break;
                        }
                        act = 1;
                        break;
                    }
                    turnx[turn] = snakex + i;
                    turny[turn] = snakey + j;
                    turndir[turn] = 1;
                    for (int k = 0; k < slength; ++k) {
                        turnstatus[k][turn] = 1;
                    }
                    turn++;
                    act = 0;
                    action = 1;
                    break;
                case 0:
                    break;
            }

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0x00);
            SDL_RenderClear(renderer);

            if (endgame()) {
                stringColor(renderer, 220, 250, " LOSER!!!", 0xFFAABBCC);

            } else {
                filledCircleRGBA(renderer, applex, appley, 8, 0XFF, 0, 0, 0xFF);

                if (action == 1) {
                    i++;
                    i = check(snakex + i) - snakex;

                    j = check(snakey + j) - snakey;
                    filledCircleRGBA(renderer, snakex + i, snakey + j, 15, 0, 0XFF, 0, 0xFF);
                    aacircleRGBA(renderer, snakex + i, snakey + j, 15, 0XFF, 0XFF, 0XFF, 0xFF);
                    aacircleRGBA(renderer, snakex + i, snakey + j, 16, 0XFF, 0XFF, 0XFF, 0xFF);
                    filledCircleRGBA(renderer, snakex + 5 + i, snakey + 5 + j, 3, 0xFF, 0, 0, 0xFF);
                    filledCircleRGBA(renderer, snakex + 5 + i, snakey - 5 + j, 3, 0xFF, 0, 0, 0xFF);


                }
                if (action == 2) {
                    j++;
                    i = check(snakex + i) - snakex;
                    j = check(snakey + j) - snakey;
                    filledCircleRGBA(renderer, snakex + i, snakey + j, 15, 0, 0XFF, 0, 0xFF);
                    aacircleRGBA(renderer, snakex + i, snakey + j, 15, 0XFF, 0XFF, 0XFF, 0xFF);
                    aacircleRGBA(renderer, snakex + i, snakey + j, 16, 0XFF, 0XFF, 0XFF, 0xFF);
                    filledCircleRGBA(renderer, snakex + 5 + i, snakey + 5 + j, 3, 0xFF, 0, 0, 0xFF);
                    filledCircleRGBA(renderer, snakex - 5 + i, snakey + 5 + j, 3, 0xFF, 0, 0, 0xFF);


                }
                if (action == 3) {
                    i--;
                    i = check(snakex + i) - snakex;
                    j = check(snakey + j) - snakey;
                    filledCircleRGBA(renderer, snakex + i, snakey + j, 15, 0, 0XFF, 0, 0xFF);
                    aacircleRGBA(renderer, snakex + i, snakey + j, 15, 0XFF, 0XFF, 0XFF, 0xFF);
                    aacircleRGBA(renderer, snakex + i, snakey + j, 16, 0XFF, 0XFF, 0XFF, 0xFF);
                    filledCircleRGBA(renderer, snakex - 5 + i, snakey + 5 + j, 3, 0xFF, 0, 0, 0xFF);
                    filledCircleRGBA(renderer, snakex - 5 + i, snakey - 5 + j, 3, 0xFF, 0, 0, 0xFF);


                }
                if (action == 4) {
                    j--;
                    i = check(snakex + i) - snakex;
                    j = check(snakey + j) - snakey;
                    filledCircleRGBA(renderer, snakex + i, snakey + j, 15, 0, 0XFF, 0, 0xFF);
                    aacircleRGBA(renderer, snakex + i, snakey + j, 15, 0XFF, 0XFF, 0XFF, 0xFF);
                    aacircleRGBA(renderer, snakex + i, snakey + j, 16, 0XFF, 0XFF, 0XFF, 0xFF);
                    filledCircleRGBA(renderer, snakex + 5 + i, snakey - 5 + j, 3, 0xFF, 0, 0, 0xFF);
                    filledCircleRGBA(renderer, snakex - 5 + i, snakey - 5 + j, 3, 0xFF, 0, 0, 0xFF);


                }
                for (int l = 0; l < slength; ++l) {

                    int k;
                    for (k = 0; k < turn; ++k) {
                        if (turnstatus[l][k] == 1) {
                            break;
                        }
                    }
                    if (circlex[l] == turnx[k] && circley[l] == turny[k]) {
                        turnstatus[l][k] = 0;
                        circledir[l] = turndir[k];
                    }
                    move(renderer, circledir[l], &circlex[l], &circley[l]);

                }

                if (slength == 0) {
                    if (applex > snakex + i - 17 && applex < snakex + i + 17 && appley > snakey + j - 17 &&
                        appley < snakey + j + 17) {
                        if (action == 1) {
                            applex = rando();
                            appley = rando();

                            circlex[slength] = snakex + i - 25;
                            circley[slength] = snakey + j;
                            circledir[slength] = action;
                            slength++;


                        }
                        if (action == 2) {

                            applex = rando();
                            appley = rando();
                            circlex[slength] = snakex + i;
                            circley[slength] = snakey + j - 25;
                            circledir[slength] = action;
                            slength++;


                        }
                        if (action == 3) {
                            applex = rando();
                            appley = rando();
                            circlex[slength] = snakex + i + 25;
                            circley[slength] = snakey + j;
                            circledir[slength] = action;
                            slength++;


                        }
                        if (action == 4) {
                            applex = rando();
                            appley = rando();
                            circlex[slength] = snakex + i;
                            circley[slength] = snakey + j + 25;
                            circledir[slength] = action;
                            slength++;

                        }

                    }
                }
                if (circledir[slength - 1] == 1) {
                    if (applex > snakex + i - 17 && applex < snakex + i + 17 && appley > snakey + j - 17 &&
                        appley < snakey + j + 17) {
                        applex = rando();
                        appley = rando();
                        while (1) {
                            int k;
                            if (!(applex > snakex + i - 20 && applex < snakex + i + 20 && appley > snakey + j - 20 &&
                                  appley < snakey + j + 20)) {
                                break;
                            }
                            for (k = 0; k < slength; ++k) {
                                if (applex > circlex - 20 && applex < circlex + 20 && appley > circley - 20 &&
                                    appley < circley + 20) {
                                    break;
                                }

                            }
                            if (k == slength) {
                                break;
                            }
                            applex = rando();
                            appley = rando();
                        }
                        circlex[slength] = circlex[slength - 1] - 25;
                        circley[slength] = circley[slength - 1];
                        circledir[slength] = circledir[slength - 1];
                        for (int k = 0; k < turn; ++k) {
                            turnstatus[slength][k] = turnstatus[slength - 1][k];
                        }
                        slength++;
                    }
                }
                if (circledir[slength - 1] == 2) {
                    if (applex > snakex + i - 17 && applex < snakex + i + 17 && appley > snakey + j - 17 &&
                        appley < snakey + j + 17) {
                        applex = rando();
                        appley = rando();
                        while (1) {
                            int k;
                            if (!(applex > snakex + i - 20 && applex < snakex + i + 20 && appley > snakey + j - 20 &&
                                  appley < snakey + j + 20)) {
                                break;
                            }
                            for (k = 0; k < slength; ++k) {
                                if (applex > circlex - 20 && applex < circlex + 20 && appley > circley - 20 &&
                                    appley < circley + 20) {
                                    break;
                                }

                            }
                            if (k == slength) {
                                break;
                            }
                            applex = rando();
                            appley = rando();
                        }
                        circlex[slength] = circlex[slength - 1];
                        circley[slength] = circley[slength - 1] - 25;
                        circledir[slength] = circledir[slength - 1];
                        for (int k = 0; k < turn; ++k) {
                            turnstatus[slength][k] = turnstatus[slength - 1][k];
                        }
                        slength++;
                    }
                }
                if (circledir[slength - 1] == 3) {
                    if (applex > snakex + i - 17 && applex < snakex + i + 17 && appley > snakey + j - 17 &&
                        appley < snakey + j + 17) {
                        applex = rando();
                        appley = rando();
                        while (1) {
                            int k;
                            if (!(applex > snakex + i - 20 && applex < snakex + i + 20 && appley > snakey + j - 20 &&
                                  appley < snakey + j + 20)) {
                                break;
                            }
                            for (k = 0; k < slength; ++k) {
                                if (applex > circlex - 20 && applex < circlex + 20 && appley > circley - 20 &&
                                    appley < circley + 20) {
                                    break;
                                }

                            }
                            if (k == slength) {
                                break;
                            }
                            applex = rando();
                            appley = rando();
                        }
                        circlex[slength] = circlex[slength - 1] + 25;
                        circley[slength] = circley[slength - 1];
                        circledir[slength] = circledir[slength - 1];
                        for (int k = 0; k < turn; ++k) {
                            turnstatus[slength][k] = turnstatus[slength - 1][k];
                        }
                        slength++;
                    }
                }
                if (circledir[slength - 1] == 4) {
                    if (applex > snakex + i - 17 && applex < snakex + i + 17 && appley > snakey + j - 17 &&
                        appley < snakey + j + 17) {
                        applex = rando();
                        appley = rando();
                        while (1) {
                            int k;
                            if (!(applex > snakex + i - 20 && applex < snakex + i + 20 && appley > snakey + j - 20 &&
                                  appley < snakey + j + 20)) {
                                break;
                            }
                            for (k = 0; k < slength; ++k) {
                                if (applex > circlex - 20 && applex < circlex + 20 && appley > circley - 20 &&
                                    appley < circley + 20) {
                                    break;
                                }

                            }
                            if (k == slength) {
                                break;
                            }
                            applex = rando();
                            appley = rando();
                        }
                        circlex[slength] = circlex[slength - 1];
                        circley[slength] = circley[slength - 1] + 25;
                        circledir[slength] = circledir[slength - 1];
                        for (int k = 0; k < turn; ++k) {
                            turnstatus[slength][k] = turnstatus[slength - 1][k];
                        }
                        slength++;
                    }
                }
            }
            SDL_RenderPresent(renderer);
            SDL_Delay(10);
        }
        if(menu==2) {
            if (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT)
                    quit = 1;
                else if (e.type == SDL_KEYDOWN) {
                    switch (e.key.keysym.sym) {
                        case SDLK_UP:
                            if (action == 2 ||
                                (fabs(snakex + i - turnx[turn - 1]) < 30 && fabs(snakey + j - turny[turn - 1]) < 30)) {
                                if (action == 2) {
                                    break;
                                }
                                act = 4;
                                break;
                            }
                            turnx[turn] = snakex + i;
                            turny[turn] = snakey + j;
                            turndir[turn] = 4;
                            for (int k = 0; k < slength; ++k) {
                                turnstatus[k][turn] = 1;
                            }
                            turn++;

                            action = 4;
                            break;
                        case SDLK_DOWN:
                            if (action == 4 ||
                                (fabs(snakex + i - turnx[turn - 1]) < 30 && fabs(snakey + j - turny[turn - 1]) < 30)) {
                                if (action == 4) {
                                    break;
                                }
                                act = 2;
                                break;
                            }
                            turnx[turn] = snakex + i;
                            turny[turn] = snakey + j;
                            turndir[turn] = 2;
                            for (int k = 0; k < slength; ++k) {
                                turnstatus[k][turn] = 1;
                            }
                            turn++;


                            action = 2;
                            break;
                        case SDLK_LEFT:
                            if (action == 1 ||
                                (fabs(snakex + i - turnx[turn - 1]) < 30 && fabs(snakey + j - turny[turn - 1]) < 30)) {
                                if (action == 1) {
                                    break;
                                }
                                act = 3;
                                break;
                            }
                            turnx[turn] = snakex + i;
                            turny[turn] = snakey + j;
                            turndir[turn] = 3;
                            for (int k = 0; k < slength; ++k) {
                                turnstatus[k][turn] = 1;
                            }
                            turn++;

                            action = 3;
                            break;
                        case SDLK_RIGHT:
                            if (action == 3 ||
                                (fabs(snakex + i - turnx[turn - 1]) < 30 && fabs(snakey + j - turny[turn - 1]) < 30)) {
                                act = 1;
                                break;
                            }
                            turnx[turn] = snakex + i;
                            turny[turn] = snakey + j;
                            turndir[turn] = 1;
                            for (int k = 0; k < slength; ++k) {
                                turnstatus[k][turn] = 1;
                            }
                            turn++;

                            action = 1;
                            break;
                    }
                }
            }

            switch (act) {
                case 4:
                    if (action == 2 ||
                        (fabs(snakex + i - turnx[turn - 1]) < 30 && fabs(snakey + j - turny[turn - 1]) < 30)) {
                        if (action == 2) {
                            break;
                        }
                        act = 4;
                        break;
                    }
                    turnx[turn] = snakex + i;
                    turny[turn] = snakey + j;
                    turndir[turn] = 4;
                    for (int k = 0; k < slength; ++k) {
                        turnstatus[k][turn] = 1;
                    }
                    turn++;
                    act = 0;

                    action = 4;
                    break;
                case 2:
                    if (action == 4 ||
                        (fabs(snakex + i - turnx[turn - 1]) < 30 && fabs(snakey + j - turny[turn - 1]) < 30)) {
                        if (action == 4) {
                            break;
                        }
                        act = 2;
                        break;
                    }
                    turnx[turn] = snakex + i;
                    turny[turn] = snakey + j;
                    turndir[turn] = 2;
                    for (int k = 0; k < slength; ++k) {
                        turnstatus[k][turn] = 1;
                    }
                    turn++;
                    act = 0;


                    action = 2;
                    break;
                case 3:
                    if (action == 1 ||
                        (fabs(snakex + i - turnx[turn - 1]) < 30 && fabs(snakey + j - turny[turn - 1]) < 30)) {
                        if (action == 1) {
                            break;
                        }
                        act = 3;
                        break;
                    }
                    turnx[turn] = snakex + i;
                    turny[turn] = snakey + j;
                    turndir[turn] = 3;
                    for (int k = 0; k < slength; ++k) {
                        turnstatus[k][turn] = 1;
                    }
                    turn++;
                    act = 0;

                    action = 3;
                    break;
                case 1:
                    if (action == 3 ||
                        (fabs(snakex + i - turnx[turn - 1]) < 30 && fabs(snakey + j - turny[turn - 1]) < 30)) {
                        if (action == 3) {
                            break;
                        }
                        act = 1;
                        break;
                    }
                    turnx[turn] = snakex + i;
                    turny[turn] = snakey + j;
                    turndir[turn] = 1;
                    for (int k = 0; k < slength; ++k) {
                        turnstatus[k][turn] = 1;
                    }
                    turn++;
                    act = 0;
                    action = 1;
                    break;
                case 0:
                    break;
            }
            int endd=0;
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0x00);
            SDL_RenderClear(renderer);
            if (snakex+i==19||snakex+i==481||snakey+j==19||snakey+j==481||circlex[slength-1]==19||circlex[slength-1]==481||circley[slength-1]==19||circley[slength-1]==481){
                endd=1;
            }
            thickLineRGBA(renderer,4,0,4,500,9, 0XFF, 0XFF, 0XFF, 0xFF);
            thickLineRGBA(renderer,496,0,496,500,9, 0XFF, 0XFF, 0XFF, 0xFF);
            thickLineRGBA(renderer,0,4,500,4,9, 0XFF, 0XFF, 0XFF, 0xFF);
            thickLineRGBA(renderer,0,496,500,496,9, 0XFF, 0XFF, 0XFF, 0xFF);
            if (endgame()||endd) {
                stringColor(renderer, 220, 250, " LOSER!!!", 0xFFAABBCC);

            } else {
                filledCircleRGBA(renderer, applex, appley, 8, 0XFF, 0, 0, 0xFF);

                if (action == 1) {
                    i++;
                    i = check(snakex + i) - snakex;

                    j = check(snakey + j) - snakey;
                    filledCircleRGBA(renderer, snakex + i, snakey + j, 15, 0, 0XFF, 0, 0xFF);
                    aacircleRGBA(renderer, snakex + i, snakey + j, 15, 0XFF, 0XFF, 0XFF, 0xFF);
                    aacircleRGBA(renderer, snakex + i, snakey + j, 16, 0XFF, 0XFF, 0XFF, 0xFF);
                    filledCircleRGBA(renderer, snakex + 5 + i, snakey + 5 + j, 3, 0xFF, 0, 0, 0xFF);
                    filledCircleRGBA(renderer, snakex + 5 + i, snakey - 5 + j, 3, 0xFF, 0, 0, 0xFF);


                }
                if (action == 2) {
                    j++;
                    i = check(snakex + i) - snakex;
                    j = check(snakey + j) - snakey;
                    filledCircleRGBA(renderer, snakex + i, snakey + j, 15, 0, 0XFF, 0, 0xFF);
                    aacircleRGBA(renderer, snakex + i, snakey + j, 15, 0XFF, 0XFF, 0XFF, 0xFF);
                    aacircleRGBA(renderer, snakex + i, snakey + j, 16, 0XFF, 0XFF, 0XFF, 0xFF);
                    filledCircleRGBA(renderer, snakex + 5 + i, snakey + 5 + j, 3, 0xFF, 0, 0, 0xFF);
                    filledCircleRGBA(renderer, snakex - 5 + i, snakey + 5 + j, 3, 0xFF, 0, 0, 0xFF);


                }
                if (action == 3) {
                    i--;
                    i = check(snakex + i) - snakex;
                    j = check(snakey + j) - snakey;
                    filledCircleRGBA(renderer, snakex + i, snakey + j, 15, 0, 0XFF, 0, 0xFF);
                    aacircleRGBA(renderer, snakex + i, snakey + j, 15, 0XFF, 0XFF, 0XFF, 0xFF);
                    aacircleRGBA(renderer, snakex + i, snakey + j, 16, 0XFF, 0XFF, 0XFF, 0xFF);
                    filledCircleRGBA(renderer, snakex - 5 + i, snakey + 5 + j, 3, 0xFF, 0, 0, 0xFF);
                    filledCircleRGBA(renderer, snakex - 5 + i, snakey - 5 + j, 3, 0xFF, 0, 0, 0xFF);


                }
                if (action == 4) {
                    j--;
                    i = check(snakex + i) - snakex;
                    j = check(snakey + j) - snakey;
                    filledCircleRGBA(renderer, snakex + i, snakey + j, 15, 0, 0XFF, 0, 0xFF);
                    aacircleRGBA(renderer, snakex + i, snakey + j, 15, 0XFF, 0XFF, 0XFF, 0xFF);
                    aacircleRGBA(renderer, snakex + i, snakey + j, 16, 0XFF, 0XFF, 0XFF, 0xFF);
                    filledCircleRGBA(renderer, snakex + 5 + i, snakey - 5 + j, 3, 0xFF, 0, 0, 0xFF);
                    filledCircleRGBA(renderer, snakex - 5 + i, snakey - 5 + j, 3, 0xFF, 0, 0, 0xFF);


                }
                for (int l = 0; l < slength; ++l) {

                    int k;
                    for (k = 0; k < turn; ++k) {
                        if (turnstatus[l][k] == 1) {
                            break;
                        }
                    }
                    if (circlex[l] == turnx[k] && circley[l] == turny[k]) {
                        turnstatus[l][k] = 0;
                        circledir[l] = turndir[k];
                    }
                    move(renderer, circledir[l], &circlex[l], &circley[l]);

                }

                if (slength == 0) {
                    if (applex > snakex + i - 17 && applex < snakex + i + 17 && appley > snakey + j - 17 &&
                        appley < snakey + j + 17) {
                        if (action == 1) {
                            applex = rando();
                            appley = rando();

                            circlex[slength] = snakex + i - 25;
                            circley[slength] = snakey + j;
                            circledir[slength] = action;
                            slength++;


                        }
                        if (action == 2) {

                            applex = rando();
                            appley = rando();
                            circlex[slength] = snakex + i;
                            circley[slength] = snakey + j - 25;
                            circledir[slength] = action;
                            slength++;


                        }
                        if (action == 3) {
                            applex = rando();
                            appley = rando();
                            circlex[slength] = snakex + i + 25;
                            circley[slength] = snakey + j;
                            circledir[slength] = action;
                            slength++;


                        }
                        if (action == 4) {
                            applex = rando();
                            appley = rando();
                            circlex[slength] = snakex + i;
                            circley[slength] = snakey + j + 25;
                            circledir[slength] = action;
                            slength++;

                        }

                    }
                }
                if (circledir[slength - 1] == 1) {
                    if (applex > snakex + i - 17 && applex < snakex + i + 17 && appley > snakey + j - 17 &&
                        appley < snakey + j + 17) {
                        applex = rando();
                        appley = rando();
                        while (1) {
                            int k;
                            if (!(applex > snakex + i - 20 && applex < snakex + i + 20 && appley > snakey + j - 20 &&
                                  appley < snakey + j + 20)) {
                                break;
                            }
                            for (k = 0; k < slength; ++k) {
                                if (applex > circlex - 20 && applex < circlex + 20 && appley > circley - 20 &&
                                    appley < circley + 20) {
                                    break;
                                }

                            }
                            if (k == slength) {
                                break;
                            }
                            applex = rando();
                            appley = rando();
                        }
                        circlex[slength] = circlex[slength - 1] - 25;
                        circley[slength] = circley[slength - 1];
                        circledir[slength] = circledir[slength - 1];
                        for (int k = 0; k < turn; ++k) {
                            turnstatus[slength][k] = turnstatus[slength - 1][k];
                        }
                        slength++;
                    }
                }
                if (circledir[slength - 1] == 2) {
                    if (applex > snakex + i - 17 && applex < snakex + i + 17 && appley > snakey + j - 17 &&
                        appley < snakey + j + 17) {
                        applex = rando();
                        appley = rando();
                        while (1) {
                            int k;
                            if (!(applex > snakex + i - 20 && applex < snakex + i + 20 && appley > snakey + j - 20 &&
                                  appley < snakey + j + 20)) {
                                break;
                            }
                            for (k = 0; k < slength; ++k) {
                                if (applex > circlex - 20 && applex < circlex + 20 && appley > circley - 20 &&
                                    appley < circley + 20) {
                                    break;
                                }

                            }
                            if (k == slength) {
                                break;
                            }
                            applex = rando();
                            appley = rando();
                        }
                        circlex[slength] = circlex[slength - 1];
                        circley[slength] = circley[slength - 1] - 25;
                        circledir[slength] = circledir[slength - 1];
                        for (int k = 0; k < turn; ++k) {
                            turnstatus[slength][k] = turnstatus[slength - 1][k];
                        }
                        slength++;
                    }
                }
                if (circledir[slength - 1] == 3) {
                    if (applex > snakex + i - 17 && applex < snakex + i + 17 && appley > snakey + j - 17 &&
                        appley < snakey + j + 17) {
                        applex = rando();
                        appley = rando();
                        while (1) {
                            int k;
                            if (!(applex > snakex + i - 20 && applex < snakex + i + 20 && appley > snakey + j - 20 &&
                                  appley < snakey + j + 20)) {
                                break;
                            }
                            for (k = 0; k < slength; ++k) {
                                if (applex > circlex - 20 && applex < circlex + 20 && appley > circley - 20 &&
                                    appley < circley + 20) {
                                    break;
                                }

                            }
                            if (k == slength) {
                                break;
                            }
                            applex = rando();
                            appley = rando();
                        }
                        circlex[slength] = circlex[slength - 1] + 25;
                        circley[slength] = circley[slength - 1];
                        circledir[slength] = circledir[slength - 1];
                        for (int k = 0; k < turn; ++k) {
                            turnstatus[slength][k] = turnstatus[slength - 1][k];
                        }
                        slength++;
                    }
                }
                if (circledir[slength - 1] == 4) {
                    if (applex > snakex + i - 17 && applex < snakex + i + 17 && appley > snakey + j - 17 &&
                        appley < snakey + j + 17) {
                        applex = rando();
                        appley = rando();
                        while (1) {
                            int k;
                            if (!(applex > snakex + i - 20 && applex < snakex + i + 20 && appley > snakey + j - 20 &&
                                  appley < snakey + j + 20)) {
                                break;
                            }
                            for (k = 0; k < slength; ++k) {
                                if (applex > circlex - 20 && applex < circlex + 20 && appley > circley - 20 &&
                                    appley < circley + 20) {
                                    break;
                                }

                            }
                            if (k == slength) {
                                break;
                            }
                            applex = rando();
                            appley = rando();
                        }
                        circlex[slength] = circlex[slength - 1];
                        circley[slength] = circley[slength - 1] + 25;
                        circledir[slength] = circledir[slength - 1];
                        for (int k = 0; k < turn; ++k) {
                            turnstatus[slength][k] = turnstatus[slength - 1][k];
                        }
                        slength++;
                    }
                }
            }
            SDL_RenderPresent(renderer);
            SDL_Delay(10);
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}