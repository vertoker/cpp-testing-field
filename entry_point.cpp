// Perfect entry point
// https://github.com/gustavo-tomas/Magnolia (entry_point.hpp)

namespace engine {
    class application {
    public:
        static application* create() { return new application(); }

        void run() {

        }
    };
}

int main(int argc, char* argv[]) {
    // Ignore unused parameters warning
    (void)argc;
    (void)argv;

    auto app = engine::application::create();
    app->run();
    delete app;

    return 0;
}