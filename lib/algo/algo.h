
class CircularBuffer {
    private:
        int size = 0;
        int start = 0;
        int length;
        float* data;

        int wrap(int index);

    public:
        CircularBuffer(float* data, int length);
        void push(float value);
        float pop();
        float at(int i);
        bool isEmpty();
        int count();
};