#include <cstdio>

#include "app.hxx"

int main(int ac, char **av) {
    demosdl2::App app = demosdl2::App::createApp();

    app.loop();

    app.quit();

    return 0;
}
