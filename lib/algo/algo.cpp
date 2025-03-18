#include "algo.h"

DetectionAlgorithm::DetectionAlgorithm(float* largeData, int ldlen, float* tempData, int tdlen, DetectionSettings settings) {
    this->settings = settings;
    this->largeBuf = CircularBuffer(largeData, ldlen);
    this->tempBuf = CircularBuffer(tempData, tdlen);
}