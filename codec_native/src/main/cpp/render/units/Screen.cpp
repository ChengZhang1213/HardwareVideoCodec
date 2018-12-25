//
// Created by mingyi.li on 2018/12/25.
//

#include "../include/Screen.h"
#include "../include/NormalDrawer.h"
#include "../entity/NativeWindow.h"

Screen::Screen() {
    name = __func__;
}

Screen::~Screen() {
    if (drawer) {
        delete drawer;
        drawer = nullptr;
    }
    if (egl) {
        delete egl;
        egl = nullptr;
    }
}

bool Screen::dispatch(Message *msg) {
    switch (msg->what) {
        case EVENT_PIPELINE_PREPARE: {
            NativeWindow *nw = dynamic_cast<NativeWindow *>(msg->obj);
            initWindow(nw->win);
            delete nw;
            return true;
        }
        case EVENT_PIPELINE_DRAW_SCREEN: {
            draw(reinterpret_cast<GLuint>(msg->obj));
            return true;
        }
        default:
            break;
    }
    return false;
}

void Screen::initWindow(ANativeWindow *win) {
    if (!egl) {
        egl = new Egl(EGL_NO_CONTEXT, win);
        drawer = new NormalDrawer();
    }
}

void Screen::draw(GLuint texture) {
    egl->makeCurrent();
    drawer->draw(texture);
    egl->swapBuffers();
}
