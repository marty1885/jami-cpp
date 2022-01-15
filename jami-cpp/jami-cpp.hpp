#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Account.hpp"
#include "JamppInternalDecl.hpp"

namespace jamipp
{
/**
 * @param id the Jami ID of the account
 * @return an object representing the account
 */
std::unique_ptr<Account> getAccountById(const std::string& id);
std::string newAccount(const std::string& alias, const std::string& password);

bool init(const std::string& application_id);
void run();
void quit();

}
