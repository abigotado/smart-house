#include "saving_account.hpp"

namespace banking {

    SavingAccount::SavingAccount(double bonus_rate, IAccount::balance_t value) : bonus_percent_(bonus_rate){
        if(bonus_rate < 0)
            throw std::invalid_argument("Negative bonus rate");
        SavingAccount::increase_balance(value); // Без явного указания, чью функцию вызывать - приведёт к потенциальным ошибкам
    }

    bool SavingAccount::reduce_balance(IAccount::transaction_t value) {
        bool success = value <= bonus_balance_;
        if(success)
            bonus_balance_ -= value;
        return success;
    }

    bool SavingAccount::increase_balance(IAccount::transaction_t value) {
        auto add_v = static_cast<transaction_t>(value * bonus_percent_);
        balance_ += value;
        bonus_balance_ += add_v;
        return true;
    }

    IAccount::balance_t SavingAccount::get_balance() const {
        return balance_ + bonus_balance_;
    }

    IAccount::balance_t SavingAccount::available_funds() const {
        return bonus_balance_;
    }

    std::shared_ptr<IAccount> SavingAccount::clone() const {
        auto new_account = std::make_shared<SavingAccount>(bonus_percent_);
        new_account->balance_ = balance_;
        new_account->bonus_balance_ = bonus_balance_;
        return new_account;
    }

}