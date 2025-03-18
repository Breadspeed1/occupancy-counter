#include "algo.h"

int CircularBuffer::wrap(int index) {
    index %= length;

    if (index < 0) index += length;

    return index;
}

CircularBuffer::CircularBuffer(float* data, int length) {
    this->data = data;
    this->length = length;
    this->sum = 0;
}

void CircularBuffer::push(float value) {
    int i = wrap(start + size);
    float temp = data[i];
    data[i] = value;

    if (size < length) {
        sum += value;
        size++;
    }
    else {
        sum += value - temp;
        start = wrap(start + 1);
    }
}

float CircularBuffer::pop() {
    if (isEmpty()) throw "Cannot pop on empty buffer";
    int i = wrap(start + --size);
    sum -= data[i];

    return data[i];
}

float CircularBuffer::at(int i) {
    if (i >= size || -i >= size) throw "Cannot access index out of range";
    int index = wrap(start + i);
    return data[index];
}

bool CircularBuffer::isEmpty() {
    return size < 1;
}

int CircularBuffer::count() {
    return size;
}

float CircularBuffer::avg() {
    return sum / size;
}