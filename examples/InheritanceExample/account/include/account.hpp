#pragma once

#include <memory>

namespace banking {

class IAccount {
public:
    using balance_t = long long;

    using transaction_t = unsigned;

    virtual bool reduce_balance(transaction_t value) = 0;

    virtual bool increase_balance(transaction_t value) = 0;

    [[nodiscard]] virtual balance_t get_balance() const = 0;

    [[nodiscard]] virtual balance_t available_funds() const = 0;

    [[nodiscard]] virtual std::shared_ptr<IAccount> clone() const = 0;

    virtual ~IAccount() = default;
};

}