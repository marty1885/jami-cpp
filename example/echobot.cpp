#include <jami-cpp/jami-cpp.hpp>
#include <iostream>
#include <jami-cpp/proxy/JamiConfigurationManagerController.hpp>
using namespace jamipp;

int main()
{
    auto jami_id = getenv("JAMI_ID");
    if(jami_id == nullptr) {
        std::cerr << "JAMI_ID enviroment variable not set\n";
        return 1;
    }

    jamipp::init("jamipp.example.echobot");
    auto account = jamipp::getAccountById(jami_id);
    if(!account) {
        std::cerr << "Account does not exist.\n";
        return 1;
    }

    account->onAnyMessage([&account](Message::Ptr message) {
        if(message->type != "text/plain")
            return;
        std::cout << "User said: " << message->body << "\n";
        account->sendMessage(message->conversation_id, message->body);
    });

    jamipp::run();
}