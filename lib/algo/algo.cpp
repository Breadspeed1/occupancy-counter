#include "algo.h"

DetectionState DetectionAlgorithm::getCurrentState() {
    return currentState;
}

int DetectionAlgorithm::getEntranceCount() {
    return entranceCount;
}

int DetectionAlgorithm::getExitCount() {
    return exitCount;
}

int DetectionAlgorithm::getCurrentOccupancy() {
    return entranceCount - exitCount;
}

void DetectionAlgorithm::reset() {
    throw "not implemented";
}

bool DetectionAlgorithm::push(float measurement) {
    throw "not implemented";
}

bool DetectionAlgorithm::evalState() {
    throw "not implemented";
}