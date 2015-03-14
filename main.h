#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <allegro.h>
#include <math.h>
#include <map>
#include <vector>
#include <fstream>

using namespace std;

int tile_x, tile_y, mapa_x = 20, mapa_y = 15;
char nome[15] = "Mapa 1.hmf", import[15] = "tiles.bmp", tileX[3] = "32", tileY[3] = "32", mapaX[3] = "20", mapaY[3] = "15";
bool grid = true;

int layer = 1;
//int layer1, layer2, layer3;
map<int, map<int, int> > layer1;
map<int, map<int, int> > layer2;
map<int, map<int, int> > layer3;
int draw_tileX, draw_tileY;
int draw_posX, draw_posY;

int deslocX_mapa = 0, deslocY_mapa = 0, deslocX_tiles = 0, deslocY_tiles = 0;
int mouseX, mouseY, mouseY2, mouseX2;

bool colisao = false;
map<int, map<int, int> > collision_layer;

map<int, BITMAP*> blited_tile;
BITMAP* import_tile;
int selected = 0;
bool tile_is_imported;
int mouseX_tile, mouseY_tile, mouseY2_tile, mouseX2_tile;
int get_tile = 0;

int editor_button_proc(int msg, DIALOG* d, int c) {
    int ret = d_button_proc(msg, d, c);

    if (ret == D_CLOSE && d->dp3)
        return ((int (*)(void))d->dp3)();

    return ret;
}

DIALOG dialog[] = {
    {d_clear_proc, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL},

    {d_box_proc, 2, 2, 257, 16, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL},
    {d_shadow_box_proc, 135, 4, 120, 12, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL},
    {d_box_proc, 262, 2, 202, 16, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL},
    {d_shadow_box_proc, 340, 4, 120, 12, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL},
    {d_box_proc, 467, 2, 207, 16, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL},
    {d_shadow_box_proc, 470, 4, 85, 12, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL},
    {d_shadow_box_proc, 560, 4, 85, 12, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL},
    {d_box_proc, 677, 2, 207, 16, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL},
    {d_shadow_box_proc, 680, 4, 85, 12, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL},
    {d_shadow_box_proc, 770, 4, 85, 12, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL},
    {d_box_proc, 887, 2, 56, 16, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL},
    {d_box_proc, 947, 2, 75, 16, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL},

    {d_text_proc, 137, 6, 0, 0, 0, 0, 0, 0, 0, 0, (void*)"Nome:", NULL, NULL},
    {d_text_proc, 472, 6, 0, 0, 0, 0, 0, 0, 0, 0, (void*)"Mapa X:", NULL, NULL},
    {d_text_proc, 562, 6, 0, 0, 0, 0, 0, 0, 0, 0, (void*)"Mapa Y:", NULL, NULL},
    {d_text_proc, 682, 6, 0, 0, 0, 0, 0, 0, 0, 0, (void*)"Tile X:", NULL, NULL},
    {d_text_proc, 772, 6, 0, 0, 0, 0, 0, 0, 0, 0, (void*)"Tile Y:", NULL, NULL},

    {d_edit_proc, 180, 6, 73, 8, 0, 0, 0, 0, 15, 0, (void*)nome, NULL, NULL},
    {d_edit_proc, 342, 6, 116, 8, 0, 0, 0, 0, 15, 0, (void*)import, NULL, NULL},
    {d_edit_proc, 529, 6, 24, 8, 0, 0, 0, 0, 2, 0, (void*)mapaX, NULL, NULL},
    {d_edit_proc, 619, 6, 24, 8, 0, 0, 0, 0, 2, 0, (void*)mapaY, NULL, NULL},
    {d_edit_proc, 739, 6, 24, 8, 0, 0, 0, 0, 2, 0, (void*)tileX, NULL, NULL},
    {d_edit_proc, 829, 6, 24, 8, 0, 0, 0, 0, 2, 0, (void*)tileY, NULL, NULL},

    {editor_button_proc, 5, 4, 60, 12, 0, 0, 0, D_EXIT, 0, 0, (void*)"Abrir", NULL, (void*)bt_Abrir},
    {editor_button_proc, 70, 4, 60, 12, 0, 0, 0, D_EXIT, 0, 0, (void*)"Salvar", NULL, (void*)bt_Salvar},
    {editor_button_proc, 265, 4, 70, 12, 0, 0, 0, D_EXIT, 0, 0, (void*)"Importar", NULL, (void*)bt_Importar},
    {editor_button_proc, 650, 4, 20, 12, 0, 0, 0, D_EXIT, 0, 0, (void*)"OK", NULL, (void*)bt_OK_Mapa},
    {editor_button_proc, 860, 4, 20, 12, 0, 0, 0, D_EXIT, 0, 0, (void*)"OK", NULL, (void*)bt_OK_Tile},
    {editor_button_proc, 890, 4, 15, 12, 0, 0, 0, D_EXIT, 0, 0, (void*)"1", NULL, (void*)bt_Layer1},
    {editor_button_proc, 907, 4, 15, 12, 0, 0, 0, D_EXIT, 0, 0, (void*)"2", NULL, (void*)bt_Layer2},
    {editor_button_proc, 924, 4, 15, 12, 0, 0, 0, D_EXIT, 0, 0, (void*)"3", NULL, (void*)bt_Layer3},
    {editor_button_proc, 950, 4, 40, 12, 0, 0, 0, D_EXIT, 0, 0, (void*)"Grid", NULL, (void*)bt_Grid},
    {editor_button_proc, 995, 4, 23, 12, 0, 0, 0, D_EXIT, 0, 0, (void*)"C", NULL, (void*)bt_Colisao},

    {NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL}
};

DIALOG_PLAYER* gui;

BITMAP* menu;
BITMAP* mapa;
BITMAP* tiles;

#endif // MAIN_H_INCLUDED
