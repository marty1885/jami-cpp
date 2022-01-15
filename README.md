# jami-cpp

A basic (enough to build a chatbot) and easy to use GNU Jami API library in C++17. The API is modeled after [reo7sp/tgbot-cpp][1]

## Dependencies

* sdbus

## Sample

```cpp
#include <jami-cpp/jami-cpp.hpp>
using namespace jamipp;

int main()
{
    jamipp::init("jampp.example.echobot");

    auto account = jamipp::getAccountById("your-jami-id-here");
    assert(accont != nullptr);

    account->onNonCommandMessage([&account](Message::Ptr message) {
        if(message->type != "text/plain")
            return;
        account->sendMessage(message->conversation_id, message->body);
    });

    account->onCommand("syn", [&account](Message::Ptr message) {
        account->sendMessage(message->conversation_id, "syn/ack!");
    });

    jamipp::run();
}
```

## TODOs:

- [ ] Mark messages seen by the bot as read
- [ ] Get display name of remote user
- [ ] Allow refusing conversation request

[1]: https://github.com/reo7sp/tgbot-cpp