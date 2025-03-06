#include "algo.h"

int CircularBuffer::wrap(int index) {
    index %= length;

    if (index < 0) index += length;

    return index;
}

CircularBuffer::CircularBuffer(float* data, int length) {
    this->data = data;
    this->length = length;
}

void CircularBuffer::push(float value) {
    int i = wrap(start + size);
    data[i] = value;

    if (size < length) size++;
    else start = wrap(start + 1);
}

float CircularBuffer::pop() {
    if (isEmpty()) throw "Cannot pop on empty buffer";
    int i = wrap(start + size - 1);
    size--;

    return data[i];
}

float CircularBuffer::at(int i) {
    int index = wrap(start + i);
    if (index >= length) throw "Cannot access index out of range";
    return data[i];
}

bool CircularBuffer::isEmpty() {
    return size < 1;
}