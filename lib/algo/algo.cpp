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
    this->currentState = DetectionState::IDLE;
}

bool DetectionAlgorithm::push(float measurement) {
    throw "not implemented";
}

DetectionState DetectionAlgorithm::evalState() {
    if (tempBuf.avg() > settings.changeMargin) {
        return DetectionState::RISING;
    }
    else if (tempBuf.avg() < -settings.changeMargin) {
        return DetectionState::FALLING;
    }
    return DetectionState::IDLE;
}