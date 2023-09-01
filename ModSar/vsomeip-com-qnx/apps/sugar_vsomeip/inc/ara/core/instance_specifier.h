//==============================================================================
// C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2021-2022 by Robert Bosch GmbH. All rights reserved.
//
// The reproduction, distribution and utilization of this file as
// well as the communication of its contents to others without express
// authorization is prohibited. Offenders will be held liable for the
// payment of damages. All rights reserved in the event of the grant
// of a patent, utility model or design.
//==============================================================================

/// @file instance_specifier.h
/// @brief A class representing an AUTOSAR Instance Specifier, which is basically an AUTOSAR shortname-path wrapper.
//==================================================================================================================

#ifndef ARA_CORE_INSTANCE_SPECIFIER_H_
#define ARA_CORE_INSTANCE_SPECIFIER_H_

#include <algorithm>

#include "ara/core/core_error_domain.h"
#include "ara/core/result.h"
#include "ara/core/string.h"
#include "ara/core/string_view.h"

namespace ara {
namespace core {

/**
 * Class representing an AUTOSAR Instance Specifier, which is basically an
 * AUTOSAR shortname-path wrapper.
 *
 * @traceid{SWS_CORE_08001}
 */
class InstanceSpecifier final {

    /*ara::core::InstanceSpecifier is basically a wrapper for a valid meta-model
  related string in the form: <shortname of Executable>/<shortname of
  ASWC>/.../<shortname context N>/<shortname of PortPrototype>.This string has to
  be a valid shortname path in terms of AUTOSAR meta model
  definitions, i.e. a row of valid AUTOSAR short names separated by "/" as path
  delimiter. */
    ara::core::String mMetaModelIdentifier;

    /**
     *  @traceid{SWS_CORE_10200}
     *  @traceid{SWS_CORE_10201}
     */
    static Result<void> Validate(StringView metaModelIdentifier) noexcept {
        // set endOffset  = -1 this is used to identify whether the pattern "/" is
        // not there in the meta model identifier string
        // by comparing with StringView::npos
        std::size_t endOffset = static_cast<std::size_t>(-1);  // point this to a "virtual leading '/'"
        do {
            const size_t currentOffset = endOffset + 1;  // skip the '/'
            endOffset = metaModelIdentifier.find("/", currentOffset);
            const size_t len = (endOffset == StringView::npos) ? StringView::npos : endOffset - currentOffset;
            StringView const pathComponent = metaModelIdentifier.substr(currentOffset, len);

            if (pathComponent.empty()) {
                return Result<void>::FromError(CoreErrc::kInvalidMetaModelPath);
            }
            if (!IsValidMetamodelIdentifierPart(pathComponent)) {
                return Result<void>::FromError(CoreErrc::kInvalidMetaModelShortname);
            }
        } while (endOffset != StringView::npos);

        return Result<void>();
    }

    constexpr static bool IsValidStartChar(char ch) noexcept {
        return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
    }

    constexpr static bool IsValidChar(char ch) noexcept {
        return IsValidStartChar(ch) || (ch >= '0' && ch <= '9') || (ch == '_');
    }

    // text can never be empty due to the if-check in line 86
    constexpr static bool IsValidMetamodelIdentifierPart(StringView text) noexcept {
        return IsValidStartChar(text[0]) && std::all_of(text.begin() + 1, text.end(), IsValidChar);
    }

    InstanceSpecifier(StringView metaModelIdentifier, bool /*tag*/) : mMetaModelIdentifier(metaModelIdentifier) {}

public:
    /**
     * @brief Create a new instance of this class.
     * @param metaModelIdentifier  stringified form of InstanceSpecifier
     * @error CoreErrc::kInvalidMetaModelShortname  if any of the path elements of @a metaModelIdentifier is missing or
     * contains invalid characters
     * @error CoreErrc::kInvalidMetaModelPath  if the @a metaModelIdentifier is not a valid path to a model element
     * @returns a Result, containing either a syntactically valid InstanceSpecifier, or an ErrorCode
     *
     * @traceid{SWS_CORE_08032}
     * @traceid{SWS_CORE_10202}
     */
    static Result<InstanceSpecifier> Create(StringView metaModelIdentifier) {

        Result<void> ret = Validate(metaModelIdentifier);
        if (!ret) {
            return Result<InstanceSpecifier>::FromError(ret.Error());
        }

        return InstanceSpecifier(metaModelIdentifier, true);
    }

    /**
     * @brief throwing ctor from meta-model string
     * @param metaModelIdentifier  stringified meta model identifier (short name
     * path) where path separator is '/'.
     * @note Lifetime of underlying string has to exceed the lifetime of the constructed InstanceSpecifier.
     * @throws InstanceSpecifierException in case the given metamodel_identifier
     * isn't a valid meta-model identifier/short name path.
     *
     * @traceid{SWS_CORE_08021}
     * @traceid{SWS_CORE_10202}
     */
    explicit InstanceSpecifier(StringView metaModelIdentifier)
        : InstanceSpecifier(Create(metaModelIdentifier).ValueOrThrow()) {}

    /**
     * @brief Destructor
     *
     * @traceid{SWS_CORE_08029}
     */
    ~InstanceSpecifier() noexcept = default;

    /**
     * @brief Method to return the stringified form of InstanceSpecifier
     * @return stringified form of InstanceSpecifier.
     * @note Lifetime of the underlying string is only guaranteed for the lifetime of the underlying string of the
     * StringView passed to the constructor.
     *
     * @traceid{SWS_CORE_08041}
     */
    StringView ToString() const noexcept { return mMetaModelIdentifier; }

    /**
     * @brief eq operator to compare with other InstanceSpecifier instance.
     * @param other InstanceSpecifier instance to compare this one with.
     * @return true in case both InstanceSpecifiers are denoting exactly the same
     * model element, false else.
     *
     * @traceid{SWS_CORE_08042}
     */
    bool operator==(InstanceSpecifier const& other) const noexcept { return mMetaModelIdentifier == other.ToString(); }

    /**
     * @brief eq operator to compare with other InstanceSpecifier instance.
     * @param other string representation to compare this one with.
     * @return true in case this InstanceSpecifiers is denoting exactly the same
     * model element as other, false else.
     *
     * @traceid{SWS_CORE_08043}
     */
    bool operator==(StringView other) const noexcept { return mMetaModelIdentifier == other; }

    /**
     * @brief uneq operator to compare with other InstanceSpecifier instance.
     * @param other InstanceSpecifier instance to compare this one with.
     * @return false in case both InstanceSpecifiers are denoting exactly the same
     * model element, true else.
     *
     * @traceid{SWS_CORE_08044}
     */
    bool operator!=(InstanceSpecifier const& other) const noexcept { return mMetaModelIdentifier != other.ToString(); }

    /**
     * @brief uneq operator to compare with other InstanceSpecifier string
     * representation.
     * @param other string representation to compare this one with.
     * @return false in case this InstanceSpecifiers is denoting exactly the same
     * model element as other, true else.
     *
     * @traceid{SWS_CORE_08045}
     */
    bool operator!=(StringView other) const noexcept { return mMetaModelIdentifier != other; }

    /**
     * @brief Lower than operator to compare with other InstanceSpecifier for
     * ordering purposes (f.i. when collecting identifiers in maps).
     * @param other InstanceSpecifier instance to compare this one with.
     * @return true in case this InstanceSpecifiers is lexically lower than other,
     * false else.
     *
     * @traceid{SWS_CORE_08046}
     */
    bool operator<(InstanceSpecifier const& other) const noexcept {
        return mMetaModelIdentifier < other.mMetaModelIdentifier;
    }
};

/// Legacy from carma: Delimiter that separates ara::meta::InstanceSpecifier and ara::com::InstanceIdentifier entries in
/// the instance manifest file.
static constexpr char InstanceSeparator = ';';

/// Legacy from carma:  Delimiter that separates the technology from the actual instance ID within a
/// ara::com::InstanceIdentifier string.
static constexpr char TechnologySeparator = ':';

/**
 * @brief Non-member function op to allow char* on lhs.
 *
 * @param lhs  stringified form of a InstanceSpecifier
 * @param rhs  an InstanceSpecifier
 * @returns true in case rhs string representation equals lhs
 *
 * @traceid{SWS_CORE_08081}
 */
inline bool operator==(StringView lhs, InstanceSpecifier const& rhs) noexcept { return lhs == rhs.ToString(); }

/**
 * @brief non-member function op to allow char* on lhs.
 *
 * @param lhs  stringified form of a InstanceSpecifier
 * @param rhs  an InstanceSpecifier
 * @returns true in case rhs string representation not equals lhs
 *
 * @traceid{SWS_CORE_08082}
 */
inline bool operator!=(StringView lhs, InstanceSpecifier const& rhs) noexcept { return lhs != rhs.ToString(); }
}  // namespace core
}  // namespace ara

#endif  // ARA_CORE_INSTANCE_SPECIFIER_H_
