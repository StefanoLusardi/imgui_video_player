#include "application.hpp"

int main(int argc, char **argv)
{
    auto app = tvp::create_application();
    return app->run(argc, argv);
}