
//  main.c
//  GB Image Viewer
//  [23/01/2017]

#include <gb/gb.h>

#define IMAGE_AMOUNT 7
UINT8 currentState, currentImage;
extern UINT8 slide1, slide1_map;
extern UINT8 slide2, slide2_map;
extern UINT8 slide3, slide3_map;
extern UINT8 slide4, slide4_map;
extern UINT8 slide5, slide5_map;
extern UINT8 slide6, slide6_map;
extern UINT8 slide7, slide7_map;
UINT8 fadeStage;

void fade_out(void) {
    fadeStage = 0;
    while(1) {
        switch(fadeStage) {
            case 0: BGP_REG = 0xE4; break;
            case 1: BGP_REG = 0x90; break;
            case 2: BGP_REG = 0x40; break;
            case 3: BGP_REG = 0x00; break;
        }
        fadeStage++;
        if (fadeStage == 4) break;
        delay(80);
        wait_vbl_done();
    }
}

void fade_in(void) {
    fadeStage = 0;
    while(1) {
        switch(fadeStage) {
            case 0: BGP_REG = 0x00; break;
            case 1: BGP_REG = 0x40; break;
            case 2: BGP_REG = 0x90; break;
            case 3: BGP_REG = 0xE4; break;
        }
        fadeStage++;
        if (fadeStage == 4) break;
        delay(80);
        wait_vbl_done();
    }
}

void displayImage(UINT8 image)NONBANKED {
    switch (image) {
        case 0: {
            set_bkg_data(0, 0, &slide1);
            set_bkg_tiles(0, 0, 20, 18, &slide1_map);
            break; }
        case 1: {
            set_bkg_data(0, 0, &slide2);
            set_bkg_tiles(0, 0, 20, 18, &slide2_map);
            break; }
        case 2: {
            set_bkg_data(0, 0, &slide3);
            set_bkg_tiles(0, 0, 20, 18, &slide3_map);
            break; }
        case 3: {
            set_bkg_data(0, 0, &slide4);
            set_bkg_tiles(0, 0, 20, 18, &slide4_map);
            break; }
        case 4: {
            set_bkg_data(0, 0, &slide5);
            set_bkg_tiles(0, 0, 20, 18, &slide5_map);
            break; }
        case 5: {
            set_bkg_data(0, 0, &slide6);
            set_bkg_tiles(0, 0, 20, 18, &slide6_map);
            break; }
        case 6: {
            set_bkg_data(0, 0, &slide7);
            set_bkg_tiles(0, 0, 20, 18, &slide7_map);
            break; }
    }
}

void main(void)NONBANKED {
    
    // start up
    HIDE_BKG;
    currentState = 0;
    currentImage = 0;
    displayImage(currentImage);
    SHOW_BKG;
    fade_in();
    
    // main loop
    for (;;) {
        switch (currentState) {
            case 0: { // wait
                if (joypad() & J_A) {
                    currentImage++;
                    if (currentImage == IMAGE_AMOUNT) currentImage = 0;
                    currentState = 1;
                }
                break; }
            case 1: { // transition
                fade_out();
                HIDE_BKG;
                disable_interrupts();
                displayImage(currentImage);
                SHOW_BKG;
                enable_interrupts();
                currentState = 0;
                fade_in();
                break; }
        }
    }
    
}
