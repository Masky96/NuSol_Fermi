//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file optical/CSat/src/CSatTrajectory.cc
/// \brief Implementation of the CSatTrajectory class
//
//
#include "CSatTrajectory.hh"

#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleTypes.hh"
#include "G4Polyline.hh"
#include "G4Polymarker.hh"
#include "G4ThreeVector.hh"
#include "G4Trajectory.hh"
#include "G4TrajectoryPoint.hh"
#include "G4VisAttributes.hh"
#include "G4VVisManager.hh"

G4ThreadLocal G4Allocator<CSatTrajectory>* CSatTrajectoryAllocator = nullptr;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CSatTrajectory::CSatTrajectory()
  : G4Trajectory()
  , fWls(false)
  , fDrawit(false)
  , fForceNoDraw(false)
  , fForceDraw(false)
{
  fParticleDefinition = nullptr;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CSatTrajectory::CSatTrajectory(const G4Track* aTrack)
  : G4Trajectory(aTrack)
  , fWls(false)
  , fDrawit(false)
{
  fParticleDefinition = aTrack->GetDefinition();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CSatTrajectory::CSatTrajectory(CSatTrajectory& right)
  : G4Trajectory(right)
  , fWls(right.fWls)
  , fDrawit(right.fDrawit)
{
  fParticleDefinition = right.fParticleDefinition;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

CSatTrajectory::~CSatTrajectory() {}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void CSatTrajectory::DrawTrajectory() const
{
  // Taken from G4VTrajectory and modified to select colours based on particle
  // type and to selectively eliminate drawing of certain trajectories.

  if(!fForceDraw && (!fDrawit || fForceNoDraw))
    return;

  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(!pVVisManager)
    return;

  const G4double markerSize = 0.05;
  G4bool lineRequired       = true;
  G4bool markersRequired    = true;

  G4Polyline trajectoryLine;
  G4Polymarker stepPoints;
  G4Polymarker auxiliaryPoints;

  for(G4int i = 0; i < GetPointEntries(); ++i)
  {
    G4VTrajectoryPoint* aTrajectoryPoint = GetPoint(i);
    const std::vector<G4ThreeVector>* auxiliaries =
      aTrajectoryPoint->GetAuxiliaryPoints();
    if(auxiliaries)
    {
      for(size_t iAux = 0; iAux < auxiliaries->size(); ++iAux)
      {
        const G4ThreeVector pos((*auxiliaries)[iAux]);
        if(lineRequired)
        {
          trajectoryLine.push_back(pos);
        }
        if(markersRequired)
        {
          auxiliaryPoints.push_back(pos);
        }
      }
    }
    const G4ThreeVector pos(aTrajectoryPoint->GetPosition());
    if(lineRequired)
    {
      trajectoryLine.push_back(pos);
    }
    if(markersRequired)
    {
      stepPoints.push_back(pos);
    }
  }

  if(lineRequired)
  {
    G4Colour colour;

    if(fParticleDefinition == G4OpticalPhoton::OpticalPhotonDefinition())
      {
	colour = G4Colour(0., 1.0, 0.0); // Green
      }
    else if(fParticleDefinition == G4Gamma::GammaDefinition())
      {
	colour = G4Color(1.0, 0.0, 1.0); //Magenta
      }
    else if(fParticleDefinition == G4Electron::ElectronDefinition())
      {
	colour = G4Color(1.0, 0.0, 0.0); //Red
      }
    else if(fParticleDefinition == G4Positron::PositronDefinition())
      {
	colour = G4Color(0.0, 0.0, 1.0); //Blue
      }
    else
      colour = G4Color(1.0, 1.0, 0.0);// Yellow
    G4VisAttributes trajectoryLineAttribs(colour);
    trajectoryLine.SetVisAttributes(&trajectoryLineAttribs);
    pVVisManager->Draw(trajectoryLine);
  }
  if(markersRequired)
  {
    auxiliaryPoints.SetMarkerType(G4Polymarker::squares);
    auxiliaryPoints.SetScreenSize(markerSize);
    auxiliaryPoints.SetFillStyle(G4VMarker::filled);
    G4VisAttributes auxiliaryPointsAttribs(G4Colour(0., 1., 1.));  // Magenta
    auxiliaryPoints.SetVisAttributes(&auxiliaryPointsAttribs);
    pVVisManager->Draw(auxiliaryPoints);

    stepPoints.SetMarkerType(G4Polymarker::circles);
    stepPoints.SetScreenSize(markerSize);
    stepPoints.SetFillStyle(G4VMarker::filled);
    G4VisAttributes stepPointsAttribs(G4Colour(1., 1., 0.));  // Yellow
    stepPoints.SetVisAttributes(&stepPointsAttribs);
    pVVisManager->Draw(stepPoints);
  }
}
