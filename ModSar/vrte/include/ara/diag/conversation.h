// --------------------------------------------------------------------------
// |              _    _ _______     .----.      _____         _____        |
// |         /\  | |  | |__   __|  .  ____ .    / ____|  /\   |  __ \       |
// |        /  \ | |  | |  | |    .  / __ \ .  | (___   /  \  | |__) |      |
// |       / /\ \| |  | |  | |   .  / / / / v   \___ \ / /\ \ |  _  /       |
// |      / /__\ \ |__| |  | |   . / /_/ /  .   ____) / /__\ \| | \ \       |
// |     /________\____/   |_|   ^ \____/  .   |_____/________\_|  \_\      |
// |                              . _ _  .                                  |
// --------------------------------------------------------------------------
//
// All Rights Reserved.
// Any use of this source code is subject to a license agreement with the
// AUTOSAR development cooperation.
// More information is available at www.autosar.org.
//
// Disclaimer
//
// This work (specification and/or software implementation) and the material
// contained in it, as released by AUTOSAR, is for the purpose of information
// only. AUTOSAR and the companies that have contributed to it shall not be
// liable for any use of the work.
//
// The material contained in this work is protected by copyright and other
// types of intellectual property rights. The commercial exploitation of the
// material contained in this work requires a license to such intellectual
// property rights.
//
// This work may be utilized or reproduced without any modification, in any
// form or by any means, for informational purposes only. For any other
// purpose, no part of the work may be utilized or reproduced, in any form
// or by any means, without permission in writing from the publisher.
//
// The work has been developed for automotive applications only. It has
// neither been developed, nor tested for non-automotive applications.
//
// The word AUTOSAR and the AUTOSAR logo are registered trademarks.
// --------------------------------------------------------------------------
#ifndef ARA_DIAG_CONVERSATION_H_INCLUDED
#define ARA_DIAG_CONVERSATION_H_INCLUDED

#include <ara/core/string_view.h>
#include <ara/core/string.h>
#include <ara/core/result.h>
#include <ara/core/vector.h>
#include <ara/diag/meta_info.h>
#include <functional>
#include <cstdint>

namespace ara {

namespace diag {

// Hide implementation details by forward declaration
namespace internal {

class ConversationImpl;

}

/** \file
 * @brief Type for current activity status
 *
 * @traceid{SWS_DM_00690}@tracestatus{draft}
 * @uptrace{RS_AP_00125}
 * @uptrace{RS_Diag_04166}
 * @uptrace{RS_Diag_04169}
 * @uptrace{RS_Diag_04209}
 * @uptrace{RS_Diag_04210}
 */
enum class ActivityStatusType : std::uint8_t
{
   kActive   = 0x00,        ///<  Currently active; i.e. request is currently processed or non-default session is active.
   kInactive = 0x01,        ///<  Currently not active
};

/** \file
 * @brief Type for the active security level.
 * @traceid{SWS_DM_00705}@tracestatus{draft}
 * @uptrace{RS_AP_00125}
 */
enum class SecurityLevelType : std::uint8_t
{
   kLocked = 0x00,          ///<  security level locked;
   //k<configuration_dependent> ///< i.e. the security is enabled, configuration dependent; formula: (SecurityAccessType (requestSeed) + 1) / 2
};

/** \file
 * @brief Type for the active diagnostic session.
 * @traceid{SWS_DM_00706}@tracestatus{draft}
 * @uptrace{RS_AP_00125}
 */
enum class SessionControlType : std::uint8_t
{
   kDefaultSession                = 0x01, ///< default session according to IS0 14229-1.
   kProgrammingSession            = 0x02, ///< programming session according to IS0 14229-1.
   kExtendedDiagnosticSession     = 0x03, ///< extended diagnostic session according to IS0 14229-1.
   kSafetySystemDiagnosticSession = 0x04  ///< safety system diagnostic session according to IS0 14229-1.
                                          ///< configuration dependent sessions
};

class AraComConversationManagerUnitTestHelper;

/**
 * @brief Conversation interface
 *
 * @traceid{SWS_DM_00693}@tracestatus{draft}
 * @uptrace{RS_Diag_04166}
 * @uptrace{RS_Diag_04169}
 */
class Conversation
{
public:
   friend class AraComConversationManagerUnitTestHelper;
   using ConversationRef = std::reference_wrapper<ara::diag::Conversation>;

   /**
    * @brief Properties allowing an identification of the conversation
    *
    * @traceid{SWS_DM_00691}@tracestatus{draft}
    * @uptrace{RS_Diag_04166}
    * @uptrace{RS_Diag_04169}
    * @uptrace{RS_Diag_04209}
    * @uptrace{RS_Diag_04210}
    */
   struct ConversationIdentifierType
   {
      ara::core::String diagnosticProtocolKind;
      std::uint16_t     diagnosticServerAddress;
      std::uint16_t     testerAddress;
   };

   /**
    * @brief Get one conversation based on given MetaInfo
    * @returns Conversation object or error
    * @param metaInfo contains additional meta information
    *
    * @traceid{SWS_DM_00692}@tracestatus{draft}
    * @uptrace{RS_AP_00139}
    * @uptrace{RS_Diag_04169}
    * @uptrace{RS_Diag_04170}
    */
   static ara::core::Result<ConversationRef> GetConversation( const MetaInfo& metaInfo );

   /**
    * @brief Get all possible conversations
    * @returns a vector of all possibe Conversation objects
    *
    * @traceid{SWS_DM_00782}@tracestatus{draft}
    * @uptrace{RS_Diag_04166}
    * @uptrace{RS_Diag_04169}
    * @uptrace{RS_Diag_04209}
    * @uptrace{RS_Diag_04210}
    */
   static ara::core::Vector<ConversationRef> GetAllConversations();

   /**
    * @brief Get all currently active conversations
    * @returns a vector of all currently active (GetActivityStatus() == kActive) Conversation objects
    *
    * @traceid{SWS_DM_00783}@tracestatus{draft}
    * @uptrace{RS_Diag_04166}
    * @uptrace{RS_Diag_04169}
    * @uptrace{RS_Diag_04209}
    * @uptrace{RS_Diag_04210}
    */
   static ara::core::Vector<ConversationRef> GetCurrentActiveConversations();

   /**
    * @brief Represents the status of an active conversation.
    * @returns the activity status of the conversation
    *
    * @traceid{SWS_DM_00694}@tracestatus{draft}
    * @uptrace{RS_AP_00139}
    * @uptrace{RS_Diag_04169}
    */
   ara::core::Result<ActivityStatusType> GetActivityStatus() const;

   /**
    * @brief Register a notifier function which is called if the activity is changed.
    * @param notifier notifier function to be called
    * @returns void when the registering went fine or error
    *
    * @traceid{SWS_DM_00695}@tracestatus{draft}
    * @uptrace{RS_AP_00139}
    * @uptrace{RS_Diag_04169}
    */
   ara::core::Result<void> SetActivityNotifier( std::function<void (ActivityStatusType)> notifier );

   /**
    * @brief Represents the current active diagnostic session of an active conversation.
    * @returns  the current session
    *
    * @traceid{SWS_DM_00696}@tracestatus{draft}
    * @uptrace{RS_AP_00139}
    * @uptrace{RS_Diag_04169}
    * @uptrace{RS_Diag_04208}
    */
   ara::core::Result<SessionControlType> GetDiagnosticSession() const;

   /**
    * @brief Register a notifier function which is called if the Session is changed.
    * @param notifier notifier function to be called
    * @returns void when the registering went fine or error
    *
    * @traceid{SWS_DM_00697}@tracestatus{draft}
    * @uptrace{RS_AP_00139}
    * @uptrace{RS_Diag_04169}
    * @uptrace{RS_Diag_04208}
    */
   ara::core::Result<void> SetDiagnosticSessionNotifier( std::function<void (SessionControlType)> notifier );


   /**
    * @brief Converts the given diagnostic session into the ShortName
    * @param session Diagnostic session the shortname shall be returned for.
    * @returns ara::core::Result<ara::core::StringView> the session as shortName; DiagnosticSession.shortName
    *
    * @traceid{SWS_DM_00707}@tracestatus{draft}
    * @uptrace{RS_Diag_04169}
    * @uptrace{RS_Diag_04208}
    */
   ara::core::Result<ara::core::StringView> GetDiagnosticSessionShortName( SessionControlType session ) const;

   /**
    * @brief Represents the current active diagnostic SecurityLevel of an active conversation.
    * @returns  the current SecurityLevel
    *
    * @traceid{SWS_DM_00698}@tracestatus{draft}
    * @uptrace{RS_AP_00139}
    * @uptrace{RS_Diag_04169}
    * @uptrace{RS_Diag_04208}
    */
   ara::core::Result<SecurityLevelType> GetDiagnosticSecurityLevel() const;

   /**
    * @brief Register a notifier function which is called if the SecurityLevel is changed.
    * @param notifier notifier function to be called
    * @returns void when the registering went fine or error
    *
    * @traceid{SWS_DM_00699}@tracestatus{draft}
    * @uptrace{RS_AP_00139}
    * @uptrace{RS_Diag_04169}
    * @uptrace{RS_Diag_04208}
    */
   ara::core::Result<void> SetSecurityLevelNotifier( std::function<void (SecurityLevelType)> notifier );


   /**
    * @brief Converts the given diagnostic SecurityLevel into the ShortName
    * @param securityLevel Security level enum the shortname shall be returned for.
    * @returns ara::core::Result<ara::core::StringView> the SecurityLevel as shortName; DiagnosticSecurityLevel.shortName
    *
    * @traceid{SWS_DM_00708}@tracestatus{draft}
    * @uptrace{RS_Diag_04169}
    * @uptrace{RS_Diag_04208}
    */
   ara::core::Result<ara::core::StringView> GetDiagnosticSecurityLevelShortName( SecurityLevelType securityLevel ) const;

   /**
    * @brief Getter for the current identification properties of the active conversation.
    * @returns the conversation information
    *
    * @traceid{SWS_DM_00700}@tracestatus{draft}
    * @uptrace{RS_AP_00139}
    * @uptrace{RS_Diag_04169}
    */
   ara::core::Result<ConversationIdentifierType> GetConversationIdentifier() const;

            #if 0 // Not yet supported in VRTE
   /**
    * @brief Method to reset the current session to default session.
    * @returns void on success or error
    *
    * @traceid{SWS_DM_00701}@tracestatus{draft}
    * @uptrace{RS_Diag_04006}
    * @uptrace{RS_Diag_04166}
    * @uptrace{RS_Diag_04169}
    * @uptrace{RS_Diag_04209}
    * @uptrace{RS_Diag_04210}
    */
   ara::core::Result<void> ResetToDefaultSession();
            #endif // Not yet supported in VRTE

private:

   /**
    * @brief Ctor is vendor-specific
    *
    * @traceid{SWS_DM_00703}@tracestatus{draft}
    */
   Conversation();

   /**
    * @brief Dtor is vendor-specific
    *
    * @traceid{SWS_DM_00704}@tracestatus{draft}
    * @uptrace{RS_AP_00134}
    */
   ~Conversation() noexcept;

   Conversation( const Conversation& ) = delete;            // non construction-copyable

   Conversation& operator=( const Conversation& ) = delete; // non copyable

   friend class                           ara::diag::internal::ConversationImpl;
   ara::diag::internal::ConversationImpl* impl;
};

}     //namespace diag

} //namespace ara

#endif // include protection
