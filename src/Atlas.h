#ifndef ATLAS_H
#define ATLAS_H


typedef struct SDL_Rect SDL_Rect;
typedef struct SDL_Texture SDL_Texture;
typedef struct SDL_Renderer SDL_Renderer;

int hash_code(const char *letter, const int num, const int attempt);
int hash(const char *letter, const int prime, const int size);

char **get_alphabet_str();
struct Alpha_Node
{
    SDL_Texture *texture;
    SDL_Rect rect;
    char *key;
};

struct Alpha_Node *new_alpha_node(const char *key, const char *path, SDL_Renderer *renderer);


typedef struct _Atlas
{
    void (*destroy)(struct _Atlas *this);
    void (*insert)(struct _Atlas *this, const char *key, SDL_Renderer *renderer, const char *path);
    struct Alpha_Node *(*search)(struct _Atlas *this, const char *key);
    void (*map)(struct _Atlas *this, SDL_Renderer *renderer);
    void (*render)(struct Alpha_Node *node, SDL_Renderer *renderer);
    struct Alpha_Node **letters;
    int size;
    int count;

} Atlas;
Atlas *CREATE_ATLAS();
void render_letter(void *obj, SDL_Renderer *renderer);
#endif /* ATLAS_H */
