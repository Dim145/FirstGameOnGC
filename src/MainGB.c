//
// Created by dimit on 13/10/2020.
//
#include <gb/gb.h>
#include "breakout-tileset.h"
#include "breakout-tilemap-level01Map.h"

#define PADDLE_Y 152
#define LARGUEUR_PADDLE (3 * 8)
#define TILE_EMPTY 128
#define BALL_WIDTH 6
#define TILE_BRICK_L   136
#define TILE_BRICK_R   137
#define DEPART_VRAM 128

extern void set_bkg_data(UINT8 first_tile, UINT8 nb_tiles, UINT8 *data);
extern void set_bkg_tiles(UINT8 x, UINT8 y, UINT8 w, UINT8 h, UINT8 *tiles);
extern void get_bkg_tiles(UINT8 x, UINT8 y, UINT8 w, UINT8 h, unsigned char *tiles);

extern UINT8 joypad(void);
extern void waitpadup(void);
extern UINT8 waitpad(UINT8 mask);
extern void waitpadup(void);

extern void scroll_bkg(INT8 x, INT8 y);
extern void move_bkg(UINT8 x, UINT8 y);
extern void wait_vbl_done(void);

extern void set_sprite_prop(UINT8 nb, UINT8 prop);
extern void set_sprite_tile(UINT8 nb, UINT8 tile);
extern void set_sprite_data(UINT8 first_tile, UINT8 nb_tiles, unsigned char *data);
extern void move_sprite(UINT8 nb, UINT8 x, UINT8 y);
extern UINT8 get_sprite_prop(UINT8 nb);

UINT8 paddle_pos_x = 76;

UINT8 ball_pos_x = 50;
UINT8 ball_pos_y = 110;
UINT8 ball_delta_x = 1;
UINT8 ball_delta_y = -1;
UINT8 nbBriques = 0;

void movePaddle( BYTE delta )
{
    paddle_pos_x = delta == 0 ? 76 : paddle_pos_x + delta;

    paddle_pos_x = paddle_pos_x < 8 ? 8 : paddle_pos_x > 168 - LARGUEUR_PADDLE ? 168 - LARGUEUR_PADDLE : paddle_pos_x;

    set_sprite_tile(1, DEPART_VRAM + 10);
    move_sprite(1, paddle_pos_x, PADDLE_Y);

    set_sprite_tile(2, DEPART_VRAM + 11);
    move_sprite(2, paddle_pos_x + 8, PADDLE_Y);

    set_sprite_tile(3, DEPART_VRAM + 12);
    move_sprite(3, paddle_pos_x + 16, PADDLE_Y);
}

void remove_brick(UINT8 x, UINT8 y)
{
    UINT8 cells[2] = {TILE_EMPTY, TILE_EMPTY};
    set_bkg_tiles(x, y, 2, 1, cells);

    nbBriques--;
}

UINT8 checkCollision( INT8 deltaX, INT8 deltaY )
{
    UINT8 tmpX = ball_pos_x + deltaX;
    UINT8 tmpY = ball_pos_y + deltaY;

    if( tmpY + BALL_WIDTH >= PADDLE_Y && tmpX + BALL_WIDTH >= paddle_pos_x && tmpX <= paddle_pos_x + LARGUEUR_PADDLE) return 1;

    if (deltaX > 0) tmpX += BALL_WIDTH-1;
    if (deltaY > 0) tmpY += BALL_WIDTH-1;

    UINT8 cellX = (tmpX - 8 ) / 8;
    UINT8 cellY = (tmpY - 16) / 8;

    UINT8 cellInBack[1];
    get_bkg_tiles(cellX, cellY, 1, 1, cellInBack);

    switch (cellInBack[0])
    {
        case TILE_BRICK_L: remove_brick(cellX, cellY);break;
        case TILE_BRICK_R: remove_brick(cellX-1, cellY);break;
    }

    return cellInBack[0] != TILE_EMPTY;
}

UINT8 checkGameOver()
{
    return ball_pos_y + BALL_WIDTH >= 18 * 8 + 16;
}

void game_draw_game_over()
{
    HIDE_SPRITES;

}

void game_draw_victory()
{
    HIDE_BKG;
    HIDE_SPRITES;
}

void main()
{
    for (int i = 0; i < TILEMAP_WIDTH; ++i)
        for (int j = 0; j < TILEMAP_HEIGHT; ++j)
        {
            TILEMAP[j + TILEMAP_HEIGHT * i] += DEPART_VRAM;

            if( TILEMAP[j + TILEMAP_HEIGHT * i] == TILE_BRICK_L) nbBriques++;
        }

    set_bkg_data(DEPART_VRAM, LEVEL_01_TILE_COUNT, LEVEL_01);
    set_bkg_tiles(0, 0, TILEMAP_WIDTH, TILEMAP_HEIGHT, TILEMAP);

    SHOW_BKG;

    set_sprite_tile(0, DEPART_VRAM + 13);
    move_sprite(0, ball_pos_x, ball_pos_y);

    movePaddle(0);

    SHOW_SPRITES;

    UINT8 bVictory = 1;
    UINT8 key;
    while (nbBriques)
    {
        key = joypad();

        if( key & J_LEFT )       movePaddle(-2);
        else if( key & J_RIGHT ) movePaddle(2);


        if( checkCollision(ball_delta_x, 0) ) ball_delta_x *= -1;
        if (checkCollision(0, ball_delta_y) ) ball_delta_y *= -1;

        // deplacement d la balle
        ball_pos_x += ball_delta_x;
        ball_pos_y += ball_delta_y;

        move_sprite(0, ball_pos_x, ball_pos_y );

        if (checkGameOver())
        {
            bVictory = 0;
            break;
        }

        wait_vbl_done();
    }

    if (!bVictory) game_draw_game_over();
    else           game_draw_victory();
}