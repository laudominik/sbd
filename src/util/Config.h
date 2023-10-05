#pragma once


namespace sbd::util {
    class Config {
    public:
        void switchDebugMode() {
            debugMode = !debugMode;
        }
        bool isDebugModeEnabled(){
            return debugMode;
        }

        static Config& instance(){
            static Config config;
            return config;
        }
    private:
        bool debugMode{false};
    };
}

