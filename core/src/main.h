
#ifndef HEXBOT_MAIN
#define HEXBOT_MAIN

#include "api.h"

#include <memory>
#include <string>
#include <random>

typedef std::shared_ptr<class Hexbot> HexbotPtr;

class Hexbot
{
    public:
        static HexbotPtr& getInstance() { return s_instance; }
    
    public:
        typedef std::function< void(int width, int height, int dataLength, void* data)> SnapshotCallback;
    
    public:
        static int Create(api::LogCallback logCallback,
            api::GetGyroscopeDataCallback getGyroscopeDataCallback,
            api::GetAccelerometerDataCallback getAccelerometerDataCallback,
            api::MoveServoCallback moveServoCallback,
            api::RequestCameraSnapshotCallback requestCameraSnapshotCallback);
    
        Hexbot(api::LogCallback logCallback,
            api::GetGyroscopeDataCallback getGyroscopeDataCallback,
            api::GetAccelerometerDataCallback getAccelerometerDataCallback,
            api::MoveServoCallback moveServoCallback,
            api::RequestCameraSnapshotCallback requestCameraSnapshotCallback);
    
        void update(float dt);
        void cameraSnapshot(int width, int height, int dataLength, void* data);
    
        int randomInt(int a, int b);
        float randomFloat(float a, float b);
    
    public:
        void log(const std::string& data);
        bool getGyroscopeData(float& x, float& y, float& z);
        bool getAccelerometerData(float& x, float& y, float& z);
        bool moveServo(int servo, float angle, float time);
        bool requestCameraSnapshot(SnapshotCallback callback);
        
    private:
        std::random_device m_randomDevice;
        std::mt19937_64 m_randomGen;
        float m_timer;
    
    private:
        static HexbotPtr s_instance;
    
        api::LogCallback m_logCallback;
        api::GetGyroscopeDataCallback m_getGyroscopeDataCallback;
        api::GetAccelerometerDataCallback m_getAccelerometerDataCallback;
        api::MoveServoCallback m_moveServoCallback;
        api::RequestCameraSnapshotCallback m_requestCameraSnapshotCallback;
    
        SnapshotCallback m_currentSnapshotCallback;
    
};

#endif