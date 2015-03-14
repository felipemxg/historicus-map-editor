#include "buttons.h"
#include "main.h"

inline void init() {
    allegro_init();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 1024, 768, 0, 0);

    install_keyboard();
    install_mouse();

    enable_hardware_cursor();

    select_mouse_cursor(MOUSE_CURSOR_ALLEGRO);
    set_window_title("Historicus MapEditor");

    show_mouse(screen);
}

inline void Reguas() {
    for (int x = 0; x < mapa_x; x++) {
        for (int y = 0; y < mapa_y; y++) {
            textprintf_centre_ex(mapa, font, (x * tile_x + 32) + deslocX_mapa, 8, makecol(0, 0, 0), -1, "%d", x + 1);
            textprintf_centre_ex(mapa, font, 11, (y * tile_y + 30) + deslocY_mapa, makecol(0, 0, 0), -1, "%d", y + 1);
        }
    }
}

inline void Scroll() {
    if (mouse_x >= 250 && mouse_y >= 20) {
        if (key[KEY_UP])
            deslocY_mapa += 5;
        if (key[KEY_DOWN])
            deslocY_mapa -= 5;
        if (key[KEY_LEFT])
            deslocX_mapa += 5;
        if (key[KEY_RIGHT])
            deslocX_mapa -= 5;

        if (key[KEY_UP] && key[KEY_LSHIFT])
            deslocY_mapa += 20;
        if (key[KEY_DOWN] && key[KEY_LSHIFT])
            deslocY_mapa -= 20;
        if (key[KEY_LEFT] && key[KEY_LSHIFT])
            deslocX_mapa += 20;
        if (key[KEY_RIGHT] && key[KEY_LSHIFT])
            deslocX_mapa -= 20;
    }
    else if (mouse_x < 250 && mouse_y >= 20 && tile_is_imported) {
        if (key[KEY_UP] && deslocY_tiles < 0)
            deslocY_tiles += 5;
        if (key[KEY_DOWN] && import_tile->h - 2024 > abs(deslocY_tiles))
            deslocY_tiles -= 5;
        if (key[KEY_LEFT] && deslocX_tiles < 0)
            deslocX_tiles += 5;
        if (key[KEY_RIGHT] && import_tile->w - 250 > abs(deslocX_tiles))
            deslocX_tiles -= 5;
    }
}

inline void Mouse() {
    int move = true;

    for (int x = 0; x < mapa_x; x++) {
        for (int y = 0; y < mapa_y; y++) {
            if (mouse_x >= ((x * tile_x + 272) + deslocX_mapa) && mouse_x <= (((x + 1) * tile_x + 272) + deslocX_mapa)) {
                mouseX = (x * tile_x) + 22;
                mouseX2 = ((x + 1) * tile_x) + 22;
            }
            if (mouse_y >= ((y * tile_y + 42) + deslocY_mapa) && mouse_y <= (((y + 1) * tile_y + 42) + deslocY_mapa)) {
                mouseY = (y * tile_y) + 22;
                mouseY2 = ((y + 1) * tile_y) + 22;
            }

            if ((mouse_x >= 272) && (mouse_y >= 42)) {
                if ((mouse_x <= ((x + 1) * tile_x) + 272 + deslocX_mapa) && (mouse_x >= (272 + deslocX_mapa)))
                    if ((mouse_y <= (((y + 1) * tile_y) + 42) + deslocY_mapa) && (mouse_y >= 42 + deslocY_mapa))
                        move = true;
                    else
                        move = false;
                else
                    move = false;
            } else
                move = false;
        }
    }

    if (move)
        rect(mapa, mouseX + deslocX_mapa, mouseY + deslocY_mapa, mouseX2 + deslocX_mapa, mouseY2 + deslocY_mapa, makecol(255, 0, 0));
}

inline void Grid() {
    if (grid) {
        for (int x = 0; x < mapa_x; x++) {
            for (int y = 0; y < mapa_y; y++) {
                rect(mapa, ((x * tile_x) + 22) + deslocX_mapa, ((y * tile_y) + 22) + deslocY_mapa, (((x + 1) * tile_x) + 22) + deslocX_mapa, (((y + 1) * tile_y) + 22) + deslocY_mapa, makecol(150, 150, 150));
            }
        }
    }
}

inline void Buffer() {
    if (tile_is_imported) {
    //-------------------------------------------------------------------------------{
        for (int y = 0; y < import_tile->h / tile_y + 1; y++) {
            for (int x = 0; x < import_tile->w / tile_x + 1; x++) {
                if (mouse_x <= 250 && mouse_y >= 20) {
                    if (mouse_b & 1) {
                        if (((mouse_x >= x * tile_x + deslocX_tiles)) && ((mouse_x <= (x + 1) * tile_x + deslocX_tiles))) {
                            mouseX_tile = x * tile_x;
                            mouseX2_tile = (x + 1) * tile_x;
                        }
                        if (((mouse_y >= (y * tile_y) + 20 + deslocY_tiles)) && ((mouse_y <= ((y + 1) * tile_y) + 20 + deslocY_tiles))) {
                            mouseY_tile = y * tile_y;
                            mouseY2_tile = (y + 1) * tile_y;
                        }

                        if (((mouse_x >= x * tile_x + deslocX_tiles)) && ((mouse_x <= (x + 1) * tile_x + deslocX_tiles))) {
                            if (((mouse_y >= (y * tile_y) + 20 + deslocY_tiles)) && ((mouse_y <= ((y + 1) * tile_y) + 20 + deslocY_tiles))) {
                                selected = (x + ((import_tile->w / tile_x) * y));
                            }
                        }
                    }
                }
            }
        }

    //-------------------------------------------------------------------------------}
    //-------------------------------------------------------------------------------{
        draw_sprite(tiles, import_tile, deslocX_tiles, deslocY_tiles);

        for (int x = 0; x < mapa_x; x++) {
            for (int y = 0; y < mapa_y; y++) {
                draw_posX = ((x * tile_x) + 22);
                draw_posY = ((y * tile_y) + 22);
                if (mouse_x >= ((x * tile_x + 272) + deslocX_mapa) && mouse_x <= (((x + 1) * tile_x + 272) + deslocX_mapa)) {
                    if (mouse_y >= ((y * tile_y + 42) + deslocY_mapa) && mouse_y <= (((y + 1) * tile_y + 42) + deslocY_mapa)) {
                        if (!colisao) {
                            if (layer == 1) {
                                if (mouse_b & 1) {
                                    layer1[x][y] = selected;
                                }
                                if (mouse_b & 2) {
                                    layer1[x][y] = -1;
                                }
                            }
                            else if (layer == 2) {
                                if (mouse_b & 1) {
                                    layer2[x][y] = selected;
                                }
                                if (mouse_b & 2) {
                                    layer2[x][y] = -1;
                                }
                            }
                            else if (layer == 3) {
                                if (mouse_b & 1) {
                                    layer3[x][y] = selected;
                                }
                                if (mouse_b & 2) {
                                    layer3[x][y] = -1;
                                }
                            }
                        } else {
                            if (mouse_b & 1) {
                                collision_layer[x][y] = 1;
                            }
                            if (mouse_b & 2) {
                                collision_layer[x][y] = 0;
                            }
                        }
                    }
                }
                if (layer1[x][y] != -1)
                    draw_sprite(mapa, blited_tile[layer1[x][y]], draw_posX + deslocX_mapa, draw_posY + deslocY_mapa);
                if (layer2[x][y] != -1)
                    draw_sprite(mapa, blited_tile[layer2[x][y]], draw_posX + deslocX_mapa, draw_posY + deslocY_mapa);
                if (layer3[x][y] != -1)
                    draw_sprite(mapa, blited_tile[layer3[x][y]], draw_posX + deslocX_mapa, draw_posY + deslocY_mapa);
                if (collision_layer[x][y] == 1 && colisao) {
                    rectfill(mapa, draw_posX + deslocX_mapa, draw_posY + deslocY_mapa, draw_posX + 10 + deslocX_mapa, draw_posY + 10 + deslocY_mapa, makecol(150, 0, 0));
                    rect(mapa, draw_posX + 1 + deslocX_mapa, draw_posY + 1 + deslocY_mapa, draw_posX + 9 + deslocX_mapa, draw_posY + 9 + deslocY_mapa, makecol(255, 0, 0));
                    rect(mapa, draw_posX + deslocX_mapa, draw_posY + deslocY_mapa, draw_posX + 10 + deslocX_mapa, draw_posY + 10 + deslocY_mapa, makecol(100, 0, 0));
                }
            }
        }
    //-------------------------------------------------------------------------------}
    }

    rect(tiles, mouseX_tile + deslocX_tiles, mouseY_tile, mouseX2_tile + deslocX_tiles, mouseY2_tile, makecol(0, 0, 0));
    rect(tiles, mouseX_tile + 1 + deslocX_tiles, mouseY_tile + 1 + deslocY_tiles, mouseX2_tile - 1 + deslocX_tiles, mouseY2_tile - 1 + deslocY_tiles, makecol(255, 0, 0));
    rect(tiles, mouseX_tile + 2 + deslocX_tiles, mouseY_tile + 2 + deslocY_tiles, mouseX2_tile - 2 + deslocX_tiles, mouseY2_tile - 2 + deslocY_tiles, makecol(0, 0, 0));

    rect(tiles, 0, 0, 249, 748, makecol(255, 255, 255));

    draw_sprite(screen, tiles, 0, 19);
    clear(tiles);

    Grid();
    Mouse();
    Scroll();

    // Onde ficaram as réguas
    rectfill(mapa, 21, 0, 772, 21, makecol(150, 200, 255));
    rectfill(mapa, 0, 21, 21, 772, makecol(150, 200, 255));

    Reguas();

    // Cria bordas nas réguas
    line(mapa, 21, 0, 21, 773, makecol(255, 255, 255));
    line(mapa, 0, 21, 772, 21, makecol(255, 255, 255));

    rectfill(mapa, 0, 0, 20, 20, makecol(150, 200, 255));

    // Mostra em qual layer será desenhado
    if (colisao)
        textout_ex(mapa, font, "C", 7, 7, makecol(0, 0, 0), -1);
    else
        textprintf_ex(mapa, font, 7, 7, makecol(0, 0, 0), -1, "%d", layer);

    // Borda principal
    rect(mapa, 0, 0, 773, 748, makecol(255, 255, 255));

    draw_sprite(screen, mapa, 250, 19);
    clear(mapa);

    draw_sprite(screen, menu, 0, 0);
    clear(menu);
}

inline void GUI() {
    set_dialog_color(dialog, makecol(0, 0, 0), makecol(150, 200, 255));

    gui_set_screen(menu);
    gui = init_dialog(dialog, -1);
}

/*--------------------------------
    Função Principal
--------------------------------*/
int main() {
    init();

    menu = create_bitmap(SCREEN_W, 20);
    tiles = create_bitmap(250, 749);
    mapa = create_bitmap(774, 749);

    GUI();

    mapa_x = atoi(mapaX);
    mapa_y = atoi(mapaY);
    tile_x = atoi(tileX);
    tile_y = atoi(tileY);

    for (int x = 0; x < mapa_x; x++) {
        for (int y = 0; y < mapa_y; y++) {
            layer1[x][y] = -1;
            layer2[x][y] = -1;
            layer3[x][y] = -1;
            collision_layer[x][y] = 0;
        }
    }

    while (!key[KEY_ESC]) {
        broadcast_dialog_message(MSG_DRAW, 0);
        update_dialog(gui);

        rect(menu, 0, 0, 1023, 19, makecol(255, 255, 255));

        Buffer();

        //vsync();
    }
}
END_OF_MAIN()

/*--------------------------------
    Funções de Botoes
----------------------------------*/

// Caso botão Abrir seja clicado...
int bt_Abrir(void) {
    ifstream openmap;

    openmap.open(nome);

    int layer;
    char c;

    openmap >> mapa_x >> c >> mapa_y >> c >> tile_x >> c >> tile_y >> c;

    for (int i = 0; i < 4; i++) {
        openmap >> c >> layer >> c;
        for (int y = 0; y < mapa_y; y++) {
            for (int x = 0; x < mapa_x; x++) {
                if (i == 0)
                    openmap >> layer1[x][y] >> c;
                if (i == 1)
                    openmap >> layer2[x][y] >> c;
                if (i == 2)
                    openmap >> layer3[x][y] >> c;
                if (i == 3)
                    openmap >> collision_layer[x][y] >> c;
            }
        }
    }

    return D_O_K;
}

// Caso botão Salvar seja clicado...
int bt_Salvar(void) {
    ofstream savemap;

    savemap.open(nome);

    savemap << mapa_x <<"; " <<  mapa_y << ";\n" << tile_x << "; " << tile_y << ";\n\n";

    for (int i = 0; i < 4; i++) {
        savemap << "[" << i << "]" << endl;

        for (int y = 0; y < mapa_y; y++) {
            for (int x  = 0; x < mapa_x; x++) {
                if (i == 0)
                    savemap << layer1[x][y] << "; ";
                if (i == 1)
                    savemap << layer2[x][y] << "; ";
                if (i == 2)
                    savemap << layer3[x][y] << "; ";
                if (i == 3)
                    savemap << collision_layer[x][y] << "; ";
            }
            savemap << endl;
        }
        savemap << "\n\n";
    }
    savemap.close();

    return D_O_K;
}

// Caso botão Importar seja clicado...
int bt_Importar(void) {
    import_tile = load_bitmap(import, NULL);

    if (!import_tile) {
        allegro_message("Impossivel importar tile!");
        tile_is_imported = false;
        return 1;
    }

    for (int x = 0; x < mapa_x; x++) {
        for (int y = 0; y < mapa_y; y++) {
            layer1[x][y] = -1;
            layer2[x][y] = -1;
            layer3[x][y] = -1;
            collision_layer[x][y] = 0;
        }
    }

    for (int y = 0; y < import_tile->h / tile_y + 1; y++) {
        for (int x = 0; x < import_tile->w / tile_x + 1; x++) {
            blited_tile[x + ((import_tile->w / tile_x) * y)] = create_bitmap(tile_x, tile_y);

            blit(import_tile, blited_tile[x + ((import_tile->w / tile_x) * y)], x * tile_x, y * tile_y, 0, 0, tile_x, tile_y);
        }
    }

    deslocX_tiles = 0;
    deslocY_tiles = 0;

    tile_is_imported = true;

    return D_O_K;
}

// Caso botão OK_Mapa seja clicado...
int bt_OK_Mapa(void) {
    int x = atoi(mapaX);
    int y = atoi(mapaY);

    if (x > 0) {
        mapa_x = atoi(mapaX);
    } else
        allegro_message("Digite um numero valido!");

    if (y > 0) {
        mapa_y = atoi(mapaY);
    } else
        allegro_message("Digite um numero valido!");

    if (tile_is_imported) {
        for (int y = 0; y < import_tile->h / tile_y + 1; y++) {
            for (int x = 0; x < import_tile->w / tile_x + 1; x++) {
                blited_tile[x + ((import_tile->w / tile_x) * y)] = create_bitmap(tile_x, tile_y);

                blit(import_tile, blited_tile[x + ((import_tile->w / tile_x) * y)], x * tile_x, y * tile_y, 0, 0, tile_x, tile_y);
            }
        }
    }

    return D_O_K;
}

// Caso botão OK_Tile seja clicado...
int bt_OK_Tile(void) {
    int x = atoi(tileX);
    int y = atoi(tileY);

    if (x > 0) {
        tile_x = atoi(tileX);
    } else
        allegro_message("Digite um numero valido!");

    if (y > 0) {
        tile_y = atoi(tileY);
    } else
        allegro_message("Digite um numero valido!");

    if (tile_is_imported) {
        for (int y = 0; y < import_tile->h / tile_y + 1; y++) {
            for (int x = 0; x < import_tile->w / tile_x + 1; x++) {
                blited_tile[x + ((import_tile->w / tile_x) * y)] = create_bitmap(tile_x, tile_y);

                blit(import_tile, blited_tile[x + ((import_tile->w / tile_x) * y)], x * tile_x, y * tile_y, 0, 0, tile_x, tile_y);
            }
        }
    }

    return D_O_K;
}

// Caso botão Layer1 seja clicado...
int bt_Layer1(void) {
    layer = 1;
    colisao = false;
    return D_O_K;
}

// Caso botão Layer2 seja clicado...
int bt_Layer2(void) {
    layer = 2;
    colisao = false;
    return D_O_K;
}

// Caso botão Layer3 seja clicado...
int bt_Layer3(void) {
    layer = 3;
    colisao = false;
    return D_O_K;
}

// Caso botão Grid seja clicado...
int bt_Grid(void) {
    if (grid == false)
        grid = true;
    else
        grid = false;

    return D_O_K;
}

// Caso botão Colisao seja clicado...
int bt_Colisao(void) {
    if (colisao == false)
        colisao = true;
    else
        colisao = false;

    return D_O_K;
}
