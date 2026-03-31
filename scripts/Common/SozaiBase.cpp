#include <Dxlib.h>
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
    }
}

void SozaiBase::setLayerBack() {
    for (auto& p : sozaiHandles) {
        sozaiManager->setSozaiLayer(p.second, -1);
    }
}


void SozaiBase::resetKey() {
    for (auto& p : sozaiHandles) {
        sozaiManager->resetSozaiKey(p.second);
    }
}