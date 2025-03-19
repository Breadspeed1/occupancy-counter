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
    incoming = 0;
    outgoing = 0;
}

float DetectionAlgorithm::filterIncoming(float measurement) {
    //do nothing until we actually add some filtering
    return measurement;
}

void DetectionAlgorithm::updateState(DetectionState newState) {
    //record someone coming in when we change from FALLING to RISING or IDLE
    if (getCurrentState() == DetectionState::FALLING && (newState == DetectionState::RISING || newState == DetectionState::IDLE)) {
        incoming++;
    }
    //record someone leaving when we change from FALLING to RISING or IDLE
    else if (getCurrentState() == DetectionState::RISING && (newState == DetectionState::FALLING || newState == DetectionState::IDLE)) {
        outgoing++;
    }
    
    //clear the rates if we change to idle
    if (newState == DetectionState::IDLE) {
        rateBuf.clear();
    }

    currentState = newState;
}

bool DetectionAlgorithm::push(float measurement, unsigned long millis) {
    observationsSinceEval++;

    //if we havent recorded any data yet avoid crashing by trying to claculate delta with previous
    //element that doesn't exist
    if (largeBuf.isEmpty()) {
        largeBuf.push(measurement);
        rateBuf.push(0);
        lastObservation = millis;
        return;
    }

    float filtered = filterIncoming(measurement);

    //find the raw delta in cm between this measurement and the last one
    float delta = (filtered - largeBuf.at(-1));

    largeBuf.push(filtered);

    //find the most recent rate of change in cm/s
    float deltaSeconds = (lastObservation - millis) / 1000;
    float rate = delta / deltaSeconds;
    rateBuf.push(rate);

    lastObservation = millis;

    //if we are due for a re-evaluation or the distance jumped to the floor, re-evaluate the state.
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
    //check if the change in cm is large enough to justify going straight from FALLING to IDLE
    if (largeBuf.at(-1) - largeBuf.at(-2) > settings.minFallingToIdleDelta && getCurrentState() == DetectionState::FALLING) {
        return DetectionState::IDLE;
    }
    //self explanatory
    else if (rateBuf.avg() > settings.rateDeltaMargin) {
        return DetectionState::RISING;
    }
    else if (rateBuf.avg() < -settings.rateDeltaMargin) {
        return DetectionState::FALLING;
    }
    return DetectionState::IDLE;
}