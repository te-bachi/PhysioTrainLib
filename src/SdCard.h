/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 02.05.2017
 */

#ifndef __SD_CARD_H__
#define __SD_CARD_H__

#include <inttypes.h>

#include <SPI.h>
#include <SPI.h>
#include <SD.h>
#include <RTClib.h>

#include "Position.h"
#include "Quaternion.h"

class SdCard {

    private:
        static const int    SD_CHIP_SELECT_PIN;
        static const int    LOG_FILE_INDEX_MAX;
        static const char  *LOG_FILE_PREFIX_TEACH;
        static const char  *LOG_FILE_PREFIX_EXERCISE;
        static const char  *LOG_FILE_PREFIX_RESULT;
        static const char  *LOG_FILE_SUFFIX;

        bool        init;
        Sd2Card     card;
        SdVolume    volume;
        File        root;

    public:
                    SdCard();
        virtual     ~SdCard();

        bool        begin();
        bool        isInitialized();

        void        openRoot();
        void        rewindRoot();
        void        closeRoot();

        void        write(File &file, DateTime &t);
        void        write(File &file, Quaternion &upperArmQ, Position &upperArmPos, Quaternion &lowerArmQ, Position &lowerArmPos);

        File        replaceTeachFile(DateTime &t);   // Write
        File        openNextTeachFile();             // Read

        File        openExerciseFile(DateTime &t);   // Write
        File        openNextExerciseFile();          // Read
        void        deleteExerciseFiles();           // Delete all

        File        openResultFile(DateTime &t);     // Write
        File        openNextResultFile();            // Read
        void        deleteResultFiles();             // Delete all

    private:
        String      getDateFileSuffix(DateTime &t);
        void        deleteFiles(String &pattern);
        File        findFile(String &pattern);

        String      getNextTeachFileSuffix();
        String      getNextExerciseFileSuffix();
        String      getNextResultFileSuffix();

};

#endif

