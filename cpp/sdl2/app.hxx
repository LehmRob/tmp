#ifndef __APP_HXX__
#define __APP_HXX__

#include <SDL.h>

namespace demosdl2 {

class App {
  public:
    static App createApp();
    ~App();
    void loop(void);
    void quit(void);

  private:
    App(SDL_Window *window);

    void signalHandler(int);

    SDL_Window *window;
    bool running;
};

}; // namespace demosdl2

#endif // __APP_HXX__
