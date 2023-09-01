/*
**********************************************************************************************************************
*
* COPYRIGHT RESERVED, Robert Bosch GmbH, 2020. All rights reserved.
* The reproduction, distribution and utilization of this document as well as the communication of its contents to
* others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
* All rights reserved in the event of the grant of a patent, utility model or design.
*
**********************************************************************************************************************
*/
/**
 * \\file  packagemanagement_skeleton.h
 *
 * \\authors  This file was generated with VRTE Flexible Safety - Manifest to Adaptive Runtime API Generator
 *
 * \\brief  Function block model for PackageManagement
 *
 */
#ifndef SERVICE_PACKAGEMANAGEMENT_SKELETON_H_INCLUDED
#define SERVICE_PACKAGEMANAGEMENT_SKELETON_H_INCLUDED

#include <string>
#include <functional>

#include "types.hpp"

struct PkgListType
{
};

struct PackageManagerStatusType
{
    PackageManagerStatusType() = default;

    template<class T>
    PackageManagerStatusType(T&&) {}
};

namespace ara {
namespace ucm {
namespace pkgmgr {
namespace skeleton {

namespace fields {

     using CurrentStatus = ara::com::Decorator<PackageManagerStatusType>;
     using GetActiveImages = ara::com::Decorator<PkgListType>;

} // namespace fields

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
struct PackageManagementSkeleton
{
    explicit PackageManagementSkeleton(const ara::com::InstanceIdentifier&) {}

     ~PackageManagementSkeleton() = default;

     void OfferService();

     void StopOfferService();

     fields::CurrentStatus CurrentStatus;
     fields::GetActiveImages GetActiveImages;

     static bool OfferService_throw_;
     static bool OfferService_custom_throw_;
};
#pragma GCC diagnostic pop



} // namespace skeleton
} // namespace pkgmgr
} // namespace ucm
} // namespace ara

#endif // SERVICE_PACKAGEMANAGEMENT_SKELETON_H_INCLUDED
