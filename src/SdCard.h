/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 02.05.2017
 */

#ifndef __SD_CARD_H__
#define __SD_CARD_H__

#include <SPI.h>
#include <SD.h>

#include "PhysioTrain.h"
#include "Position.h"
#include "Quaternion.h"

class SdCard {

    private:
        static const int    SD_CHIP_SELECT_PIN;
        static const int    LOG_FILE_INDEX_MAX;
        static const char  *LOG_FILE_PREFIX_TEACH;
        static const char  *LOG_FILE_PREFIX_EXERCISE;
        static const char  *LOG_FILE_SUFFIX;

        bool        init;
        Sd2Card     card;
        SdVolume    volume;
        SdFile      root;

    public:
                    SdCard();
        virtual     ~SdCard();

        bool        begin();
        bool        isInitialized();
//        File        openRead(PhysioTrain::Mode mode);
//        File        openWrite(PhysioTrain::Mode mode);
        void        close(File &file);
        void        write(File &file, Quaternion &upperArmQ, Position &upperArmPos, Quaternion &lowerArmQ, Position &lowerArmPos);

        File        openTeachFile(bool *error);
        File        replaceTeachFile();
        File        openNextExerciseFile(bool *error);
        void        deleteExerciseFiles();

    private:
        String      getNextExerciseFile(bool *error);
};

#endif

