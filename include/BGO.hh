#ifndef BGO_HH
#define BGO_HH

#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"

class BGO
{
public:
  BGO(G4String name);
  ~BGO();

  G4LogicalVolume* GetLogical() { return mother_lv; }
  G4double GetLength() { return full_length; }
  G4double GetOverlapLength() { return overlap_length; }

private:
  G4LogicalVolume* mother_lv;
  G4double full_length;
  G4double overlap_length;

};

#endif
