#pragma once

#include "JamiConfigurationManagerProxy.h"
#include <iostream>
#include <map>

namespace jamipp
{

class Account;

class JamiConfigurationManagerController : public sdbus::ProxyInterfaces<cx::ring::Ring::ConfigurationManager_proxy>
{
public:
    JamiConfigurationManagerController(sdbus::IConnection& conn, std::string destination, std::string object_path)
        : ProxyInterfaces(conn, std::move(destination), std::move(object_path))
    {
        registerProxy();
    }

    ~JamiConfigurationManagerController()
    {
        unregisterProxy();
    }

    virtual void onExportOnRingEnded(const std::string& accountID, const int32_t& status, const std::string& PIN) override {}
    virtual void onDeviceRevocationEnded(const std::string& accountID, const std::string& deviceId, const int32_t& status) override {}
    virtual void onAccountProfileReceived(const std::string& accountID, const std::string& displayName, const std::string& photo) override {}
    virtual void onKnownDevicesChanged(const std::string& accountID, const std::map<std::string, std::string>& devices) override {}
    virtual void onRegisteredNameFound(const std::string& accountID, const int32_t& status, const std::string& address, const std::string& name) override {}
    virtual void onNameRegistrationEnded(const std::string& accountID, const int32_t& status, const std::string& name) override {}
    virtual void onUserSearchEnded(const std::string& accountID, const int32_t& status, const std::string& query, const std::vector<std::map<std::string, std::string>>& result) override {}
    virtual void onIncomingAccountMessage(const std::string& accountID, const std::string& messageID, const std::string& from, const std::map<std::string, std::string>& payloads) override {}
    virtual void onAccountMessageStatusChanged(const std::string& accountID, const std::string& conversationId, const std::string& peer, const std::string& id, const int32_t& status) override {}
    virtual void onProfileReceived(const std::string& accountID, const std::string& from, const std::string& path) override {}
    virtual void onComposingStatusChanged(const std::string& accountId, const std::string& conversationId, const std::string& contactId, const int32_t& status) override {}
    virtual void onVolumeChanged(const std::string& device, const double& value) override {}
    virtual void onHardwareDecodingChanged(const bool& state) override {}
    virtual void onHardwareEncodingChanged(const bool& state) override {}
    virtual void onAudioDeviceEvent() override {}
    virtual void onAudioMeter(const std::string& id, const double& level) override {}
    virtual void onAccountsChanged() override {}
    virtual void onAccountDetailsChanged(const std::string& accountID, const std::map<std::string, std::string>& details) override {}
    virtual void onRegistrationStateChanged(const std::string& accountID, const std::string& registrationState, const int32_t& registrationDetail, const std::string& registrationDetailStr) override {}
    virtual void onVolatileAccountDetailsChanged(const std::string& accountID, const std::map<std::string, std::string>& details) override {}
    virtual void onStunStatusFailure(const std::string& reason) override {}
    virtual void onErrorAlert(const int32_t& code) override {}
    virtual void onCertificateStateChanged(const std::string& accountId, const std::string& certId, const std::string& state) override {}
    virtual void onCertificatePinned(const std::string& certId) override {}
    virtual void onCertificatePathPinned(const std::string& path, const std::vector<std::string>& certIds) override {}
    virtual void onCertificateExpired(const std::string& certId) override {}
    virtual void onIncomingTrustRequest(const std::string& accountID, const std::string& conversationId, const std::string& from, const std::vector<uint8_t>& payload, const uint64_t& receiveTime) override {}
    virtual void onContactAdded(const std::string& accountID, const std::string& uri, const bool& confirmed) override {}
    virtual void onContactRemoved(const std::string& accountID, const std::string& uri, const bool& banned) override {}
    virtual void onMediaParametersChanged(const std::string& accountID) override {}
    virtual void onMigrationEnded(const std::string& accountID, const std::string& result) override {}
    virtual void onDataTransferEvent(const std::string& accountId, const std::string& conversationId, const std::string& interactionId, const std::string& fileId, const int32_t& code) override {}
    virtual void onConversationLoaded(const uint32_t& id, const std::string& account_id, const std::string& conversation_id, const std::vector<std::map<std::string, std::string>>& messages) override {}
    virtual void onMessageReceived(const std::string& account_id, const std::string& conversation_id, const std::map<std::string, std::string>& message) override;
    virtual void onConversationRequestReceived(const std::string& account_id, const std::string& conversation_id, const std::map<std::string, std::string>& metadatas) override;
    virtual void onConversationRequestDeclined(const std::string& account_id, const std::string& conversation_id) override {}
    virtual void onConversationReady(const std::string& account_id, const std::string& conversation_id) override {}
    virtual void onConversationRemoved(const std::string& account_id, const std::string& conversation_id) override {}
    virtual void onConversationMemberEvent(const std::string& account_id, const std::string& conversation_id, const std::string& member_uri, const int32_t& event) override {}
    virtual void onOnConversationError(const std::string& account_id, const std::string& conversation_id, const uint32_t& code, const std::string& what) override {}
    virtual void onDebugMessageReceived(const std::string& message) override {}
    virtual void onMessageSend(const std::string& message) override {}

    std::map<std::string, Account*> handlers_;
    void registerHandler(const std::string& account_id, Account* account);
    void unregisterHandler(const std::string& account_id);
};

}