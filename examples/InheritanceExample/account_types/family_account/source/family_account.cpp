#include <numeric>

#include "family_account.hpp"

namespace banking {

    FamilyAccount &FamilyAccount::link_account(const std::shared_ptr<IAccount>& acc) {
        linked_accounts_.emplace_back(acc);
        return *this;
    }

    bool FamilyAccount::increase_balance(IAccount::transaction_t value) {
        return false;
    }

    IAccount::balance_t FamilyAccount::get_balance() const {
        remove_unexisting_accounts();
        return std::accumulate(linked_accounts_.cbegin(), linked_accounts_.cend(), empty_v,
                               [](balance_t acc, const std::weak_ptr<IAccount>& ptr){
                                   return acc + ptr.lock()->get_balance();
                               });
    }

    IAccount::balance_t FamilyAccount::available_funds() const {
        remove_unexisting_accounts();
        return std::accumulate(linked_accounts_.cbegin(), linked_accounts_.cend(), empty_v,
                               [](balance_t acc, const std::weak_ptr<IAccount>& ptr){
                                   return acc + ptr.lock()->available_funds();
                               });
    }

    bool FamilyAccount::reduce_balance(IAccount::transaction_t value) {
        balance_t available = available_funds();
        bool success = available >= value;
        if(success) {
            auto pos = linked_accounts_.begin();
            balance_t total = value;
            while (total > 0) {
                auto it = pos->lock();
                balance_t reduce = std::min(total, it->available_funds());
                it->reduce_balance(reduce);
                total -= reduce;
                ++pos;
            }
        }
        return success;
    }

    void FamilyAccount::remove_unexisting_accounts() const {
        auto pos = std::remove_if(linked_accounts_.begin(), linked_accounts_.end(),
                                  [](const auto& ptr) { return ptr.expired();});
        linked_accounts_.erase(pos, linked_accounts_.end());
    }

    std::shared_ptr<IAccount> FamilyAccount::clone() const {
        return std::make_shared<FamilyAccount>(linked_accounts_.cbegin(), linked_accounts_.cend());
    }
}