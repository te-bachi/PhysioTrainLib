/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 07.04.2017
 */

#include "SdCard.h"


const int    SdCard::SD_CHIP_SELECT_PIN         = 38;
const int    SdCard::LOG_FILE_INDEX_MAX         = 1024;
const char  *SdCard::LOG_FILE_PREFIX_TEACH      = "teach";
const char  *SdCard::LOG_FILE_PREFIX_EXERCISE   = "exercise_";
const char  *SdCard::LOG_FILE_PREFIX_RESULT     = "result_";
const char  *SdCard::LOG_FILE_SUFFIX            = ".txt";


SdCard::SdCard()
: init(false)
{
    //
}

SdCard::~SdCard()
{
    //
}


bool
SdCard::begin()
{
    if (!SD.begin(SD_CHIP_SELECT_PIN)) {
      return false;
    }

    if (!card.init(SPI_HALF_SPEED, SD_CHIP_SELECT_PIN)) {
      return false;
    }

    if (!volume.init(card)) {
      return false;
    }

    init = true;

    return true;
}

bool
SdCard::isInitialized()
{
    return init;
}

//File
//SdCard::openRead(PhysioTrain::Mode mode)
//{
//    if (PhysioTrain::MODE == PhysioTrain::TEACH) {
//        //file = SD.open(logFileName.c_str(), FILE_WRITE);
//
//    } else {
//        //file = SD.open(logFileName.c_str(), FILE_WRITE);
//
//    }
//}
//
//
//File
//SdCard::openWrite(PhysioTrain::Mode mode)
//{
//    if ()
//    file = SD.open(logFileName.c_str(), FILE_WRITE);
//}

void
SdCard::close(File &file)
{
    /*
    myFile = SD.open(logFileName.c_str(), FILE_WRITE);
    String data = "";
    data += logFileName;
    data += "\r\nbla";
    myFile.write(data.c_str(), data.length());
    myFile.close();
    logFileName = nextLogFile();
    break;
    */
}

void
SdCard::write(File &file, Quaternion &upperArmQ, Position &upperArmPos, Quaternion &lowerArmQ, Position &lowerArmPos)
{
    /*
    myFile = SD.open(logFileName.c_str(), FILE_WRITE);
    String data = "";
    data += logFileName;
    data += "\r\nbla";
    myFile.write(data.c_str(), data.length());
    myFile.close();
    logFileName = nextLogFile();
    break;
    */

}

File
SdCard::openTeachFile(bool *error)
{
    String filename;
    filename  = String(LOG_FILE_PREFIX_TEACH);
    filename += String(LOG_FILE_SUFFIX);

    /* Check if file exists => error */
    if (SD.exists(filename.c_str())) {
        *error = true;
        return File();
    }

    return SD.open(filename.c_str(), FILE_WRITE);
}

File
SdCard::replaceTeachFile()
{
    String filename;
    filename  = String(LOG_FILE_PREFIX_TEACH);
    filename += String(LOG_FILE_SUFFIX);

    /*  If the file exists, delete file first */
    if (SD.exists(filename.c_str())) {
        SD.remove(filename.c_str());
    }

    return SD.open(filename.c_str(), FILE_WRITE);
}

File
SdCard::openNextExerciseFile(bool *error)
{
    String filename = getNextExerciseFile(error);

    return SD.open(filename.c_str(), FILE_WRITE);
}

File
SdCard::openNextResultFile(bool *error)
{
    String filename = getNextExerciseFile(error);

    return SD.open(filename.c_str(), FILE_WRITE);
}

void
SdCard::deleteExerciseFiles()
{
    String      filename;
    int         i;

    for (i = 0; i < LOG_FILE_INDEX_MAX; i++) {

        /* Construct a file with FOLDER/PREFIX[Index].SUFFIX */
        filename  = String(LOG_FILE_PREFIX_EXERCISE);
        filename += String(i);
        filename += String(LOG_FILE_SUFFIX);

        /*  If the file name doesn't exist, return it */
        if (!SD.exists(filename)) {
            return;
        }

        SD.remove(filename.c_str());

        /* Otherwise increment the index, and try again */
        i++;
    }
}

/**
 * Find the next available log file. Or return a null string
 * if we've reached the maximum file limit.
 */
String
SdCard::getNextExerciseFile(bool *error)
{
    String      filename;
    int         i;

    for (i = 0; i < LOG_FILE_INDEX_MAX; i++) {

        /* Construct a file with FOLDER/PREFIX[Index].SUFFIX */
        filename = String(LOG_FILE_PREFIX_EXERCISE);
        filename += String(i);
        filename += String(LOG_FILE_SUFFIX);

        /*  If the file name doesn't exist, return it */
        if (!SD.exists(filename)) {
            *error = false;
            return filename;
        }

        /* Otherwise increment the index, and try again */
        i++;
    }

    *error = true;
    return "";
}

/**
 * Find the next available log file. Or return a null string
 * if we've reached the maximum file limit.
 */
String
SdCard::getNextResultFile(bool *error)
{
    String      filename;
    int         i;

    for (i = 0; i < LOG_FILE_INDEX_MAX; i++) {

        /* Construct a file with FOLDER/PREFIX[Index].SUFFIX */
        filename = String(LOG_FILE_PREFIX_RESULT);
        filename += String(i);
        filename += String(LOG_FILE_SUFFIX);

        /*  If the file name doesn't exist, return it */
        if (!SD.exists(filename)) {
            *error = false;
            return filename;
        }

        /* Otherwise increment the index, and try again */
        i++;
    }

    *error = true;
    return "";
}
