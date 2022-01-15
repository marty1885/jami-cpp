#pragma once

#include <string>
#include <functional>
#include <map>
#include "Message.hpp"

namespace jamipp
{

class Account
{
public:
    Account(const std::string& account_id, const std::string& jami_id);
    ~Account();

    const std::string& alias() const { return alias_; };

    // Active functions
    void sendMessage(const std::string& conversationId, const std::string& message);
    void sendFile(const std::string& conversationId, const std::string& file_path, std::string disp_name);
    void setDisplayName(const std::string& name);

    // Event handlers
    void onAnyMessage(std::function<void(Message::Ptr)> handler);
    void onCommand(const std::string& command, std::function<void(Message::Ptr)> handler);
    void onUnknownCommand(std::function<void(Message::Ptr)> handler);
    void onNonCommandMessage(std::function<void(Message::Ptr)> handler);
    void onConversationStart(std::function<void(const std::string&)> handler);

    // Internal APIs
    void handleMessageRecivedEvent(Message::Ptr message);
    void handleConversationStartEnvent(const std::string& conversationId);
protected:
    std::string account_id_;
    std::string jami_id_;
    std::string alias_;
    std::function<void(const std::string&)> conversation_start_handler_;
    std::function<void(Message::Ptr)> message_handler_;
    std::function<void(Message::Ptr)> non_command_handler_;
    std::function<void(Message::Ptr)> unknown_command_handler_;
    std::map<std::string, std::function<void(Message::Ptr)>> command_handlers_;
};


} // namespace jamipp
