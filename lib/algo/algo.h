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
        void clear();
};

enum DetectionState {
    RISING,
    FALLING,
    IDLE,
};

struct DetectionSettings {
    //minimum absolute cm/s to decide to change states to RISING/FALLING
    float rateDeltaMargin;

    //minimum delta cm to change from FALLING straight to IDLE
    float minFallingToIdleDelta;
};

class DetectionAlgorithm {
    private:
        DetectionSettings settings;
        CircularBuffer largeBuf;
        CircularBuffer rateBuf;
        int evalCounter = 0;

        int incoming = 0;
        int outgoing = 0;

        unsigned long lastObservation = 0;

        int observationsSinceEval = 0;

        DetectionState currentState = DetectionState::IDLE;

        DetectionState evalState();

        float filterIncoming(float measurement);

        void updateState(DetectionState newState);
    
    public:
        DetectionAlgorithm(float* largeData, int ldlen, float* tempData, int tdlen, DetectionSettings settings): largeBuf(largeData, ldlen), rateBuf(tempData, tdlen), settings(settings) {}

        DetectionState getCurrentState();
        int getIncoming();
        int getOutgoing();
        int getNetIncoming();

        void reset();

        bool push(float measurement, unsigned long millis);
};