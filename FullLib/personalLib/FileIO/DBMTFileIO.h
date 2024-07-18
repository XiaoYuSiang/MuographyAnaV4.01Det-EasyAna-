#include <TFile.h>
#include <TKey.h>
#include <TDirectory.h>
#include <iostream>
#include <map>
#include <vector>

void keepLastObjectWithSameName(const char* fileName, const char* objectName) {
    // Open the file in UPDATE mode
    TFile* file = TFile::Open(fileName, "UPDATE");
    if (!file || file->IsZombie()) {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return;
    }

    // Get the list of all keys
    TList* keyList = file->GetListOfKeys();
    std::map<std::string, std::vector<TKey*> > objectMap;

    // Populate the map with object names and their keys
    TIter next(keyList);
    TKey* key;
    while ((key = (TKey*)next())) {
        std::string keyName = key->GetName();
        if (keyName == objectName) {
            objectMap[keyName].push_back(key);
        }
    }

    // If there are objects with the same name
    if (objectMap.find(objectName) != objectMap.end()) {
        std::vector<TKey*>& keys = objectMap[objectName];
        if (keys.size() > 1) {
            // Delete all but the last object with the same name
            for (size_t i = 0; i < keys.size() - 1; ++i) {
                file->Delete(Form("%s;%d", objectName, keys[i]->GetCycle()));
            }
        }
    }

    // Write changes to the file and close it
    file->Write();
    file->Close();
    delete file;

    std::cout << "Only the last object with the name " << objectName << " has been retained in the file: " << fileName << std::endl;
}
