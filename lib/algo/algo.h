class CircularBuffer {
    private:
        int size = 0;
        int start = 0;
        int length;
        float* data;
        float sum = 0;

        int wrap(int index);

    public:
        CircularBuffer(float* data, int length): data(data), length(length) {};
        void push(float value);
        float pop();
        float at(int i);
        bool isEmpty();
        int count();
        float avg();
        int len();
};

enum DetectionState {
    RISING,
    FALLING,
    IDLE,
};

struct DetectionSettings {

};

class DetectionAlgorithm {
    private:
        DetectionSettings settings;
        CircularBuffer largeBuf;
        CircularBuffer tempBuf;
        int evalCounter = 0;

        int entranceCount = 0;
        int exitCount = 0;

        DetectionState currentState = DetectionState::IDLE;

        bool evalState();
    
    public:
        DetectionAlgorithm(float* largeData, int ldlen, float* tempData, int tdlen, DetectionSettings settings): largeBuf(largeData, ldlen), tempBuf(tempData, tdlen), settings(settings) {}

        DetectionState getCurrentState();
        int getEntranceCount();
        int getExitCount();
        int getCurrentOccupancy();

        void reset();

        bool push(float measurement);
};