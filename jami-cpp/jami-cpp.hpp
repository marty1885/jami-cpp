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

/**
 * @brief Creates a new Jami user and return the Jami ID
 * @param display_name the displaied name of the new user
 * @param password passwor of the user archive
 * @return Jami ID of the new user
 */
[[nodiscard]] std::string newAccount(const std::string& display_name, const std::string& password);

/**
 * @brief initializes jami-cpp
 * @param application_id the DBus ID of the current application
 * @return true if initialized successfully. False otherwisse
 */
bool init(const std::string& application_id);

/**
 * @brief block until quit
 */
void run();

/**
 * @brief Quit jami-cpp
 */
void quit();

}
