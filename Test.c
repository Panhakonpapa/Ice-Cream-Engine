/*#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int width, height;
    unsigned char* data; // This will hold texture data, which needs to be freed
} Texture;

typedef struct {
    Texture* textures;
    size_t size;
    size_t capacity;
} TextureArray;

// Initialize the texture array
void init_texture_array(TextureArray* array) {
    array->size = 0;
    array->capacity = 10; // Initial capacity
    array->textures = malloc(array->capacity * sizeof(Texture));
}

// Add texture to the array
void add_texture(TextureArray* array, Texture texture) {
    if (array->size == array->capacity) {
        array->capacity *= 2; // Double the capacity
        array->textures = realloc(array->textures, array->capacity * sizeof(Texture));
    }
    array->textures[array->size++] = texture;
}

// Free a single texture's data
void free_texture(Texture* texture) {
    free(texture->data); // Free the texture data if allocated
}

// Free the texture array
void free_texture_array(TextureArray* array) {
    for (size_t i = 0; i < array->size; i++) {
        free_texture(&array->textures[i]); // Free each texture's data
    }
    free(array->textures); // Free the array itself
}

int main() {
    TextureArray myTextures;
    init_texture_array(&myTextures);
    
    // Example usage: Creating a new texture
    Texture newTexture = {800, 600, malloc(800 * 600 * 4)}; // Assuming RGBA format (4 bytes per pixel)
    if (newTexture.data == NULL) {
        perror("Failed to allocate memory for texture data");
        free_texture_array(&myTextures); // Free any allocated memory before exiting
        return 1;
    }
    
    // Add the new texture to the array
    add_texture(&myTextures, newTexture);
    
    // Clean up
    free_texture_array(&myTextures); // Free all textures and the array
    return 0;
}
*/
