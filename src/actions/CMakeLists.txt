project(G4HorusActions)

add_library(${PROJECT_NAME}
            ActionInitialization.cc
            PhysicsList.cc
            EventActionHistogram.cc
            EventActionNtuple.cc
            EventActionSoco.cc
            PrimaryGeneratorAction.cc
            PrimaryGeneratorActionCascade.cc
            PrimaryGeneratorActionScattering.cc
            PrimaryGeneratorScattering.cc
            PrimaryGeneratorCascade.cc
            CascadeMessenger.cc
            RunActionHistogram.cc
            RunActionNtuple.cc
            RunActionSoco.cc)
add_library(G4Horus::actions ALIAS ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} G4Horus::soco stdc++fs)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
