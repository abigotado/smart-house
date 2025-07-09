#pragma once

#include <account.hpp>
#include <vector>

namespace banking{

class FamilyAccount : public IAccount {
public:
    FamilyAccount() = default;

    template<class Iter>
    FamilyAccount(Iter first, Iter last) : linked_accounts_(first, last) {}

    FamilyAccount& link_account(const std::shared_ptr<IAccount>& acc);

    bool reduce_balance(transaction_t value) override;

    bool increase_balance(transaction_t value) override;

    [[nodiscard]] balance_t get_balance() const override;

    [[nodiscard]] balance_t available_funds() const override;

    [[nodiscard]] std::shared_ptr<IAccount> clone() const override;

private:
    void remove_unexisting_accounts() const;

    static constexpr balance_t empty_v = 0;

    mutable std::vector<std::weak_ptr<IAccount>> linked_accounts_;
};

}