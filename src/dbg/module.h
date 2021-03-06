#ifndef _MODULE_H
#define _MODULE_H

#include "_global.h"

struct MODSECTIONINFO
{
    duint addr;      // Virtual address
    duint size;      // Virtual size
    char name[MAX_SECTION_SIZE * 5];  // Escaped section name
};

struct MODIMPORTINFO
{
    duint addr;     // Virtual address
    char name[MAX_IMPORT_SIZE];
    char moduleName[MAX_MODULE_SIZE];
};

struct MODINFO
{
    duint base = 0;  // Module base
    duint size = 0;  // Module size
    duint hash = 0;  // Full module name hash
    duint entry = 0; // Entry point

    char name[MAX_MODULE_SIZE];         // Module name (without extension)
    char extension[MAX_MODULE_SIZE];    // File extension
    char path[MAX_PATH];                // File path (in UTF8)

    std::vector<MODSECTIONINFO> sections;
    std::vector<MODIMPORTINFO> imports;

    HANDLE fileHandle = nullptr;
    DWORD loadedSize = 0;
    HANDLE fileMap = nullptr;
    ULONG_PTR fileMapVA = 0;

    int party;  // Party. Currently used value: 0: User, 1: System

    MODINFO()
    {
        memset(name, 0, sizeof(name));
        memset(extension, 0, sizeof(extension));
        memset(path, 0, sizeof(path));
    }
};

bool ModLoad(duint Base, duint Size, const char* FullPath);
bool ModUnload(duint Base);
void ModClear();
MODINFO* ModInfoFromAddr(duint Address);
bool ModNameFromAddr(duint Address, char* Name, bool Extension);
duint ModBaseFromAddr(duint Address);
duint ModHashFromAddr(duint Address);
duint ModHashFromName(const char* Module);
duint ModContentHashFromAddr(duint Address);
duint ModBaseFromName(const char* Module);
duint ModSizeFromAddr(duint Address);
std::string ModNameFromHash(duint Hash);
bool ModSectionsFromAddr(duint Address, std::vector<MODSECTIONINFO>* Sections);
bool ModImportsFromAddr(duint Address, std::vector<MODIMPORTINFO>* Imports);
duint ModEntryFromAddr(duint Address);
int ModPathFromAddr(duint Address, char* Path, int Size);
int ModPathFromName(const char* Module, char* Path, int Size);
void ModGetList(std::vector<MODINFO> & list);
int ModGetParty(duint Address);
void ModSetParty(duint Address, int Party);
bool ModAddImportToModule(duint Base, const MODIMPORTINFO & importInfo);

#endif // _MODULE_H
