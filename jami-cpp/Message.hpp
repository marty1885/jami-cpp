#pragma once

#include <string>
#include <cstdint>
#include <memory>

namespace jamipp
{
struct Message
{
    std::string author;
    std::string conversation_id;
    std::string body;
    std::string id;
    std::string linearizedParent;
    std::string parents;
    int64_t timestamp;
    std::string type;

    using Ptr = std::shared_ptr<Message>;
};
}