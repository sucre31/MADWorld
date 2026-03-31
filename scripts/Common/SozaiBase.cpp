#include "SozaiBase.h"

void SozaiBase::setSozaiManager(SozaiManager* manager) {
	sozaiManager = manager;
}

void SozaiBase::setActive(bool flag) {
    isActive = flag;
    if (flag) {
        setLayerFront();
        setKey();
    }
    else {
        setLayerBack();
        resetKey();
    }
}

void SozaiBase::setLayerFront() {
    for (auto& p : sozaiHandles) {
        sozaiManager->setSozaiLayer(p.second, 1);
        sozaiManager->setReverseFlag(p.second, false);
    }
}

void SozaiBase::setLayerBack() {
    for (auto& p : sozaiHandles) {
        sozaiManager->setSozaiLayer(p.second, -1);
        sozaiManager->setReverseFlag(p.second, false);
    }
}


void SozaiBase::resetKey() {
    for (auto& p : sozaiHandles) {
        sozaiManager->resetSozaiKey(p.second);
    }
}