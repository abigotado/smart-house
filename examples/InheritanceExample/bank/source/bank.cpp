#include "bank.hpp"

namespace banking {
    Bank::Card::Card(Bank::account_id_t account_id, Bank::pin_code_t pin) : account_id_(account_id),
                                                                            pin_code_(pin) {}

    bool Bank::Card::set_password(Bank::pin_code_t old_pin, Bank::pin_code_t new_pin) {
        bool success = pin_code_ == old_pin;
        if(success)
            pin_code_ = new_pin;
        return success;
    }

    std::optional<Bank::account_id_t> Bank::Card::get_account(Bank::pin_code_t pin) const {
        if(pin_code_ == pin)
            return account_id_;
        else
            return std::nullopt;
    }


    Bank::AccountInfo Bank::open_new_account(std::shared_ptr<IAccount> new_account) {
        data_->accounts.emplace(data_->id_counter, std::move(new_account));
        pin_code_t pin = generate_random_pin();
        account_id_t id = data_->id_counter++;
        AccountInfo result {
            .card = Card(id, pin),
            .account_id = id,
            .pin_code = pin
        };
        return result;
    }

    Bank::pin_code_t Bank::generate_random_pin() {
        return data_->distribution(data_->randomDevice);
    }

    Bank::account_clonning_result Bank::open_same_account(const Bank::Card &card, Bank::pin_code_t pin) {
        auto account = card.get_account(pin);
        if(!account)
            return { std::nullopt, operation_status::wrong_pin };
        auto pos = data_->accounts.find(*account);
        if(pos == data_->accounts.end())
            return { std::nullopt, operation_status::invalid_source_account };
        return { open_new_account(pos->second->clone()), operation_status::success };
    }

    Bank::operation_status Bank::close_account(const Bank::Card &card, Bank::pin_code_t pin) {
        auto account = card.get_account(pin);
        if(!account)
            return operation_status::wrong_pin;
        if(data_->accounts.erase(*account) == 0)
            return operation_status::invalid_source_account;
        return operation_status::success;
    }

    Bank::operation_status Bank::change_password(Bank::Card &card, Bank::pin_code_t old_pin, Bank::pin_code_t new_pin) {
        return card.set_password(old_pin, new_pin) ? operation_status::success :
                                                     operation_status::wrong_pin;
    }

    Bank::operation_status Bank::get_cash(IAccount::transaction_t amount, const Bank::Card &card, Bank::pin_code_t pin) {
        auto account = card.get_account(pin);
        if(!account)
            return operation_status::wrong_pin;
        auto pos = data_->accounts.find(*account);
        if(pos == data_->accounts.end())
            return operation_status::invalid_source_account;
        return pos->second->reduce_balance(amount) ? operation_status::success :
                                                     operation_status::not_enough_money;
    }

    Bank::balance_result Bank::get_balance(const Bank::Card &card, Bank::pin_code_t pin) const {
        auto account = card.get_account(pin);
        if(!account)
            return { std::nullopt, operation_status::wrong_pin };
        auto pos = data_->accounts.find(*account);
        if(pos == data_->accounts.end())
            return { std::nullopt, operation_status::invalid_source_account };
        return { pos->second->get_balance(), operation_status::success };
    }

    Bank::operation_status Bank::transfer_to_account(Bank::account_id_t other_account, IAccount::transaction_t amount,
                                                     const Bank::Card &card, Bank::pin_code_t pin) {
        auto account = card.get_account(pin);
        if(!account)
            return  operation_status::wrong_pin;

        auto pos_src = data_->accounts.find(*account);
        if(pos_src == data_->accounts.end())
            return operation_status::invalid_source_account;

        if(pos_src->second->available_funds() < amount)
            return operation_status::not_enough_money;

        auto pos_dst = data_->accounts.find(other_account);
        if(pos_dst == data_->accounts.end())
            return operation_status::invalid_destination_account;

        if(!pos_dst->second->increase_balance(amount))
            return operation_status::operation_declined;

        pos_src->second->reduce_balance(amount);
        return operation_status::success;
    }

}