#include "Portfolio.h"

using namespace boost::gregorian;
using namespace std;

bool Portfolio::IsEmpty() const {
    return 0 == holdings_.size();
}
void Portfolio::Purchase(const string& symbol, unsigned int shareCount, const date& transactionDate)
{
    Transact(symbol, shareCount, transactionDate);
}
void Portfolio::Sell(const std::string& symbol, unsigned int shareCount, const date& transactionDate)
{
    if (shareCount > ShareCount(symbol)) throw InvalidSellException();
    Transact(symbol, -shareCount, transactionDate);
}

unsigned int Portfolio::ShareCount(const string& symbol) const
{
    auto it = holdings_.find(symbol);
    if (it == holdings_.end()) return 0;
    return it->second;
}

std::vector<PurchaseRecord> Portfolio::Purchases(const std::string &symbol) const {
    return purchaseRecords.find(symbol)->second;
}

void Portfolio::Transact(const std::string &symbol, int shareChange, const boost::gregorian::date &transactionDate)
{
    ThrowIfShareCountIsZero(shareChange);
    UpdateShareCount(symbol, shareChange);
    AddPurchaseRecord(symbol, shareChange, transactionDate);
}

void Portfolio::UpdateShareCount(const std::string &symbol, int shareChange)
{
    holdings_[symbol] = ShareCount(symbol) + shareChange;
}

void Portfolio::ThrowIfShareCountIsZero(int shareChange) const
{
    if (shareChange == 0) throw InvalidPurchaseException();
}

void Portfolio::AddPurchaseRecord(const std::string &symbol, int shareCount, const boost::gregorian::date &date)
{
    purchases.push_back(PurchaseRecord(shareCount, date));
    auto it = purchaseRecords.find(symbol);

    if (it == purchaseRecords.end())
        purchaseRecords[symbol] = vector<PurchaseRecord>();
    purchaseRecords[symbol].push_back(PurchaseRecord(shareCount, date));

}
