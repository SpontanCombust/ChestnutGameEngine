#pragma once


#ifdef _WIN32
    #ifdef ChestnutGameEngine_EXPORTS
        #define CHESTNUT_API __declspec(dllexport)
    #else
        #define CHESTNUT_API __declspec(dllimport)
    #endif
#else
    #define CHESTNUT_API
#endif

// initial vertex capacity of the (colored) polygon renderer
#define CHESTNUT_POLYGON_RENDERER_INIT_VERTEX_CAPACITY 100 

// initial index capacity of the (colored) polygon renderer
#define CHESTNUT_POLYGON_RENDERER_INIT_INDEX_CAPACITY 150 


// initial sprite capacity of the sprite renderer
#define CHESTNUT_SPRITE_RENDERER_INIT_SPRITE_CAPACITY 100


// initial glyph capacity of the text renderer
#define CHESTNUT_TEXT_RENDERER_INIT_GLYPH_CAPACITY 128 


// point size of the initializing font configuration
#define CHESTNUT_FONT_RESOURCE_INIT_FONT_POINT_SIZE 16 

// style of the initializing font configuration
#define CHESTNUT_FONT_RESOURCE_INIT_FONT_STYLE EFontStyle::NORMAL 


// Causes the system thread to halt until GPU finishes processing current frame
// If not enabled can cause hard problems 
// When testing with low-demand setup, not enabling it lead to complete freeze on my Ubuntu laptop
// This applies if you don't set a hard framerate limit in the engine
#define CHESTNUT_SIMPLE2D_RENDERING_SYSTEM_FORCE_GPU_SYNCHRONIZATION 1


#ifdef _WIN32
    #define CHESTNUT_ENGINE_ASSETS_DIR_PATH "../../assets"
#else
    #define CHESTNUT_ENGINE_ASSETS_DIR_PATH "../assets"
#endif

