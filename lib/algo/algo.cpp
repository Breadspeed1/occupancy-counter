#include "algo.h"

DetectionState DetectionAlgorithm::getCurrentState() {
    return currentState;
}

int DetectionAlgorithm::getIncoming() {
    return incoming;
}

int DetectionAlgorithm::getOutgoing() {
    return outgoing;
}

int DetectionAlgorithm::getNetIncoming() {
    return incoming - outgoing;
}

void DetectionAlgorithm::reset() {
    this->currentState = DetectionState::IDLE;
    rateBuf.clear();
    largeBuf.clear();
}

float DetectionAlgorithm::filterIncoming(float measurement) {
    //do nothing until we actually add some filtering
    return measurement;
}

void DetectionAlgorithm::updateState(DetectionState newState) {
    if (getCurrentState() == DetectionState::FALLING && (newState == DetectionState::RISING || newState == DetectionState::IDLE)) {
        incoming++;
    }
    else if (getCurrentState() == DetectionState::RISING && (newState == DetectionState::FALLING || newState == DetectionState::IDLE)) {
        outgoing++;
    }
    
    if (newState == DetectionState::IDLE) {
        rateBuf.clear();
    }

    currentState = newState;
}

bool DetectionAlgorithm::push(float measurement, unsigned long millis) {
    observationsSinceEval++;

    if (largeBuf.isEmpty()) {
        largeBuf.push(measurement);
        rateBuf.push(0);
        lastObservation = millis;
        return;
    }

    float filtered = filterIncoming(measurement);

    float delta = (filtered - largeBuf.at(-1));

    largeBuf.push(filtered);

    float deltaSeconds = (lastObservation - millis) / 1000;
    float rate = delta / deltaSeconds;
    rateBuf.push(rate);

    lastObservation = millis;

    if (observationsSinceEval == rateBuf.len() || delta > settings.minFallingToIdleDelta) {
        observationsSinceEval = 0;
        DetectionState evaluated = evalState();
        bool changed = evaluated != getCurrentState();

        if (changed) updateState(evaluated);
        return changed;
    }

    return false;
}

DetectionState DetectionAlgorithm::evalState() {
    if (largeBuf.at(-1) - largeBuf.at(-2) > settings.minFallingToIdleDelta && getCurrentState() == DetectionState::FALLING) {
        return DetectionState::IDLE;
    }
    else if (rateBuf.avg() > settings.rateDeltaMargin) {
        return DetectionState::RISING;
    }
    else if (rateBuf.avg() < -settings.rateDeltaMargin) {
        return DetectionState::FALLING;
    }
    return DetectionState::IDLE;
}