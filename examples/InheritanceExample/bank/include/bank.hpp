#pragma once

#include <unordered_map>
#include <optional>
#include <random>
#include <limits>

#include <account.hpp>

namespace banking {

class Bank {
public:
    using account_id_t = std::size_t;

    using pin_code_t = std::size_t;

    class Card {
    private:
        friend class Bank;

        Card(account_id_t account_id, pin_code_t pin);

        bool set_password(pin_code_t old_pin, pin_code_t new_pin);

        [[nodiscard]] std::optional<account_id_t> get_account(pin_code_t pin) const;

        std::size_t account_id_;

        std::size_t pin_code_;
    };

    struct AccountInfo {
        Card card;
        account_id_t account_id;
        pin_code_t pin_code;
    };

    enum class operation_status {
        success,
        wrong_pin,
        invalid_source_account,
        invalid_destination_account,
        not_enough_money,
        operation_declined
    };

    struct account_clonning_result {
        std::optional<AccountInfo> account_info;
        operation_status status;
    };

    struct balance_result {
        std::optional<IAccount::balance_t> balance;
        operation_status status;
    };

    AccountInfo open_new_account(std::shared_ptr<IAccount> new_account);

    account_clonning_result open_same_account(const Card& card, pin_code_t pin);

    operation_status close_account(const Card& card, pin_code_t pin);

    static operation_status change_password(Card& card, pin_code_t old_pin, pin_code_t new_pin);

    operation_status get_cash(IAccount::transaction_t amount, const Card& card, pin_code_t pin);

    operation_status transfer_to_account (account_id_t other_account, IAccount::transaction_t amount,
                              const Card& card, pin_code_t pin);

    [[nodiscard]] balance_result get_balance(const Card& card, pin_code_t pin) const;

private:
    static constexpr pin_code_t MIN_PIN = std::numeric_limits<pin_code_t>::min();

    static constexpr pin_code_t MAX_PIN = std::numeric_limits<pin_code_t>::max();

    pin_code_t generate_random_pin();

    struct data_base {
        account_id_t id_counter {0};
        std::unordered_map<account_id_t, std::shared_ptr<IAccount>> accounts {};
        std::mt19937_64 randomDevice {0};
        std::uniform_int_distribution<pin_code_t> distribution {MIN_PIN, MAX_PIN};
    };

    std::shared_ptr<data_base> data_ = std::make_shared<data_base>();
};

}