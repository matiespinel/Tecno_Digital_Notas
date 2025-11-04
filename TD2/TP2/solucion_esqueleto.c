#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// ===========ejericio 1 ==========
//funciones 
char* strDuplicate(char* src){
    int contador = 0; 
    while (src[contador] != '\0') { // me fijo cuando termina el str 
        contador++;// longitud del src
        printf("contador: %d\n", contador);//para ver que este andno bien
    }
    char* ret = (char*)malloc(sizeof(char) * (contador + 1)); // +1 para el \0?
    for(int i =0; i <contador; i++){
        ret[i] = src[i];
    }
    ret[contador] = '\0';
    return ret;
}
//comparacion lexicografica
int strCompare(char* s1, char* s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] < s2[i]) return -1;  // s1 es menor
        if (s1[i] > s2[i]) return 1;   // s1 es mayor
        i++;
    }

    // Si uno terminó antes que el otro
    if (s1[i] == '\0' && s2[i] == '\0') return 0;  // iguales
    if (s1[i] == '\0') return -1;  // s1 más corto → menor
    return 1;                      // s2 más corto → mayor
}

char* strConcatenate(char* src1, char* src2){
    int len1 =0;
    int len2 =0;
    while (src1[len1] != '\0'){
        len1++;
    }
    while (src2[len2] != '\0'){
        len2++;
    }
    char* ret = (char*) malloc (sizeof(char) * (len1 + len2 +1)); // +1 para el \0?
    for(int i =0; i < len1; i++){
        ret[i] = src1[i];
    }
    for(int j =0; j < len2; j++){
        ret[len1 + j] = src2[j];
    }
    ret[len1 + len2] = '\0';
    free(src1);
    free(src2);
    return ret;
}

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
        GardenRow* row = board->rows[i];
        //hay planta?
            RowSegment* segment = row->first_segment;
            while(segment) {// recorro todos los segmentos de una fila
                RowSegment* next_segment = segment->next;
                if(segment->planta_data) {
                    free(segment->planta_data);
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
    GardenRow* garden_row = board->rows[row];
    RowSegment* segment = garden_row->first_segment;
    RowSegment* plant_segment = (RowSegment*)malloc(sizeof(RowSegment));
    // se debe buscar dentro de los segmentos cual tiene el espacio para la planta, es decir dentro de start_col cual es el mayor o igual.
    while (segment) {// recorro todos los segmentos de la fila, si bien al inicio hay uno solo, despues en juego hay mas. 
        if (segment->start_col <= col && (segment->start_col + segment->length) > col) {// miro si es el mio 
            //pregunto si el segmento es vacio
            if (segment->status == STATUS_VACIO) {
                // Si está vacío, puedo usarlo
                break;
            }
            if (segment->status == STATUS_PLANTA)
            {
                // Si ya hay una planta, no puedo colocar otra
                return 0;
            }
        }
        segment = segment->next;
    }
    // ahora segment tiene el segmento donde esta la columna que necesitamos 
    plant_segment->next = segment->next;// enlazo el proximo si existe. 
    segment->next = plant_segment;//puntero al nuevo segmento de planta que creamos
    plant_segment->start_col = col;
    plant_segment->status = STATUS_PLANTA;
    segment->length= col - segment->start_col; // ajusto el largo del segmento viejo
    plant_segment->length =1; // el nuevo segmento de planta tiene largo 1
    Planta* nueva_planta = (Planta*)malloc(sizeof(Planta));
    plant_segment->planta_data = nueva_planta;//paso planta nueva al segmento de planta
    // ahora vemos si la parte derecha del segmento planta tiene espacio para otro segmento vacio
    //miro longitud total de la row completa
    if (plant_segment->next == NULL && (col + 1) < GRID_COLS) {// hay lugar para segmento vacio a la derecha y el segmento planta de por si ya no tiene. 
        RowSegment* nuevo_segmento_vacio = (RowSegment*)malloc(sizeof(RowSegment));
        nuevo_segmento_vacio->status = STATUS_VACIO;
        nuevo_segmento_vacio->start_col = col +1;
        nuevo_segmento_vacio->length = GRID_COLS - (col +1);
        nuevo_segmento_vacio->planta_data = NULL;
        nuevo_segmento_vacio->next = plant_segment->next;
        plant_segment->next = nuevo_segmento_vacio;// checkear si esto anda bien
    }
    
    // TODO: Recorrer la lista de RowSegment hasta encontrar el segmento VACIO que contenga a `col`.
    // TODO: Si se encuentra y tiene espacio, realizar la lógica de DIVISIÓN de segmento. sumar planta al segmento sin que se rompa la linea de segmentos solo se pasa plant data 
    // TODO: Crear la nueva `Planta` con memoria dinámica y asignarla al `planta_data` del nuevo segmento.
    printf("Función gameBoardAddPlant no implementada.\n");
    return 0;
}

void gameBoardRemovePlant(GameBoard* board, int row, int col) {//MODIFICAR porque yo paso planta y no segmento, tengo que borrar el segmento especifico con la planta y borrarlo, despues meter uno nuevo.
    // mismo que arriba pero en vez de poner saco 
    // TODO: Encontrar la GardenRow correcta.
    GardenRow* garden_row = &board->rows[row];
    RowSegment* segment = garden_row->first_segment;
    RowSegment* prev_segment = NULL;
    int segmento_anterior = -1;// variable para saber que segmento es el mio 
    // se debe buscar dentro de los segmentos cual tiene el espacio de la planta, es decir dentro de start_col cual es el mayor o igual.
    for (int i = 0; i < GRID_COLS; i++) {// recorro todos los segmentos de la fila.
        if (segment->start_col <= col && (segment->start_col + segment->length) > col) {//miro si es el mio 
            //pregunto si el segmento es vacio
            if (segment->status == STATUS_VACIO) {
                // Si está vacío, no hago nada 
                return;
            }
            if (segment->status == STATUS_PLANTA)
            {
                // Si ya hay una planta, no puedo colocar otra
                break;// lo encontre 
            }
        }
        segment = segment->next;
        segmento_anterior++;
    }

    if (segmento_anterior >= 0) {
        // Encuentro el segmento anterior al actual
        prev_segment = garden_row->first_segment;
        for (int i = 0; i < segmento_anterior; i++) {
            prev_segment = prev_segment->next;
        }
    }
    // ahora segment tiene el segmento donde esta la columna que necesitamos sacar la planta
    if (segment->next == NULL) {// si es el ultimo segmento no puedo fusionar a la derecha
        segment->status = STATUS_VACIO;
        free(segment->planta_data);
        segment->planta_data = NULL;
        prev_segment->length += segment->length;
        prev_segment->next = NULL;
        free(segment);
        //aumentar longitud del anterior segmento y mantener su puntero al siguiente como NULL
        return;
    }
    // si no es el ultimo segmento puedo fusionar a la derecha
    prev_segment->length += segment->length;
    prev_segment->next = segment->next->next;
    free(segment->planta_data);
    segment->next = NULL;
    free(segment);
    if (prev_segment->next->status== STATUS_VACIO) {// si el siguiente tambien es vacio lo fusiono
        prev_segment->length += prev_segment->next->length;
        RowSegment* temp = prev_segment->next;
        prev_segment->next = prev_segment->next->next;
        free(temp);
    }
    return;
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
    new_zombie_node->zombie_data.pos_x = SCREEN_WIDTH;
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
        ZombieNode* zombie = board->rows[r].first_zombie;
        while (zombie) {
            if (zombie->zombie_data.activo) {
                float distance_per_tick = ZOMBIE_DISTANCE_PER_CYCLE / (float)(ZOMBIE_TOTAL_FRAMES * ZOMBIE_ANIMATION_SPEED);
                zombie->zombie_data.pos_x -= distance_per_tick;
                zombie->zombie_data.pos_x = (int)zombie->zombie_data.pos_x;
                zombie->zombie_data.frame_timer++;
                if (zombie->zombie_data.frame_timer >= ZOMBIE_ANIMATION_SPEED) {
                    zombie->zombie_data.frame_timer = 0;
                    zombie->zombie_data.current_frame = (zombie->zombie_data.current_frame + 1) % ZOMBIE_TOTAL_FRAMES;
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
                Planta* p = segment->planta_data;
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
                        dispararArveja(board, r, segment->start_col);
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
                if (SDL_HasIntersection(&board->arvejas[j].rect, &board->rows[i].first_zombie->zombie_data.rect)) {// verificar si es suficiente preguntar el primero de la lista de zombies
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
        if (!board->arvejas[i].activo) {// check si el ! hace falta.
            RowSegment* segment = board->rows[row].first_segment;
            while (segment)
            {
                if (segment->status == STATUS_PLANTA && segment->start_col == col) {
                    break;
                }
                segment = segment->next;
            }// ahora ya tengo mi segmento planta a dispatar. 
            board->arvejas[i].rect.x = segment->planta_data->rect.x + (CELL_WIDTH / 2);//tengo que calcular la posicion x e y de la arveja en base a la planta que dispara, por ende tengo que encontrar el segmento correspondiente a esa planta, dentro de la lista enlazada de segmentos de la fila row
            board->arvejas[i].rect.y = segment->planta_data->rect.y + (CELL_HEIGHT / 4);
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
                Planta* p = segment->planta_data;
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
        ZombieNode* z = garden_row->first_zombie;
        while (z) {
            if (z->zombie_data.activo) {
                SDL_Rect src_rect = { z->zombie_data.current_frame * ZOMBIE_FRAME_WIDTH, 0, ZOMBIE_FRAME_WIDTH, ZOMBIE_FRAME_HEIGHT };
                SDL_RenderCopy(renderer, tex_zombie_sheet, &src_rect, &z->zombie_data.rect);
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


int main(int argc, char* args[]) {// sumo game board como parametro porque lo necesito para ver cuando termino.
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
            GardenRow* row = &game_board->rows[i];
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
    char* original = "Hola, Mundo!";
    printf("Original: %s\n", original);
    char* copia = strDuplicate(original);
    printf("Copia: %s\n", copia);
    free(copia);

    //1. String vac ́ıo.
    char* vacio = "";
    char* copiaVacio = strDuplicate(vacio);
    printf("Original: %s\n", vacio);
    printf("Copia: %s\n", copiaVacio);
    free(copiaVacio);

    //2. String de un car ́acter.
    char* unCaracter = "A";
    char* copiaUnCaracter = strDuplicate(unCaracter);
    printf("Original: %s\n", unCaracter);
    printf("Copia: %s\n", copiaUnCaracter);
    free(copiaUnCaracter);
    //3. String que incluya todos los caracteres v ́alidos distintos de cero.
    char* todosCaracteres = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_+-=[]{}|;':\",.<>/?`~ ";
    char* copiaTodosCaracteres = strDuplicate(todosCaracteres);
    printf("Original: %s\n", todosCaracteres);
    printf("Copia: %s\n", copiaTodosCaracteres);
    free(copiaTodosCaracteres);

    //strCompare:
    //1. Dos string vac ́ıos.
    char* vacio1 = "";
    char* vacio2 = "";
    printf("Comparacion de dos strings vacios: %d\n", strCompare(vacio1, vacio2)); // Esperado: 0

    //2. Dos string de un car ́acter.
    char* charA = "A";
    char* charB = "B";
    printf("Comparacion de 'A' y 'B': %d\n", strCompare(charA, charB)); // Esperado: -1
    //3. Strings iguales hasta un car ́acter (hacer cmpStr(s1,s2) y cmpStr(s2,s1)).
    char* s1 = "HelloX";
    char* s2 = "HelloY";
    printf("Comparacion de '%s' y '%s': %d\n", s1, s2, strCompare(s1, s2)); // Esperado: -1
    printf("Comparacion de '%s' y '%s': %d\n", s2, s1, strCompare(s2, s1)); // Esperado: 1
    //4. Dos strings diferentes (hacer cmpStr(s1,s2) y cmpStr(s2,s1)).
    char* diff1 = "Sistema Operativo para para teclado";
    char* diff2 = "Pileta redonda en dias de lluvia";
    printf("Comparacion de '%s' y '%s': %d\n", diff1, diff2, strCompare(diff1, diff2)); // Esperado: 1
    printf("Comparacion de '%s' y '%s': %d\n", diff2, diff1, strCompare(diff2, diff1)); // Esperado: -1
    //strConcatenate:
    //1. Un string vac ́ıo y un string de 3 caracteres.
    char* vacioConcat = "";
    char* tresCaracteres = "abc";
    char* resultadoConcat1 = strConcatenate(strDuplicate(vacioConcat), strDuplicate(tresCaracteres));//el duplicado ya que la funcion deja libre la memoria
    printf("Concatenacion de vacio y 'abc': %s\n", resultadoConcat1);
    //2. Un string de 3 caracteres y un string vac ́ıo.
    char* resultadoConcat2 = strConcatenate(strDuplicate(tresCaracteres), strDuplicate(vacioConcat));
    printf("Concatenacion de 'abc' y vacio: %s\n", resultadoConcat2);
    //3. Dos strings de 1 caracter.
    char* charX = "X";
    char* charY = "Y";
    char* resultadoConcat3 = strConcatenate(strDuplicate(charX), strDuplicate(charY));
    //4. Dos strings de 5 caracteres.
    char* cincoX = "ABCDE";
    char* cincoY = "FGHIJ";
    char* resultadoConcat4 = strConcatenate(strDuplicate(cincoX), strDuplicate(cincoY));
    printf("Concatenacion de '%s' y '%s': %s\n", cincoX, cincoY, resultadoConcat4);
    return 0;
}
