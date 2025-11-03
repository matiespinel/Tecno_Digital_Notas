#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ========= CONSTANTES DEL JUEGO =========
#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 500

#define GRID_OFFSET_X 220
#define GRID_OFFSET_Y 59
#define GRID_WIDTH 650
#define GRID_HEIGHT 425

#define GRID_ROWS 5
#define GRID_COLS 9
#define CELL_WIDTH (GRID_WIDTH / GRID_COLS)
#define CELL_HEIGHT (GRID_HEIGHT / GRID_ROWS)

#define PEASHOOTER_FRAME_WIDTH 177
#define PEASHOOTER_FRAME_HEIGHT 166
#define PEASHOOTER_TOTAL_FRAMES 31
#define PEASHOOTER_ANIMATION_SPEED 4
#define PEASHOOTER_SHOOT_FRAME 18

#define ZOMBIE_FRAME_WIDTH 164
#define ZOMBIE_FRAME_HEIGHT 203
#define ZOMBIE_TOTAL_FRAMES 90
#define ZOMBIE_ANIMATION_SPEED 2
#define ZOMBIE_DISTANCE_PER_CYCLE 40.0f

#define MAX_ARVEJAS 100
#define PEA_SPEED 5
#define ZOMBIE_SPAWN_RATE 300


// ========= ESTRUCTURAS DE DATOS =========
typedef struct {
    int row, col;
} Cursor;

typedef struct {
    SDL_Rect rect;
    int activo;
    int cooldown;
    int current_frame;
    int frame_timer;
    int debe_disparar;
} Planta;

typedef struct {
    SDL_Rect rect;
    int activo;
} Arveja;

typedef struct {
    SDL_Rect rect;
    int activo;
    int vida;
    int row;
    int current_frame;
    int frame_timer;
    float pos_x;
} Zombie;

// ========= NUEVAS ESTRUCTURAS =========
#define STATUS_VACIO 0
#define STATUS_PLANTA 1

typedef struct RowSegment {
    int status;
    int start_col;
    int length;
    Planta* planta_data;
    struct RowSegment* next;
} RowSegment;

typedef struct ZombieNode {
    Zombie zombie_data;
    struct ZombieNode* next;
} ZombieNode;

typedef struct GardenRow {
    RowSegment* first_segment;
    ZombieNode* first_zombie;
} GardenRow;

typedef struct GameBoard {
    GardenRow rows[GRID_ROWS];
    Arveja arvejas[MAX_ARVEJAS]; //array adicional para manejar las arvejas
    int zombie_spawn_timer; // variable para saber cada cuanto crear un zombie
} GameBoard;


// ========= VARIABLES GLOBALES =========
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* tex_background = NULL;
SDL_Texture* tex_peashooter_sheet = NULL;
SDL_Texture* tex_zombie_sheet = NULL;
SDL_Texture* tex_pea = NULL;

Cursor cursor = {0, 0};
GameBoard* game_board = NULL;

// ========= FUNCIONES =========

GameBoard* gameBoardNew() {
    GameBoard* board = (GameBoard*)malloc(sizeof(GameBoard));
    if (!board) return NULL;

    board->zombie_spawn_timer = ZOMBIE_SPAWN_RATE;

    for (int i = 0; i < GRID_ROWS; i++) {
        RowSegment* first = (RowSegment*)malloc(sizeof(RowSegment));
        if (!first) {
            free(board);
            return NULL;
        }
        first->status = STATUS_VACIO;
        first->start_col = 0;
        first->length = GRID_COLS;
        first->planta_data = NULL;
        first->next = NULL;

        board->rows[i].first_segment = first;
        board->rows[i].first_zombie = NULL;
    }
    for(int i = 0; i < MAX_ARVEJAS; i++) {
        board->arvejas[i].activo = 0;
    }
    return board;
}

void gameBoardDelete(GameBoard* board) {
    // TODO: Liberar toda la memoria dinámica.
    // TODO: Recorrer cada GardenRow.
    if (!board) return;// caso base
    for(int i = 0; i < GRID_ROWS; i++) {
        GardenRow* row = &board->rows[i];
        //hay planta?
            RowSegment* segment = row->first_segment;
            while(segment) {// recorro todos los segmentos de una fila
                RowSegment* next_segment = segment->next;
                if(segment->planta_data) {
                    free(segment->planta_data);//revisar pq las planbtas no estan en malloc 
                }
                free(segment);
                segment = next_segment;
            }

    // Recorremos todas las filas del jardín
    
        GardenRow* row = &board->rows[i];

        // 1️⃣ Liberar todos los zombies de la fila
        ZombieNode* znode = row->first_zombie;
        while (znode) {//cuando sea NULL termina
            ZombieNode* next_z = znode->next;//avanzo 
            free(znode);
            znode = next_z;//sigo con el siguiente
        }
        row->first_zombie = NULL;

    // TODO: Liberar todos los RowSegment (y los planta_data si existen).
    // TODO: Liberar todos los ZombieNode.

    free(board);
    // TODO: Finalmente, liberar el GameBoard.
    printf("Función gameBoardDelete no implementada.\n");
    }
}
int gameBoardAddPlant(GameBoard* board, int row, int col) {// MODIFICAR porque yo paso planta y no segmento, tengo que borrar el segmento especifico y crear uno nuevo con la planta
    // TODO: Encontrar la GardenRow correcta.
    GardenRow* garden_row = &board->rows[row];
    RowSegment* segment = garden_row->first_segment;
    for (int i = 0; i < col; i++)
    {
        RowSegment* anterior = segment;
        RowSegment* next_segment = segment->next;
        segment = next_segment;
    }
    RowSegment* segmentsig = segment->next;
    int dato = segment->length;
    int dato2 = segment->start_col;
    if(segment->planta_data == NULL) {//si no hay planta es decir statuas null
        // si no hay planta la pongo
        RowSegment* nuevo = (RowSegment*)malloc(sizeof(RowSegment));
        nuevo->status = STATUS_PLANTA;
        Planta* nueva_planta = (Planta*)malloc(sizeof(Planta));
        nuevo->planta_data = nueva_planta;
        anterior->next = nuevo;
        nuevo->next = segmentsig;
        nuevo->length = dato;
        nuevo->start_col = dato2;
        free(segment);
    }
    
    // TODO: Recorrer la lista de RowSegment hasta encontrar el segmento VACIO que contenga a `col`.
    // TODO: Si se encuentra y tiene espacio, realizar la lógica de DIVISIÓN de segmento. sumar planta al segmento sin que se rompa la linea de segmentos solo se pasa plant data 
    // TODO: Crear la nueva `Planta` con memoria dinámica y asignarla al `planta_data` del nuevo segmento.
    printf("Función gameBoardAddPlant no implementada.\n");
    return 0;
}

void gameBoardRemovePlant(GameBoard* board, int row, int col) {//MODIFICAR porque yo paso planta y no segmento, tengo que borrar el segmento especifico con la planta y borrarlo, despues meter uno nuevo.
    // mismo que arriba pero en vez de poner saco 
    GardenRow* garden_row = &board->rows[row];
    RowSegment* segment = garden_row->first_segment;
    for (int i = 0; i < col; i++)
    {
        RowSegment* anterior = segment;
        RowSegment* next_segment = segment->next;
        segment = next_segment;
    }
    RowSegment* segmentsig = segment->next;
    int dato = segment->length;
    int dato2 = segment->start_col;
    if(segment->planta_data != NULL) {//si hay planta es decir statuas !null
        // si hay planta la saco
        segment->planta_data = NULL;
        segment->status = STATUS_VACIO;
        free(segment->planta_data);//libero la planta
    }
    RowSegment* nuevo = (RowSegment*)malloc(sizeof(RowSegment));
    nuevo->status = STATUS_VACIO;
    anterior->next = nuevo;
    nuevo->next = segmentsig;
    nuevo->length = dato;
    nuevo->start_col = dato2;
    free(segment);
    // TODO: Similar a AddPlant, encontrar el segmento que contiene `col`.
    // TODO: Si es un segmento de tipo PLANTA, convertirlo a VACIO y liberar el `planta_data`.
    // TODO: Implementar la lógica de FUSIÓN con los segmentos vecinos si también son VACIO.
    // sigue la logica de segmentos planteada en la consigna al elminar el segmento e insertando otro nuevo en su lugar. 
    printf("Función gameBoardRemovePlant no implementada.\n");
}

void gameBoardAddZombie(GameBoard* board, int row) {
    // TODO: Crear un nuevo ZombieNode con memoria dinámica.
    GardenRow* garden_row = &board->rows[row];
    RowSegment* segment = garden_row->first_segment;
    ZombieNode* new_zombie_node = (ZombieNode*)malloc(sizeof(ZombieNode));
    new_zombie_node->pos_x = SCREEN_WIDTH;
    new_zombie_node->zombie_data.row = row;
    new_zombie_node->zombie_data.activo = 1;
    new_zombie_node->zombie_data.current_frame=0;
    new_zombie_node->zombie_data.frame_timer=0;
    new_zombie_node->zombie_data.vida=100;
    // TODO: Inicializar sus datos (posición, vida, animación, etc.).
    // TODO: Agregarlo a la lista enlazada simple de la GardenRow correspondiente.
    printf("Función gameBoardAddZombie no implementada.\n");
}

void gameBoardUpdate(GameBoard* board) {
    if (!board) return;
    // TODO: Re-implementar la lógica de `actualizarEstado` usando las nuevas estructuras.
    // TODO: Recorrer las listas de zombies de cada fila para moverlos y animarlos.
    // TODO: Recorrer las listas de segmentos de cada fila para gestionar los cooldowns y animaciones de las plantas.
    // TODO: Actualizar la lógica de disparo, colisiones y spawn de zombies.
    // logica vieja 
    for (int r = 0; r < GRID_ROWS; r++) {
        ZombieNode* zombie = garden_rows[r].first_zombie;
        while (zombie) {
            if (zombie->zombie_data.activo) {
                float distance_per_tick = ZOMBIE_DISTANCE_PER_CYCLE / (float)(ZOMBIE_TOTAL_FRAMES * ZOMBIE_ANIMATION_SPEED);
                zombie->pos_x -= distance_per_tick;
                zombie->rect.x = (int)zombie->pos_x;
                zombie->frame_timer++;
                if (zombie->frame_timer >= ZOMBIE_ANIMATION_SPEED) {
                    zombie->frame_timer = 0;
                    zombie->current_frame = (zombie->current_frame + 1) % ZOMBIE_TOTAL_FRAMES;
            }
            }
            zombie = zombie->next;
        }
    }

    for (int r = 0; r < GRID_ROWS; r++) {// recorro todas las filas y columnas buscando plantas y actualizandolas
        GardenRow* garden_row = &board->rows[r]; 
        RowSegment* segment = garden_row->first_segment;
        while (segment) {
            if (segment->status) {
                Planta* p = &segment->planta_data;
                if (p->cooldown <= 0) {
                        p->debe_disparar = 1;
                } else {
                    p->cooldown--;
                }
                p->frame_timer++;
                if (p->frame_timer >= PEASHOOTER_ANIMATION_SPEED) {
                    p->frame_timer = 0;
                    p->current_frame = (p->current_frame + 1) % PEASHOOTER_TOTAL_FRAMES;
                    if (p->debe_disparar && p->current_frame == PEASHOOTER_SHOOT_FRAME) {
                        dispararArveja(r, c);
                        p->cooldown = 120;
                        p->debe_disparar = 0;
                    }
                }
            }
        }
    }

    for (int i = 0; i < MAX_ARVEJAS; i++) {
        if (board->arvejas[i].activo) {
            board->arvejas[i].rect.x += PEA_SPEED;
            if (board->arvejas[i].rect.x > SCREEN_WIDTH) board->arvejas[i].activo = 0;
        }
    }
    for (int i = 0; i < GRID_ROWS; i++) {//modificada para que use gameboard y las estructuras nuevas, la logica es la misma que en el base nada mas adaptada a las nuevas estructuras de datos.
        if (!board->rows[i].first_zombie->zombie_data.activo) continue;
        for (int j = 0; j < MAX_ARVEJAS; j++) {
            if (!board->arvejas[j].activo) continue;
            int arveja_row = (board->arvejas[j].rect.y - GRID_OFFSET_Y) / CELL_HEIGHT;
            if (board->rows[i].first_zombie->zombie_data.row == arveja_row) {
                if (SDL_HasIntersection(&board->arvejas[j].rect, &board->rows[i].first_zombie->rect)) {// verificar si es suficiente preguntar el primero de la lista de zombies 
                    board->arvejas[j].activo = 0;
                    board->rows[i].first_zombie->zombie_data.vida -= 25;
                    if (board->rows[i].first_zombie->zombie_data.vida <= 0) board->rows[i].first_zombie->zombie_data.activo = 0;
                }
            }
        }
    }
    // YA ACTUALIZADO EL SPAWN DE ZOMBIES
    board->zombie_spawn_timer--;
    if (board->zombie_spawn_timer <= 0) {
        gameBoardAddZombie(board, rand() % GRID_ROWS);
        board->zombie_spawn_timer = ZOMBIE_SPAWN_RATE;
    }
}
void dispararArveja(GameBoard* board, int row, int col) {//modificada para que use gameboard y las estructuras nuevas, la logica es la misma que en el base nada mas adaptada a las nuevas estructuras de datos. 
    for (int i = 0; i < MAX_ARVEJAS; i++) {
        if (!board->arvejas[i].activo) {
            board->arvejas[i].rect.x = board->rows[row].segments[col].rect.x + (CELL_WIDTH / 2);
            board->arvejas[i].rect.y = board->rows[row].segments[col].rect.y + (CELL_HEIGHT / 4);
            board->arvejas[i].rect.w = 20;
            board->arvejas[i].rect.h = 20;
            board->arvejas[i].activo = 1;
            break;
        }
    }
}
void gameBoardDraw(GameBoard* board) { // la estructura de dibujar fue modificada nada mes en los accesos a las plantas y demas, la logica de dibujo es la misma que la proporcionada en el juego base.
    if (!board) return;
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, tex_background, NULL, NULL);

    // TODO: Re-implementar la lógica de `dibujar` usando las nuevas estructuras.
    // TODO: Recorrer las listas de segmentos para dibujar las plantas.
    // TODO: Recorrer las listas de zombies para dibujarlos.
    // TODO: Dibujar las arvejas y el cursor.
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, tex_background, NULL, NULL);

    for (int r = 0; r < GRID_ROWS; r++) {// recorro todas las filas y columnas buscando plantas y actualizandolas
        GardenRow* garden_row = &board->rows[r]; 
        RowSegment* segment = garden_row->first_segment;
        while (segment) {
            if (segment->status) {// el status es indicador de planta como se decia en la consigna que si este es = 1 hay planta
                Planta* p = &segment->planta_data;
                SDL_Rect src_rect = { p->current_frame * PEASHOOTER_FRAME_WIDTH, 0, PEASHOOTER_FRAME_WIDTH, PEASHOOTER_FRAME_HEIGHT };
                SDL_RenderCopy(renderer, tex_peashooter_sheet, &src_rect, &p->rect);
            }
            segment = segment->next;
        }
    }
    for (int i = 0; i < MAX_ARVEJAS; i++) {// arvejas 
        if (board->arvejas[i].activo) SDL_RenderCopy(renderer, tex_pea, NULL, &board->arvejas[i].rect);
    }
    for (int r = 0; r < GRID_ROWS; r++) {// recorro todas las filas y miro sus listas de zombies
        GardenRow* garden_row = &board->rows[r];
        Zombie* z = garden_row->first_zombie;
        while (z) {
            if (z->activo) {
                SDL_Rect src_rect = { z->current_frame * ZOMBIE_FRAME_WIDTH, 0, ZOMBIE_FRAME_WIDTH, ZOMBIE_FRAME_HEIGHT };
                SDL_RenderCopy(renderer, tex_zombie_sheet, &src_rect, &z->rect);
            }
            z = z->next;
        }
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 200);
    SDL_Rect cursor_rect = {GRID_OFFSET_X + cursor.col * CELL_WIDTH, GRID_OFFSET_Y + cursor.row * CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT};
    SDL_RenderDrawRect(renderer, &cursor_rect);

    SDL_RenderPresent(renderer);

    SDL_RenderPresent(renderer);
}

SDL_Texture* cargarTextura(const char* path) {
    SDL_Texture* newTexture = IMG_LoadTexture(renderer, path);
    if (newTexture == NULL) printf("No se pudo cargar la textura %s! SDL_image Error: %s\n", path, IMG_GetError());
    return newTexture;
}
int inicializar() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return 0;
    window = SDL_CreateWindow("Plantas vs Zombies - Base para TP", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) return 0;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) return 0;
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) return 0;
    tex_background = cargarTextura("res/Frontyard.png");
    tex_peashooter_sheet = cargarTextura("res/peashooter_sprite_sheet.png");
    tex_zombie_sheet = cargarTextura("res/zombie_sprite_sheet.png");
    tex_pea = cargarTextura("res/pea.png");
    return 1;
}
void cerrar() {
    SDL_DestroyTexture(tex_background);
    SDL_DestroyTexture(tex_peashooter_sheet);
    SDL_DestroyTexture(tex_zombie_sheet);
    SDL_DestroyTexture(tex_pea);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}


int main(int argc, char* args[]) {
    srand(time(NULL));
    if (!inicializar()) return 1;

    game_board = gameBoardNew();

    SDL_Event e;
    int game_over = 0;

    while (!game_over) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) game_over = 1;
            if (e.type == SDL_MOUSEMOTION) {
                int mouse_x = e.motion.x;
                int mouse_y = e.motion.y;
                if (mouse_x >= GRID_OFFSET_X && mouse_x < GRID_OFFSET_X + GRID_WIDTH &&
                    mouse_y >= GRID_OFFSET_Y && mouse_y < GRID_OFFSET_Y + GRID_HEIGHT) {
                    cursor.col = (mouse_x - GRID_OFFSET_X) / CELL_WIDTH;
                    cursor.row = (mouse_y - GRID_OFFSET_Y) / CELL_HEIGHT;
                }
            }
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                gameBoardAddPlant(game_board, cursor.row, cursor.col);
            }
        }

        gameBoardUpdate(game_board);
        gameBoardDraw(game_board);

        // TODO: Agregar la lógica para ver si un zombie llegó a la casa y terminó el juego
        for(int i = 0; i < GRID_ROWS; i++) {
            GardenRow* row = &board->rows[i];
            ZombieNode* znode = row->first_zombie;
            while (znode) {//cuando sea NULL termina
                ZombieNode* next_z = znode->next;//avanzo 
                if (znode->zombie_data.activo && znode->zombie_data.pos_x < GRID_OFFSET_X) {//esto se accede desde zombie data y usdando activo y pos sabes si llego;
                printf("GAME OVER - Un zombie llego a tu casa!\n");
                game_over = 1;
                break;
            }
                znode = next_z;//sigo con el siguiente
        }
        row->first_zombie = NULL;
        
    
        }

        SDL_Delay(16);
    }

    gameBoardDelete(game_board);
    cerrar();
    return 0;
}
