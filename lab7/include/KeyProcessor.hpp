#pragma once

class KeyProcessor {
public:
    enum Mode {
        ORIGINAL = 0,
        GRAY,
        BLUR,
        CANNY,
        INVERT,
        SOBEL,
        THRESHOLD
    };

    Mode process(int key);
};
