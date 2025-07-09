#pragma once

#include <account.hpp>

namespace banking{

class DebitAccount : public IAccount {
public:
    explicit DebitAccount(balance_t value = 0);

    bool reduce_balance(transaction_t value) override;

    bool increase_balance(transaction_t value) override;

    [[nodiscard]] balance_t get_balance() const override;

    [[nodiscard]] balance_t available_funds() const override;

    [[nodiscard]] std::shared_ptr<IAccount> clone() const override;

private:
    balance_t balance_;
};

}