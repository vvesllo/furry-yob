#include "../include/Core/App.h"


int main()
{
    App* app = new App{ 1280, 720, "FurryYOB" };

    app->run();

    delete app;
}