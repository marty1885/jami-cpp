#include "JamiConfigurationManagerController.hpp"
#include "../Message.hpp"
#include "../Account.hpp"

using namespace jamipp;

static std::string value_or(const std::map<std::string, std::string>& map, const std::string& key, const std::string& default_val = "")
{
    auto it = map.find(key);
    if(it != map.end())
        return it->second;
    return default_val;
}

void JamiConfigurationManagerController::onMessageReceived(const std::string& account_id
    , const std::string& conversation_id, const std::map<std::string, std::string>& message)
{
    auto it = handlers_.find(account_id);
    if(it != handlers_.end()) {
        auto msg = std::make_shared<Message>();
        msg->author = value_or(message, "author");
        msg->conversation_id = conversation_id;
        msg->body = value_or(message, "body");
        msg->id = value_or(message, "id");
        msg->linearizedParent = value_or(message, "linearizedParent");
        msg->parents = value_or(message, "parents");
        msg->timestamp = std::stoull(value_or(message, "timestamp", "0"));
        msg->type = value_or(message, "type");
        it->second->handleMessageRecivedEvent(std::move(msg));
    }
}

void JamiConfigurationManagerController::onConversationRequestReceived(const std::string& account_id
    , const std::string& conversation_id, const std::map<std::string, std::string>& metadatas)
{
    auto it = handlers_.find(account_id);
    if(it != handlers_.end()) {
        // TODO: Add some way to decline conversation request
        acceptConversationRequest(account_id, conversation_id);
        it->second->handleConversationStartEnvent(conversation_id);
    }
}

void JamiConfigurationManagerController::registerHandler(const std::string& jami_id, Account* account)
{
    handlers_[jami_id] = account;
}

void JamiConfigurationManagerController::unregisterHandler(const std::string& jami_id)
{
    handlers_.erase(jami_id);
}