#include "Account.hpp"
#include "proxy/JamiConfigurationManagerController.hpp"
#include "JamppInternalDecl.hpp"

using namespace jamipp;

Account::Account(const std::string& account_id, const std::string& jami_id)
    : account_id_(account_id), jami_id_(jami_id)
{
    configuration_manager_->registerHandler(account_id, this);
    auto detail = configuration_manager_->getAccountDetails(account_id);
    display_name_ = detail["Account.displayName"];
}

Account::~Account()
{
    configuration_manager_->unregisterHandler(account_id_);
}

void Account::sendMessage(const std::string& conversationId, const std::string& message)
{
    configuration_manager_->sendMessage(account_id_, conversationId, message, "");
}

void Account::sendFile(const std::string& conversationId, const std::string& file_path, std::string disp_name)
{
    if(disp_name.empty())
        disp_name = file_path.substr(file_path.find_last_of("/\\"));
    configuration_manager_->sendFile(account_id_, conversationId, file_path, disp_name, "");
}

void Account::setDisplayName(const std::string& name)
{
    configuration_manager_->setAccountDetails(account_id_, {{"Account.displayName", name}});
    display_name_ = name;
}

void Account::handleMessageRecivedEvent(Message::Ptr message)
{
    if(message->author == jami_id_)
        return;

    if(message_handler_)
        message_handler_(message);
    
    if(message->type != "text/plain"
        || !(message->body.size() != 0 && message->body[0] == '/')) {
	    if(non_command_handler_)
            non_command_handler_(message);
        return;
    }
    
    auto n = message->body.find(' ');
    auto command = message->body.substr(1, n == std::string::npos ? n : n-1);
    auto it = command_handlers_.find(command);
    if(it != command_handlers_.end())
        it->second(message);
    else if(unknown_command_handler_)
        unknown_command_handler_(message);
}

void Account::handleConversationStartEnvent(const std::string& conversationId)
{
    if(conversation_start_handler_)
        conversation_start_handler_(conversationId);
}

void Account::onAnyMessage(std::function<void(Message::Ptr)> handler)
{
    message_handler_ = std::move(handler);
}

void Account::onNonCommandMessage(std::function<void(Message::Ptr)> handler)
{
    non_command_handler_ = std::move(handler);
}

void Account::onUnknownCommand(std::function<void(Message::Ptr)> handler)
{
    unknown_command_handler_ = std::move(handler);
}

void Account::onCommand(const std::string& command, std::function<void(Message::Ptr)> handler)
{
    command_handlers_[command] = std::move(handler);
}

void Account::onConversationStart(std::function<void(const std::string&)> handler)
{
    conversation_start_handler_ = std::move(handler);
}