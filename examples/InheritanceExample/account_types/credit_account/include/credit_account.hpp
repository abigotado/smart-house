#pragma once

#include <account.hpp>

namespace banking{

class CreditAccount : public IAccount {
public:
    CreditAccount(balance_t credit_limit, double commission_rate);

    bool reduce_balance(transaction_t value) override;

    bool increase_balance(transaction_t value) override;

    [[nodiscard]] balance_t get_balance() const override;

    [[nodiscard]] balance_t available_funds() const override;

    [[nodiscard]] std::shared_ptr<IAccount> clone() const override;

private:
    const balance_t limit_;

    const double commission_rate_;

    balance_t balance_ = 0;
};

}