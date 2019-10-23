#include "SocoAnalysisManager.hh"
#include "G4RootFileManager.hh"
#include <memory>

SocoAnalysisManager* SocoAnalysisManager::gInstance = nullptr;

SocoAnalysisManager* SocoAnalysisManager::Instance()
{
    if (gInstance == nullptr) {
        gInstance = new SocoAnalysisManager();
    }
    return gInstance;
}

SocoAnalysisManager::SocoAnalysisManager()
    : fFile()
    , fFileMessenger(this)
{
}

G4bool SocoAnalysisManager::Write()
{
    {
        std::lock_guard<std::mutex> lF {fLockFile};
        if (!fFile.is_open()) {
            return false;
        }
        {
            std::lock_guard<std::mutex> lE {fLockEvents};
            for (const auto& event : fEvents) {
                event.write(fFile);
            }
            fEvents.clear();
        }
        fFile.flush();
    }

    return true;
}

void SocoAnalysisManager::Destroy()
{
    fFile.close();
    if (G4Threading::IsMasterThread() && gInstance != nullptr) {
        delete gInstance;
        gInstance = nullptr;
    }
}
void SocoAnalysisManager::SetFileName(const G4String& fileName)
{
    if (!G4Threading::IsMasterThread()) {
        return;
    }

    {
        std::lock_guard<std::mutex> lF {fLockFile};
        fFile.open(fileName + ".evt");

        // Header
        SOCO::EventHeader header = {SOCO::SOCO_EVENT_MAGIC, fEvents.size()};
        fFile.write(reinterpret_cast<const char*>(&header), sizeof(header));

        // Metadata
        SOCO::EventMetadataHeader metadata = {SOCO::SOCO_META_MAGIC, 0};
        std::string metadataData("Generated by g4horus");
        metadata.size = metadataData.size();
        fFile.write(reinterpret_cast<const char*>(&metadata), sizeof(metadata));
        fFile.write(metadataData.c_str(), metadataData.size());

        // Data Start Magic
        fFile.write(reinterpret_cast<const char*>(&SOCO::SOCO_DATA_MAGIC), sizeof(SOCO::SOCO_DATA_MAGIC));

        fFile.flush();
    }
}
