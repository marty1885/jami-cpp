#include <thread>
#include <chrono>
#include "jami-cpp.hpp"
#include "Account.hpp"
#include "proxy/JamiConfigurationManagerController.hpp"

using namespace jamipp;

std::unique_ptr<sdbus::IConnection> connection_;
std::unique_ptr<JamiConfigurationManagerController> jamipp::configuration_manager_;

bool jamipp::init(const std::string& application_id)
{    
    connection_ = sdbus::createSessionBusConnection(application_id);
    configuration_manager_ = std::make_unique<JamiConfigurationManagerController>(*connection_, "cx.ring.Ring", "/cx/ring/Ring/ConfigurationManager");
    return true;
}

void jamipp::run()
{
    connection_->enterEventLoop();
}

void jamipp::quit()
{
    connection_->leaveEventLoop();
}

std::unique_ptr<Account> jamipp::getAccountById(const std::string& jami_id)
{
    auto accounts = configuration_manager_->getAccountList();
    for(const auto& account : accounts) {
        auto account_detail = configuration_manager_->getAccountDetails(account);
        auto account_jami_id = account_detail["Account.username"]; // Yes, Jami "username" is the account ID
        if(account_jami_id == jami_id)
            return std::make_unique<Account>(account, account_jami_id);
    }
    return nullptr;
}

std::string jamipp::newAccount(const std::string& display_name, const std::string& password)
{
    std::map<std::string, std::string> details;
    details["Account.displayName"] = display_name;
    details["Account.type"] = "RING";
    details["Account.archivePassword"] = password;
    auto account_id = configuration_manager_->addAccount(details);

    // HACK: Poll Jami until account is populated
    std::map<std::string, std::string> account_detail;
    while(true) {
        account_detail = configuration_manager_->getAccountDetails(account_id);
        if(account_detail["Account.username"] != "")
            break;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    
    return account_detail["Account.username"];
}