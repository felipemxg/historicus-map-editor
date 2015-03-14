#include <allegro.h>
#include "main.h"

inline void buffer() {
     // Onde ficaram as réguas
    rectfill(mapa, 21, 0, 772, 21, makecol(150, 200, 255));
    rectfill(mapa, 0, 21, 21, 772, makecol(150, 200, 255));

    Reguas();

    // Cria bordas nas réguas
    line(mapa, 21, 0, 21, 773, makecol(255, 255, 255));
    line(mapa, 0, 21, 772, 21, makecol(255, 255, 255));

    rectfill(mapa, 0, 0, 20, 20, makecol(150, 200, 255));

    // Mostra em qual layer será desenhado
    textprintf_ex(mapa, font, 7, 7, makecol(0, 0, 0), -1, "%d", layer);

    // Borda principal
    rect(mapa, 0, 0, 773, 748, makecol(255, 255, 255));

    draw_sprite(screen, mapa, 250, 19);
    clear(mapa);

    draw_sprite(screen, menu, 0, 0);
    clear(menu);
}
