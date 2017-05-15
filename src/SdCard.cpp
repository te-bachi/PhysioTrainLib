/*******************************************************************************
 * PhysioTrain (c) 2017
 * Andreas Bachmann
 * 07.04.2017
 */

#include "config.h"
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
    //pinMode(SD_CHIP_SELECT_PIN, OUTPUT);

    if (!SD.begin(SD_CHIP_SELECT_PIN)) {
        SerialUSB.println("SD.begin(SD_CHIP_SELECT_PIN) failed!");
        return false;
    }

    /*
    if (!card.init(SPI_HALF_SPEED, SD_CHIP_SELECT_PIN)) {
        SerialUSB.println("SD.begin(SD_CHIP_SELECT_PIN) failed!");
      return false;
    }

    if (!volume.init(card)) {
        SerialUSB.println("SD.begin(SD_CHIP_SELECT_PIN) failed!");
      return false;
    }
    */

    init = true;

    // Can't create new file when opened!!
    ///root = SD.open("/");

    SerialUSB.println("SdCard::begin() end");
    return true;
}

bool
SdCard::isInitialized()
{
    return init;
}

void
SdCard::openRoot()
{
    root = SD.open("/");
}

void
SdCard::rewindRoot()
{
    root.rewindDirectory();
}

void
SdCard::closeRoot()
{
    root.close();
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


/******************************************************************************
 * Teach file
 */
File
SdCard::replaceTeachFile(DateTime &t)
{
    String filename;


//    String pattern = LOG_FILE_PREFIX_TEACH;
//
//    rewindRoot();
//    File   file    = findFile(pattern);
//
//    /*  If the file exists, delete file first */
//    if (file) {
//        filename = file.name();
//        file.close();
//        SD.remove(filename);
//    }

    /* Create new file */
    //filename  = String(LOG_FILE_PREFIX_TEACH);
    //filename += getDateFileSuffix(t);
    filename  = getNextTeachFileSuffix();
    //filename += String(LOG_FILE_SUFFIX);

    SerialUSB.print("replaceTeachFile: ");
    SerialUSB.println(filename);

    File file = SD.open(filename, FILE_WRITE);
    if (file) {
        file.print(String("test 123"));
        SerialUSB.println("Write done!");
    } else {
        SerialUSB.println("Write failed!");
    }

    return file;
}

File
SdCard::openNextTeachFile()
{
    String pattern = String(LOG_FILE_PREFIX_TEACH);
    return findFile(pattern);
}

/******************************************************************************
 * Exercise file
 */
File
SdCard::openExerciseFile(DateTime &t)
{
    String filename;

    /* Create new file */
    filename  = String(LOG_FILE_PREFIX_EXERCISE);
    //filename += getDateFileSuffix(t);
    filename += getNextExerciseFileSuffix();
    filename += String(LOG_FILE_SUFFIX);

    SerialUSB.print("openExerciseFile: ");
    SerialUSB.println(filename);

    return SD.open(filename.c_str(), FILE_WRITE);
}

File
SdCard::openNextExerciseFile()
{
    String pattern = LOG_FILE_PREFIX_EXERCISE;
    return findFile(pattern);
}

void
SdCard::deleteExerciseFiles()
{
    String pattern = LOG_FILE_PREFIX_EXERCISE;
    deleteFiles(pattern);
}

/******************************************************************************
 * Result file
 */
File
SdCard::openResultFile(DateTime &t)
{
    String filename;

    /* Create new file */
    filename  = String(LOG_FILE_PREFIX_RESULT);
    //filename += getDateFileSuffix(t);
    filename += getNextExerciseFileSuffix();
    filename += String(LOG_FILE_SUFFIX);

    return SD.open(filename.c_str(), FILE_WRITE);
}

File
SdCard::openNextResultFile()
{
    String pattern = LOG_FILE_PREFIX_RESULT;
    return findFile(pattern);
}

void
SdCard::deleteResultFiles()
{
    String pattern = LOG_FILE_PREFIX_RESULT;
    deleteFiles(pattern);
}


/******************************************************************************
 * Private methods
 */

String
SdCard::getDateFileSuffix(DateTime &t)
{
    char buf[32];

    sprintf(buf, "%04d_%02d_%02d_%02d_%02d_%02d", t.year(), t.month(),  t.day(),
                                                  t.hour(), t.minute(), t.second());

    return String(buf);
}

void
SdCard::deleteFiles(String &pattern)
{
    File    entry;
    bool    removeFile;
    String  filename;

    /*** REWIND ***/
    root.rewindDirectory();

    while (true) {
        removeFile = false;
        entry      = root.openNextFile(FILE_READ);

        /* EOF */
        if (!entry) {
            break;
        }

        /* Is directory */
        if (entry.isDirectory()) {
            // no nothing

        /* Is regular file */
        } else {
            filename = entry.name();
            if (filename.startsWith(pattern)) {
                removeFile = true;
            }
        }

        entry.close();

        /* Remove permanently */
        if (removeFile) {
            SD.remove(filename.c_str());
        }
    }
}

File
SdCard::findFile(String &pattern)
{
    File    entry;
    String  filename;

    /*** DON'T REWIND => CONTINUE ***/

    while (true) {
        entry  = root.openNextFile(FILE_READ);

        /* EOF */
        if (!entry) {
            break;
        }

        /* Is directory */
        if (entry.isDirectory()) {
            // no nothing

        /* Is regular file */
        } else {
            filename = entry.name();
            if (filename.startsWith(pattern)) {
                /* Return opened file */
                return entry;
            }
        }

        entry.close();
    }
    return File();
}

String
SdCard::getNextTeachFileSuffix()
{
    String      filename;
    int         i;

    for (i = 0; i < LOG_FILE_INDEX_MAX; i++) {

        /* Construct a file with FOLDER/PREFIX[Index].SUFFIX */
        filename  = String(LOG_FILE_PREFIX_TEACH);
        filename += String(i);
        filename += String(LOG_FILE_SUFFIX);

        /*  If the file name doesn't exist, return it */
        if (!SD.exists(filename)) {
            return filename;
        }

        /* Otherwise increment the index, and try again */
        i++;
    }

    return "";
}

String
SdCard::getNextExerciseFileSuffix()
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
            return filename;
        }

        /* Otherwise increment the index, and try again */
        i++;
    }

    return "";
}

/**
 * Find the next available log file. Or return a null string
 * if we've reached the maximum file limit.
 */
String
SdCard::getNextResultFileSuffix()
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
            return filename;
        }

        /* Otherwise increment the index, and try again */
        i++;
    }

    return "";
}
