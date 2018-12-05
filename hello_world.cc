
// based on https://gist.github.com/ad8e/dd150b775ae6aa4d5cf1a092e4713add

#include "SkCanvas.h"
#include "SkSurface.h"
#include "SkStream.h"
#include "SkImage.h"
#include "GrBackendSurface.h"
#include "GrContext.h"
#include "gl/GrGLInterface.h"
#include "SDL.h"
#include <GL/gl.h>

#include <iostream>

void draw(SkCanvas* canvas) {
    canvas->clear(SK_ColorWHITE);
    SkPaint paint;
    paint.setTextSize(32.0f);
    paint.setAntiAlias(true);
    paint.setColor(SK_ColorBLACK);
    paint.setStyle(SkPaint::kFill_Style);
    canvas->drawString("Skia Test", 20, 32, paint);
}


int main() {
    uint32_t windowFlags = 0;
    const int kWidth = 960;
    const int kHeight = 640;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
    static const int kStencilBits = 8;  // Skia needs 8 stencil bits
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, kStencilBits);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    static const int kMsaaSampleCount = 4;
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, kMsaaSampleCount);
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    SDL_Window* window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED, kWidth, kHeight, windowFlags);
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, glContext);
    int dw, dh;
    SDL_GL_GetDrawableSize(window, &dw, &dh);
    glViewport(0, 0, dw, dh);
    glClearColor(1, 1, 1, 1);
    glClearStencil(0);
    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    GrContextOptions options;
    auto context = GrContext::MakeGL(nullptr, options);
    GrGLFramebufferInfo framebufferInfo;
    framebufferInfo.fFBOID = 0; // assume default framebuffer
    framebufferInfo.fFormat = GL_RGBA8;

    SkColorType colorType;
    if (kRGBA_8888_GrPixelConfig == kSkia8888_GrPixelConfig) {
        colorType = kRGBA_8888_SkColorType;
    }
    else {
        colorType = kBGRA_8888_SkColorType;
    }
    GrBackendRenderTarget backendRenderTarget(kWidth, kHeight,
        0, // sample count
        0, // stencil bits
        framebufferInfo);

    auto surface = SkSurface::MakeFromBackendRenderTarget(context.get(), backendRenderTarget, kBottomLeft_GrSurfaceOrigin, colorType, nullptr, nullptr);
    if (surface == nullptr) abort();

    auto canvas = surface->getCanvas();
    for (;;) {
        bool quit = false;
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_MOUSEMOTION:
                if (event.motion.state == SDL_PRESSED) {
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.state == SDL_PRESSED) {
                }
                break;
            case SDL_KEYDOWN: {
                SDL_Keycode key = event.key.keysym.sym;
                if (key == SDLK_ESCAPE) {
                    quit= true;
                }
                break;
            }
            case SDL_QUIT:
                quit = true;
                break;
            default:
                break;
            }
        }
        if (quit) {
            break;
        }
        draw(canvas);
        context->flush();
        SDL_GL_SwapWindow(window);
    }
}