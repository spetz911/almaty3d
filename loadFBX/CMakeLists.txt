cmake_minimum_required(VERSION 3.1)
project(loadFBX)

include_directories(../ThirdParty/FBX/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++")

set(SOURCE_FILES
    Common/AnimationUtility.cxx
    Common/AnimationUtility.h
    Common/Common.cxx
    Common/Common.h
    Common/GeometryUtility.cxx
    Common/GeometryUtility.h
    src/DisplayAnimation.cxx
    src/DisplayAnimation.h
    src/DisplayCache.cxx
    src/DisplayCache.h
    src/DisplayCamera.cxx
    src/DisplayCamera.h
    src/DisplayCommon.cxx
    src/DisplayCommon.h
    src/DisplayGenericInfo.cxx
    src/DisplayGenericInfo.h
    src/DisplayGlobalSettings.cxx
    src/DisplayGlobalSettings.h
    src/DisplayHierarchy.cxx
    src/DisplayHierarchy.h
    src/DisplayLight.cxx
    src/DisplayLight.h
    src/DisplayLink.cxx
    src/DisplayLink.h
    src/DisplayLodGroup.cxx
    src/DisplayLodGroup.h
    src/DisplayMarker.cxx
    src/DisplayMarker.h
    src/DisplayMaterial.cxx
    src/DisplayMaterial.h
    src/DisplayMesh.cxx
    src/DisplayMesh.h
    src/DisplayNurb.cxx
    src/DisplayNurb.h
    src/DisplayPatch.cxx
    src/DisplayPatch.h
    src/DisplayPivotsAndLimits.cxx
    src/DisplayPivotsAndLimits.h
    src/DisplayPose.cxx
    src/DisplayPose.h
    src/DisplayShape.cxx
    src/DisplayShape.h
    src/DisplaySkeleton.cxx
    src/DisplaySkeleton.h
    src/DisplayTexture.cxx
    src/DisplayTexture.h
    src/DisplayUserProperties.cxx
    src/DisplayUserProperties.h
    src/main.cxx
    )

FIND_LIBRARY(F_LIBRARY Foundation REQUIRED)

find_library(LIB_I_NEED fbxsdk HINTS ../ThirdParty/FBX/lib)

add_executable(loadFBX ${SOURCE_FILES} )

target_link_libraries(loadFBX ${F_LIBRARY} ${LIB_I_NEED})
