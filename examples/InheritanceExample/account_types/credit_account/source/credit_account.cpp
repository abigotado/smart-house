#include "credit_account.hpp"

namespace banking {

    CreditAccount::CreditAccount(IAccount::balance_t credit_limit,
                                 double commission_rate) : limit_(-credit_limit),
                                                          commission_rate_(1 + commission_rate) {
        if(credit_limit <= 0)
            throw std::invalid_argument("Negative credit limit");
        if(commission_rate < 0)
            throw std::invalid_argument("Negative commission rate");
    }
    bool CreditAccount::reduce_balance(IAccount::transaction_t value) {
        auto reduce_value = static_cast<balance_t>(value * commission_rate_);
        balance_t new_balance = balance_ - reduce_value;
        bool success = new_balance >= limit_;
        if(success)
            balance_ = new_balance;
        return success;
    }

    bool CreditAccount::increase_balance(IAccount::transaction_t value) {
        balance_ += value;
        return true;
    }

    IAccount::balance_t CreditAccount::get_balance() const {
        return balance_;
    }

    IAccount::balance_t CreditAccount::available_funds() const {
        auto available = static_cast<double>((balance_ - limit_)) / commission_rate_;
        return static_cast<balance_t>(available);
    }

    std::shared_ptr<IAccount> CreditAccount::clone() const {
        auto new_account = std::make_shared<CreditAccount>(limit_, commission_rate_);
        new_account->balance_ = balance_;
        return new_account;
    }
}