#pragma once

#include "G4UserRunAction.hh"

class G4Run;

class RunActionSoco : public G4UserRunAction {
  public:
    RunActionSoco();
    ~RunActionSoco() override;
    RunActionSoco(const RunActionSoco&) = delete;
    RunActionSoco(RunActionSoco&&) = delete;
    RunActionSoco& operator=(const RunActionSoco&) = delete;
    RunActionSoco& operator=(RunActionSoco&&) = delete;

    void BeginOfRunAction(const G4Run* /*aRun*/) override;
    void EndOfRunAction(const G4Run* /*aRun*/) override;
};
