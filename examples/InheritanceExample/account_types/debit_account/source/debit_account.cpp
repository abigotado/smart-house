#include "debit_account.hpp"

namespace banking {
    DebitAccount::DebitAccount(IAccount::balance_t value) : balance_(value) {
        if(balance_ < 0)
            throw std::invalid_argument("Negative account balance");
    }

    bool DebitAccount::reduce_balance(IAccount::transaction_t value) {
        bool success = balance_ >= value;
        if (success)
            balance_ -= value;
        return success;
    }

    bool DebitAccount::increase_balance(IAccount::transaction_t value) {
        balance_ += value;
        return true;
    }

    IAccount::balance_t DebitAccount::get_balance() const {
        return balance_;
    }

    IAccount::balance_t DebitAccount::available_funds() const {
        return balance_;
    }

    std::shared_ptr<IAccount> DebitAccount::clone() const {
        return std::make_shared<DebitAccount>(balance_);
    }
}